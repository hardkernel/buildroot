################################################################################
#
# libecore
#
################################################################################

LIBECORE_VERSION = 1.7.10
LIBECORE_SOURCE = ecore-$(LIBECORE_VERSION).tar.bz2
LIBECORE_SITE = http://download.enlightenment.org/releases
LIBECORE_LICENSE = BSD-2c
LIBECORE_LICENSE_FILES = COPYING

LIBECORE_INSTALL_STAGING = YES

LIBECORE_DEPENDENCIES = host-pkgconf libeina

HOST_LIBECORE_DEPENDENCIES = host-pkgconf host-libeina host-libevas
HOST_LIBECORE_CONF_OPTS += 		\
	--enable-ecore-evas 		\
	--disable-simple-x11 		\
	--disable-ecore-directfb 	\
	--disable-ecore-x 		\
	--disable-ecore-x-xcb 		\
	--disable-ecore-imf-xim

# default options
LIBECORE_CONF_OPTS = --disable-simple-x11

ifeq ($(BR2_PACKAGE_TSLIB),y)
LIBECORE_DEPENDENCIES += tslib
endif

ifeq ($(BR2_PACKAGE_LIBGLIB2),y)
LIBECORE_DEPENDENCIES += libglib2
endif

ifeq ($(BR2_PACKAGE_OPENSSL),y)
LIBECORE_DEPENDENCIES += openssl
LIBECORE_CONF_OPTS += --enable-openssl
else
LIBECORE_CONF_OPTS += --disable-openssl
endif

ifeq ($(BR2_PACKAGE_GNUTLS)$(BR2_PACKAGE_LIBGCRYPT),yy)
LIBECORE_DEPENDENCIES += gnutls libgcrypt
LIBECORE_CONF_OPTS += --enable-gnutls --with-libgcrypt-prefix=$(STAGING_DIR)/usr
else
LIBECORE_CONF_OPTS += --disable-gnutls
endif

ifeq ($(BR2_PACKAGE_LIBCURL),y)
LIBECORE_DEPENDENCIES += libcurl
endif

# libecore
ifeq ($(BR2_PACKAGE_LIBECORE_DIRECTFB),y)
LIBECORE_CONF_OPTS += --enable-ecore-directfb
LIBECORE_DEPENDENCIES += directfb
else
LIBECORE_CONF_OPTS += --disable-ecore-directfb
endif

ifeq ($(BR2_PACKAGE_LIBECORE_FB),y)
LIBECORE_CONF_OPTS += --enable-ecore-fb
else
LIBECORE_CONF_OPTS += --disable-ecore-fb
endif

ifeq ($(BR2_PACKAGE_LIBECORE_SDL),y)
LIBECORE_CONF_OPTS += --enable-ecore-sdl
LIBECORE_DEPENDENCIES += sdl
else
LIBECORE_CONF_OPTS += --disable-ecore-sdl
endif

ifeq ($(BR2_PACKAGE_LIBECORE_X),y)
LIBECORE_CONF_OPTS += --enable-ecore-x \
	--with-x=$(STAGING_DIR) \
	--x-includes=$(STAGING_DIR)/usr/include \
	--x-libraries=$(STAGING_DIR)/usr/lib
LIBECORE_DEPENDENCIES += xlib_libXext xlib_libX11
else
LIBECORE_CONF_OPTS += --disable-ecore-x --disable-ecore-imf-xim
endif

ifeq ($(BR2_PACKAGE_XLIB_LIBXCOMPOSITE),y)
LIBECORE_DEPENDENCIES += xlib_libXcomposite 
endif

ifeq ($(BR2_PACKAGE_XLIB_LIBXDAMAGE),y)
LIBECORE_DEPENDENCIES += xlib_libXdamage
endif

ifeq ($(BR2_PACKAGE_LIBECORE_X_XCB),y)
LIBECORE_CONF_OPTS += --enable-ecore-x-xcb
LIBECORE_DEPENDENCIES += libxcb xlib_libX11 xcb-util pixman

# src/util/makekeys is executed at build time to generate
# ecore_xcb_keysym_table.h, so it should get compiled for the host.
# The ecore makefile unfortunately doesn't know about cross
# compilation so this doesn't work.  Long term, we should probably
# teach it about CC_FOR_BUILD, but for now simply build makekeys by
# hand in advance
define LIBECORE_BUILD_MAKEKEYS_FOR_HOST
	$(HOST_CONFIGURE_OPTS) $(MAKE1) -C $(@D)/src/util makekeys.o makekeys
endef

LIBECORE_PRE_CONFIGURE_HOOKS += LIBECORE_BUILD_MAKEKEYS_FOR_HOST
else
LIBECORE_CONF_OPTS += --disable-ecore-x-xcb
endif

# libecore-evas
ifeq ($(BR2_PACKAGE_LIBECORE_EVAS),y)
LIBECORE_CONF_OPTS += --enable-ecore-evas
LIBECORE_DEPENDENCIES += libevas
else
LIBECORE_CONF_OPTS += --disable-ecore-evas
endif

$(eval $(autotools-package))
$(eval $(host-autotools-package))

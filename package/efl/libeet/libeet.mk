################################################################################
#
# libeet
#
################################################################################

LIBEET_VERSION = 1.7.10
LIBEET_SOURCE = eet-$(LIBEET_VERSION).tar.bz2
LIBEET_SITE = http://download.enlightenment.org/releases
LIBEET_LICENSE = BSD-2c
LIBEET_LICENSE_FILES = COPYING

LIBEET_INSTALL_STAGING = YES

LIBEET_DEPENDENCIES = host-pkgconf zlib jpeg libeina
HOST_LIBEET_DEPENDENCIES = host-pkgconf host-zlib host-libjpeg host-libeina

ifeq ($(BR2_PACKAGE_GNUTLS)$(BR2_PACKAGE_LIBGCRYPT),yy)
LIBEET_DEPENDENCIES += gnutls libgcrypt
LIBEET_CONF_ENV += LIBGCRYPT_CONFIG=$(STAGING_DIR)/usr/bin/libgcrypt-config
LIBEET_CONF_OPTS += --enable-gnutls
else
LIBEET_CONF_OPTS += --disable-gnutls
endif

$(eval $(autotools-package))
$(eval $(host-autotools-package))

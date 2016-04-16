################################################################################
#
# sqlite
#
################################################################################

SQLITE_VERSION = 3090200
SQLITE_SOURCE = sqlite-autoconf-$(SQLITE_VERSION).tar.gz
SQLITE_SITE = http://www.sqlite.org/2015
SQLITE_LICENSE = Public domain
SQLITE_LICENSE_FILES = tea/license.terms
SQLITE_INSTALL_STAGING = YES

# Patching Makefile.am:
SQLITE_AUTORECONF = YES

ifeq ($(BR2_PACKAGE_SQLITE_STAT3),y)
SQLITE_CFLAGS += -DSQLITE_ENABLE_STAT3
endif

ifeq ($(BR2_PACKAGE_SQLITE_ENABLE_FTS3),y)
SQLITE_CFLAGS += -DSQLITE_ENABLE_FTS3
endif

ifeq ($(BR2_PACKAGE_SQLITE_ENABLE_UNLOCK_NOTIFY),y)
SQLITE_CFLAGS += -DSQLITE_ENABLE_UNLOCK_NOTIFY
endif

ifeq ($(BR2_PACKAGE_SQLITE_SECURE_DELETE),y)
SQLITE_CFLAGS += -DSQLITE_SECURE_DELETE
endif

ifeq ($(BR2_PACKAGE_SQLITE_NO_SYNC),y)
SQLITE_CFLAGS += -DSQLITE_NO_SYNC
endif

SQLITE_CONF_ENV = CFLAGS="$(TARGET_CFLAGS) $(SQLITE_CFLAGS)"

ifeq ($(BR2_STATIC_LIBS),y)
SQLITE_CONF_OPTS += --enable-dynamic-extensions=no
endif

ifeq ($(BR2_TOOLCHAIN_HAS_THREADS),y)
SQLITE_CONF_OPTS += --enable-threadsafe
else
SQLITE_CONF_OPTS += --disable-threadsafe
endif

ifeq ($(BR2_PACKAGE_SQLITE_READLINE),y)
SQLITE_DEPENDENCIES += ncurses readline
SQLITE_CONF_OPTS += --with-readline-inc="-I$(STAGING_DIR)/usr/include"
else
SQLITE_CONF_OPTS += --disable-readline
endif

$(eval $(autotools-package))
$(eval $(host-autotools-package))

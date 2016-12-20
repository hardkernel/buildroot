#############################################################
#
# C2PLAY
#
#############################################################
C2PLAY_VERSION = $(call qstrip,$(BR2_PACKAGE_C2PLAY_VERSION))
C2PLAY_SOURCE = v$(C2PLAY_VERSION).zip
C2PLAY_SITE = https://github.com/OtherCrashOverride/c2play/archive
C2PLAY_DEPENDENCIES = alsa-lib aml_libs ffmpeg libass

define C2PLAY_EXTRACT_CMDS
	$(UNZIP) -d $(@D) $(DL_DIR)/$(C2PLAY_SOURCE)
	mv $(@D)/c2play-$(BR2_PACKAGE_C2PLAY_VERSION)/* $(@D)
	$(RM) -r $(@D)/c2play-$(BR2_PACKAGE_C2PLAY_VERSION)
endef

define C2PLAY_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) CC=$(TARGET_CXX) CXX=$(TARGET_CXX) -C $(@D) c2play
	$(TARGET_MAKE_ENV) cp $(@D)/c2play $(TARGET_DIR)/usr/bin/
endef

define C2PLAY_CLEAN_CMDS
	$(MAKE) -C $(@D) clean
endef

$(eval $(generic-package))

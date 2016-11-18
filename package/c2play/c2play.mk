#############################################################
#
# C2PLAY
#
#############################################################
C2PLAY_VERSION = 1.0
C2PLAY_SOURCE = master.zip
C2PLAY_SITE = https://github.com/OtherCrashOverride/c2play/archive
C2PLAY_DEPENDENCIES = alsa-lib aml_libs ffmpeg

define C2PLAY_EXTRACT_CMDS
	$(UNZIP) -d $(@D) $(DL_DIR)/$(C2PLAY_SOURCE)
	mv $(@D)/c2play-master/* $(@D)
	$(RM) -r $(@D)/c2play-master
endef

define C2PLAY_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) CC=$(TARGET_CXX) CFLAGS='$(TARGET_CFLAGS) -MMD -MF .$(@F).d -std=c++11' -C $(@D) all
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) install
endef

define C2PLAY_CLEAN_CMDS
	$(MAKE) -C $(@D) clean
endef

$(eval $(generic-package))

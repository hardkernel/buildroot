################################################################################
#
# amlogic 8812au driver
#
################################################################################

RTK8812AU_VERSION = $(call qstrip,$(BR2_PACKAGE_RTK8812AU_GIT_VERSION))
RTK8812AU_SITE = $(call qstrip,$(BR2_PACKAGE_RTK8812AU_GIT_REPO_URL))
define RTK8812AU_BUILD_CMDS
	mkdir -p $(LINUX_DIR)/../hardware/wifi/realtek/drivers;
	ln -sf $(RTK8812AU_DIR) $(LINUX_DIR)/../hardware/wifi/realtek/drivers/8812au
endef
$(eval $(generic-package))

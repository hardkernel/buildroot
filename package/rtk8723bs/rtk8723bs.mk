################################################################################
#
# amlogic 8723bs driver
#
################################################################################

RTK8723BS_VERSION = $(call qstrip,$(BR2_PACKAGE_RTK8723BS_GIT_VERSION))
RTK8723BS_SITE = $(call qstrip,$(BR2_PACKAGE_RTK8723BS_GIT_REPO_URL))
define RTK8723BS_BUILD_CMDS
	mkdir -p $(LINUX_DIR)/../hardware/wifi/realtek/drivers;
	ln -sf $(RTK8723BS_DIR) $(LINUX_DIR)/../hardware/wifi/realtek/drivers/8723bs
endef
$(eval $(generic-package))

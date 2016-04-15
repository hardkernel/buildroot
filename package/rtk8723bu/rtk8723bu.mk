################################################################################
#
# amlogic 8723bu driver
#
################################################################################

RTK8723BU_VERSION = $(call qstrip,$(BR2_PACKAGE_RTK8723BU_GIT_VERSION))
RTK8723BU_SITE = $(call qstrip,$(BR2_PACKAGE_RTK8723BU_GIT_REPO_URL))
$(eval $(generic-package))

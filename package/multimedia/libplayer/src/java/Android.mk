#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(call all-java-files-under, src)

LOCAL_SDK_VERSION := current

LOCAL_MODULE:= amlogic.libplayer
#LOCAL_JAVA_LIBRARIES := 

#LOCAL_PROGUARD_ENABLED := disabled
LOCAL_PROGUARD_FLAGS := -include $(LOCAL_PATH)/proguard.flags

# Generate a checksum that will be used in the app to determine whether the
# firmware in /system/etc/firmware needs to be updated.

#include $(BUILD_JAVA_LIBRARY)
include $(BUILD_STATIC_JAVA_LIBRARY)

#MAKE_XML
include $(CLEAR_VARS)
LOCAL_MODULE := amlogic.libplayer.xml
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(TARGET_OUT_ETC)/permissions
LOCAL_SRC_FILES := $(LOCAL_MODULE)
include $(BUILD_PREBUILT)



##################################################

include $(call all-makefiles-under,$(LOCAL_PATH))

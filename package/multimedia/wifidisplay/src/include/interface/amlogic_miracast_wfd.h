/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __AMLOGIC_MIRACAST_WFD_H__
#define __AMLOGIC_MIRACAST_WFD_H__

namespace android {
extern "C" {
extern int connect_to_wifi_source(const char *sourceHost, int32_t sourcePort);
extern void disconnectSink(void);
}
} // namespace android

#endif/*__AMLOGIC_MIRACAST_WFD_H__*/

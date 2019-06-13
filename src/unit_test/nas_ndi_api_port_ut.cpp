/*
 * Copyright (c) 2019 Dell Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * THIS CODE IS PROVIDED ON AN *AS IS* BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 * FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 * See the Apache Version 2.0 License for specific language governing
 * permissions and limitations under the License.
 */

/*
 * nas_ndi_api_port_ut.cpp
 *
 */

#include "nas_ndi_port.h"
#include "gtest/gtest.h"

t_std_error ndi_port_set_packet_drop(npu_id_t npu_id, npu_port_t port_id,
                                     ndi_port_drop_mode_t mode, bool enable)
{
    printf("Entering function %s\n", __FUNCTION__);
    return STD_ERR_OK;
}

TEST(nas_ndi_port, set_port_drop_mode)
{
    ASSERT_TRUE(ndi_port_set_packet_drop(0, 1, NDI_PORT_DROP_UNTAGGED, true) == STD_ERR_OK);
    ASSERT_TRUE(ndi_port_set_packet_drop(0, 1, NDI_PORT_DROP_TAGGED, false) == STD_ERR_OK);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

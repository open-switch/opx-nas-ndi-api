/*
 * Copyright (c) 2019 Dell Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 * FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 * See the Apache Version 2.0 License for specific language governing
 * permissions and limitations under the License.
 */

/*
 * filename: nas_ndi_fc.h
 */


#ifndef __NAS_NDI_FC_H
#define __NAS_NDI_FC_H

#include "std_error_codes.h"
#include "nas_ndi_common.h"
#include "ds_common_types.h"
#include "dell-base-if-fc.h"
#include "dell-base-interface-common.h"

#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

typedef std::vector <uint32_t> hwports_t;
typedef union {
    uint64_t u64;
    int32_t  s32;
    uint32_t u32;
    uint16_t u16;
    bool     ty_bool;
    struct {
        uint32_t *     vals;
        size_t         len;
    } list;
    hal_mac_addr_t mac;
} nas_fc_param_t ;

typedef struct {
    cps_api_attr_id_t attr_id;
    nas_fc_param_t value;
} nas_fc_id_value_t;


t_std_error ndi_delete_fc_port(npu_id_t npu_id, port_t port);

t_std_error ndi_create_fc_port(npu_id_t npu_id, port_t port, BASE_IF_SPEED_t speed, uint32_t *hw_port_list, size_t count );

t_std_error ndi_set_fc_attr(npu_id_t npu_id, port_t port, nas_fc_param_t *param, uint64_t attr);

t_std_error ndi_get_fc_attr(npu_id_t npu_id, port_t port, nas_fc_id_value_t *prt, int count);




#ifdef __cplusplus
}
#endif
#endif /* NAS_NDI_FC_H_ */

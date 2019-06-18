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
 * filename: nas_ndi_ipmc.h
 */

/**
 * \file nas_ndi_ipmc.h
 * \brief NDI interface APIs for IP multicast
 **/


#ifndef __NAS_NDI_IPMC_H
#define __NAS_NDI_IPMC_H

#include "std_error_codes.h"
#include "ds_common_types.h"
#include "nas_types.h"
#include "nas_ndi_common.h"
#include "nas_ndi_router_interface.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NDI_IPMC_NULL_OBJECT_ID 0LL

typedef enum {
    REPL_GROUP_OWNER_NONE,
    REPL_GROUP_OWNER_L2MC,
    REPL_GROUP_OWNER_IPMC,
    REPL_GROUP_OWNER_VXLAN
}ndi_repl_grp_owner_type_t;

typedef enum {
    NDI_SW_PORT_NPU_PORT,
    NDI_SW_PORT_LAG
} ndi_sw_port_type_t;

typedef struct _ndi_sw_port_s {
    ndi_sw_port_type_t port_type;
    union {
        ndi_port_t npu_port;
        ndi_obj_id_t lag;
    } u;
} ndi_sw_port_t;

typedef struct _ndi_sw_port_list_s {
    size_t port_count;
    ndi_sw_port_t *list;
} ndi_sw_port_list_t;

typedef struct _ndi_mc_grp_mbr_s {
    ndi_rif_id_t rif_id;
    ndi_sw_port_list_t port_list;
} ndi_mc_grp_mbr_t;

typedef enum {
    ADD_GRP_MBR,
    DEL_GRP_MBR,
    UPDATE_GRP_MBR
} ndi_mc_grp_op_t;

typedef enum {
    NDI_IPMC_GRP_MBR,
    NDI_RPF_GRP_MBR,
} ndi_mc_grp_mbr_type_t;

t_std_error ndi_create_repl_group(npu_id_t npu_id, ndi_repl_grp_owner_type_t owner,
                                  ndi_mc_grp_mbr_t *rpf_grp_mbr,
                                  size_t ipmc_grp_mbr_cnt, ndi_mc_grp_mbr_t *ipmc_grp_mbr,
                                  ndi_obj_id_t *repl_group_id_p);

t_std_error ndi_delete_repl_group(npu_id_t npu_id, ndi_obj_id_t repl_group_id);

t_std_error ndi_update_repl_group(npu_id_t npu_id, ndi_obj_id_t repl_group_id,
                                  ndi_mc_grp_op_t op, ndi_mc_grp_mbr_type_t mbr_type,
                                  ndi_mc_grp_mbr_t *grp_mbr);

#ifdef __cplusplus
}
#endif
#endif

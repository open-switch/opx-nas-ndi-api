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
 * filename: nas_ndi_mcast.h
 */

/**
 * \file nas_ndi_mcast.h
 * \brief NDI interface APIs for multicast
 **/


#ifndef __NAS_NDI_MCAST_H
#define __NAS_NDI_MCAST_H

#include "std_error_codes.h"
#include "ds_common_types.h"
#include "nas_types.h"
#include "nas_ndi_common.h"
#include "nas_ndi_router_interface.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NDI_MAX_MC_ENTRY_ATTR   2

typedef enum {
    NAS_NDI_MCAST_ENTRY_TYPE_XG,
    NAS_NDI_MCAST_ENTRY_TYPE_SG
} ndi_mcast_entry_type_t;

typedef struct _ndi_mcast_entry {
    hal_vlan_id_t vlan_id;
    ndi_mcast_entry_type_t type;
    hal_ip_addr_t dst_ip;
    hal_ip_addr_t src_ip;
    ndi_obj_id_t group_id;
    bool copy_to_cpu;
} ndi_mcast_entry_t;

typedef enum {
    NAS_NDI_MCAST_UPD_GRP,
    NAS_NDI_MCAST_UPD_COPY_TO_CPU
} ndi_mcast_update_type_t;

/**
 * @brief Create a new Multicast Entry in NPU
 *
 * @param npu_id - NPU ID in which to create
 * @param mc_entry_p - Attributes for the Multicast Entry being created
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_mcast_entry_create(npu_id_t npu_id, const ndi_mcast_entry_t *mc_entry_p);

/**
 * @brief Delete an existing Multicast Entry from NPU
 *
 * @param npu_id - NPU ID in which to delete
 * @param mc_entry_id - Attributes for the Multicast Entry to be deleted.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_mcast_entry_delete(npu_id_t npu_id, const ndi_mcast_entry_t *mc_entry_p);

t_std_error ndi_mcast_entry_update(npu_id_t npu_id, const ndi_mcast_entry_t *mc_entry_p,
                                   ndi_mcast_update_type_t upd_type);

typedef enum {
    NAS_NDI_IPMC_ENTRY_TYPE_XG,
    NAS_NDI_IPMC_ENTRY_TYPE_SG
} ndi_ipmc_entry_type_t;

typedef enum {
    NAS_NDI_IPMC_UPD_REPL_GRP,
    NAS_NDI_IPMC_UPD_COPY_TO_CPU
} ndi_ipmc_update_type_t;

typedef struct _ndi_ipmc_entry_s {
    ndi_vrf_id_t vrf_id;
    ndi_ipmc_entry_type_t type;
    hal_ip_addr_t dst_ip;
    hal_ip_addr_t src_ip;
    ndi_obj_id_t repl_group_id;
    bool copy_to_cpu;
    bool route_hit; //read-only
    ndi_rif_id_t iif_rif_id; //RIF ID of routes Incoming Interface
} ndi_ipmc_entry_t;

t_std_error ndi_ipmc_entry_create(npu_id_t npu_id, const ndi_ipmc_entry_t *ipmc_entry_p);

t_std_error ndi_ipmc_entry_delete(npu_id_t npu_id, const ndi_ipmc_entry_t *ipmc_entry_p);

t_std_error ndi_ipmc_entry_update(npu_id_t npu_id, const ndi_ipmc_entry_t *ipmc_entry_p,
                                  ndi_ipmc_update_type_t upd_type);

t_std_error ndi_ipmc_entry_get(npu_id_t npu_id, ndi_ipmc_entry_t *ipmc_entry_p);

#ifdef __cplusplus
}
#endif
#endif

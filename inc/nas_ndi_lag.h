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
 * filename: nas_ndi_lag.h
 */


#ifndef NAS_NDI_LAG_H_
#define NAS_NDI_LAG_H_

#include "std_error_codes.h"
#include "dell-base-interface-common.h"
#include "ds_common_types.h"
#include "nas_ndi_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup LAG NDIAPI
 *
 This file consists of the NDI API's to create,delete and manage ports to LAG Group.

 Important APIs are:
 @{
     ndi_create_lag
     ndi_delete_lag
     ndi_add_ports_to_lag
     ndi_del_ports_from_lag

 */

/**
 * Create a Lag Group
 *
 * @param npu_id - NPU that contains lag group
 *
 * @param ndi_lag_id - NDI lag group reference ID
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_create_lag(npu_id_t npu_id,ndi_obj_id_t *ndi_lag_id);

/**
 * Delete a Lag group
 *
 * @param npu_id - NPU that contains lag group
 *
 * @param ndi_lag_id - NDI lag group reference ID
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_delete_lag(npu_id_t npu_id, ndi_obj_id_t ndi_lag_id);

/**
 * Add ports to lag
 *
 * @param npu_id - NPU that contains lag group
 *
 * @param ndi_lag_id - NDI lag group reference ID
 *
 * @param lag_port_list - List of ports to be added to lag
 *
 * @param ndi_lag_member_id - NDI lag member reference ID
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */

t_std_error ndi_add_ports_to_lag(npu_id_t npu_id, ndi_obj_id_t ndi_lag_id,ndi_port_list_t *lag_port_list,
                   ndi_obj_id_t *ndi_lag_member_id);

/**
 * Delete ports from lag
 *
 * @param npu_id - NPU that contains lag group
 *
 * @param ndi_lag_member_id- NDI lag member reference ID
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */

t_std_error ndi_del_ports_from_lag(npu_id_t npu_id,ndi_obj_id_t ndi_lag_member_id);

/**
 * Enable/Disable traffic on Lag member port
 *
 * @param npu_id - NPU that contains lag group
 *
 * @param ndi_lag_member_id - NDI lag member reference ID
 *
 * @param egress_disable - enable or disable Traffic on the port
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_set_lag_member_attr(npu_id_t npu_id, ndi_obj_id_t ndi_lag_member_id,
                bool egress_disable);

/**
 * get traffic enable/disable mode of lag member port
 *
 * @param npu_id - npu that contains lag group
 *
 * @param ndi_lag_member_id - ndi lag member reference id
 *
 * @param egress_disable - pointer to store traffic enable/disable mode of the port
 *
 * @return std_err_ok if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_get_lag_member_attr(npu_id_t npu_id, ndi_obj_id_t ndi_lag_member_id,
                bool *egress_disable);

/** This function sets the default pvid for lag
 *  Set it when the port is untagged .
 * @param npu_id npu id
 * @param lag_id Lag ID
 * @vlan_id Vlan ID
 * @return standard error
 */

t_std_error ndi_set_lag_pvid(npu_id_t npu_id, ndi_obj_id_t lag_id,
                             hal_vlan_id_t vlan_id);

/** This function sets the mac learn mode for lag
 * @param npu_id npu id
 * @param mode MAC Learn Mode
 * @return standard error
 */
t_std_error ndi_set_lag_learn_mode(npu_id_t npu_id, ndi_obj_id_t ndi_lag_id,
        BASE_IF_MAC_LEARN_MODE_t mode);

/**
 * This function is used to enable/disable tagged or untagged packet drop mode
 * for specific Lag
 * @param npu_id NPU ID
 * @param lag_id Lag ID
 * @param mode packet drop mode
 * @enable enable or disable packet drop mode
 * @return standard error
 */

t_std_error ndi_lag_set_packet_drop(npu_id_t npu_id, ndi_obj_id_t ndi_lag_id,
                                     ndi_port_drop_mode_t mode, bool enable);

/**
@}
*/

/** This function is used to set the resilient attributes hash configuration 
 * for LAG.
 * @param npu_id npu id
 * @param ndi_lag_id LAG id 
 * @param boolean, if resilient hash is enabled or disabled
 * @return standard error
 */
t_std_error ndi_set_lag_resilient_hash(npu_id_t npu_id, 
                                        ndi_obj_id_t ndi_lag_id, bool enabled);

#ifdef __cplusplus
}
#endif
#endif /* NAS_NDI_LAG_H_ */

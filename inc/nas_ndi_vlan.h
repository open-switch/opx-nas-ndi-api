/*
 * Copyright (c) 2016 Dell Inc.
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
 * filename: nas_ndi_vlan.h
 */


#ifndef NAS_NDI_VLAN_H_
#define NAS_NDI_VLAN_H_

#include "std_error_codes.h"
#include "ds_common_types.h"
#include "nas_ndi_common.h"

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Add a Vlan entry in the vlanTable
 *
 * @param vlan_id - Vlan to be configured
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_create_vlan(npu_id_t npu_id, hal_vlan_id_t vlan_id);

/**
 * @brief Delete a Vlan entry from the vlanTable
 *
 * @param vlan_id - Vlan to be deleted
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_delete_vlan(npu_id_t npu_id, hal_vlan_id_t vlan_id);

/**
 * @brief Add ports to Vlan
 *
 * @param vlan_id - Vlan ID where ports are to be added.
 *
 * @param p_t_nas_port - List of tagged ports
 *
 * @param p_ut_nas_port- List of untagged ports
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */

t_std_error ndi_add_ports_to_vlan(npu_id_t npu_id, hal_vlan_id_t vlan_id, \
                                  ndi_port_list_t *p_t_port_list, ndi_port_list_t *p_ut_port_list);


/**
 * @brief Delete ports from Vlan
 *
 * @param vlan_id - Vlan ID from where ports are to be deleted.
 *
 * @param p_t_nas_port - List of tagged ports
 *
 * @param p_ut_nas_port- List of untagged ports
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */

t_std_error ndi_del_ports_from_vlan(npu_id_t npu_id, hal_vlan_id_t vlan_id, \
                                    ndi_port_list_t *p_t_port_list, ndi_port_list_t *p_ut_port_list);

/**
 * @brief Gets Vlan Statistics
 *
 * @param[in] npu_id - NPU ID
 *
 * @param[in] vlan_id - Vlan ID
 *
 * @param[in] stats - array of vlan counter ids
 *
 * @param[out] stats_val - statistics counter values
 *
 * @param[in] len - number of statistics to be queried
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */

t_std_error ndi_vlan_stats_get(npu_id_t npu_id, hal_vlan_id_t vlan_id, \
                               ndi_stat_id_t *stats,
                               uint64_t* stats_val, size_t len);

/**
 * @brief Add or Delete ports from Vlan
 *
 * @param vlan_id - Vlan ID from where ports are to be deleted.
 *
 * @param p_tagged_list - List of tagged ports
 *
 * @param p_untagged_list- List of untagged ports
 *
 * @param ad_vlan : Boolean variable that specifies whether to add or delete
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */

t_std_error ndi_add_or_del_ports_to_vlan(npu_id_t npu_id, hal_vlan_id_t vlan_id,
                                         ndi_port_list_t *p_tagged_list,
                                         ndi_port_list_t *p_untagged_list,
                                         bool add_vlan);

/**
 * @brief Add lag to vlan
 *
 * @param vlan_id - Vlan ID where lags are to be added.
 *
 * @param tagged_lag_list - List of tagged lags.
 *
 * @param tagged_lag_cnt- size of tagged_lag_list.
 *
 * @param untagged_lag_list- List of untagged lags.
 *
 * @untag_lag_cnt- size of untagged_lag_list.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */



t_std_error ndi_add_lag_to_vlan(npu_id_t npu_id, hal_vlan_id_t vlan_id,
                                           ndi_obj_id_t *tagged_lag_list, size_t  tagged_lag_cnt,
                                           ndi_obj_id_t *untagged_lag_list ,size_t untag_lag_cnt);

/**
 * @brief Delete lag from vlan
 *
 * @param vlan_id - Vlan ID where lags are to be deleted.
 *
 * @param tagged_lag_list - List of tagged lags.
 *
 * @param tagged_lag_cnt- size of tagged_lag_list.
 *
 * @param untagged_lag_list- List of untagged lags.
 *
 * @untag_lag_cnt- size of untagged_lag_list.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */

t_std_error ndi_del_lag_from_vlan(npu_id_t npu_id, hal_vlan_id_t vlan_id,
                                           ndi_obj_id_t *tagged_lag_list, size_t  tagged_lag_cnt,
                                           ndi_obj_id_t *untagged_lag_list ,size_t untag_lag_cnt);


/**
 * @brief Enable/Disable learning on a Vlan
 *
 * @param npu_id - NPU ID
 *
 * @param vlan_id - Vlan ID from where ports are to be deleted.
 *
 * @param learning_mode : Enable/Disable learning
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */

t_std_error ndi_set_vlan_learning(npu_id_t npu_id, hal_vlan_id_t vlan_id,
                                  bool learning_mode);


/**
 * @brief Delete the VLAN members created by SAI in default VLAN
 *
 * @param npu_id - NPU ID
 *
 * @param npu_port - NPU Port (valid only in del_all is false)
 *
 * @param del_all - True if all members need to removed. False otherwise.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_del_new_member_from_default_vlan(npu_id_t npu_id,
        npu_port_t npu_port, bool del_all);

/**
 * @brief Set multicast lookup key for VLAN.
 *
 * @param npu_id - NPU ID on which look up key is set.
 * @param vlan_id - VLAN for which look up key is set.
 * @param af - IPv4 or IPV6 address family.
 * @param key - look up key value.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_vlan_set_mcast_lookup_key(npu_id_t npu_id, hal_vlan_id_t vlan_id,
                                          uint32_t af, ndi_vlan_mcast_lookup_key_type_t key);

#ifdef __cplusplus
}
#endif
#endif /* NAS_NDI_VLAN_H_ */

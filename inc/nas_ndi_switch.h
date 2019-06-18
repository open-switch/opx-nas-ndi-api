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
 * nas_ndi_switch.h
 *
 */


#ifndef NAS_NDI_SWITCH_H_
#define NAS_NDI_SWITCH_H_

#include "std_error_codes.h"
#include "ds_common_types.h"
#include "nas_types.h"

#include "dell-base-switch-element.h"
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////
//Utilities to convert IDs from NDI to SAI and vice-versa
/////////////////////////////////////////////////////////
#define ndi_acl_ndi2sai_slice_id(x)         (sai_object_id_t) (x)
#define ndi_acl_sai2ndi_slice_id(x)         (ndi_obj_id_t) (x)

/**
 * This union holds all of the possible types used to communicate with the switch
 * There are two general functions that applications can perform.  Get attribute and set attribute.
 *
 * Currently only one attribute can be set at a time.
 */
typedef union {
    int32_t  s32;
    uint32_t u32;
    uint16_t u16;
    struct {
        uint32_t *     vals;
        size_t         len;
    } list;
    struct {
        size_t         len;
        ndi_obj_id_t *  vals;
    } obj_list;
    hal_mac_addr_t mac;
} nas_ndi_switch_param_t ;

/**
 * Set an attribute into the NPU based on the yang switch model and the yang switch types.
 * @param npu the npu to update
 * @param attr the attribute switch parameter
 * @param param the actual data passed to the NDI layer to set into the switch
 * @return STD_ERR_OK on success
 */
t_std_error ndi_switch_set_attribute(npu_id_t npu, BASE_SWITCH_SWITCHING_ENTITIES_SWITCHING_ENTITY_t attr,
        const nas_ndi_switch_param_t *param);

/**
 * Get list of attributes for switch entity object.
 * @param attrlist is a output param and it will be populated with switch entity
 * attributes.
 * @return void.
 */

void ndi_switch_attr_list_get (std::vector<uint32_t> &attrlist);


/**
 * Get an attribute from the NPU based on the yang switch model and the yang switch types.
 * @param npu the npu to update
 * @param attr the attribute switch parameter
 * @param param the actual data read from the NDI layer
 * @return STD_ERR_OK on success
 */
t_std_error ndi_switch_get_attribute(npu_id_t npu, BASE_SWITCH_SWITCHING_ENTITIES_SWITCHING_ENTITY_t attr,
        nas_ndi_switch_param_t *param);

/**
 * @brief Configure MAC aging time
 *
 * @param npu_id - NPU id where the mac age time is applied on
 *
 * @param timeout_value - MAC age timeout value to be configured
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_switch_mac_age_time_set(npu_id_t npu_id, uint32_t timeout_value);

/**
 * @brief Retrieve MAC aging time
 *
 * @param npu_id - NPU id where the mac age time is queried on
 *
 * @param timeout_value - MAC age timeout as return value
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_switch_mac_age_time_get(npu_id_t npu_id, uint32_t *timeout_value);


/**
 * @brief Set the switch log level for given switch subsystem id
 *
 * @param subsystem_id - switch subsystem id
 * @param level - log level to be set
 *
 * @return - STD_ERR_OK if operation is successful otherwise a different
 *           error code is returned.
 */
t_std_error ndi_switch_set_sai_log_level(BASE_SWITCH_SUBSYSTEM_t subsystem_id,
                                         BASE_SWITCH_LOG_LEVEL_t level);

/**
 * @brief Retrieve per port queue info and cpu port queue info
 * @param npu_id - NPU id
 * @param [out] ucast_queues - number of unicast queues per port
 * @param [out] mcast_queues - number of multicast queues per port
 * @param [out] total_queues - total queues per port
 * @param [out] cpu_queues - number of queues on cpu port
 */
t_std_error ndi_switch_get_queue_numbers(npu_id_t npu_id,
                        uint32_t *ucast_queues, uint32_t *mcast_queues,
                        uint32_t *total_queues, uint32_t *cpu_queues);

/**
 * @brief Retrieve HQoS tree levels
 * @param npu_id - NPU id
 * @param [out] max_level - max number of levels in HQoS hierarchy
 */
t_std_error ndi_switch_get_max_number_of_scheduler_group_level(npu_id_t npu_id,
                        uint32_t *max_level);

/**
 * @brief Retrieve switch ACL slice list
 * @param npu_id - NPU id
 * @param [out] max_level - max number of levels in HQoS hierarchy
 * @return STD_ERR_OK on success
 */
t_std_error ndi_switch_get_slice_list(npu_id_t npu_id, nas_ndi_switch_param_t *param);

/**
 * This function gets switch statistics
 * @param ndi_id
 * @param list of switch stats types to query
 * @param number of switch stats types specified
 * @param[out] counters: stats will be stored in the same order of the counter_ids
 * return standard error
 */
 t_std_error ndi_switch_get_statistics(npu_id_t npu_id,
                                BASE_SWITCH_SWITCHING_ENTITIES_SWITCH_STATS_t *counter_ids,
                                uint_t number_of_counters,
                                uint64_t *counters);
#ifdef __cplusplus
}
#endif

#endif /* NAS_NDI_SWITCH_H_ */

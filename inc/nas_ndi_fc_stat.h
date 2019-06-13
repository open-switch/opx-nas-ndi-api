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
 * filename: nas_ndi_fc_stat.h
 */


#ifndef __NAS_NDI_FC_STAT_H
#define __NAS_NDI_FC_STAT_H

#include "std_error_codes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This function retrieves FC statistics for a given port.
 * @param npu_id npu id
 * @param port_id port id
 * @param ndi_stats_counter_ids Pointer to nas_stat_id_t array
 * @param stats_val Pointer to array which holds values of counters
 * @param len number of counters
 * @return STD_ERR_OK if successful otherwise an error code indicating the failure
 */
t_std_error ndi_port_fc_stats_get(npu_id_t npu_id, npu_port_t port_id,
                               ndi_stat_id_t *ndi_stats_counter_ids,
                               uint64_t* stats_val, size_t len);


/**
 * This function clears all FC statistics for a given port, no support to delete
 * specific counter/s for now.
 * @param npu_id npu id
 * @param port_id port id
 * @param ndi_stats_counter_ids Pointer to stats array
 * @param len number of counters
 * @return STD_ERR_OK if successful otherwise an error code indicating the failure
 */
t_std_error ndi_port_fc_stats_clear(npu_id_t npu_id, npu_port_t port_id,
                               ndi_stat_id_t *ndi_stats_counter_ids,
                               size_t len);
/**
 *  \}
 */

#ifdef __cplusplus
}
#endif
#endif

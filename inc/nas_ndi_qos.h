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
 * filename: nas_ndi_qos.h
 */


#ifndef __NAS_NDI_QOS_H
#define __NAS_NDI_QOS_H

#include "std_error_codes.h"
#include "dell-base-qos.h"
#include "nas_ndi_common.h"

#ifdef __cplusplus
extern "C" {
#endif


#define NDI_QOS_NULL_OBJECT_ID 0LL

/** \defgroup NDIAPIQoS NDI API - QoS Functionality
 *
 *  \{
 */
#define BASE_QOS_POLICER_STAT_TYPE_MAX (BASE_QOS_POLICER_STAT_TYPE_RED_BYTES + 1)

typedef struct qos_policer_struct{
    BASE_QOS_METER_TYPE_t            meter_type;
    BASE_QOS_METER_MODE_t            meter_mode;
    BASE_QOS_METER_COLOR_SOURCE_t    color_source;
    BASE_QOS_POLICER_ACTION_t        green_packet_action;
    BASE_QOS_POLICER_ACTION_t        yellow_packet_action;
    BASE_QOS_POLICER_ACTION_t        red_packet_action;
    uint64_t         committed_burst;
    uint64_t         committed_rate;
    uint64_t         peak_burst;
    uint64_t         peak_rate;
    uint_t                           stat_list_count; // number of elements
    BASE_QOS_POLICER_STAT_TYPE_t     stat_list[BASE_QOS_POLICER_STAT_TYPE_MAX];
} qos_policer_struct_t;

typedef struct policer_stats_struct_t {
    uint64_t packets;
    uint64_t bytes;
    uint64_t green_packets;
    uint64_t green_bytes;
    uint64_t yellow_packets;
    uint64_t yellow_bytes;
    uint64_t red_packets;
    uint64_t red_bytes;
} policer_stats_struct_t;

/**
 * This function creates a policer in the NPU.
 * @param npu_id npu id
 * @param nas_attr_list based on the CPS API attribute enumeration values
 * @param num_attr number of attributes in attr_list array
 * @param p policer structure to be modified
 * @param[out] ndi_policer_id
 * @return standard error
 */
t_std_error ndi_qos_create_policer(npu_id_t npu_id,
                                   const nas_attr_id_t *nas_attr_list,
                                   uint_t num_attr,
                                   const qos_policer_struct_t *p,
                                   ndi_obj_id_t *ndi_policer_id);

 /**
  * This function sets the policer attributes in the NPU.
  * @param  npu id
  * @param  ndi_policer_id
  * @param attr_id based on the CPS API attribute enumeration values
  * @param p policer structure to be modified
  * @return standard error
  */
t_std_error ndi_qos_set_policer_attr(npu_id_t npu_id, ndi_obj_id_t ndi_policer_id,
                                     BASE_QOS_METER_t attr_id, const qos_policer_struct_t *p);

/**
 * This function deletes a policer in the NPU.
 * @param npu_id npu id
 * @param ndi_policer_id
 * @return standard error
 */
t_std_error ndi_qos_delete_policer(npu_id_t npu_id, ndi_obj_id_t ndi_policer_id);

/**
 * This function get a policer from the NPU.
 * @param npu_id npu id
 * @param ndi_policer_id
 * @param nas_attr_list based on the CPS API attribute enumeration values
 * @param num_attr number of attributes in attr_list array
 * @param[out] qos_policer_struct_t filled if success
 * @return standard error
 */
t_std_error ndi_qos_get_policer(npu_id_t npu_id,
                                ndi_obj_id_t ndi_policer_id,
                                const nas_attr_id_t *nas_attr_list,
                                uint_t num_attr,
                                qos_policer_struct_t *p);

/**
 * This function get a policer from the NPU.
 * @param npu_id npu id
 * @param ndi_policer_id
 * @param stat_list_count number of statistics types to retrieve
 * @param *stat_list list of statistics types to retrieve
 * @param[out] *counters statistics
 * @return standard error
 */
t_std_error ndi_qos_get_policer_stat(npu_id_t npu_id,
                                ndi_obj_id_t ndi_policer_id,
                                uint_t     stat_list_count,
                                const BASE_QOS_POLICER_STAT_TYPE_t * stat_list,
                                policer_stats_struct_t * counters);



// TO BE DEPRECATED
typedef struct qos_wred_struct{
    bool    g_enable;        // WRED enabled/disabled on green traffic
    uint_t  g_min;            // WRED min threshold for green traffic
    uint_t  g_max;            // WRED max threshold for green traffic
    uint_t  g_drop_prob;    // Green traffic drop probability when min-threshold is crossed

    bool    y_enable;        // WRED enabled/disabled on yellow traffic
    uint_t  y_min;            // WRED min threshold for yellow traffic
    uint_t  y_max;            // WRED max threshold for yellow traffic
    uint_t  y_drop_prob;    // Yellow traffic drop probability when min-threshold is crossed

    bool    r_enable;        // WRED enabled/disabled on red traffic
    uint_t  r_min;            // WRED min threshold for red traffic
    uint_t  r_max;            // WRED max threshold for red traffic
    uint_t  r_drop_prob;    // Red traffic drop probability when min-threshold is crossed

    uint_t  weight;            // Weight factor to calculate the average queue size based on historic average
    BASE_QOS_ECN_MARK_MODE_t ecn_mark;          // ECN marking mode
}qos_wred_struct_t;


// TO BE DEPRECATED
/**
 * This function creates a WRED profile in the NPU.
 * @param npu id
 * @param nas_attr_list based on the CPS API attribute enumeration values
 * @param num_attr number of attributes in attr_list array
 * @param p WRED structure to be modified
 * @param[out] ndi_wred_id
 * @return standard error
 */
t_std_error ndi_qos_create_wred_profile(npu_id_t npu_id,
                                const nas_attr_id_t *nas_attr_list,
                                uint_t num_attr,
                                const qos_wred_struct_t *p,
                                ndi_obj_id_t *ndi_wred_id);

// TO BE DEPRECATED
 /**
  * This function sets the wred profile attributes in the NPU.
  * @param npu id
  * @param ndi_wred_id
  * @param attr_id based on the CPS API attribute enumeration values
  * @param p wred structure to be modified
  * @return standard error
  */
t_std_error ndi_qos_set_wred_profile_attr(npu_id_t npu_id, ndi_obj_id_t ndi_wred_id,
                                  BASE_QOS_WRED_PROFILE_t attr_id, const qos_wred_struct_t *p);

// TO BE DEPRECATED
/**
 * This function deletes a wred profile in the NPU.
 * @param npu id
 * @param ndi_wred_id
 * @return standard error
 */
t_std_error ndi_qos_delete_wred_profile(npu_id_t npu_id, ndi_obj_id_t ndi_wred_id);

// TO BE DEPRECATED
/**
 * This function get a wred profile from the NPU.
 * @param npu id
 * @param ndi_wred_id
 * @param nas_attr_list based on the CPS API attribute enumeration values
 * @param num_attr number of attributes in attr_list array
 * @param[out] qos_wred_struct_t filled if success
 * @return standard error
 */
t_std_error ndi_qos_get_wred_profile(npu_id_t npu_id,
                            ndi_obj_id_t ndi_wred_id,
                            const nas_attr_id_t *nas_attr_list,
                            uint_t num_attr,
                            qos_wred_struct_t *p);

/**
 * This function creates a WRED profile in the NPU.
 * @param npu id
 * @param num_attr number of attributes in attr_list array
 * @param nas_attr_list list of CPS API attribute IDs and values
 * @param[out] ndi_wred_id
 * @return standard error
 */
t_std_error ndi_qos_create_wred_ecn_profile(npu_id_t npu_id,
                                uint_t num_attr,
                                const nas_attribute_t * nas_attr_list,
                                ndi_obj_id_t *ndi_wred_id);

 /**
  * This function sets the wred profile attributes in the NPU.
  * @param npu id
  * @param ndi_wred_id
  * @param nas_attr attribute id and value
  * @return standard error
  */
t_std_error ndi_qos_set_wred_ecn_profile_attr(npu_id_t npu_id,
                                  ndi_obj_id_t ndi_wred_id,
                                  nas_attribute_t nas_attr);

/**
 * This function deletes a wred profile in the NPU.
 * @param npu id
 * @param ndi_wred_id
 * @return standard error
 */
t_std_error ndi_qos_delete_wred_ecn_profile(npu_id_t npu_id, ndi_obj_id_t ndi_wred_id);

/**
 * This function get a wred profile from the NPU.
 * @param npu id
 * @param ndi_wred_id
 * @param num_attr number of attributes in attr_list array
 * @param[in/out] nas_attr_list list of CPS API attribute IDs and values
 * @return standard error. When successful, nas_attr_list is filled with values
 */
t_std_error ndi_qos_get_wred_ecn_profile(npu_id_t npu_id,
                            ndi_obj_id_t ndi_wred_id,
                            uint_t num_attr,
                            nas_attribute_t * nas_attr_list);




typedef struct ndi_qos_queue_struct_t {
    ndi_port_t        ndi_port;
    BASE_QOS_QUEUE_TYPE_t     type;
    uint8_t          queue_index;
    ndi_obj_id_t     parent;
    ndi_obj_id_t    wred_id;
    ndi_obj_id_t    buffer_profile;
    ndi_obj_id_t    scheduler_profile;
} ndi_qos_queue_struct_t;


/**
 * This function creates a Scheduler group ID in the NPU.
 * @param npu id
 * @param nas_attr_list based on the CPS API attribute enumeration values
 * @param num_attr number of attributes in attr_list array
 * @param p scheduler group structure to be modified
 * @param[out] ndi_queue_id
 * @return standard error
 */
t_std_error ndi_qos_create_queue(npu_id_t npu_id,
                                const nas_attr_id_t *nas_attr_list,
                                uint_t num_attr,
                                const ndi_qos_queue_struct_t *p,
                                ndi_obj_id_t *ndi_queue_id);

 /**
  * This function sets the queue attributes in the NPU.
  * @param npu id
  * @param ndi_queue_id
  * @param attr_id based on the CPS API attribute enumeration values
  * @param p queue structure to be modified
  * @return standard error
  */
t_std_error ndi_qos_set_queue_attr(npu_id_t npu_id,
                                    ndi_obj_id_t ndi_queue_id,
                                    BASE_QOS_QUEUE_t attr_id,
                                    const ndi_qos_queue_struct_t *p);

/**
 * This function deletes a queue in the NPU.
 * @param npu_id npu id
 * @param ndi_queue_id
 * @return standard error
 */
t_std_error ndi_qos_delete_queue(npu_id_t npu_id,
                                    ndi_obj_id_t ndi_queue_id);

/**
 * This function get a queue from the NPU.
 * @param npu id
 * @param ndi_queue_id
 * @param nas_attr_list based on the CPS API attribute enumeration values
 * @param num_attr number of attributes in attr_list array
 * @param[out] ndi_qos_queue_struct_t filled if success
 * @return standard error
 */
t_std_error ndi_qos_get_queue(npu_id_t npu_id,
                            ndi_obj_id_t ndi_queue_id,
                            const nas_attr_id_t *nas_attr_list,
                            uint_t num_attr,
                            ndi_qos_queue_struct_t *p);


/**
 * This function gets the total number of queues on a port
 * @param ndi_port_id
 * @Return standard error code
 */
uint_t ndi_qos_get_number_of_queues(ndi_port_t ndi_port_id);


/**
 * This function gets the list of queues of a port
 * @param ndi_port_id
 * @param count size of the queue_list
 * @param[out] ndi_queue_id_list[] to be filled with either the number of queues
 *            that the port owns or the size of array itself, whichever is less.
 * @Return Number of queues retrieved.
 */
uint_t ndi_qos_get_queue_id_list(ndi_port_t ndi_port_id,
                                uint_t count,
                                ndi_obj_id_t *ndi_queue_id_list);

/**
 * This function gets the list of shadow queue object on different MMUs
 * @param npu_id
 * @param ndi_queue_id
 * @param count, size of the ndi_shadow_q_list[]
 * @param[out] ndi_shadow_q_list[] will be filled
 * @Return The total number of shadow queue objects on different MMUs.
 *         If the count is smaller than the actual number of shadow queue
 *         objects, ndi_shadow_q_list[] will not be filled.
 */
uint_t ndi_qos_get_shadow_queue_list(npu_id_t npu_id,
                            ndi_obj_id_t ndi_queue_id,
                            uint_t count,
                            ndi_obj_id_t * ndi_shadow_q_list);

typedef struct nas_qos_queue_stat_counter_t {
    uint64_t packets;
    uint64_t bytes;
    uint64_t dropped_packets;
    uint64_t dropped_bytes;
    uint64_t green_packets;
    uint64_t green_bytes;
    uint64_t green_dropped_packets;
    uint64_t green_dropped_bytes;
    uint64_t yellow_packets;
    uint64_t yellow_bytes;
    uint64_t yellow_dropped_packets;
    uint64_t yellow_dropped_bytes;
    uint64_t red_packets;
    uint64_t red_bytes;
    uint64_t red_dropped_packets;
    uint64_t red_dropped_bytes;
    uint64_t green_discard_dropped_packets;
    uint64_t green_discard_dropped_bytes;
    uint64_t yellow_discard_dropped_packets;
    uint64_t yellow_discard_dropped_bytes;
    uint64_t red_discard_dropped_packets;
    uint64_t red_discard_dropped_bytes;
    uint64_t discard_dropped_packets;
    uint64_t discard_dropped_bytes;
    uint64_t current_occupancy_bytes;
    uint64_t watermark_bytes;
    uint64_t shared_current_occupancy_bytes;
    uint64_t shared_watermark_bytes;
} nas_qos_queue_stat_counter_t;

/**
 * This function gets the queue statistics
 * @param ndi_port_id
 * @param ndi_queue_id
 * @param list of queue counter types to query
 * @param number of queue counter types specified
 * @param[out] counter stats
 * return standard error
 * @deprecated since 7.7.0+opx1
 * @see ndi_qos_get_extended_queue_statistics()
 */
t_std_error ndi_qos_get_queue_stats(ndi_port_t ndi_port_id,
                                ndi_obj_id_t ndi_queue_id,
                                BASE_QOS_QUEUE_STAT_t *counter_ids,
                                uint_t number_of_counters,
                                nas_qos_queue_stat_counter_t *stats);
/**
 * This function gets the queue statistics
 * @param ndi_port_id
 * @param ndi_queue_id
 * @param list of queue counter types to query
 * @param number of queue counter types specified
 * @param[out] counters: stats will be stored in the same order of the counter_ids
 * return standard error
 * @deprecated since 7.7.0+opx1
 * @see ndi_qos_get_extended_queue_statistics()
 *
  * return standard error
 */
t_std_error ndi_qos_get_queue_statistics(ndi_port_t ndi_port_id,
                                ndi_obj_id_t ndi_queue_id,
                                BASE_QOS_QUEUE_STAT_t *counter_ids,
                                uint_t number_of_counters,
                                uint64_t *counters);

/**
 * This function gets the queue statistics
 * @param ndi_port_id
 * @param ndi_queue_id
 * @param list of queue counter types to query
 * @param number of queue counter types specified
 * @param[out] counters: stats will be stored in the same order of the counter_ids
 * @param counters to clear on read
 * @param snapshot counters to read
  * return standard error
 */
t_std_error ndi_qos_get_extended_queue_statistics(ndi_port_t ndi_port_id,
                                ndi_obj_id_t ndi_queue_id,
                                BASE_QOS_QUEUE_STAT_t *counter_ids,
                                uint_t number_of_counters,
                                uint64_t *counters,
                                ndi_stats_mode_t ndi_stats_mode,
                                bool is_snapshot_counters);

/**
 * This function clears the queue statistics
 * @param ndi_port_id
 * @param ndi_queue_id
 * @param list of queue counter types to clear
 * @param number of queue counter types specified
 * return standard error
 */
t_std_error ndi_qos_clear_queue_stats(ndi_port_t ndi_port_id,
                                ndi_obj_id_t ndi_queue_id,
                                BASE_QOS_QUEUE_STAT_t *counter_ids,
                                uint_t number_of_counters);

/**
 * This function clears the queue statistics
 * @param ndi_port_id
 * @param ndi_queue_id
 * @param list of queue counter types to clear
 * @param number of queue counter types specified
 * @param snapshot counters to clear
 * return standard error
 */
t_std_error ndi_qos_clear_extended_queue_statistics(ndi_port_t ndi_port_id,
                                ndi_obj_id_t ndi_queue_id,
                                BASE_QOS_QUEUE_STAT_t *counter_ids,
                                uint_t number_of_counters,
                                bool is_snapshot_counters);

typedef struct qos_scheduler_struct{
    BASE_QOS_SCHEDULING_TYPE_t     algorithm;
    BASE_QOS_METER_TYPE_t         meter_type;
    uint32_t    weight;
    uint64_t    min_rate;
    uint64_t    min_burst;
    uint64_t    max_rate;
    uint64_t    max_burst;

} qos_scheduler_struct_t;


/**
 * This function creates a Scheduler profile ID in the NPU.
 * @param npu id
 * @param nas_attr_list based on the CPS API attribute enumeration values
 * @param num_attr number of attributes in attr_list array
 * @param p Scheduler structure to be modified
 * @param[out] ndi_scheduler_id
 * @return standard error
 */
t_std_error ndi_qos_create_scheduler_profile(npu_id_t npu_id,
                                const nas_attr_id_t *nas_attr_list,
                                uint_t num_attr,
                                const qos_scheduler_struct_t *p,
                                ndi_obj_id_t *ndi_scheduler_id);

 /**
  * This function sets the scheduler profile attributes in the NPU.
  * @param npu id
  * @param ndi_scheduler_id
  * @param attr_id based on the CPS API attribute enumeration values
  * @param p scheduler structure to be modified
  * @return standard error
  */
t_std_error ndi_qos_set_scheduler_profile_attr(npu_id_t npu_id,
                                    ndi_obj_id_t ndi_scheduler_id,
                                    BASE_QOS_SCHEDULER_PROFILE_t attr_id,
                                    const qos_scheduler_struct_t *p);

/**
 * This function deletes a scheduler profile in the NPU.
 * @param npu_id npu id
 * @param ndi_scheduler_id
 * @return standard error
 */
t_std_error ndi_qos_delete_scheduler_profile(npu_id_t npu_id,
                                    ndi_obj_id_t ndi_scheduler_id);

/**
 * This function get a scheduler profile from the NPU.
 * @param npu id
 * @param ndi_scheduler_id
 * @param nas_attr_list based on the CPS API attribute enumeration values
 * @param num_attr number of attributes in attr_list array
 * @param[out] qos_scheduler_struct_t filled if success
 * @return standard error
 */
t_std_error ndi_qos_get_scheduler_profile(npu_id_t npu_id,
                            ndi_obj_id_t ndi_scheduler_id,
                            const nas_attr_id_t *nas_attr_list,
                            uint_t num_attr,
                            qos_scheduler_struct_t *p);


typedef struct ndi_qos_scheduler_group_struct{
    uint8_t         max_child;
    ndi_port_t      ndi_port;
    uint32_t        level;
    ndi_obj_id_t    scheduler_profile_id;
    ndi_obj_id_t    parent;
    uint32_t        child_count;
    ndi_obj_id_t    *child_list;
} ndi_qos_scheduler_group_struct_t;


/**
 * This function creates a Scheduler group ID in the NPU.
 * @param npu id
 * @param nas_attr_list based on the CPS API attribute enumeration values
 * @param num_attr number of attributes in attr_list array
 * @param p scheduler group structure to be modified
 * @param[out] ndi_scheduler_group_id
 * @return standard error
 */
t_std_error ndi_qos_create_scheduler_group(npu_id_t npu_id,
                                const nas_attr_id_t *nas_attr_list,
                                uint_t num_attr,
                                const ndi_qos_scheduler_group_struct_t *p,
                                ndi_obj_id_t *ndi_scheduler_group_id);

 /**
  * This function sets the scheduler_group attributes in the NPU.
  * @param npu id
  * @param ndi_scheduler_group_id
  * @param attr_id based on the CPS API attribute enumeration values
  * @param p scheduler_group structure to be modified
  * @return standard error
  */
t_std_error ndi_qos_set_scheduler_group_attr(npu_id_t npu_id,
                                    ndi_obj_id_t ndi_scheduler_group_id,
                                    BASE_QOS_SCHEDULER_GROUP_t attr_id,
                                    const ndi_qos_scheduler_group_struct_t *p);

/**
 * This function deletes a scheduler_group in the NPU.
 * @param npu_id npu id
 * @param ndi_scheduler_group_id
 * @return standard error
 */
t_std_error ndi_qos_delete_scheduler_group(npu_id_t npu_id,
                                    ndi_obj_id_t ndi_scheduler_group_id);

/**
 * This function get a scheduler_group from the NPU.
 * @param npu id
 * @param ndi_scheduler_group_id
 * @param nas_attr_list based on the CPS API attribute enumeration values
 * @param num_attr number of attributes in attr_list array
 * @param[out] ndi_qos_scheduler_group_struct_t filled if success
 * @return standard error
 */
t_std_error ndi_qos_get_scheduler_group(npu_id_t npu_id,
                            ndi_obj_id_t ndi_scheduler_group_id,
                            const nas_attr_id_t *nas_attr_list,
                            uint_t num_attr,
                            ndi_qos_scheduler_group_struct_t *p);



// The following default values should match the default SAI values
#define NDI_DEFAULT_TRAFFIC_CLASS 0
#define NDI_DEFAULT_COLOR   BASE_QOS_PACKET_COLOR_GREEN
#define NDI_DEFAULT_DOT1P   0
#define NDI_DEFAULT_DSCP    0
#define NDI_DEFAULT_QID     0
#define NDI_DEFAULT_PG      0

typedef enum  {
    NDI_QOS_MAP_DOT1P_TO_TC,
    NDI_QOS_MAP_DOT1P_TO_COLOR,
    NDI_QOS_MAP_DOT1P_TO_TC_COLOR,
    NDI_QOS_MAP_DSCP_TO_TC,
    NDI_QOS_MAP_DSCP_TO_COLOR,
    NDI_QOS_MAP_DSCP_TO_TC_COLOR,
    NDI_QOS_MAP_TC_TO_QUEUE,
    NDI_QOS_MAP_TC_TO_DSCP,
    NDI_QOS_MAP_TC_TO_DOT1P,
    NDI_QOS_MAP_TC_COLOR_TO_DSCP,
    NDI_QOS_MAP_TC_COLOR_TO_DOT1P,
    NDI_QOS_MAP_TC_TO_PG,
    NDI_QOS_MAP_PG_TO_PFC,
    NDI_QOS_MAP_PFC_TO_QUEUE,
    NDI_QOS_MAP_MAX, // limit
} ndi_qos_map_type_t;


// DSCP uses 6-bits of uint8_t
typedef uint8_t     DSCP_TYPE;

// DOT1P uses 3-bits of uint8_t
typedef uint8_t     DOT1P_TYPE;

typedef struct ndi_qos_map_params_t {
    /* The following field are selectively filled
     * based on the type of qos map and whether the
     * structure is used by a Key or by a Value.
     */
    // Traffic Class
    uint_t        tc;

    // DSCP value
    DSCP_TYPE   dscp;

    // dot1p value
    DOT1P_TYPE  dot1p;

    // Traffic color
    BASE_QOS_PACKET_COLOR_t color;

    // ndi queue id
    ndi_obj_id_t    qid;

    // local priority group id
    uint8_t     pg;

    // pfc priority
    DOT1P_TYPE     prio;


} ndi_qos_map_params_t;

typedef struct ndi_qos_map_struct{

    ndi_qos_map_params_t key;

    ndi_qos_map_params_t value;

} ndi_qos_map_struct_t;

/**
 * This function creates a map ID in the NPU.
 * @param npu id
 * @param type of qos map
 * @param count number of qos_map_struct to follow
 * @param key-to-value mappings
 * @param[out] ndi_map_id
 * @return standard error
 */
t_std_error ndi_qos_create_map(npu_id_t npu_id,
                                ndi_qos_map_type_t type,
                                uint_t count,
                                const ndi_qos_map_struct_t *p,
                                ndi_obj_id_t *ndi_map_id);

/**
 * This function updates one key-to-value mapping for a map.
 * @param npu id
 * @param ndi_map_id
 * @param number of map entries
 * @param key-to-value mapping
 * @return standard error
 */
t_std_error ndi_qos_set_map_attr(npu_id_t npu_id,
                     ndi_obj_id_t ndi_map_id,
                     uint_t map_entry_count,
                     const ndi_qos_map_struct_t *map_entry);


/**
 * This function deletes a map in the NPU.
 * @param npu_id npu id
 * @param ndi_map_id
 * @return standard error
 */
t_std_error ndi_qos_delete_map(npu_id_t npu_id,
                               ndi_obj_id_t ndi_map_id);

/**
 * This function get a map from the NPU.
 * @param npu id
 * @param ndi_map_id
 * @param[out] type of qos map
 * @param count number of qos_map_struct to be queried
 * @param[out] key-to-value mappings
 * @return standard error
 */
t_std_error ndi_qos_get_map(npu_id_t npu_id,
                            ndi_obj_id_t ndi_map_id,
                            ndi_qos_map_type_t *type,
                            uint_t count,
                            ndi_qos_map_struct_t *p);


typedef struct qos_port_ing_struct {
    uint_t          default_tc;
    ndi_obj_id_t    dot1p_to_tc_map;
    ndi_obj_id_t    dot1p_to_color_map;
    ndi_obj_id_t    dot1p_to_tc_color_map;
    ndi_obj_id_t    dscp_to_tc_map;
    ndi_obj_id_t    dscp_to_color_map;
    ndi_obj_id_t    dscp_to_tc_color_map;
    ndi_obj_id_t    tc_to_queue_map;
    BASE_QOS_FLOW_CONTROL_t flow_control;
    ndi_obj_id_t    policer_id;
    ndi_obj_id_t    flood_storm_control;
    ndi_obj_id_t    bcast_storm_control;
    ndi_obj_id_t    mcast_storm_control;
    uint_t          priority_group_number;
    uint_t          num_priority_group_id;
    ndi_obj_id_t    * priority_group_id_list;
    uint8_t         per_priority_flow_control;
    ndi_obj_id_t    tc_to_priority_group_map;
    ndi_obj_id_t    priority_group_to_pfc_priority_map;
    uint_t          num_buffer_profile;
    ndi_obj_id_t    * buffer_profile_list;
}qos_port_ing_struct_t;


 /**
  * This function sets port ingress profile attributes in the NPU.
  * @param npu id
  * @param port id
  * @param attr_id based on the CPS API attribute enumeration values
  * @param p port ingress structure to be modified
  * @return standard error
  */
t_std_error ndi_qos_set_port_ing_profile_attr(npu_id_t npu_id,
                                  npu_port_t port_id,
                                  BASE_QOS_PORT_INGRESS_t attr_id,
                                  const qos_port_ing_struct_t *p);

/**
 * This function get a port ingress profile from the NPU.
 * @param npu id
 * @param port id
 * @param nas_attr_list based on the CPS API attribute enumeration values
 * @param num_attr number of attributes in attr_list array
 * @param[out] qos_port_ing_struct_t filled if success
 * @return standard error
 */
t_std_error ndi_qos_get_port_ing_profile(npu_id_t npu_id,
                            npu_port_t port_id,
                            const BASE_QOS_PORT_INGRESS_t *nas_attr_list,
                            uint_t num_attr,
                            qos_port_ing_struct_t *p);

typedef struct qos_port_egr_struct {
    uint_t                  buffer_limit;
    ndi_obj_id_t            wred_profile_id;
    ndi_obj_id_t            scheduler_profile_id;
    uint_t                  num_ucast_queue;
    uint_t                  num_mcast_queue;
    uint_t                  num_queue;
    uint_t                  num_queue_id;
    ndi_obj_id_t            * queue_id_list;
    ndi_obj_id_t            tc_to_queue_map;
    ndi_obj_id_t            tc_to_dot1p_map;
    ndi_obj_id_t            tc_to_dscp_map;
    ndi_obj_id_t            tc_color_to_dot1p_map;
    ndi_obj_id_t            tc_color_to_dscp_map;
    ndi_obj_id_t            pfc_priority_to_queue_map;
    uint_t                  num_buffer_profile;
    ndi_obj_id_t            * buffer_profile_list;
}qos_port_egr_struct_t;

 /**
  * This function sets port egress profile attributes in the NPU.
  * @param npu id
  * @param port id
  * @param attr_id based on the CPS API attribute enumeration values
  * @param p port egress structure to be modified
  * @return standard error
  */
t_std_error ndi_qos_set_port_egr_profile_attr(npu_id_t npu_id,
                                  npu_port_t port_id,
                                  BASE_QOS_PORT_EGRESS_t attr_id,
                                  const qos_port_egr_struct_t *p);
/**
 * This function get a port egress profile from the NPU.
 * @param npu id
 * @param port id
 * @param nas_attr_list based on the CPS API attribute enumeration values
 * @param num_attr number of attributes in attr_list array
 * @param[out] qos_port_eg_struct_t filled if success
 * @return standard error
 */
t_std_error ndi_qos_get_port_egr_profile(npu_id_t npu_id,
                            npu_port_t port_id,
                            const BASE_QOS_PORT_EGRESS_t *nas_attr_list,
                            uint_t num_attr,
                            qos_port_egr_struct_t *p);

/**
 * This function gets the total number of scheduler-groups on a port
 * @param ndi_port_id
 * @Return number of scheduler-group
 */
uint_t ndi_qos_get_number_of_scheduler_groups(ndi_port_t ndi_port_id);


/**
 * This function gets the list of scheduler-groups of a port
 * @param ndi_port_id
 * @param count size of the scheduler-group list
 * @param[out] ndi_sg_id_list[] to be filled with either the number of scheduler-groups
 *            that the port owns or the size of array itself, whichever is less.
 * @Return Number of scheduler-groups retrieved.
 */
uint_t ndi_qos_get_scheduler_group_id_list(ndi_port_t ndi_port_id,
                                           uint_t count,
                                           ndi_obj_id_t *ndi_sg_id_list);



typedef struct qos_buffer_pool_struct{
    uint32_t shared_size;     // Read-only, remaining shared buffer size
    BASE_QOS_BUFFER_POOL_TYPE_t     type;     // buffer pool type: Ingress or Egress
    uint32_t size;             // total size of the buffer pool
    BASE_QOS_BUFFER_THRESHOLD_MODE_t threshold_mode; // shared threshold mode for the buffer pool
    uint32_t xoff_size;        // shared headroom pool size in bytes for lossless traffic
    ndi_obj_id_t wred_profile_id;  // WRED profile attached to the pool
}qos_buffer_pool_struct_t;


/**
 * This function creates a buffer_pool in the NPU.
 * @param npu id
 * @param nas_attr_list based on the CPS API attribute enumeration values
 * @param num_attr number of attributes in attr_list array
 * @param p buffer_pool structure to be modified
 * @param[out] ndi_buffer_pool_id
 * @return standard error
 */
t_std_error ndi_qos_create_buffer_pool(npu_id_t npu_id,
                                const nas_attr_id_t *nas_attr_list,
                                uint_t num_attr,
                                const qos_buffer_pool_struct_t *p,
                                ndi_obj_id_t *ndi_buffer_pool_id);

 /**
  * This function sets the buffer_pool attributes in the NPU.
  * @param npu id
  * @param ndi_buffer_pool_id
  * @param attr_id based on the CPS API attribute enumeration values
  * @param p buffer_pool structure to be modified
  * @return standard error
  */
t_std_error ndi_qos_set_buffer_pool_attr(npu_id_t npu_id, ndi_obj_id_t ndi_buffer_pool_id,
                                  BASE_QOS_BUFFER_POOL_t attr_id, const qos_buffer_pool_struct_t *p);

/**
 * This function deletes a buffer_pool in the NPU.
 * @param npu id
 * @param ndi_buffer_pool_id
 * @return standard error
 */
t_std_error ndi_qos_delete_buffer_pool(npu_id_t npu_id, ndi_obj_id_t ndi_buffer_pool_id);

/**
 * This function get a buffer_pool from the NPU.
 * @param npu id
 * @param ndi_buffer_pool_id
 * @param nas_attr_list based on the CPS API attribute enumeration values
 * @param num_attr number of attributes in attr_list array
 * @param[out] qos_buffer_pool_struct_t filled if success
 * @return standard error
 */
t_std_error ndi_qos_get_buffer_pool(npu_id_t npu_id,
                            ndi_obj_id_t ndi_buffer_pool_id,
                            const nas_attr_id_t *nas_attr_list,
                            uint_t num_attr,
                            qos_buffer_pool_struct_t *p);

/**
 * This function gets the list of shadow buffer_pool object on different MMUs
 * @param npu_id
 * @param ndi_buffer_pool_id
 * @param count, size of ndi_shadow_pool_list[]
 * @param[out] ndi_shadow_pool_list[] will be filled if successful
 * @Return The total number of shadow buffer_pool objects on different MMUs.
 *         If the count is smaller than the actual number of shadow buffer_pool
 *         objects, ndi_shadow_pool_list[] will not be filled.
 */
uint_t ndi_qos_get_shadow_buffer_pool_list(npu_id_t npu_id,
                            ndi_obj_id_t ndi_buffer_pool_id,
                            uint_t count,
                            ndi_obj_id_t * ndi_shadow_pool_list);

typedef struct nas_qos_buffer_pool_stat_counter_t {
    uint64_t current_occupancy_bytes;
    uint64_t watermark_bytes;
} nas_qos_buffer_pool_stat_counter_t;

/**
 * This function gets the buffer_pool statistics
 * @param npu_id
 * @param ndi_buffer_pool_id
 * @param list of buffer_pool counter types to query
 * @param number of buffer_pool counter types specified
 * @param[out] counter stats
 * return standard error
 * @deprecated since 7.7.0+opx1
 * @see ndi_qos_get_extended_buffer_pool_statistics()
*/
t_std_error ndi_qos_get_buffer_pool_stats(npu_id_t npu_id,
                                ndi_obj_id_t ndi_buffer_pool_id,
                                BASE_QOS_BUFFER_POOL_STAT_t *counter_ids,
                                uint_t number_of_counters,
                                nas_qos_buffer_pool_stat_counter_t *stats);

/**
 * This function gets the buffer_pool statistics (New API)
 * @param npu_id
 * @param ndi_buffer_pool_id
 * @param list of buffer_pool counter types to query
 * @param number of buffer_pool counter types specified
 * @param[out] counter stats will be in the same order of the counter_ids.
 * return standard error
 * @deprecated since 7.7.0+opx1
 * @see ndi_qos_get_extended_buffer_pool_statistics()
 */
t_std_error ndi_qos_get_buffer_pool_statistics(npu_id_t npu_id,
                                ndi_obj_id_t ndi_buffer_pool_id,
                                BASE_QOS_BUFFER_POOL_STAT_t *counter_ids,
                                uint_t number_of_counters,
                                uint64_t *stats);

/**
 * This function gets the buffer_pool statistics
 * @param npu_id
 * @param ndi_buffer_pool_id
 * @param list of buffer_pool counter types to query
 * @param number of buffer_pool counter types specified
 * @param[out] counters: stats will be stored in the same order of the counter_ids
 * @param read and clean
 * @param snapshot counter
 * return standard error
 */

t_std_error ndi_qos_get_extended_buffer_pool_statistics(npu_id_t npu_id,
                                ndi_obj_id_t ndi_buffer_pool_id,
                                BASE_QOS_BUFFER_POOL_STAT_t *counter_ids,
                                uint_t number_of_counters,
                                uint64_t *counters,
                                ndi_stats_mode_t ndi_stats_mode,
                                bool is_snapshot_counters);

/**
 * This function clears the buffer_pool statistics
 * @param npu_id
 * @param ndi_buffer_pool_id
 * @param list of buffer_pool counter types to clear
 * @param number of buffer_pool counter types specified
 * return standard error
 * @deprecated since 7.7.0+opx1
 * @see ndi_qos_clear_extended_buffer_pool_statistics()
*/
t_std_error ndi_qos_clear_buffer_pool_stats(npu_id_t npu_id,
                                ndi_obj_id_t ndi_buffer_pool_id,
                                BASE_QOS_BUFFER_POOL_STAT_t *counter_ids,
                                uint_t number_of_counters);

/**
 * This function clears the buffer_pool statistics
 * @param npu_id
 * @param ndi_buffer_pool_id
 * @param list of buffer_pool counter types to clear
 * @param number of buffer_pool counter types specified
 * @param snapshot counters
 * return standard error
 */
t_std_error ndi_qos_clear_extended_buffer_pool_statistics(npu_id_t npu_id,
                                ndi_obj_id_t ndi_buffer_pool_id,
                                BASE_QOS_BUFFER_POOL_STAT_t *counter_ids,
                                uint_t number_of_counters, bool is_snapshot_counters);

typedef struct ndi_qos_buffer_profile_struct{
    ndi_obj_id_t pool_id;       // pool id for the buffer profile
    uint32_t buffer_size;       // reserved buffer size in bytes
    uint32_t threshold_mode;    // buffer profile threshold to rewrite the pool threshold mode if set
    uint8_t  shared_dynamic_th; // index to pre-defined Alpha value
    uint32_t shared_static_th;  // static threshold for the shared usage in bytes
    uint32_t xoff_th;   // XOFF threshold in bytes
    uint32_t xon_th;    // XON threshold in bytes
    uint32_t xon_offset_th; // XON hysteresis value
}ndi_qos_buffer_profile_struct_t;


/**
 * This function creates a buffer_profile in the NPU.
 * @param npu id
 * @param nas_attr_list based on the CPS API attribute enumeration values
 * @param num_attr number of attributes in attr_list array
 * @param p buffer_profile structure to be modified
 * @param[out] ndi_buffer_profile_id
 * @return standard error
 */
t_std_error ndi_qos_create_buffer_profile(npu_id_t npu_id,
                                const nas_attr_id_t *nas_attr_list,
                                uint_t num_attr,
                                const ndi_qos_buffer_profile_struct_t *p,
                                ndi_obj_id_t *ndi_buffer_profile_id);

 /**
  * This function sets the buffer_profile attributes in the NPU.
  * @param npu id
  * @param ndi_buffer_profile_id
  * @param attr_id based on the CPS API attribute enumeration values
  * @param p buffer_profile structure to be modified
  * @return standard error
  */
t_std_error ndi_qos_set_buffer_profile_attr(npu_id_t npu_id, ndi_obj_id_t ndi_buffer_profile_id,
                                  BASE_QOS_BUFFER_PROFILE_t attr_id, const ndi_qos_buffer_profile_struct_t *p);

/**
 * This function deletes a buffer_profile in the NPU.
 * @param npu id
 * @param ndi_buffer_profile_id
 * @return standard error
 */
t_std_error ndi_qos_delete_buffer_profile(npu_id_t npu_id, ndi_obj_id_t ndi_buffer_profile_id);

/**
 * This function get a buffer_profile from the NPU.
 * @param npu id
 * @param ndi_buffer_profile_id
 * @param nas_attr_list based on the CPS API attribute enumeration values
 * @param num_attr number of attributes in attr_list array
 * @param[out] qos_buffer_profile_struct_t filled if success
 * @return standard error
 */
t_std_error ndi_qos_get_buffer_profile(npu_id_t npu_id,
                            ndi_obj_id_t ndi_buffer_profile_id,
                            const nas_attr_id_t *nas_attr_list,
                            uint_t num_attr,
                            ndi_qos_buffer_profile_struct_t *p);


typedef struct ndi_qos_priority_group_attribute{
    ndi_obj_id_t buffer_profile; // buffer profile id to which the priority group is referring
}ndi_qos_priority_group_attribute_t;



/**
 * This function sets the priority_group profile attributes in the NPU.
 * @param ndi_port_id
 * @param ndi_priority_group_id
 * @param buffer_profile_id
 * @return standard error
 */
t_std_error ndi_qos_set_priority_group_buffer_profile_id(ndi_port_t ndi_port_id,
                                        ndi_obj_id_t ndi_priority_group_id,
                                        ndi_obj_id_t buffer_profile_id);


/**
 * This function get a priority_group from the NPU.
 * @param ndi_port_id
 * @param ndi_priority_group_id
 * @param[out] ndi_qos_priority_group_struct_t filled if success
 * @return standard error
 */
t_std_error ndi_qos_get_priority_group_attribute(ndi_port_t ndi_port_id,
                            ndi_obj_id_t ndi_priority_group_id,
                            ndi_qos_priority_group_attribute_t *p);


/**
 * This function gets the total number of priority groups on a port
 * @param ndi_port_id
 * @Return standard error code
 */
uint_t ndi_qos_get_number_of_priority_groups(ndi_port_t ndi_port_id);


/**
 * This function gets the list of priority groups of a port
 * @param ndi_port_id
 * @param count size of the pg_list
 * @param[out] ndi_pg_id_list[] to be filled with either the number of pgs
 *            that the port owns or the size of array itself, whichever is less.
 * @Return Number of pgs retrieved.
 */
uint_t ndi_qos_get_priority_group_id_list(ndi_port_t ndi_port_id,
                                uint_t count,
                                ndi_obj_id_t *ndi_pg_id_list);

/**
 * This function gets the list of shadow priority group object on different MMUs
 * @param npu_id
 * @param ndi_pg_id
 * @param count, size of ndi_shadow_pg_list[]
 * @param[out] ndi_shadow_pg_list[] will be filled if successful
 * @Return The total number of shadow pg objects on different MMUs.
 *         If the count is smaller than the actual number of shadow pg
 *         objects, ndi_shadow_pg_list[] will not be filled.
 */
uint_t ndi_qos_get_shadow_priority_group_list(npu_id_t npu_id,
                            ndi_obj_id_t ndi_pg_id,
                            uint_t count,
                            ndi_obj_id_t * ndi_shadow_pg_list);

typedef struct nas_qos_priority_group_stat_counter_t {
    uint64_t packets;
    uint64_t bytes;
    uint64_t current_occupancy_bytes;
    uint64_t watermark_bytes;
    uint64_t shared_current_occupancy_bytes;
    uint64_t shared_watermark_bytes;
    uint64_t xoff_room_current_occupancy_bytes;
    uint64_t xoff_room_watermark_bytes;
} nas_qos_priority_group_stat_counter_t;

/**
 * This function gets the priority_group statistics
 * @param ndi_port_id
 * @param ndi_priority_group_id
 * @param list of priority_group counter types to query
 * @param number of priority_group counter types specified
 * @param[out] counter stats
 * return standard error
 * @deprecated since 7.7.0+opx1
 * @see ndi_qos_get_extended_priority_group_statistics()
 */
t_std_error ndi_qos_get_priority_group_stats(ndi_port_t ndi_port_id,
                                ndi_obj_id_t ndi_priority_group_id,
                                BASE_QOS_PRIORITY_GROUP_STAT_t *counter_ids,
                                uint_t number_of_counters,
                                nas_qos_priority_group_stat_counter_t *stats);

/**
 * This function gets the priority_group statistics
 * @param ndi_port_id
 * @param ndi_priority_group_id
 * @param list of priority_group counter types to query
 * @param number of priority_group counter types specified
 * @param[out] counter stats
 * @param is counter read and clear
 * @param is snapshot counter
 * return standard error
 */
t_std_error ndi_qos_get_extended_priority_group_statistics(ndi_port_t ndi_port_id,
                                ndi_obj_id_t ndi_priority_group_id,
                                BASE_QOS_PRIORITY_GROUP_STAT_t *counter_ids,
                                uint_t number_of_counters,
                                uint64_t *counters,
                                ndi_stats_mode_t ndi_stats_mode,
                                bool is_snapshot_counters);

/**
 * This function clears the priority_group statistics
 * @param ndi_port_id
 * @param ndi_priority_group_id
 * @param list of priority_group counter types to clear
 * @param number of priority_group counter types specified
 * return standard error
 * @deprecated since 7.7.0+opx1
 * @see ndi_qos_clear_extended_priority_group_statistics()
 */
t_std_error ndi_qos_clear_priority_group_stats(ndi_port_t ndi_port_id,
                                ndi_obj_id_t ndi_priority_group_id,
                                BASE_QOS_PRIORITY_GROUP_STAT_t *counter_ids,
                                uint_t number_of_counters);

/**
 * This function clears the priority_group statistics
 * @param ndi_port_id
 * @param ndi_priority_group_id
 * @param list of priority_group counter types to clear
 * @param number of priority_group counter types specified
 * @param is snapshot counters
 * return standard error
 */
t_std_error ndi_qos_clear_extended_priority_group_statistics(ndi_port_t ndi_port_id,
                                ndi_obj_id_t ndi_priority_group_id,
                                BASE_QOS_PRIORITY_GROUP_STAT_t *counter_ids,
                                uint_t number_of_counters,
                                bool is_snapshot_counters);


typedef struct ndi_qos_port_pool_struct {
    ndi_port_t      ndi_port;
    ndi_obj_id_t    ndi_pool_id;
    ndi_obj_id_t    wred_profile_id;

} ndi_qos_port_pool_struct_t;

/**
 * This function creates a port_pool in the NPU.
 * @param npu id
 * @param nas_attr_list based on the CPS API attribute enumeration values
 * @param num_attr number of attributes in attr_list array
 * @param p port_pool structure to be modified
 * @param[out] ndi_port_pool_id
 * @return standard error
 */
t_std_error ndi_qos_create_port_pool(npu_id_t npu_id,
                                const nas_attr_id_t *nas_attr_list,
                                uint_t num_attr,
                                const ndi_qos_port_pool_struct_t *p,
                                ndi_obj_id_t *ndi_port_pool_id);

 /**
  * This function sets the port_pool attributes in the NPU.
  * @param npu id
  * @param ndi_port_pool_id
  * @param attr_id based on the CPS API attribute enumeration values
  * @param p port_pool structure to be modified
  * @return standard error
  */
t_std_error ndi_qos_set_port_pool_attr(npu_id_t npu_id,
                                ndi_obj_id_t ndi_port_pool_id,
                                BASE_QOS_PORT_POOL_t attr_id,
                                const ndi_qos_port_pool_struct_t *p);

/**
 * This function deletes a port_pool in the NPU.
 * @param npu id
 * @param ndi_port_pool_id
 * @return standard error
 */
t_std_error ndi_qos_delete_port_pool(npu_id_t npu_id,
                            ndi_obj_id_t ndi_port_pool_id);

/**
 * This function get a port_pool from the NPU.
 * @param npu id
 * @param ndi_port_pool_id
 * @param nas_attr_list based on the CPS API attribute enumeration values
 * @param num_attr number of attributes in attr_list array
 * @param[out] qos_port_pool_struct_t filled if success
 * @return standard error
 */
t_std_error ndi_qos_get_port_pool(npu_id_t npu_id,
                            ndi_obj_id_t ndi_port_pool_id,
                            const nas_attr_id_t *nas_attr_list,
                            uint_t num_attr,
                            ndi_qos_port_pool_struct_t *p);

typedef struct nas_qos_port_pool_stat_counter_t {
    uint64_t green_discard_dropped_packets;
    uint64_t green_discard_dropped_bytes;
    uint64_t yellow_discard_dropped_packets;
    uint64_t yellow_discard_dropped_bytes;
    uint64_t red_discard_dropped_packets;
    uint64_t red_discard_dropped_bytes;
    uint64_t discard_dropped_packets;
    uint64_t discard_dropped_bytes;
    uint64_t current_occupancy_bytes;
    uint64_t watermark_bytes;
    uint64_t shared_current_occupancy_bytes;
    uint64_t shared_watermark_bytes;
} nas_qos_port_pool_stat_counter_t;

/**
 * This function gets the port pool statistics
 * @param npu_id
 * @param ndi_port_pool_id
 * @param list of port_pool counter types to query
 * @param number of port_pool counter types specified
 * @param[out] counter stats
 * return standard error
 */
t_std_error ndi_qos_get_port_pool_stats(ndi_port_t ndi_port,
                                ndi_obj_id_t ndi_port_pool_id,
                                BASE_QOS_PORT_POOL_STAT_t *counter_ids,
                                uint_t number_of_counters,
                                nas_qos_port_pool_stat_counter_t *stats);
/**
 * This function gets the port pool statistics
 * @param npu_id
 * @param ndi_port_pool_id
 * @param list of port_pool counter types to query
 * @param number of port_pool counter types specified
 * @param[out] counter: stats are filled in the same order of the counter_ids
 * return standard error
 */
t_std_error ndi_qos_get_port_pool_statistics(ndi_port_t ndi_port,
                                ndi_obj_id_t ndi_port_pool_id,
                                BASE_QOS_PORT_POOL_STAT_t *counter_ids,
                                uint_t number_of_counters,
                                uint64_t * counters);

/**
 * This function clears the port_pool statistics
 * @param npu_id
 * @param ndi_port_pool_id
 * @param list of port_pool counter types to clear
 * @param number of port_pool counter types specified
 * return standard error
 */
t_std_error ndi_qos_clear_port_pool_stats(ndi_port_t ndi_port,
                                ndi_obj_id_t ndi_port_pool_id,
                                BASE_QOS_PORT_POOL_STAT_t *counter_ids,
                                uint_t number_of_counters);


/**
 *  \}
 */

#ifdef __cplusplus
}
#endif
#endif

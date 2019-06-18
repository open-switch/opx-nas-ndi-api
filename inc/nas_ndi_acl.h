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
 * filename: nas_ndi_acl.h
 */

/**
 * \file nas_ndi_acl.h
 * \brief NDI interface APIs for ACL
 **/


#ifndef __NAS_NDI_ACL_H
#define __NAS_NDI_ACL_H

#include "std_error_codes.h"
#include "ds_common_types.h"
#include "dell-base-acl.h"
#include "nas_types.h"
#include "nas_ndi_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup NDIAPIAcl NDI API - ACL
 *
 *  \{
 */
typedef  uint32_t   ndi_acl_priority_t;
typedef  uint16_t   ndi_acl_l4_port_t;

/**
 * @brief ACL Table data structure passed from NAS to NDI
 * Contains data for ACL Table provisioning in SAI.
 */
typedef struct _ndi_acl_slice_attr {
    uint32_t                slice_index;
    uint32_t                pipeline_index;
    size_t                  used_count;
    size_t                  avail_count;
    BASE_ACL_STAGE_t        stage;

    //list of acl table object id's returned as part of get
    size_t                  acl_table_count;
    ndi_obj_id_t           *acl_table_list;
} ndi_acl_slice_attr_t;

/**
 * @brief ACL Table data structure passed from NAS to NDI
 * Contains data for ACL Table provisioning in SAI.
 */
typedef struct _ndi_acl_table {
    BASE_ACL_STAGE_t        stage;
    ndi_acl_priority_t      priority;
    size_t                  filter_count;
    BASE_ACL_MATCH_TYPE_t  *filter_list;
    uint32_t                size;
    size_t                  udf_grp_count;
    ndi_obj_id_t            *udf_grp_id_list;
    size_t                  action_count;
    BASE_ACL_ACTION_TYPE_t *action_list;
} ndi_acl_table_t;


/**
 * @brief ACL Table attribute data structure passed from NDI to NAS
 * Contains data for ACL Table attributes retrieved from SAI.
 */
typedef struct _ndi_acl_table_attr {

    //list of acl table used entry count returned as part of get
    //each entry in this list represent the count for one pipeline.
    size_t                  acl_table_used_entry_list_count;
    uint32_t               *acl_table_used_entry_list;

    //list of acl table available entry count returned as part of get
    //each entry in this list represent the count for one pipeline.
    size_t                  acl_table_avail_entry_list_count;
    uint32_t               *acl_table_avail_entry_list;
} ndi_acl_table_attr_t;


/**
 * @brief Type associated with the union data in ndi_acl_entry_filter_t.
 */
typedef enum {
    NDI_ACL_FILTER_IP_TYPE,
    NDI_ACL_FILTER_IP_FRAG,
    NDI_ACL_FILTER_PORT,
    NDI_ACL_FILTER_PORTLIST,
    NDI_ACL_FILTER_MAC_ADDR,
    NDI_ACL_FILTER_IPV4_ADDR,
    NDI_ACL_FILTER_IPV6_ADDR,
    NDI_ACL_FILTER_U32,
    NDI_ACL_FILTER_U16,
    NDI_ACL_FILTER_U8,
    NDI_ACL_FILTER_OBJ_ID,
    NDI_ACL_FILTER_OBJ_ID_LIST,
    NDI_ACL_FILTER_BOOL,
    NDI_ACL_FILTER_U8LIST,
    NDI_ACL_FILTER_BRIDGE_TYPE,
} ndi_acl_filter_values_type_t;

/**
 * @brief Type associated with the union data in ndi_acl_entry_action_t.
 */
typedef enum {
    NDI_ACL_ACTION_NO_VALUE = 1,
    NDI_ACL_ACTION_PKT_ACTION,
    NDI_ACL_ACTION_OBJ_ID,
    NDI_ACL_ACTION_OBJ_ID_LIST,
    NDI_ACL_ACTION_PORT,
    NDI_ACL_ACTION_PORTLIST,
    NDI_ACL_ACTION_MAC_ADDR,
    NDI_ACL_ACTION_IPV4_ADDR,
    NDI_ACL_ACTION_IPV6_ADDR,
    NDI_ACL_ACTION_U32,
    NDI_ACL_ACTION_U16,
    NDI_ACL_ACTION_U8,
    NDI_ACL_ACTION_PKT_COLOR,
    NDI_ACL_ACTION_U64,
} ndi_acl_action_values_type_t;

/**
 * @brief Convenience type to group all possible values that are
 *        commonly used as data for ACL Filters and ACL actions.
 */
typedef union {
        ndi_obj_id_t                   ndi_obj_ref;
        ndi_obj_id_list_t              ndi_obj_ref_list;
        ndi_port_t                     ndi_port;
        ndi_port_list_t                ndi_portlist;
        hal_mac_addr_t                 mac;
        dn_ipv4_addr_t                 ipv4;
        dn_ipv6_addr_t                 ipv6;
        uint64_t                       u64;
        uint32_t                       u32;
        uint16_t                       u16;
        uint8_t                        u8;
        ndi_byte_list_t                ndi_u8list;
} ndi_acl_values_t;

/**
 * @brief ACL Action data structure used in NAS and NDI
 * Contains data for ACL Action provisioning in SAI.
 */
typedef struct _ndi_acl_entry_action {
    BASE_ACL_ACTION_TYPE_t        action_type;
    ndi_acl_action_values_type_t  values_type;
    union {
        BASE_ACL_PACKET_ACTION_TYPE_t  pkt_action;
        BASE_ACL_PACKET_COLOR_t        pkt_color;
        ndi_acl_values_t               values;
    };
} ndi_acl_entry_action_t;

/**
 * @brief ACL Filter data structure passed from NAS to NDI
 * Contains data for ACL Filter provisioning in SAI.
 */
typedef struct {
    BASE_ACL_MATCH_TYPE_t           filter_type;
    ndi_acl_filter_values_type_t    values_type;
    union {
        BASE_ACL_MATCH_IP_TYPE_t    ip_type;
        BASE_ACL_MATCH_IP_FRAG_t    ip_frag;
        ndi_acl_values_t            values;
   } data;
    union {
        ndi_acl_values_t            values;
    } mask;
    uint8_t                         udf_seq_no;
} ndi_acl_entry_filter_t;

/**
 * @brief ACL Entry data structure passed from NAS to NDI
 * Contains data for ACL Entry/Rule provisioning in SAI.
 */
typedef struct _ndi_acl_entry {
    ndi_obj_id_t            table_id;
    ndi_acl_priority_t      priority;
    size_t                  filter_count;
    ndi_acl_entry_filter_t *filter_list;
    size_t                  action_count;
    ndi_acl_entry_action_t *action_list;
} ndi_acl_entry_t;

/*
 * @brief ACL Counter data structure passed from NAS to NDI
 * Contains data for ACL Counter provisioning in SAI.
 */
typedef struct _ndi_acl_counter {
    ndi_obj_id_t      table_id;
    bool              enable_pkt_count;
    bool              enable_byte_count;
} ndi_acl_counter_t;

/**
 * @brief Create a new ACL table in NPU
 *
 * @param npu_id - NPU ID in which to create
 * @param t_create - Attributes for the ACL table being created
 * @param[out] ndi_tbl_id - Table ID generated by NDI.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_table_create (npu_id_t npu_id,
                                  const ndi_acl_table_t* ndi_tbl_p,
                                  ndi_obj_id_t* ndi_tbl_id_p);

/**
 * @brief Delete an existing ACL table from NPU
 *
 * @param npu_id - NPU ID in which to delete
 * @param ndi_tbl_id - NDI Table ID of table to be deleted.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_table_delete (npu_id_t npu_id,
                                  ndi_obj_id_t ndi_tbl_id);

/**
 * @brief Modify the Priority of an existing ACL table
 *
 * @param npu_id - NPU ID in which to modify
 * @param ndi_tbl_id - NDI Table ID of table to be modified.
 * @param tbl_priority - New value for Table priority.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_table_set_priority (npu_id_t npu_id,
                                        ndi_obj_id_t ndi_tbl_id,
                                        ndi_acl_priority_t tbl_priority);

/**
 * @brief Create a new ACL Entry in NPU
 *
 * @param npu_id - NPU ID in which to create
 * @param t_create - Attributes for the ACL Entry being created
 * @param[out] ndi_entry_id - Entry ID generated by NDI.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_entry_create (npu_id_t npu_id,
                                  const ndi_acl_entry_t* ndi_entry_p,
                                  ndi_obj_id_t* ndi_entry_id_p);

/**
 * @brief Delete an existing ACL Entry from NPU
 *
 * @param npu_id - NPU ID in which to delete
 * @param ndi_entry_id - NDI Entry ID of Entry to be deleted.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_entry_delete (npu_id_t npu_id,
                                  ndi_obj_id_t ndi_entry_id);

/**
 * @brief Modify the Priority of an existing ACL entry
 *
 * @param npu_id - NPU ID in which to modify
 * @param ndi_entry_id - NDI Entry ID of entry to be modified.
 * @param entry_priority - New value for Entry priority.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_entry_set_priority (npu_id_t npu_id,
                                        ndi_obj_id_t ndi_entry_id,
                                        ndi_acl_priority_t entry_priority);

/**
 * @brief Add/Modify individual Filter field of an existing ACL entry
 *
 * @param npu_id - NPU ID in which to modify
 * @param ndi_entry_id - NDI Entry ID of entry to be modified.
 * @param filter - New or modified filter field parameter.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_entry_set_filter (npu_id_t npu_id,
                                      ndi_obj_id_t ndi_entry_id,
                                      ndi_acl_entry_filter_t *filter_p);

/**
 * @brief Add/Modify individual Action of an existing ACL entry
 *
 * @param npu_id - NPU ID in which to modify
 * @param ndi_entry_id - NDI Entry ID of entry to be modified.
 * @param action - New or modified action parameter.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_entry_set_action (npu_id_t npu_id,
                                      ndi_obj_id_t ndi_entry_id,
                                      ndi_acl_entry_action_t *action_p);

/**
 * @brief Disable individual Filter field in an existing ACL entry
 *
 * @param npu_id - NPU ID in which to modify
 * @param ndi_entry_id - NDI Entry ID of entry to be modified.
 * @param filter_id - Type of Filter Match Field to be removed.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_entry_disable_filter (npu_id_t npu_id,
                                          ndi_obj_id_t ndi_entry_id,
                                          BASE_ACL_MATCH_TYPE_t filter_id);

/**
 * @brief Disable individual Action in an existing ACL entry
 *
 * @param npu_id - NPU ID in which to modify
 * @param ndi_entry_id - NDI Entry ID of entry to be modified.
 * @param action_id - Type of Action to be removed.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_entry_disable_action (npu_id_t npu_id,
                                          ndi_obj_id_t ndi_entry_id,
                                          BASE_ACL_ACTION_TYPE_t action_id);

/**
 * @brief Disable Set_Counter Action in an existing ACL entry
 *
 * @param npu_id - NPU ID in which to modify
 * @param ndi_entry_id - NDI Entry ID of entry to be modified.
 * @param ndi_counter_id - NDI Counter ID of counter to be disabled.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_entry_disable_counter_action (npu_id_t npu_id,
                                          ndi_obj_id_t ndi_entry_id,
                                          ndi_obj_id_t ndi_counter_id);

/**
 * @brief Create a new ACL counter in NPU
 *
 * @param npu_id - NPU ID in which to create
 * @param ndi_counter - Attributes for the ACL Counter being created
 * @param[out] ndi_counter_id - Counter ID generated by NDI.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_counter_create (npu_id_t npu_id,
                                    const ndi_acl_counter_t* ndi_counter_p,
                                    ndi_obj_id_t* ndi_counter_id_p);

/**
 * @brief Delete an existing ACL Counter from NPU
 *
 * @param npu_id - NPU ID in which to delete
 * @param ndi_counter_id - NDI Counter ID of Entry to be deleted.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_counter_delete (npu_id_t npu_id,
                                    ndi_obj_id_t ndi_counter_id);

/**
 * @brief Enable/Disable packet count mode for the counter
 *
 * @param npu_id - NPU ID in which to modify
 * @param ndi_counter_id - NDI Counter ID of entry to be modified.
 * @param enable - Bool - Enable (True) Disable (False).
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_counter_enable_pkt_count (npu_id_t npu_id,
                                              ndi_obj_id_t ndi_counter_id,
                                              bool enable);

/**
 * @brief Enable/Disable byte count mode for the counter
 *
 * @param npu_id - NPU ID in which to modify
 * @param ndi_counter_id - NDI Counter ID of entry to be modified.
 * @param enable - Bool - Enable (True) Disable (False).
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_counter_enable_byte_count (npu_id_t npu_id,
                                               ndi_obj_id_t ndi_counter_id,
                                               bool enable);
/**
 * @brief Set pkt count for the counter - can be used to reset counter to 0
 *
 * @param npu_id - NPU ID in which to modify
 * @param ndi_counter_id - NDI Counter ID of entry to be modified.
 * @param count - value to set.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_counter_set_pkt_count (npu_id_t npu_id,
                                            ndi_obj_id_t ndi_counter_id,
                                            uint64_t pkt_count);

/**
 * @brief Set byte count for the counter - can be used to reset counter to 0
 *
 * @param npu_id - NPU ID in which to modify
 * @param ndi_counter_id - NDI Counter ID of entry to be modified.
 * @param count - value to set.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_counter_set_byte_count (npu_id_t npu_id,
                                            ndi_obj_id_t ndi_counter_id,
                                            uint64_t byte_count);

/**
 * @brief Get packet count for the counter
 *
 * @param npu_id - NPU ID in which to modify
 * @param ndi_counter_id - NDI Counter ID of entry to be obtained.
 * @param [out] count - result in packets.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_counter_get_pkt_count (npu_id_t npu_id,
                                           ndi_obj_id_t ndi_counter_id,
                                           uint64_t* pkt_count_p);

/**
 * @brief Get byte count for the counter
 *
 * @param npu_id - NPU ID in which to modify
 * @param ndi_counter_id - NDI Counter ID of entry to be obtained.
 * @param [out] count - result in bytes.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_counter_get_byte_count (npu_id_t npu_id,
                                            ndi_obj_id_t ndi_counter_id,
                                            uint64_t* byte_count_p);

/**
 * @brief Get byte and packet count for the counter
 *
 * @param npu_id - NPU ID in which to modify
 * @param ndi_counter_id - NDI Counter ID of entry to be obtained.
 * @param [out] byte_count - result in bytes.
 * @param [out] pkt_count - result in packets.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_counter_get_count (npu_id_t npu_id,
                                       ndi_obj_id_t ndi_counter_id,
                                       uint64_t* byte_count_p,
                                       uint64_t* pkt_count_p);

typedef enum {
    NDI_ACL_RANGE_L4_SRC_PORT,
    NDI_ACL_RANGE_L4_DST_PORT,
    NDI_ACL_RANGE_OUTER_VLAN,
    NDI_ACL_RANGE_INNER_VLAN,
    NDI_ACL_RANGE_PACKET_LENGTH
} ndi_acl_range_type_t;

typedef struct _ndi_acl_range {
    ndi_acl_range_type_t type;
    uint32_t min;
    uint32_t max;
} ndi_acl_range_t;


/**
 * @brief Create a new ACL range in NPU
 *
 * @param npu_id - NPU ID in which to create
 * @param acl_range_p - Attributes for the ACL Range being created
 * @param[out] ndi_range_id - Range ID generated by NDI.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_range_create(npu_id_t npu_id, const ndi_acl_range_t *acl_range_p,
                                 ndi_obj_id_t *ndi_range_id_p);
/**
 * @brief Delete an existing ACL Range from NPU
 *
 * @param npu_id - NPU ID in which to delete
 * @param ndi_range_id - NDI Range ID of ACL Range to be deleted.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_acl_range_delete(npu_id_t npu_id, ndi_obj_id_t ndi_range_id);


/**
 * @brief Retrieve existing ACL Slice usage information
 *
 * @param npu_id - NPU ID in which to retrieve
 * @param slice_id - NDI ID of ACL Slice to be retrieved.
 * @param[out] slice_attr - ACL Slice attribute information returned from NDI.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */

t_std_error ndi_acl_get_slice_attribute (npu_id_t npu_id, ndi_obj_id_t slice_id,
                                         ndi_acl_slice_attr_t *slice_attr);

/**
 * @brief Retrieve existing ACL Table usage information
 *
 * @param npu_id - NPU ID in which to retrieve
 * @param table_id - NDI ID of ACL Table to be retrieved.
 * @param[out] table_attr - ACL Table attribute information returned from NDI.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */

t_std_error ndi_acl_get_acl_table_attribute (npu_id_t npu_id, ndi_obj_id_t table_id,
                                             ndi_acl_table_attr_t *table_attr);

/**
 * \}
 */
#ifdef __cplusplus
}
#endif
#endif

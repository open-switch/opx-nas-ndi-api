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
 * filename: nas_ndi_mac.h
 */

#ifndef NAS_NDI_MAC_H_
#define NAS_NDI_MAC_H_

#include "std_error_codes.h"
#include "ds_common_types.h"
#include "nas_ndi_common.h"
#include "dell-base-l2-mac.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup NDI API - MAC Functionality
 *
 *  \{
 */


/**
 * @brief MAC entry type to determine which type of flooding domain it belongs to
 */
typedef enum{
    NDI_MAC_ENTRY_TYPE_1Q,              /** MAC entry belongs to VLAN aware flooding domain */
    NDI_MAC_ENTRY_TYPE_1D_LOCAL,        /** MAC entry belongs to 1D bridge and is local */
    NDI_MAC_ENTRY_TYPE_1D_REMOTE,       /** MAC entry belongs to 1D bridge and is remote */
}ndi_mac_entry_type_t;



/**
 * @brief MAC entry attributes flag to be used when updating the MAC address entry
 */
typedef enum {
    NDI_MAC_ENTRY_ATTR_TYPE=1,              /** MAC entry type static/dynamic */
    NDI_MAC_ENTRY_ATTR_PORT_ID,             /** Port ID associated with entry  */
    NDI_MAC_ENTRY_ATTR_PKT_ACTION,          /** Packet action when this MAC entry is hit */
    NDI_MAC_ENTRY_ATTR_ENDPOINT_IP,         /** Remote endpoint IP for MAC entry only
                                                applicable for NDI_MAC_ENTRY_TYPE_1D_REMOTE*/
    NDI_MAC_ENTRY_ATTR_MAX
} ndi_mac_attr_flags;


/**
 *@brief  MAC entry struct which contains attributes to create/update/delete
 *@brief  MAC address entries.
 *
 * Depending on the type of the mac_entry_type and the type of operation
 * (create/update/delete) some of the attributes are mandatory. Each function
 * lists the attributes which it is expecting
 */

typedef struct ndi_mac_entry_s {
    npu_id_t                    npu_id;          /** NPU ID */
    hal_vlan_id_t               vlan_id;         /** VLAN ID */
    ndi_port_t                  port_info;       /** NDI port (npu/local port) */
    hal_mac_addr_t              mac_addr;        /** MAC address */
    bool                        is_static;       /** Flag to determine static/dynamic */
    BASE_MAC_PACKET_ACTION_t    action;          /** Packet action */
    ndi_mac_attr_flags          attr_flag;       /** Attribute flag */
    uint64_t                    ndi_lag_id;      /** When MAC entry belongs to LAG */
    uint64_t                    bridge_id;       /** 1D Bridge ID */
    uint64_t                    endpoint_ip_port;/** Endpoint IP port */
    hal_ip_addr_t               endpoint_ip;     /** Remote end-point IP */
    ndi_mac_entry_type_t        mac_entry_type;  /** To indicate what type of MAC entry is being
                                                     programmed. Default is NDI_MAC_ENTRY_TYPE_1Q */
} ndi_mac_entry_t;


/**
 * @brief To determine MAC delete operation type
 */
typedef enum {
    NDI_MAC_DEL_SINGLE_ENTRY=1,        /** Delete single entry */
    NDI_MAC_DEL_BY_PORT,               /** Delete all the entries by port */
    NDI_MAC_DEL_BY_VLAN,               /** Delete all the entries by vlan */
    NDI_MAC_DEL_BY_PORT_VLAN,          /** Delete all the entries by port/vlan combination */
    NDI_MAC_DEL_BY_BRIDGE,             /** Delete all the entries by 1D bridge id */
    NDI_MAC_DEL_BY_BRIDGE_ENDPOINT_IP, /** Delete all the entries by vni */
    NDI_MAC_DEL_ALL_ENTRIES,           /** Delete all the entries */
    NDI_MAC_DEL_BY_PORT_VLAN_SUBPORT,  /** Delete all the entries by port vlan subport */
    NDI_MAC_DEL_INVALID_TYPE
} ndi_mac_delete_type_t;


/**
 *@brief To determine the MAC entry event type when MAC entry notification is
 *@brief given from below layer
 *
 */
typedef enum {
    NDI_MAC_EVENT_LEARNED   = 1,    /** New MAC entry learned */
    NDI_MAC_EVENT_AGED,             /** MAC entry aged */
    NDI_MAC_EVENT_FLUSHED,          /** MAC entry removed */
    NDI_MAC_EVENT_MOVED,            /** MAC entry moved */
    NDI_MAC_EVENT_INVALID
} ndi_mac_event_type_t;


/**
 * @brief Add a new MAC address entry into the MAC Table
 * @param entry - MAC address entry to be configured
 *
 * Mandatory attributes
 *
 * mac_entry_type                    attributes
 * NDI_MAC_ENTRY_TYPE_1Q             vlan_id,mac_addr and port_info/ndi_lag_id
 * NDI_MAC_ENTRY_TYPE_1D_LOCAL       bridge_id,mac_addr and port_info/ndi_lag_id
 * NDI_MAC_ENTRY_TYPE_1D_REMOTE      vni,mac_addr and endpoint_ip
 *
 * @return - STD_ERR_OK if operation is successful otherwise a different error code is returned.
 */
t_std_error ndi_create_mac_entry(ndi_mac_entry_t *entry);


/**
 * @brief Update existing MAC Address entry attributes
 * @param entry - MAC entry containing the key and new attributes that needs to be updated
 * @param attr_changed - flag to indicate which attribute in the MAC entry needs to be updated
 *
 * Mandatory attributes
 *
 * mac_entry_type                    attributes
 * NDI_MAC_ENTRY_TYPE_1Q             vlan_id,mac_addr
 * NDI_MAC_ENTRY_TYPE_1D_LOCAL       bridge_id,mac_addr
 * NDI_MAC_ENTRY_TYPE_1D_REMOTE      vni,mac_addr
 *
 * @return - STD_ERR_OK if operation is successful otherwise a different error code is returned.
 */
t_std_error ndi_update_mac_entry(ndi_mac_entry_t * entry, ndi_mac_attr_flags attr_changed);


/**
 * @brief Delete MAC entry/entries  based on delete_type flag
 * @param entry - MAC entry containing attributes to be deleted based on the delete_flag
 * @param delete_type - flag to indicate the type (single/port/port-vlan/vlan/bridge/vni/vni-ip/all)
 * @param type_set - flag to indicate whether all entries needs to be flushed under the type.
 *                   If this is not set all entries(static/dynamic) should be flushed.
 *
 * Mandatory attributes
 *
 * delete_type                        attributes
 * NDI_MAC_DEL_SINGLE_ENTRY           mac_addr/vlan_id,mac_addr/bridge_id
 * NDI_MAC_DEL_BY_PORT,               port_info
 * NDI_MAC_DEL_BY_VLAN,               vlan_id
 * NDI_MAC_DEL_BY_PORT_VLAN           port_info/vlan_id
 * NDI_MAC_DEL_BY_BRIDGE              bridge_id
 * NDI_MAC_DEL_BY_BRIDGE_ENDPOINT_IP  bridge_id/endpoint ip
 * NDI_MAC_DEL_ALL_ENTRIES            none
 *
 * @return - STD_ERR_OK if operation is successful otherwise a different error code is returned.
 */
t_std_error ndi_delete_mac_entry(ndi_mac_entry_t *entry, ndi_mac_delete_type_t delete_type, bool type_set);


/**
 * @brief   MAC entry event notification callback function type
 * @param   npu_id NPU ID
 * @param   ndi_mac_event_type_t event type
 * @param   ndi_mac_entry_t MAC entry details
 * @return  None
 */
typedef void (*ndi_mac_event_notification_fn) (npu_id_t npu_id, ndi_mac_event_type_t mac_event, ndi_mac_entry_t *mac_entry, bool is_lag_index);


/**
 * @brief This function is used to register the callback function for MAC event notification with NDI
 * @param reg_fn - Callback function for MAC event notification
 * @return STD_ERR_OK if operation is successful otherwise a different error code is returned.
 */
t_std_error ndi_mac_event_notify_register(ndi_mac_event_notification_fn reg_fn);


/**
 * @brief Retrieve the MAC entry
 * @param mac_entry - Caller to fill up the mandatory fields into this entry
 *                    i.e. npu_id, vlan_id, mac_addr
 *                    This entry will be filled up with further details after successful execution
 *                    i.e. port_id, action, is_static
 * @return STD_ERR_OK if operation is successful otherwise a different error code is returned.
 */
t_std_error ndi_get_mac_entry_attr(ndi_mac_entry_t *mac_entry);


/**
 * @deprecated - This method is deprecated and should not be used.
 * @brief This is an empty function which shall be removed.
 */
t_std_error ndi_set_mac_entry_attr(ndi_mac_entry_t *mac_entry);

/**
 *  \}
 */
#ifdef __cplusplus
}
#endif
#endif /* NAS_NDI_MAC_H_ */

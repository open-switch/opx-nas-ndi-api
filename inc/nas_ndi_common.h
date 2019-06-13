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
 * filename: nas_ndi_common.h
 */


#ifndef __NAS_NDI_COMMON_H
#define __NAS_NDI_COMMON_H

#include "std_error_codes.h"
#include "stddef.h"
#include "std_type_defs.h"
#include "ds_common_types.h"
#include "nas_types.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup NDICOMMON NDI DEFS - NAS NDI Common definitions
 *
 *  \{
 */

#define NDI_VLAN_TPID 0x8100
#define NDI_GRE_TYPE 0x88BE
#define NDI_TTL 255
#define NDI_IPV4_VERSION 4
#define NDI_IPV6_VERSION 6

/*
 * ndi_stat_id represents the ids statistics id defined in dell-base-statisctis.h
 * which is of type BASE_STATS_INTERFACE_t, BASE_STATS_VLAN_t,
 * BASE_STATS_INTERFACE_IP_t,BASE_STATS_INTERFACE_ETHER_t,
 * BASE_STATS_INTERFACE_ETHER_IN_t,BASE_STATS_INTERFACE_ETHER_OUT_t,
 * BASE_STATS_INTERFACE_IF_t
 */
typedef uint64_t ndi_stat_id_t;
typedef uint64_t bridge_id_t;

/**
 * @class NDI Switch operational Status
 */

typedef enum _ndi_switch_oper_status_t
{
   NDI_SWITCH_OPER_UNKNOWN,
   NDI_SWITCH_OPER_UP,
   NDI_SWITCH_OPER_DOWN,
   NDI_SWITCH_OPER_FAILED,
} ndi_switch_oper_status_t;

typedef enum _ndi_bridge_packets_type
{
    NDI_BRIDGE_PKT_UNICAST,
    NDI_BRIDGE_PKT_MULTICAST,
    NDI_BRIDGE_PKT_BROADCAST,
    NDI_BRIDGE_PKT_ALL
} ndi_bridge_packets_type_t;


typedef enum nas_1d_param
{
    VRF_OID,
    UNDERLAY_OID,
    BRIDGE_OID,
} nas_1d_param_t;

/**
 * Type of packets that would be discarded by NPU port
 */
typedef enum {
    NDI_PORT_DROP_UNTAGGED,     /* Port will discard all untagged packets */
    NDI_PORT_DROP_TAGGED        /* Port will discard all tagged packets */
} ndi_port_drop_mode_t;



typedef enum ndi_port_type{
    ndi_port_type_PORT=1,
    ndi_port_type_LAG,
}ndi_port_type_t;

/* Common typedef for passing id-value pair */
typedef struct entry {
    nas_attr_id_t attr_id;
    void *val;
    size_t vlen;
} nas_com_id_value_t;

typedef struct nas_custom_id_value {
    nas_1d_param_t attr_id;
    void *val;
    size_t vlen;
} nas_custom_id_value_t;

/**
 * @class NDI Port operational Status
 */
typedef enum _ndi_port_oper_status_t {
   ndi_port_OPER_UP,
   ndi_port_OPER_DOWN,
   ndi_port_OPER_FAIL,
   ndi_port_OPER_TESTING,
} ndi_port_oper_status_t;

typedef struct _ndi_intf_link_state_t {
    ndi_port_oper_status_t oper_status;
} ndi_intf_link_state_t;

typedef enum _ndi_port_event_t {
    ndi_port_ADD,
    ndi_port_DELETE,
} ndi_port_event_t;
/**
 * @class NDI type to represent a system-wide physical port
 */
typedef struct _ndi_port_t {
    npu_id_t      npu_id; // System wide NPU ID
    npu_port_t    npu_port; // port id local to each NPU
} ndi_port_t;

/**
 * @class NDI type to represent a list of system-wide physical ports
 */
typedef struct _ndi_port_list {
    size_t          port_count;
    ndi_port_t*     port_list;
} ndi_port_list_t;

/**
 * @brief NDI type to represent List of NDI Object IDs.
 */
typedef struct _ndi_obj_id_list {
    size_t          count;
    ndi_obj_id_t*   list;
} ndi_obj_id_list_t;

typedef struct _ndi_byte_list {
    size_t      byte_count;
    uint8_t     *byte_list;
} ndi_byte_list_t;

/**
 * @class NDI PAcket Attribute, These will be obsolete in next phase
 */
typedef enum _ndi_packet_trap_id_t{
    NDI_PACKET_TRAP_ID_DEFAULT = 0,

    NDI_PACKET_TRAP_ID_SAMPLEPACKET = 1,
    NDI_PACKET_TRAP_ID_L3_MTU_ERROR = 2,

    NDI_PACKET_TRAP_ID_MAX,
} ndi_packet_trap_id_t;

typedef struct vrf_underlay_rif {
    ndi_obj_id_t vrf_oid;
    ndi_obj_id_t underlay_rif_id;
} vrf_underlay_rif_t;


/**
 * @class NDI packet transmit type
 */
typedef enum _ndi_packet_tx_type_t {
    /** bypass switch ASIC processing pipeline,
     * tx packet goes to the specified output port directly */
    NDI_PACKET_TX_TYPE_PIPELINE_BYPASS,
    /** tx packet goes to the switch ASIC processing pipeline to decide the output port */
    NDI_PACKET_TX_TYPE_PIPELINE_LOOKUP,
    /* tx packet goes to the switch ASIC and floods on the .1d bridge using L2MC */
    NDI_PACKET_TX_TYPE_PIPELINE_HYBRID_BRIDGE
}ndi_packet_tx_type_t;


typedef struct _ndi_packet_attr{

/** NPU Id for the packet rx/tx */
    npu_id_t npu_id;

/** Port on which the packet was received */
    npu_port_t rx_port;

/** Destination port for packet to be transmitted to. */
    npu_port_t tx_port;

/** Trap ID */
    ndi_obj_id_t trap_id;

/** packet transmit type. (MANDATORY_ON_SEND) */
    ndi_packet_tx_type_t tx_type;

    bridge_id_t bridge_id;
} ndi_packet_attr_t;

typedef struct _hwport_list_t {
    uint32_t count;
    uint32_t *list;
} hwport_list_t;


typedef struct nas_attribute_t {
    nas_attr_id_t    id;
    void *data;
    size_t len;
} nas_attribute_t;

typedef enum {
    NAS_NDI_VLAN_MCAST_LOOKUP_KEY_MACDA,
    NAS_NDI_VLAN_MCAST_LOOKUP_KEY_XG,
    NAS_NDI_VLAN_MCAST_LOOKUP_KEY_SG,
    NAS_NDI_VLAN_MCAST_LOOKUP_KEY_XG_AND_SG
} ndi_vlan_mcast_lookup_key_type_t;

typedef enum {
    /* Read only */
    NAS_NDI_STATS_MODE_READ,
    /* Read and clear */
    NAS_NDI_STATS_MODE_READ_AND_CLEAR,

    /* Sync h/w counters(realtime)*/
    NAS_NDI_STATS_MODE_SYNC,

    /* Sync h/w counters(realtime) and read */
    NAS_NDI_STATS_MODE_SYNC_AND_READ,
} ndi_stats_mode_t;

/** callback functions */

/**
 * @brief   Switch shutdown request callback types. NAS can register
 * @param   npu_id NPU ID
 * @return  None
 */
typedef void (*ndi_switch_shutdown_request_fn) (npu_id_t npu_id);

/**
 * @brief   Port operational status update callback types.  NAS can register
 * @param   npu_id NPU ID
 * @param   port_id NPU port Id
 * @param   link_state port link state
 * @return  None
 */
typedef void (*ndi_port_oper_status_change_fn) (npu_id_t npu_id, npu_port_t port_id, ndi_intf_link_state_t *link_state );

/**
 * @brief   Port ADD and DELETE event update callback type. NAS can register
 * @param   ndi_port NPU ID and port id
 * @param   port add/delete event pointer
 * @param   hwport hwport mapped to the ndi port
 * @return  None
 */
typedef void (*ndi_port_event_update_fn) (ndi_port_t  *ndi_port, ndi_port_event_t event, uint32_t hwport);

/**
 * @brief This is the function prototype to receive an etherframe from the NDI layer
 * @param pkt    - the data to receive
 * @param len    - length
 * @param p_attr - packet attribute list
 * @return standard error
 */
typedef t_std_error (*ndi_packet_rx_type)(uint8_t *pkt, uint32_t len, ndi_packet_attr_t *p_attr);


/*!
 *  Function to transmit packet via NPU
 *  \param[in]  buf    - packet buffer to transmit
 *  \param[in]  len    - length of packet
 *  \param[in]  p_attr - packet attribute list
 *  \return     std_error
 */
t_std_error ndi_packet_tx (uint8_t* buf, uint32_t len, ndi_packet_attr_t *p_attr);

/**
 * @brief register a callback with the NDI layer
 * @param reg_fun the function that will handle the received packets
 * @return standard error
 */
t_std_error ndi_packet_rx_register(ndi_packet_rx_type reg_fun);

/**
 *  \}
 */

#ifdef __cplusplus
}
#endif

#endif

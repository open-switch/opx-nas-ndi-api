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
 * nas_ndi_1d_bridge.h
 */

#ifndef _NAS_NDI_BRIDGE_D_H_
#define _NAS_NDI_BRIDGE_D_H_

#include "nas_ndi_common.h"
#include "nas_ndi_stg.h"
#include "dell-base-if-phy.h"

#ifdef __cplusplus
extern "C"{
#endif


/**
 * @brief Create vlan unaware bridge 1d
 *
 * @param[in] npu_id - NPU ID
 *
 * @param[out] br_oid - created bridge id.
 *
 * @return STD_ERR_OK if operation is successful otherwise
 *  error code is returned.
 */

t_std_error ndi_create_bridge_1d(npu_id_t npu_id, bridge_id_t *br_oid);


/**
 * @brief Delate vlan unaware bridge 1d
 *
 * @param[in] npu_id - NPU ID
 *
 * @param[in] br_oid - bridge id.
 *
 * @return STD_ERR_OK if operation is successful otherwise
 *  error code is returned.
 */

t_std_error ndi_delete_bridge_1d(npu_id_t npu_id, bridge_id_t br_oid);


/**
 * @brief Gets Bridge Statistics
 *
 * @param[in] npu_id - NPU ID
 *
 * @param[in] br_oid - SAI Bridge Object ID
 *
 * @param[in] stats - array of Bridge counter ids
 *
 * @param[out] stats_val - statistics counter values
 *
 * @param[in] len - number of statistics to be queried
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */

t_std_error ndi_bridge_1d_stats_get(npu_id_t npu_id, bridge_id_t br_oid, ndi_stat_id_t *stats, uint64_t* stats_val, size_t len);

/**
 * @brief Clear Bridge statistics for a give bridge object id
 *
 * @param[in] npu_id - NPU ID
 *
 * @param[in] br_oid - SAI Bridge Object ID
 *
 * @param[in] stats - array of Bridge counter IDs
 *
 * @param[in] len - number of statistics to be cleared
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */

t_std_error ndi_bridge_1d_stats_clear(npu_id_t npu_id, bridge_id_t br_oid, ndi_stat_id_t *stats, size_t len);


/**
 * @brief Gets Bridge Port Statistics
 *
 * @param[in] npu_id - NPU ID
 *
 * @param port- npu port to get stats
 *
 * @param vlan_id - Vlan ID associated with the bridge port.
 *
 * @param[in] ndi_stat_ids - array of Bridge counter ids
 *
 * @param[out] stats_val - statistics counter values
 *
 * @param[in] len - number of statistics to be queried
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_bridge_port_stats_get(npu_id_t npu_id, npu_port_t port, hal_vlan_id_t vlan_id, ndi_stat_id_t *ndi_stat_ids, uint64_t* stats_val, size_t len);


/**
 * @brief Clear Bridge Port Statistics for a bridge port of given port and vlan id
 *
 * @param[in] npu_id - NPU ID
 *
 * @param port- npu port of the bridge port
 *
 * @param vlan_id - Vlan ID associated with the bridge port.
 *
 * @param[in] ndi_stat_ids - array of Bridge counter IDs
 *
 * @param[in] len - number of statistics to be cleared
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_bridge_port_stats_clear(npu_id_t npu_id, npu_port_t port, hal_vlan_id_t vlan_id,
                                        ndi_stat_id_t *ndi_stat_ids, size_t len);

/**
 * @brief Gets Bridge Port Lag Statistics
 *
 * @param[in] npu_id - NPU ID
 *
 * @param lag_id - lag ID  to be added
 *
 * @param vlan_id - Vlan ID associated with the lag.
 *
 * @param[in] ndi_stat_ids - array of Bridge counter ids
 *
 * @param[out] stats_val - statistics counter values
 *
 * @param[in] len - number of statistics to be queried
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_lag_bridge_port_stats_get(npu_id_t npu_id, ndi_lag_id_t ndi_lag_id, hal_vlan_id_t vlan_id, ndi_stat_id_t *ndi_stat_ids, uint64_t* stats_val, size_t len);

/**
 * @brief Clear Bridge Port Statistics for a bridge port of given lag and vlan id
 *
 * @param[in] npu_id - NPU ID
 *
 * @param ndi_lag_id - LAG Id of the bridge port
 *
 * @param vlan_id - VLAN ID associated with the bridge port.
 *
 * @param[in] ndi_stat_ids - array of Bridge counter IDs
 *
 * @param[in] len - number of statistics to be cleared
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_lag_bridge_port_stats_clear(npu_id_t npu_id, ndi_lag_id_t ndi_lag_id, hal_vlan_id_t vlan_id,
                                            ndi_stat_id_t *ndi_stat_ids, size_t len);

/**
 * @brief Gets Bridge Port tunnel Statistics
 *
 * @param[in] npu_id - NPU ID
 *
 * @param[in] bridge_oid - bridge ID
 *
 * @param[in] tunnel_params - combination of name value pair excepting tunnel config params like Src IP, Dest IP, vni
 *
 * @param[in] tp_len - number of tunnel_params
 *
 * @param[in] ndi_stat_ids - array of Bridge counter ids
 *
 * @param[out] stats_val - statistics counter values
 *
 * @param[in] len - number of statistics to be queried
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_tunnel_bridge_port_stats_get(npu_id_t npu_id, nas_bridge_id_t bridge_oid, nas_com_id_value_t tunnel_params[], size_t tp_len, ndi_stat_id_t *ndi_stat_ids, uint64_t* stats_val, size_t len);

/**
 * @brief Gets Tunnel Statistics
 *
 * @param[in] npu_id - NPU ID
 *
 * @param[in] tunnel_params - combination of name value pair excepting tunnel config params like Src IP, Dest IP, vni
 *
 * @param[in] tp_len - number of tunnel_params
 *
 * @param[in] ndi_stat_ids - array of Bridge counter ids
 *
 * @param[out] stats_val - statistics counter values
 *
 * @param[in] len - number of statistics to be queried
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_tunnel_stats_get(npu_id_t npu_id, nas_com_id_value_t tunnel_params[], size_t tp_len, ndi_stat_id_t *ndi_stat_ids, uint64_t* stats_val, size_t len);

/**
 * @brief Clear Tunnel Statistics for a given tunnel
 *
 * @param[in] npu_id - NPU ID
 *
 * @param[in] tunnel_params - tunnel local IP Address (  attr_id : TUNNEL_CLEAR_TUNNEL_STATS_INPUT_LOCAL_IP_ADDR,
 *                                                       val     : hal_ip_addr_t structure)
 *                          - tunnel remote IP Address ( attr_id : TUNNEL_CLEAR_TUNNEL_STATS_INPUT_remote_IP_ADDR,
 *                                                       val     : hal_ip_addr_t structure)
 *
 * @param[in] tp_len - number of tunnel_params
 *
 * @param[in] ndi_stat_ids - array of Bridge counter IDs to be cleared
 *
 * @param[in] len - number of statistics to be cleared
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_tunnel_stats_clear(npu_id_t npu_id, nas_com_id_value_t tunnel_params[], size_t tp_len,
                                   ndi_stat_id_t *ndi_stat_ids, size_t len);

/**
 * @brief Add ports to 1d bridge
 *
 * @param npu_id - NPU ID
 *
 * @param br_oid - bridge id.
 *
 * @param port- npu port to be added
 *
 * @param vlan_id - Vlan ID associated with the port.(P,V)
 *
 * @param tag -True if the port is tagged.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */

t_std_error ndi_1d_bridge_member_port_add(npu_id_t npu_id, bridge_id_t br_oid , npu_port_t port, hal_vlan_id_t  vlan_id, bool tag);


/**
 * @brief Delete port from 1d bridge.
 *
 * @param npu_id - NPU ID
 *
 * @param port- npu port to be deleted
 *
 * @param vlan_id - Vlan ID associated with the port.(P,V)
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */

t_std_error ndi_1d_bridge_member_port_delete(npu_id_t npu_id, npu_port_t port, hal_vlan_id_t  vlan_id);


/**
 * @brief Add lag to 1d bridge
 *
 * @param npu_id - NPU ID
 *
 * @param br_oid - bridge id.
 *
 * @param lag_id - lag ID  to be added
 *
 * @param vlan_id - Vlan ID associated with the lag.
 *
 * @param tag - True if the lag is tagged.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */

t_std_error ndi_1d_bridge_member_lag_add(npu_id_t npu_id, bridge_id_t br_oid , ndi_lag_id_t lag_id, hal_vlan_id_t  vlan_id, bool tag);


/**
 * @brief Delete lag from 1d bridge.
 *
 * @param npu_id - NPU ID
 *
 * @param lag_id - lag_id of the lag to be removed from 1d bridge
 *
 * @param vlan_id - Vlan ID associated with the lag.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */

t_std_error ndi_1d_bridge_member_lag_delete(npu_id_t npu_id, ndi_lag_id_t lag_id, hal_vlan_id_t  vlan_id);

/**
 * @brief Create underlay rif.
 *
 * @param npu_id[in] - NPU ID
 *
 * @param underlay_rif_oid[out]- OID of underlay_rif created.
 *
 * @param vr_oid[in] -Virtual router id.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */


t_std_error ndi_create_underlay_rif(npu_id_t npu_id, ndi_obj_id_t *underlay_rif_oid, ndi_obj_id_t vr_oid);


/**
 * @brief Add remote end point.
 *
 * @param[in] npu_id - NPU ID
 *
 * @param[in] bridge_oid - bridge ID
 *
 * @param[in] tunnel_params - combination of name value pair accepting tunnel config params like Src IP, Dest IP, vni using CPS attribute
 *
 * @param[in] len - number of tunnel_params
 *
 * @param[in]  cus_param - name value pair to send bridge, vrf and rif oid  .
 *
 *@param[out] cus_len - number of cus_params
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */


t_std_error nas_ndi_add_remote_endpoint(npu_id_t npu_id, nas_com_id_value_t tunnel_params[], size_t len,
nas_custom_id_value_t cus_param[], size_t cus_len, ndi_obj_id_t *tun_brport_oid);

/**
 * @brief Delete remote end point.
 *
 * @param[in] npu_id - NPU ID
 *
 * @param[in] bridge_oid - bridge ID
 *
 * @param[in] tunnel_params - combination of name value pair excepting tunnel config params like Src IP, Dest IP, vni
 *
 * @param[in] len - number of tunnel_params
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */


t_std_error nas_ndi_remove_remote_endpoint(npu_id_t npu_id, nas_bridge_id_t bridge_oid, nas_com_id_value_t tunnel_params[], size_t len);

/**
 * @brief flood control on 1d bridge for unknown dest mac Packet.
 *
 * @param[in] npu_id - NPU ID
 *
 * @param[in] bridge_oid - bridge ID
 *
 * @param[in] multicast_grp - L2MC group of the bridge.
 *
 * @param[in] pkt_type - packet types : unicast, multicast, broadcast or all
 *
 * @param[in] enable_flood- enable  flooding of the unknown packets in 1d BRIDGE.
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */

t_std_error ndi_flood_control_1d_bridge(npu_id_t npu_id, ndi_obj_id_t br_oid,  ndi_obj_id_t multicast_grp,
           ndi_bridge_packets_type_t pkt_type, bool enable_flood);

/**
 * @breif Set the tunnel bridge port's MAC Learning Mode.
 *
 * @param[in] npu_id - NPU ID
 *
 * @param[in] tun_brport - tunnel bridge port  ID
 *
 * @param[in] mode -  MAC learn mode to be set for tunnel bridge port
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 */
t_std_error ndi_tunport_mac_learn_mode_set(npu_id_t npu_id, ndi_obj_id_t tun_brport,
                                        BASE_IF_PHY_MAC_LEARN_MODE_t mode);



/**
 * @brief Set the attributes for bridge sub port
 *
 * @param[in] npu_id - NPU ID
 *
 * @param[in] port_id - Port ID which could be physical port id or lag object id
 *
 * @param[in] port_type -  Port type which is of type ndi_port_type_t
 *
 * @param[in] vlan_id - VLAN ID of the sub port
 *
 * @param[in] attribute_key_val - array of attribute id (key) and its value
 *
 * Following attributes are supported currently
 *
 * Attribute Id                                 type
 * DELL_IF_IF_INTERFACES_INTERFACE_MAC_LEARN -  BASE_IF_MAC_LEARN_MODE_t (uint32_t)
 *
 *
 * @param[in] key_val_size - size of the attribute_key_val array
 *
 * @return STD_ERR_OK if operation is successful otherwise a different
 *  error code is returned.
 *
 */

t_std_error ndi_bridge_sub_port_attr_set(npu_id_t npu_id, ndi_obj_id_t port_id,ndi_port_type_t port_type,
                                         hal_vlan_id_t vlan_id,
                                         nas_com_id_value_t attribute_key_val[], size_t key_val_size);

#ifdef __cplusplus
}
#endif

#endif  /*   _NAS_NDI_BRIDGE_D_H_*/

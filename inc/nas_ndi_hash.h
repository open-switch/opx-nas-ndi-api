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
 * nas_ndi_hash.h
 */

#ifndef _NAS_NDI_HASH_H
#define _NAS_NDI_HASH_H

#include "std_error_codes.h"

#ifdef __cplusplus
extern "C"{
#endif

t_std_error nas_ndi_create_all_hash_objects (void);
t_std_error nas_ndi_set_hash_obj (uint64_t object_id, uint32_t nr_hash_fields,
                                  uint32_t *hash_fields);
t_std_error nas_ndi_get_hash (uint64_t object_id, uint32_t *nr_hash_fields,
                              uint32_t *hash_fields);

#ifdef __cplusplus
}
#endif



#endif

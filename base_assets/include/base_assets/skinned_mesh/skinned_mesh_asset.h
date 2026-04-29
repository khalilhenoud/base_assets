/**
 * @file skinned_mesh_asset.h
 * @author khalilhenoud@gmail.com
 * @brief
 * @version 0.1
 * @date 2026-04-22
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef SKINNED_MESH_ASSET_H
#define SKINNED_MESH_ASSET_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <base_assets/internal/module.h>
#include <base_assets/mesh/mesh_asset.h>
#include <library/asset/types.h>
#include <library/containers/cvector.h>
#include <library/string/cstring.h>
#include <math/matrix4f.h>


////////////////////////////////////////////////////////////////////////////////
//| skinned_asset_t, '*' = skinned_mesh_asset
//|=============================================================================
//| OPERATION                   | SUPPORTED
//|=============================================================================
//|    *_def                    | YES
//|    *_is_def                 | YES
//|    *_replicate              |
//|    *_fullswap               |
//|    *_serialize              | YES
//|    *_deserialize            | YES
//|    *_hash                   |
//|    *_is_equal               |
//|    *_type_size              | YES
//|    *_type_alignment         |
//|    *_type_id_count          |
//|    *_type_ids               |
//|    *_owns_alloc             | YES
//|    *_get_alloc              | YES
//|    *_cleanup                | YES
//|    *_get_dir                | YES
//|    *_get_loader             | YES
//|    *_get_deloader           | YES
//|    *_type_asset_count       | YES
//|    *_type_get_assets        | YES
//|    *_is_asset_type          | YES
////////////////////////////////////////////////////////////////////////////////

typedef struct allocator_t allocator_t;
typedef struct binary_stream_t binary_stream_t;

typedef
struct skeleton_node_t {
  cstring_t name;               // corresponds to a bone, unless it is a helper
  matrix4f transform;
  cvector_t children;           // uint32_t, index into skeleton_t
  uint32_t bone_index;          // uint32_t max means it is invalid
} skeleton_node_t;

// NOTE: for simplicity, I am currently not treating this as a separate type
typedef
struct skeleton_asset_t {
  cvector_t nodes;              // skeleton_node_t
} skeleton_asset_t;

typedef
struct skeleton_bone_t {
  cstring_t name;
  matrix4f offset_matrix;       // mesh to bone local space
} skeleton_bone_t;

// TODO: compress these!
typedef
struct bone_id_weight_t {
  uint32_t id[8];
  float weight[8];
} bone_id_weight_t;

// NOTE: for simplicity, I am not treating mesh as a detached asset file
typedef
struct skinned_mesh_asset_t {
  mesh_asset_t mesh;
  cvector_t bones;
  skeleton_asset_t skeleton;
  cvector_t vertex_to_bones;         // cvector_t of bone_id_weight_t
} skinned_mesh_asset_t;

BASE_ASSETS_API
void
skinned_mesh_asset_def(void *ptr);

BASE_ASSETS_API
uint32_t
skinned_mesh_asset_is_def(const void *ptr);

BASE_ASSETS_API
void
skinned_mesh_asset_serialize(
  const void *src,
  binary_stream_t *stream);

BASE_ASSETS_API
void
skinned_mesh_asset_deserialize(
  void *dst,
  const allocator_t *allocator,
  binary_stream_t* stream);

BASE_ASSETS_API
size_t
skinned_mesh_asset_type_size(void);

BASE_ASSETS_API
uint32_t
skinned_mesh_asset_owns_alloc(void);

BASE_ASSETS_API
const allocator_t *
skinned_mesh_asset_get_alloc(const void *ptr);

BASE_ASSETS_API
void
skinned_mesh_asset_cleanup(
  void *ptr,
  const allocator_t *allocator);

BASE_ASSETS_API
const char *
skinned_mesh_asset_get_dir(void);

BASE_ASSETS_API
loader_t
skinned_mesh_asset_get_loader(void);

BASE_ASSETS_API
deloader_t
skinned_mesh_asset_get_deloader(void);

BASE_ASSETS_API
uint32_t
skinned_mesh_asset_type_asset_count(const void *src);

BASE_ASSETS_API
void
skinned_mesh_asset_type_get_assets(const void *src, const asset_ref_t *refs[]);

BASE_ASSETS_API
uint32_t
skinned_mesh_asset_is_asset_type(void);

#ifdef __cplusplus
}
#endif

#endif
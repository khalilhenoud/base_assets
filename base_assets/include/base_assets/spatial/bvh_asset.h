/**
 * @file bvh_asset.h
 * @author khalilhenoud@gmail.com
 * @brief
 * @version 0.1
 * @date 2026-04-29
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef BVH_ASSET_H
#define BVH_ASSET_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <base_assets/internal/module.h>
#include <library/asset/types.h>
#include <library/containers/cvector.h>
#include <math/vector3f.h>


////////////////////////////////////////////////////////////////////////////////
//| bvh_asset_t, '*' = bvh_asset
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
struct bvh_aabb_t {
  point3f min_max[2];
} bvh_aabb_t;

// NOTE: left_first meaning depends on the tri_count. If tri_count is 0, the
// node is an interior node and left_first will be an offset into the node
// array, otherwise we are dealing with a leaf and left_first will be an offset
// into the triangle array.
typedef
struct bvh_node_t {
  bvh_aabb_t bounds;
  uint32_t left_first, tri_count;
} bvh_node_t;

// NOTE: the max size of node array is max: 2 * (count + 1) - 1.
// We also allocate an extra unused node that is left unused so we can adhere to
// cache alignment in the future.
typedef
struct bvh_asset_t {
  cvector_t faces;          // face_t
  cvector_t normals;        // vector3f
  cvector_t bounds;         // bhv_aabb_t
  cvector_t nodes;          // bvh_node_t
} bvh_asset_t;

BASE_ASSETS_API
void
bvh_asset_def(void *ptr);

BASE_ASSETS_API
uint32_t
bvh_asset_is_def(const void *ptr);

BASE_ASSETS_API
void
bvh_asset_serialize(
  const void *src,
  binary_stream_t *stream);

BASE_ASSETS_API
void
bvh_asset_deserialize(
  void *dst,
  const allocator_t *allocator,
  binary_stream_t* stream);

BASE_ASSETS_API
size_t
bvh_asset_type_size(void);

BASE_ASSETS_API
uint32_t
bvh_asset_owns_alloc(void);

BASE_ASSETS_API
const allocator_t *
bvh_asset_get_alloc(const void *ptr);

BASE_ASSETS_API
void
bvh_asset_cleanup(
  void *ptr,
  const allocator_t *allocator);

BASE_ASSETS_API
const char *
bvh_asset_get_dir(void);

BASE_ASSETS_API
loader_t
bvh_asset_get_loader(void);

BASE_ASSETS_API
deloader_t
bvh_asset_get_deloader(void);

BASE_ASSETS_API
uint32_t
bvh_asset_type_asset_count(const void *src);

BASE_ASSETS_API
void
bvh_asset_type_get_assets(const void *src, const asset_ref_t *refs[]);

BASE_ASSETS_API
uint32_t
bvh_asset_is_asset_type(void);

#ifdef __cplusplus
}
#endif

#endif
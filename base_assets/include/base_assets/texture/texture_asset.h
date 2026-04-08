/**
 * @file texture_asset.h
 * @author khalilhenoud@gmail.com
 * @brief
 * @version 0.1
 * @date 2023-09-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef SCENE_TEXTURE_H
#define SCENE_TEXTURE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <base_assets/internal/module.h>
#include <library/string/cstring.h>


////////////////////////////////////////////////////////////////////////////////
//| texture_asset_t, '*' = texture
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

// TODO: replace with the content of texture_runtime_t
typedef
struct texture_asset_t {
  cstring_t path;
} texture_asset_t;

BASE_ASSETS_API
void
texture_asset_def(void *ptr);

BASE_ASSETS_API
uint32_t
texture_asset_is_def(const void *ptr);

BASE_ASSETS_API
void
texture_asset_serialize(
  const void *src,
  binary_stream_t *stream);

BASE_ASSETS_API
void
texture_asset_deserialize(
  void *dst,
  const allocator_t *allocator,
  binary_stream_t* stream);

BASE_ASSETS_API
size_t
texture_asset_type_size(void);

BASE_ASSETS_API
uint32_t
texture_asset_owns_alloc(void);

BASE_ASSETS_API
const allocator_t *
texture_asset_get_alloc(const void *ptr);

BASE_ASSETS_API
void
texture_asset_cleanup(
  void *ptr,
  const allocator_t *allocator);

////////////////////////////////////////////////////////////////////////////////
// TODO: REMOVE
BASE_ASSETS_API
void
texture_asset_setup(
  texture_asset_t *texture,
  const char *path,
  const allocator_t* allocator);

#ifdef __cplusplus
}
#endif

#endif
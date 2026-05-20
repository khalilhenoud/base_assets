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
#ifndef TEXTURE_ASSET_H
#define TEXTURE_ASSET_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <acsu/internal/module.h>
#include <library/asset/types.h>
#include <library/containers/cvector.h>


////////////////////////////////////////////////////////////////////////////////
//| texture_asset_t, '*' = texture_asset
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
enum texture_format_t {
  TEXTURE_FORMAT_RGBA,
  TEXTURE_FORMAT_BGRA,
  TEXTURE_FORMAT_RGB,
  TEXTURE_FORMAT_BGR,
  TEXTURE_FORMAT_LA,             // luminance/alpha
  TEXTURE_FORMAT_L,
  TEXTURE_FORMAT_A,
  TEXTURE_FORMAT_COUNT
} texture_format_t;

typedef
struct texture_asset_t {
  uint32_t width;
  uint32_t height;
  texture_format_t format;
  cvector_t buffer;
} texture_asset_t;

ACSU_API
void
texture_asset_def(void *ptr);

ACSU_API
uint32_t
texture_asset_is_def(const void *ptr);

ACSU_API
void
texture_asset_serialize(
  const void *src,
  binary_stream_t *stream);

ACSU_API
void
texture_asset_deserialize(
  void *dst,
  const allocator_t *allocator,
  binary_stream_t* stream);

ACSU_API
size_t
texture_asset_type_size(void);

ACSU_API
uint32_t
texture_asset_owns_alloc(void);

ACSU_API
const allocator_t *
texture_asset_get_alloc(const void *ptr);

ACSU_API
void
texture_asset_cleanup(
  void *ptr,
  const allocator_t *allocator);

ACSU_API
const char *
texture_asset_get_dir(void);

ACSU_API
loader_t
texture_asset_get_loader(void);

ACSU_API
deloader_t
texture_asset_get_deloader(void);

ACSU_API
uint32_t
texture_asset_type_asset_count(const void *src);

ACSU_API
void
texture_asset_type_get_assets(const void *src, const asset_ref_t *refs[]);

ACSU_API
uint32_t
texture_asset_is_asset_type(void);

#ifdef __cplusplus
}
#endif

#endif
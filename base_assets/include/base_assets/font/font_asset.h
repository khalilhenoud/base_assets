/**
 * @file font_asset.h
 * @author khalilhenoud@gmail.com
 * @brief
 * @version 0.1
 * @date 2026-04-26
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef FONT_ASSET_H
#define FONT_ASSET_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <base_assets/internal/module.h>
#include <base_assets/texture/texture_asset.h>
#include <library/asset/types.h>

#define FONT_ASSET_MAX_GLYPH_COUNT 256


////////////////////////////////////////////////////////////////////////////////
//| font_asset_t, '*' = font_asset
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
typedef float glyph_bounds_t[6];

typedef
struct glyph_data_t {
  uint32_t x, y;
  uint32_t width;
  uint32_t width_offset;
} glyph_data_t;

// NOTE: we are embedding the texture asset for simplicity.
typedef
struct font_asset_t {
  texture_asset_t texture;
  uint32_t texture_width, texture_height;
  uint32_t cell_width, cell_height;
  uint32_t font_width, font_height;
  uint32_t start_char;

  glyph_data_t glyphs[FONT_ASSET_MAX_GLYPH_COUNT];
  glyph_bounds_t bounds[FONT_ASSET_MAX_GLYPH_COUNT];
} font_asset_t;

BASE_ASSETS_API
void
font_asset_def(void *ptr);

BASE_ASSETS_API
uint32_t
font_asset_is_def(const void *ptr);

BASE_ASSETS_API
void
font_asset_serialize(
  const void *src,
  binary_stream_t *stream);

BASE_ASSETS_API
void
font_asset_deserialize(
  void *dst,
  const allocator_t *allocator,
  binary_stream_t* stream);

BASE_ASSETS_API
size_t
font_asset_type_size(void);

BASE_ASSETS_API
uint32_t
font_asset_owns_alloc(void);

BASE_ASSETS_API
const allocator_t *
font_asset_get_alloc(const void *ptr);

BASE_ASSETS_API
void
font_asset_cleanup(
  void *ptr,
  const allocator_t *allocator);

BASE_ASSETS_API
const char *
font_asset_get_dir(void);

BASE_ASSETS_API
loader_t
font_asset_get_loader(void);

BASE_ASSETS_API
deloader_t
font_asset_get_deloader(void);

BASE_ASSETS_API
uint32_t
font_asset_type_asset_count(const void *src);

BASE_ASSETS_API
void
font_asset_type_get_assets(const void *src, const asset_ref_t *refs[]);

BASE_ASSETS_API
uint32_t
font_asset_is_asset_type(void);

#ifdef __cplusplus
}
#endif

#endif
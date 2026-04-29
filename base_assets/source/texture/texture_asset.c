/**
 * @file texture_asset.c
 * @author khalilhenoud@gmail.com
 * @brief
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <assert.h>
#include <string.h>
#include <base_assets/texture/texture_asset.h>
#include <library/allocator/allocator.h>
#include <library/asset/asset_ref.h>
#include <library/core/core.h>
#include <library/type_registry/type_registry.h>


void
texture_asset_def(void *ptr)
{
  assert(ptr);

  {
    texture_asset_t *texture = (texture_asset_t *)ptr;
    memset(texture, 0, sizeof(texture_asset_t));
  }
}

uint32_t
texture_asset_is_def(const void *ptr)
{
  assert(ptr);

  {
    const texture_asset_t *texture = (const texture_asset_t *)ptr;
    texture_asset_t def;
    texture_asset_def(&def);
    return !memcmp(texture, &def, sizeof(texture_asset_t));
  }
}

void
texture_asset_serialize(
  const void *src,
  binary_stream_t *stream)
{
  assert(src && stream);

  {
    const texture_asset_t *texture = (const texture_asset_t *)src;
    binary_stream_write(stream, &texture->width, sizeof(uint32_t));
    binary_stream_write(stream, &texture->height, sizeof(uint32_t));
    binary_stream_write(stream, &texture->format, sizeof(int32_t));
    cvector_serialize(&texture->buffer, stream);
  }
}

void
texture_asset_deserialize(
  void *dst,
  const allocator_t *allocator,
  binary_stream_t *stream)
{
  assert(dst && allocator && stream);

  {
    texture_asset_t *texture = (texture_asset_t *)dst;
    const size_t s_u32 = sizeof(uint32_t), s_i32 = sizeof(int32_t);
    binary_stream_read(stream, (uint8_t *)&texture->width, s_u32, s_u32);
    binary_stream_read(stream, (uint8_t *)&texture->height, s_u32, s_u32);
    binary_stream_read(stream, (uint8_t *)&texture->format, s_i32, s_i32);
    cvector_deserialize(&texture->buffer, allocator, stream);
  }
}

size_t
texture_asset_type_size(void)
{
  return sizeof(texture_asset_t);
}

uint32_t
texture_asset_owns_alloc(void)
{
  return 0;
}

const allocator_t *
texture_asset_get_alloc(const void *ptr)
{
  return NULL;
}

void
texture_asset_cleanup(
  void *ptr,
  const allocator_t *allocator)
{
  assert(ptr && !texture_asset_is_def(ptr));
  assert(allocator);

  {
    texture_asset_t *texture = (texture_asset_t *)ptr;
    cvector_cleanup2(&texture->buffer);
    texture_asset_def(texture);
  }
}

const char *
texture_asset_get_dir(void)
{
  static const char *directory = "textures";
  return directory;
}

static
void
texture_asset_loader(
  void **ptr_addr,
  const asset_ref_t *asset_ref,
  const allocator_t *allocator)
{
  assert(ptr_addr && asset_ref && allocator);
  asset_ref_sanity_check(asset_ref, get_type_id(texture_asset_t));

  {
    texture_asset_t **ptr = (texture_asset_t **)ptr_addr;
    texture_asset_t *asset_ptr = *ptr;
    binary_stream_t *stream = binary_stream_from_file(
      asset_ref->path.str, allocator);
    *ptr = allocator->mem_alloc(sizeof(texture_asset_t));
    texture_asset_def(asset_ptr);
    texture_asset_deserialize(asset_ptr, allocator, stream);
    binary_stream_cleanup(stream);
    allocator->mem_free(stream);
  }
}

static
void
texture_asset_deloader(
  void **ptr_addr,
  const asset_ref_t *asset_ref,
  const allocator_t *allocator)
{
  assert(ptr_addr && asset_ref && allocator);
  asset_ref_sanity_check(asset_ref, get_type_id(texture_asset_t));

  {
    texture_asset_t **ptr = (texture_asset_t **)ptr_addr;
    texture_asset_t *asset_ptr = *ptr;
    texture_asset_cleanup(asset_ptr, allocator);
    allocator->mem_free(asset_ptr);
    *ptr = NULL;
  }
}

loader_t
texture_asset_get_loader(void)
{
  return texture_asset_loader;
}

deloader_t
texture_asset_get_deloader(void)
{
  return texture_asset_deloader;
}

uint32_t
texture_asset_type_asset_count(const void *src)
{
  return 0;
}

void
texture_asset_type_get_assets(const void *src, const asset_ref_t *refs[])
{}

uint32_t
texture_asset_is_asset_type(void)
{
  return 1;
}

////////////////////////////////////////////////////////////////////////////////
INITIALIZER(register_texture_asset_t)
{
  vtable_t vtable;
  memset(&vtable, 0, sizeof(vtable_t));
  vtable.fn_def = texture_asset_def;
  vtable.fn_is_def = texture_asset_is_def;
  vtable.fn_serialize = texture_asset_serialize;
  vtable.fn_deserialize = texture_asset_deserialize;
  vtable.fn_type_size = texture_asset_type_size;
  vtable.fn_owns_alloc = texture_asset_owns_alloc;
  vtable.fn_get_alloc = texture_asset_get_alloc;
  vtable.fn_cleanup = texture_asset_cleanup;
  vtable.fn_get_dir = texture_asset_get_dir;
  vtable.fn_get_loader = texture_asset_get_loader;
  vtable.fn_get_deloader = texture_asset_get_deloader;
  vtable.fn_type_asset_count = texture_asset_type_asset_count;
  vtable.fn_type_get_assets = texture_asset_type_get_assets;
  vtable.fn_is_asset_type = texture_asset_is_asset_type;
  register_type(get_type_id(texture_asset_t), &vtable);
}
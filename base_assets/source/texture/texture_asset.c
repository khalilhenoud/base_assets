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
    cstring_serialize(&texture->path, stream);
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
    cstring_def(&texture->path);
    cstring_deserialize(&texture->path, allocator, stream);
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
    cstring_cleanup2(&texture->path);
  }
}

////////////////////////////////////////////////////////////////////////////////
void
texture_asset_setup(
  texture_asset_t *texture,
  const char *path,
  const allocator_t* allocator)
{
  assert(allocator);
  assert(texture && texture_asset_is_def(texture));
  assert(path);

  cstring_setup(&texture->path, path, allocator);
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
  register_type(get_type_id(texture_asset_t), &vtable);
}
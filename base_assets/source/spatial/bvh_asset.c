/**
 * @file bvh_asset.c
 * @author khalilhenoud@gmail.com
 * @brief
 * @version 0.1
 * @date 2026-04-29
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <assert.h>
#include <string.h>
#include <base_assets/spatial/bvh_asset.h>
#include <library/allocator/allocator.h>
#include <library/asset/asset_ref.h>
#include <library/core/core.h>
#include <library/type_registry/type_registry.h>


void
bvh_asset_def(void *ptr)
{
  assert(ptr);

  {
    bvh_asset_t *bvh = (bvh_asset_t *)ptr;
    memset(bvh, 0, sizeof(bvh_asset_t));
  }
}

uint32_t
bvh_asset_is_def(const void *ptr)
{
  assert(ptr);

  {
    const bvh_asset_t *bvh = (const bvh_asset_t *)ptr;
    bvh_asset_t def;
    bvh_asset_def(&def);
    return !memcmp(bvh, &def, sizeof(bvh_asset_t));
  }
}

void
bvh_asset_serialize(
  const void *src,
  binary_stream_t *stream)
{
  assert(src && stream);

  {
    const bvh_asset_t *bvh = (const bvh_asset_t *)src;
    cvector_serialize(&bvh->normals, stream);
    cvector_serialize(&bvh->faces, stream);
    cvector_serialize(&bvh->bounds, stream);
    cvector_serialize(&bvh->nodes, stream);
  }
}

void
bvh_asset_deserialize(
  void *dst,
  const allocator_t *allocator,
  binary_stream_t *stream)
{
  assert(dst && allocator && stream);

  {
    bvh_asset_t *bvh = (bvh_asset_t *)dst;
    bvh_asset_def(bvh);
    cvector_deserialize(&bvh->normals, allocator, stream);
    cvector_deserialize(&bvh->faces, allocator, stream);
    cvector_deserialize(&bvh->bounds, allocator, stream);
    cvector_deserialize(&bvh->nodes, allocator, stream);
  }
}

size_t
bvh_asset_type_size(void)
{
  return sizeof(bvh_asset_t);
}

uint32_t
bvh_asset_owns_alloc(void)
{
  return 0;
}

const allocator_t *
bvh_asset_get_alloc(const void *ptr)
{
  return NULL;
}

void
bvh_asset_cleanup(
  void *ptr,
  const allocator_t *allocator)
{
  assert(ptr && !bvh_asset_is_def(ptr));
  assert(allocator);

  {
    bvh_asset_t *bvh = (bvh_asset_t *)ptr;
    cvector_cleanup2(&bvh->normals);
    cvector_cleanup2(&bvh->faces);
    cvector_cleanup2(&bvh->bounds);
    cvector_cleanup2(&bvh->nodes);
  }
}

const char *
bvh_asset_get_dir(void)
{
  static const char *directory = "bvhs";
  return directory;
}

static
void
bvh_asset_loader(
  void **ptr_addr,
  const asset_ref_t *asset_ref,
  const allocator_t *allocator)
{
  assert(ptr_addr && asset_ref && allocator);
  asset_ref_sanity_check(asset_ref, get_type_id(bvh_asset_t));

  {
    bvh_asset_t **ptr = (bvh_asset_t **)ptr_addr;
    bvh_asset_t *asset_ptr = *ptr;
    binary_stream_t *stream = binary_stream_from_file(
      asset_ref->path.str, allocator);
    *ptr = allocator->mem_alloc(sizeof(bvh_asset_t));
    bvh_asset_def(asset_ptr);
    bvh_asset_deserialize(asset_ptr, allocator, stream);
    binary_stream_cleanup(stream);
    allocator->mem_free(stream);
  }
}

static
void
bvh_asset_deloader(
  void **ptr_addr,
  const asset_ref_t *asset_ref,
  const allocator_t *allocator)
{
  assert(ptr_addr && asset_ref && allocator);
  asset_ref_sanity_check(asset_ref, get_type_id(bvh_asset_t));

  {
    bvh_asset_t **ptr = (bvh_asset_t **)ptr_addr;
    bvh_asset_t *asset_ptr = *ptr;
    bvh_asset_cleanup(asset_ptr, allocator);
    allocator->mem_free(asset_ptr);
    *ptr = NULL;
  }
}

loader_t
bvh_asset_get_loader(void)
{
  return bvh_asset_loader;
}

deloader_t
bvh_asset_get_deloader(void)
{
  return bvh_asset_deloader;
}

uint32_t
bvh_asset_type_asset_count(const void *src)
{
  assert(src);
  return 0;
}

void
bvh_asset_type_get_assets(const void *src, const asset_ref_t *refs[])
{
  assert(src);
}

uint32_t
bvh_asset_is_asset_type(void)
{
  return 1;
}

////////////////////////////////////////////////////////////////////////////////
INITIALIZER(register_bvh_asset_t)
{
  vtable_t vtable;
  memset(&vtable, 0, sizeof(vtable_t));
  vtable.fn_def = bvh_asset_def;
  vtable.fn_is_def = bvh_asset_is_def;
  vtable.fn_serialize = bvh_asset_serialize;
  vtable.fn_deserialize = bvh_asset_deserialize;
  vtable.fn_type_size = bvh_asset_type_size;
  vtable.fn_owns_alloc = bvh_asset_owns_alloc;
  vtable.fn_get_alloc = bvh_asset_get_alloc;
  vtable.fn_cleanup = bvh_asset_cleanup;
  vtable.fn_get_dir = bvh_asset_get_dir;
  vtable.fn_get_loader = bvh_asset_get_loader;
  vtable.fn_get_deloader = bvh_asset_get_deloader;
  vtable.fn_type_asset_count = bvh_asset_type_asset_count;
  vtable.fn_type_get_assets = bvh_asset_type_get_assets;
  vtable.fn_is_asset_type = bvh_asset_is_asset_type;
  register_type(get_type_id(bvh_asset_t), &vtable);
}
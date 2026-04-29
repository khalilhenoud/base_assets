/**
 * @file animation_asset.c
 * @author khalilhenoud@gmail.com
 * @brief
 * @version 0.1
 * @date 2026-04-26
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <assert.h>
#include <string.h>
#include <base_assets/animation/animation_asset.h>
#include <library/allocator/allocator.h>
#include <library/asset/asset_ref.h>
#include <library/core/core.h>
#include <library/type_registry/type_registry.h>


void
animation_asset_def(void *ptr)
{
  assert(ptr);

  {
    animation_asset_t *animation = (animation_asset_t *)ptr;
    memset(animation, 0, sizeof(animation_asset_t));
  }
}

uint32_t
animation_asset_is_def(const void *ptr)
{
  assert(ptr);

  {
    const animation_asset_t *animation = (const animation_asset_t *)ptr;
    animation_asset_t def;
    animation_asset_def(&def);
    return !memcmp(animation, &def, sizeof(animation_asset_t));
  }
}

static
void
animation_asset_node_serialize(
  const void *src,
  binary_stream_t *stream)
{
  assert(src && stream);

  {
    const animation_asset_node_t *node = (const animation_asset_node_t *)src;
    cstring_serialize(&node->name, stream);
    cvector_serialize(&node->position_keys, stream);
    cvector_serialize(&node->rotation_keys, stream);
    cvector_serialize(&node->scale_keys, stream);
  }
}

void
animation_asset_serialize(
  const void *src,
  binary_stream_t *stream)
{
  assert(src && stream);

  {
    const animation_asset_t *animation = (const animation_asset_t *)src;
    cstring_serialize(&animation->name, stream);
    binary_stream_write(stream, &animation->duration, sizeof(float));
    binary_stream_write(stream, &animation->ticks_per_second, sizeof(float));
    cvector_serialize_func(
      &animation->channels, stream, animation_asset_node_serialize);
  }
}

static
void
animation_asset_node_deserialize(
  void *dst,
  const allocator_t *allocator,
  binary_stream_t *stream)
{
  assert(dst && allocator && stream);

  {
    animation_asset_node_t *node = (animation_asset_node_t *)dst;
    cstring_def(&node->name);
    cstring_deserialize(&node->name, allocator, stream);
    cvector_deserialize(&node->position_keys, allocator, stream);
    cvector_deserialize(&node->rotation_keys, allocator, stream);
    cvector_deserialize(&node->scale_keys, allocator, stream);
  }
}

void
animation_asset_deserialize(
  void *dst,
  const allocator_t *allocator,
  binary_stream_t *stream)
{
  assert(dst && allocator && stream);

  {
    animation_asset_t *animation = (animation_asset_t *)dst;
    cstring_def(&animation->name);
    cstring_deserialize(&animation->name, allocator, stream);
    binary_stream_read(
      stream, (uint8_t *)&animation->duration,
      sizeof(float), sizeof(float));
    binary_stream_read(
      stream, (uint8_t *)&animation->ticks_per_second,
      sizeof(float), sizeof(float));
    cvector_deserialize_func(
      &animation->channels,
      allocator,
      stream,
      animation_asset_node_deserialize);
  }
}

size_t
animation_asset_type_size(void)
{
  return sizeof(animation_asset_t);
}

uint32_t
animation_asset_owns_alloc(void)
{
  return 0;
}

const allocator_t *
animation_asset_get_alloc(const void *ptr)
{
  return NULL;
}

static
void
animation_asset_node_cleanup(
  void *ptr,
  const allocator_t *allocator)
{
  assert(ptr && allocator);

  {
    animation_asset_node_t *node = (animation_asset_node_t *)ptr;
    cstring_cleanup2(&node->name);
    cvector_cleanup2(&node->position_keys);
    cvector_cleanup2(&node->rotation_keys);
    cvector_cleanup2(&node->scale_keys);
    memset(node, 0, sizeof(animation_asset_node_t));
  }
}

void
animation_asset_cleanup(
  void *ptr,
  const allocator_t *allocator)
{
  assert(ptr && !animation_asset_is_def(ptr));
  assert(allocator);

  {
    animation_asset_t *animation = (animation_asset_t *)ptr;
    cstring_cleanup2(&animation->name);
    cvector_cleanup_func(
      &animation->channels, NULL, animation_asset_node_cleanup);
    animation_asset_def(animation);
  }
}

const char *
animation_asset_get_dir(void)
{
  static const char *directory = "animations";
  return directory;
}

static
void
animation_asset_loader(
  void **ptr_addr,
  const asset_ref_t *asset_ref,
  const allocator_t *allocator)
{
  assert(ptr_addr && asset_ref && allocator);
  asset_ref_sanity_check(asset_ref, get_type_id(animation_asset_t));

  {
    animation_asset_t **ptr = (animation_asset_t **)ptr_addr;
    animation_asset_t *asset_ptr = *ptr;
    binary_stream_t *stream = binary_stream_from_file(
      asset_ref->path.str, allocator);
    *ptr = allocator->mem_alloc(sizeof(animation_asset_t));
    animation_asset_def(asset_ptr);
    animation_asset_deserialize(asset_ptr, allocator, stream);
    binary_stream_cleanup(stream);
    allocator->mem_free(stream);
  }
}

static
void
animation_asset_deloader(
  void **ptr_addr,
  const asset_ref_t *asset_ref,
  const allocator_t *allocator)
{
  assert(ptr_addr && asset_ref && allocator);
  asset_ref_sanity_check(asset_ref, get_type_id(animation_asset_t));

  {
    animation_asset_t **ptr = (animation_asset_t **)ptr_addr;
    animation_asset_t *asset_ptr = *ptr;
    animation_asset_cleanup(asset_ptr, allocator);
    allocator->mem_free(asset_ptr);
    *ptr = NULL;
  }
}

loader_t
animation_asset_get_loader(void)
{
  return animation_asset_loader;
}

deloader_t
animation_asset_get_deloader(void)
{
  return animation_asset_deloader;
}

uint32_t
animation_asset_type_asset_count(const void *src)
{
  assert(src);

  return 0;
}

void
animation_asset_type_get_assets(const void *src, const asset_ref_t *refs[])
{
  assert(src);
}

uint32_t
animation_asset_is_asset_type(void)
{
  return 1;
}

////////////////////////////////////////////////////////////////////////////////
INITIALIZER(register_animation_asset_t)
{
  vtable_t vtable;
  memset(&vtable, 0, sizeof(vtable_t));
  vtable.fn_def = animation_asset_def;
  vtable.fn_is_def = animation_asset_is_def;
  vtable.fn_serialize = animation_asset_serialize;
  vtable.fn_deserialize = animation_asset_deserialize;
  vtable.fn_type_size = animation_asset_type_size;
  vtable.fn_owns_alloc = animation_asset_owns_alloc;
  vtable.fn_get_alloc = animation_asset_get_alloc;
  vtable.fn_cleanup = animation_asset_cleanup;
  vtable.fn_get_dir = animation_asset_get_dir;
  vtable.fn_get_loader = animation_asset_get_loader;
  vtable.fn_get_deloader = animation_asset_get_deloader;
  vtable.fn_type_asset_count = animation_asset_type_asset_count;
  vtable.fn_type_get_assets = animation_asset_type_get_assets;
  vtable.fn_is_asset_type = animation_asset_is_asset_type;
  register_type(get_type_id(animation_asset_t), &vtable);
}
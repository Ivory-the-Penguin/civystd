/*
  ----- Ivy Binary -----
  Version: 1.1.2
  License: MIT-0

  This header only library has binary serilization for the ivystd.
*/

#ifndef IVY_BIN_H
#define IVY_BIN_H

#include <stdio.h>

#include "ivy_core.h"
#include "ivy_linmath.h"
#include "ivy_sv.h"

static const u64 bin_magic = 0x5F4E49425956495FULL;

typedef enum {
  BIN_NONE,
  BIN_ENCODING,
  BIN_DECODING,
} bin_state_t;

struct bin_t;

typedef void (*bin_process_fn)(struct bin_t *bin, void *data);

typedef struct bin_t {
  bin_process_fn process_cb;
  bin_state_t state;
  FILE *file;
} bin_t;

IVY_FORCE_INLINE bin_t bin_make(bin_process_fn process_cb) {
  return (bin_t){
      .process_cb = process_cb,
      .state = BIN_NONE,
      .file = NULL,
  };
}

IVY_FORCE_INLINE void bin_process_raw(bin_t *bin, void *ptr, u64 item_size,
                                      u64 count) {
  switch (bin->state) {
    case BIN_ENCODING:
      fwrite(ptr, item_size, count, bin->file);
      break;
    case BIN_DECODING:
      fread(ptr, item_size, count, bin->file);
      break;
    case BIN_NONE:
      IVY_ASSERT(bin->state != BIN_NONE, "Bin can't be doing nothing!");
      break;
  }
}

IVY_FORCE_INLINE void bin_process_i8(bin_t *bin, i8 *n) {
  bin_process_raw(bin, n, sizeof(i8), 1);
}

IVY_FORCE_INLINE void bin_process_u8(bin_t *bin, u8 *n) {
  bin_process_raw(bin, n, sizeof(u8), 1);
}

IVY_FORCE_INLINE void bin_process_i16(bin_t *bin, i16 *n) {
  bin_process_raw(bin, n, sizeof(i16), 1);
}

IVY_FORCE_INLINE void bin_process_u16(bin_t *bin, u16 *n) {
  bin_process_raw(bin, n, sizeof(u16), 1);
}

IVY_FORCE_INLINE void bin_process_i32(bin_t *bin, i32 *n) {
  bin_process_raw(bin, n, sizeof(i32), 1);
}

IVY_FORCE_INLINE void bin_process_u32(bin_t *bin, u32 *n) {
  bin_process_raw(bin, n, sizeof(u32), 1);
}

IVY_FORCE_INLINE void bin_process_i64(bin_t *bin, i64 *n) {
  bin_process_raw(bin, n, sizeof(i64), 1);
}

IVY_FORCE_INLINE void bin_process_u64(bin_t *bin, u64 *n) {
  bin_process_raw(bin, n, sizeof(u64), 1);
}

IVY_FORCE_INLINE void bin_process_f32(bin_t *bin, f32 *n) {
  bin_process_raw(bin, n, sizeof(f32), 1);
}

IVY_FORCE_INLINE void bin_process_f64(bin_t *bin, f64 *n) {
  bin_process_raw(bin, n, sizeof(f64), 1);
}

IVY_FORCE_INLINE void bin_process_vec2(bin_t *bin, vec2_t *v) {
  bin_process_raw(bin, v, sizeof(vec2_t), 1);
}

IVY_FORCE_INLINE void bin_process_vec3(bin_t *bin, vec3_t *v) {
  bin_process_raw(bin, v, sizeof(vec3_t), 1);
}

IVY_FORCE_INLINE void bin_process_vec4(bin_t *bin, vec4_t *v) {
  bin_process_raw(bin, v, sizeof(vec4_t), 1);
}

IVY_FORCE_INLINE void bin_process_mat2(bin_t *bin, mat2_t *m) {
  bin_process_raw(bin, m, sizeof(mat2_t), 1);
}

IVY_FORCE_INLINE void bin_process_mat3(bin_t *bin, mat3_t *m) {
  bin_process_raw(bin, m, sizeof(mat3_t), 1);
}

IVY_FORCE_INLINE void bin_process_mat4(bin_t *bin, mat4_t *m) {
  bin_process_raw(bin, m, sizeof(mat4_t), 1);
}

IVY_FORCE_INLINE u64 bin_process_array(bin_t *bin, void **data, u64 item_size,
                                       u64 count, allocator_t alloc) {
  bin_process_u64(bin, &count);

  if (bin->state == BIN_DECODING) {
    *data = ivy_alloc(alloc, item_size * count);
  }

  bin_process_raw(bin, *data, item_size, count);

  return count;
}

IVY_FORCE_INLINE void bin_process_sv(bin_t *bin, string_view_t *sv,
                                     allocator_t alloc) {
  sv->length =
      bin_process_array(bin, (void **)&sv->data, sizeof(c8), sv->length, alloc);
}

IVY_FORCE_INLINE void bin_encode_to_file(bin_t *bin, void *data,
                                         const char *path) {
  bin->file = fopen(path, "wb");
  bin->state = BIN_ENCODING;

  u64 magic_number = bin_magic;
  bin_process_u64(bin, &magic_number);

  bin->process_cb(bin, data);

  fclose(bin->file);
  bin->file = NULL;
  bin->state = BIN_NONE;
}

IVY_FORCE_INLINE void bin_decode_from_file(bin_t *bin, void *data,
                                           const char *path) {
  bin->file = fopen(path, "rb");
  bin->state = BIN_DECODING;

  u64 loaded_magic = 0;
  bin_process_u64(bin, &loaded_magic);
  IVY_ASSERT(loaded_magic == bin_magic,
             "File doesn't have right magic header!");

  bin->process_cb(bin, data);

  fclose(bin->file);
  bin->file = NULL;
  bin->state = BIN_NONE;
}

#ifdef IVY_ATLEAST_C11

#define bin_process(bin_ptr, item_ptr) \
  _Generic((item_ptr),                 \
      i8 *: bin_process_i8,            \
      u8 *: bin_process_u8,            \
      i16 *: bin_process_i16,          \
      u16 *: bin_process_u16,          \
      i32 *: bin_process_i32,          \
      u32 *: bin_process_u32,          \
      i64 *: bin_process_i64,          \
      u64 *: bin_process_u64,          \
      f32 *: bin_process_f32,          \
      f64 *: bin_process_f64,          \
      vec2_t *: bin_process_vec2,      \
      vec3_t *: bin_process_vec3,      \
      vec4_t *: bin_process_vec4,      \
      mat2_t *: bin_process_mat2,      \
      mat3_t *: bin_process_mat3,      \
      mat4_t *: bin_process_mat4)((bin_ptr), (item_ptr))

#endif

#endif

/*
  ----- Ivy Binary -----
  Version: 0.9.0
  License: MIT-0
*/

#ifndef IVY_BIN_H
#define IVY_BIN_H

#include <stdio.h>

#include "ivy_core.h"
#include "ivy_linmath.h"
#include "ivy_sv.h"

#define BIN_MAGIC "_IVY_BIN_"
#define BIN_MAGIC_LENGTH 8

typedef enum {
  BIN_NONE,
  BIN_ENCODING,
  BIN_DECODING,
} bin_state_t;

struct bin_t;

typedef void (*bin_encode_fn)(struct bin_t *bin, void *data);

typedef struct bin_t {
  bin_encode_fn encode_cb;
  bin_state_t state;
  FILE *file;
} bin_t;

IVY_FORCE_INLINE bin_t bin_make(bin_encode_fn encode_cb) {
  return (bin_t){
      .encode_cb = encode_cb,
      .state = BIN_NONE,
      .file = NULL,
  };
}

IVY_FORCE_INLINE void bin_encode_raw(bin_t *bin, void *ptr, u64 item_size,
                                     u64 count) {
  IVY_ASSERT(bin->state == BIN_ENCODING,
             "Bin is either doing nothing or decoding!");
  fwrite(ptr, item_size, count, bin->file);
}

IVY_FORCE_INLINE void bin_encode_i8(bin_t *bin, i8 n) {
  bin_encode_raw(bin, &n, sizeof(i8), 1);
}

IVY_FORCE_INLINE void bin_encode_u8(bin_t *bin, u8 n) {
  bin_encode_raw(bin, &n, sizeof(u8), 1);
}

IVY_FORCE_INLINE void bin_encode_i16(bin_t *bin, i16 n) {
  bin_encode_raw(bin, &n, sizeof(i16), 1);
}

IVY_FORCE_INLINE void bin_encode_u16(bin_t *bin, u16 n) {
  bin_encode_raw(bin, &n, sizeof(u16), 1);
}

IVY_FORCE_INLINE void bin_encode_i32(bin_t *bin, i32 n) {
  bin_encode_raw(bin, &n, sizeof(i32), 1);
}

IVY_FORCE_INLINE void bin_encode_u32(bin_t *bin, u32 n) {
  bin_encode_raw(bin, &n, sizeof(u32), 1);
}

IVY_FORCE_INLINE void bin_encode_i64(bin_t *bin, i64 n) {
  bin_encode_raw(bin, &n, sizeof(i64), 1);
}

IVY_FORCE_INLINE void bin_encode_u64(bin_t *bin, u64 n) {
  bin_encode_raw(bin, &n, sizeof(u64), 1);
}

IVY_FORCE_INLINE void bin_encode_f32(bin_t *bin, f32 n) {
  bin_encode_raw(bin, &n, sizeof(f32), 1);
}

IVY_FORCE_INLINE void bin_encode_f64(bin_t *bin, f64 n) {
  bin_encode_raw(bin, &n, sizeof(f64), 1);
}

IVY_FORCE_INLINE void bin_encode_vec2(bin_t *bin, vec2_t v) {
  bin_encode_raw(bin, &v, sizeof(vec2_t), 1);
}

IVY_FORCE_INLINE void bin_encode_vec3(bin_t *bin, vec3_t v) {
  bin_encode_raw(bin, &v, sizeof(vec3_t), 1);
}

IVY_FORCE_INLINE void bin_encode_vec4(bin_t *bin, vec4_t v) {
  bin_encode_raw(bin, &v, sizeof(vec4_t), 1);
}

IVY_FORCE_INLINE void bin_encode_mat2(bin_t *bin, mat2_t m) {
  bin_encode_raw(bin, &m, sizeof(mat2_t), 1);
}

IVY_FORCE_INLINE void bin_encode_mat3(bin_t *bin, mat3_t m) {
  bin_encode_raw(bin, &m, sizeof(mat3_t), 1);
}

IVY_FORCE_INLINE void bin_encode_mat4(bin_t *bin, mat4_t m) {
  bin_encode_raw(bin, &m, sizeof(mat4_t), 1);
}

IVY_FORCE_INLINE void bin_encode_array(bin_t *bin, void *data, u64 item_size,
                                       u64 count) {
  bin_encode_u64(bin, count);
  bin_encode_raw(bin, data, item_size, count);
}

IVY_FORCE_INLINE void bin_encode_sv(bin_t *bin, string_view_t sv) {
  bin_encode_array(bin, (void *)sv.data, sizeof(c8), sv.length);
}

IVY_FORCE_INLINE void bin_encode_to_file(bin_t *bin, void *data,
                                         const char *path) {
  bin->file = fopen(path, "wb");
  bin->state = BIN_ENCODING;

  bin_encode_array(bin, BIN_MAGIC, sizeof(c8), BIN_MAGIC_LENGTH);

  bin->encode_cb(bin, data);

  fclose(bin->file);
  bin->file = NULL;
  bin->state = BIN_NONE;
}

#ifdef IVY_ATLEAST_C11

#define bin_encode(bin_ptr, item) \
  _Generic((item),                \
      i8: bin_encode_i8,          \
      u8: bin_encode_u8,          \
      i16: bin_encode_i16,        \
      u16: bin_encode_u16,        \
      i32: bin_encode_i32,        \
      u32: bin_encode_u32,        \
      i64: bin_encode_i64,        \
      u64: bin_encode_u64,        \
      f32: bin_encode_f32,        \
      f64: bin_encode_f64,        \
      vec2_t: bin_encode_vec2,    \
      vec3_t: bin_encode_vec3,    \
      vec4_t: bin_encode_vec4,    \
      mat2_t: bin_encode_mat2,    \
      mat3_t: bin_encode_mat3,    \
      mat4_t: bin_encode_mat4,    \
      string_view_t: bin_encode_sv)((bin_ptr), (item))

#endif

#endif

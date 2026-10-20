/*
  ----- Ivy Binary -----
  Version: 0.6.0
  License: MIT-0
*/

#ifndef IVY_BIN_H
#define IVY_BIN_H

#include <stdio.h>

#include "ivy_core.h"
#include "ivy_linmath.h"
#include "ivy_sv.h"

typedef enum {
  BIN_NONE,
  BIN_ENCODING,
  BIN_DECODING,
} bit_type_t;

typedef struct {
  FILE *file;
  bit_type_t type;
} bin_t;

IVY_FORCE_INLINE bin_t bin_make_encoder(const char *path) {
  bin_t out;

  out.file = fopen(path, "wb");
  out.type = BIN_ENCODING;

  return out;
}

IVY_FORCE_INLINE void bin_close(bin_t *bin) {
  fclose(bin->file);
  bin->type = BIN_NONE;
}

IVY_FORCE_INLINE void bin_encode_raw(bin_t *bin, void *ptr, u64 item_size,
                                     u64 items) {
  fwrite(ptr, item_size, items, bin->file);
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

IVY_FORCE_INLINE void bin_encode_c8(bin_t *bin, c8 n) {
  bin_encode_raw(bin, &n, sizeof(c8), 1);
}

IVY_FORCE_INLINE void bin_encode_b8(bin_t *bin, b8 n) {
  bin_encode_raw(bin, &n, sizeof(b8), 1);
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

IVY_FORCE_INLINE void bin_encode_sv(bin_t *bin, string_view_t sv) {
  bin_encode_u64(bin, sv.length);
  bin_encode_raw(bin, (void *)sv.data, sizeof(c8), sv.length);
}

#endif

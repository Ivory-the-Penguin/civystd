/*
  ----- Ivy Binary -----
  Version: 0.1.0
  License: MIT-0
*/

#ifndef IVY_BIN_H
#define IVY_BIN_H

#include <stdio.h>

#include "ivy_core.h"

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

IVY_FORCE_INLINE void bin_encode_u8(bin_t *bin, u8 byte) {
  fwrite(&byte, sizeof(u8), 1, bin->file);
}

#endif

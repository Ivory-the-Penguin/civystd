/*
  ----- Ivy String View -----
  Version: 1.5.1
  License: MIT-0
This stb-style header has a feature-full string view for the ivystd.
  Use IVY_IMPL macro for implementation

  ----- Usage -----
  We have a string_view_t, which contains a pointer to the original data and the
  length. To go through every character, you would use:
  SV_FOREACH(sv, i, offset) {
    putchar(sv.data[i]);
  }

  Or the reverse variation:
  SV_FOREACH_REV(sv, i, offset) {
    putchar(sv.data[i]);
  }

  sv is the value of the sv (so not a pointer), i is the name of the index, and
  offset has the offset from the initial position (from the start for the normal
  variation, and from the end for the reverse variation).
To make a string view from a string literal / c string, you use the sv func:
  string_view_t sv = sv("Hello, World!");

  And from any string with a custom length:
  string_view_t sv = (string_view_t) {
    .data = str,
    .length = str_len,
  };

  All of the builtin string view functions start with a sv_ prefix. We have the
  following functions:

  ~ sv_compare(a, b) : Compares a and b lexicographically.

  ~ sv_has_prefix(sv, prefix) : Check if the sv has a prefix of prefix.

  ~ sv_chop_left(sv, n) : Returns sv with the left side chopped by n chars.

  ~ sv_chop_right(sv, n) : Returns sv with the right side chopped by n chars.

  ~ sv_trim_left(sv) : Returns sv with the left side trimmed of whitespaces.

  ~ sv_trim_right(sv) : Returns sv with the right side trimmed of whitespaces.

  ~ sv_trim(sv) : Returns sv with both sides trimmed of whitespaces.
.
  ~ sv_combine(alloc, a, b) : Returns a and b concatenated. Allocated with
alloc.

  ~ sv_chop_by_delimiter(*sv, delimiter) : Returns a string view which was taken
  from the start of sv to the delimiter, and modifies sv to be right afterwards
  (also consumes the delimiter). It frees any instances of the delimiter at the
  beginning (greedy chopping, like strtok).

  ~ sv_chop_by_type(*sv, is_type) : Same as sv_chop_by_delimiter, but the
  delimiter is defined by the is_type function (int taken in, and int returned).

  ~ sv_chop_by_type_rev(*sv, is_type) : Same as sv_chop_by_type, BUT, the
  is_type function determines what ISN'T a delimiter. So you can use isalpha to
  chop until we reach a non-alphabetic character.

  ----- Credits -----
  The initial implementation was a copied from Tsoding's video, "C Strings are
  Terrible!" (https://www.youtube.com/watch?v=y8PLpDgZc0E). You can technically
  view this as an expanded version of his implementation.
*/

#ifndef IVY_SV_H
#define IVY_SV_H

#include <ctype.h>
#include <string.h>

#include "ivy_allocator.h"
#include "ivy_core.h"

typedef struct {
  const c8 *data;
  u64 length;
} string_view_t;

#define SV_FOREACH(sv, i, offset) \
  for (u64(i) = (offset); (i) < (sv).length; (i)++)

#define SV_FOREACH_REV(sv, i, offset) \
  for (u64(i) = (sv).length - (offset); (i--) > 0;)

#define SV_FMT "%.*s"

// Only for c strings. If you need a sv, just manually create the string view
IVY_FORCE_INLINE string_view_t sv(const char *c_str) {
  return (string_view_t){
      .data = (const c8 *)c_str,
      .length = strlen(c_str),
  };
}

/*
-1 means a is smaller than b,
0 means a is equal to b,
1 means a is bigger than b,
*/
IVY_FORCE_INLINE i8 sv_compare(string_view_t a, string_view_t b) {
  int cmp = memcmp(a.data, b.data, (a.length < b.length ? a.length : b.length));

  if (cmp == 0) {
    if (a.length == b.length) {
      return 0;
    }

    return (a.length > b.length ? 1 : -1);
  }

  return (cmp > 0 ? 1 : -1);
}

IVY_FORCE_INLINE b8 sv_has_prefix(string_view_t sv, string_view_t prefix) {
  if (prefix.length > sv.length) {
    return false;
  }

  return memcmp(sv.data, prefix.data, prefix.length) == 0;
}

IVY_FORCE_INLINE string_view_t sv_chop_left(string_view_t sv, u64 n) {
  IVY_ASSERT(sv.length >= n, "String view is too small to be chopped");
  sv.data += n;
  sv.length -= n;

  return sv;
}

IVY_FORCE_INLINE string_view_t sv_chop_right(string_view_t sv, u64 n) {
  IVY_ASSERT(sv.length >= n, "String view is too small to be chopped");
  sv.length -= n;
  return sv;
}

IVY_FORCE_INLINE string_view_t sv_trim_left(string_view_t sv) {
  while (sv.length > 0 && isspace((c8)sv.data[0])) {
    sv = sv_chop_left(sv, 1);
  }

  return sv;
}

IVY_FORCE_INLINE string_view_t sv_trim_right(string_view_t sv) {
  while (sv.length > 0 && isspace((c8)sv.data[sv.length - 1])) {
    sv = sv_chop_right(sv, 1);
  }

  return sv;
}

IVY_FORCE_INLINE string_view_t sv_trim(string_view_t sv) {
  sv = sv_trim_left(sv);
  sv = sv_trim_right(sv);
  return sv;
}

// Has a secret '\0' in the end.
// Recommended to use ivy_format instead of this.
IVY_FORCE_INLINE string_view_t sv_combine(allocator_t alloc, string_view_t a,
                                          string_view_t b) {
  c8 *new_buffer = (c8 *)ivy_alloc(alloc, a.length + b.length + 1);
  memcpy(new_buffer, a.data, a.length);
  memcpy(new_buffer + a.length, b.data, b.length);
  new_buffer[a.length + b.length] = '\0';
  return (string_view_t){
      .data = new_buffer,
      .length = a.length + b.length,
  };
}

string_view_t sv_chop_by_delimiter(string_view_t *sv, c8 delimiter);

// is_type is what IS a delimiter.
string_view_t sv_chop_by_type(string_view_t *sv, int (*is_type)(int c));

// is_type is what ISN'T a delimiter.
string_view_t sv_chop_by_type_rev(string_view_t *sv, int (*is_type)(int c));

#ifdef IVY_IMPL

string_view_t sv_chop_by_delimiter(string_view_t *sv, c8 delimiter) {
  while (sv->length > 0 && sv->data[0] == delimiter) {
    *sv = sv_chop_left(*sv, 1);
  }

  if (sv->length == 0) {
    return *sv;
  }

  u64 end = 0;
  do {
    end++;
  } while (end < sv->length && sv->data[end] != delimiter);

  string_view_t out;
  if (end < sv->length) {
    out = (string_view_t){
        .data = sv->data,
        .length = end,
    };
    *sv = sv_chop_left(*sv, end + 1);
    return out;
  }

  out = *sv;
  *sv = sv_chop_left(*sv, sv->length);
  return out;
}

// is_type is what IS a delimiter
string_view_t sv_chop_by_type(string_view_t *sv, int (*is_type)(int c)) {
  while (sv->length > 0 && is_type((c8)sv->data[0])) {
    *sv = sv_chop_left(*sv, 1);
  }

  if (sv->length == 0) {
    return *sv;
  }

  u64 end = 0;
  do {
    end++;
  } while (end < sv->length && !is_type((c8)sv->data[end]));

  string_view_t out;
  if (end < sv->length) {
    out = (string_view_t){
        .data = sv->data,
        .length = end,
    };
    *sv = sv_chop_left(*sv, end + 1);
    return out;
  }

  out = *sv;
  *sv = sv_chop_left(*sv, sv->length);
  return out;
}

// is_type is what ISN'T a delimiter
string_view_t sv_chop_by_type_rev(string_view_t *sv, int (*is_type)(int c)) {
  while (sv->length > 0 && !is_type((c8)sv->data[0])) {
    *sv = sv_chop_left(*sv, 1);
  }

  if (sv->length == 0) {
    return *sv;
  }

  u64 end = 0;
  do {
    end++;
  } while (end < sv->length && is_type((c8)sv->data[end]));

  string_view_t out;
  if (end < sv->length) {
    out = (string_view_t){
        .data = sv->data,
        .length = end,
    };
    *sv = sv_chop_left(*sv, end + 1);
    return out;
  }

  out = *sv;
  *sv = sv_chop_left(*sv, sv->length);
  return out;
}

#endif

#endif

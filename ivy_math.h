/*
  ----- Ivy Math -----
  Version: 0.6.2
  License: MIT-0

  This header only library has some useful maths functions for the ivystd.
*/

#ifndef IVY_MATH_H
#define IVY_MATH_H

#define IVY_MATH_MAJOR 0
#define IVY_MATH_MINOR 6
#define IVY_MATH_FIX 2

#include "ivy_core.h"

#define IVY_PI 3.14159265359f
#define IVY_2PI 6.28318530718f
#define IVY_HALF_PI 1.570796326795f
#define IVY_INV_2PI 0.15915494309189533576f

#define IVY_RAD2DEG(radians) ((radians) * (180.0f / IVY_PI))
#define IVY_DEG2RAD(degrees) ((degrees) * (IVY_PI / 180.0f))

#define IVY_MIN(a, b) ((a) < (b) ? (a) : (b))
#define IVY_MAX(a, b) ((a) > (b) ? (a) : (b))

#define IVY_CLAMP(value, min, max) \
  ((value) > (max) ? (max) : ((value) < (min) ? (min) : (value)))

#define IVY_LERP(a, b, t) ((a) + ((b) - (a)) * (t))

#define IVY_ABS(x) ((x) < 0 ? -(x) : (x))

// exponent by squaring
IVY_FORCE_INLINE f32 ivy_pow_f(f32 x, i64 n) {
  if (n < 0) {
    x = 1 / x;
    n *= -1;
  }

  if (n == 0) {
    return 1;
  }

  f32 y = 1;
  while (n > 1) {
    if (n & 1) {
      y = x * y;
      n -= 1;
    }
    x = x * x;
    n >>= 1;
  }

  return x * y;
}

// exponent by squaring
IVY_FORCE_INLINE u64 ivy_pow_u64(u64 x, u64 n) {
  if (n == 0) {
    return 1;
  }

  u64 y = 1;
  while (n > 1) {
    if (n & 1) {
      y = x * y;
      n -= 1;
    }
    x = x * x;
    n >>= 1;
  }

  return x * y;
}

// exponent by squaring
IVY_FORCE_INLINE i64 ivy_pow_i64(i64 x, u64 n) {
  if (n == 0) {
    return 1;
  }

  i64 out = (i64)ivy_pow_u64((x < 0 ? (u64)-x : (u64)x), n);

  if (x < 0 && (n & 1)) {
    out *= -1;
  }

  return out;
}

#define IVY_COMPARE_DECIMAL(a, b, precision) (IVY_ABS((a) - (b)) <= (precision))

IVY_FORCE_INLINE f32 ivy_sin(f32 x) {
  f32 quot = x * IVY_INV_2PI;
  f32 rounded = (f32)((int)(quot + (quot >= 0.0f ? 0.5f : -0.5f)));
  x = x - IVY_2PI * rounded;

  if (x > IVY_HALF_PI) x = IVY_PI - x;
  if (x < -IVY_HALF_PI) x = -IVY_PI - x;

  f32 x2 = x * x;

  const f32 c1 = -1.666666667e-01f;
  const f32 c2 = 8.333333333e-03f;
  const f32 c3 = -1.984126984e-04f;
  const f32 c4 = 2.755731922e-06f;

  return x * (1.0f + x2 * (c1 + x2 * (c2 + x2 * (c3 + x2 * c4))));
}

IVY_FORCE_INLINE f32 ivy_cos(f32 x) { return ivy_sin(x + IVY_HALF_PI); }

IVY_FORCE_INLINE f32 ivy_tan(f32 x) { return ivy_sin(x) / ivy_cos(x); }

IVY_FORCE_INLINE f32 ivy_inv_sqrt(f32 x) {
  long i;
  f32 x2, y;
  const f32 threehalfs = 1.5f;

  x2 = x * 0.5f;
  y = x;
  memcpy(&i, &y, sizeof(i));
  i = 0x5f3759df - (i >> 1);
  memcpy(&y, &i, sizeof(y));
  y = y * (threehalfs - (x2 * y * y));

  return y;
}

IVY_FORCE_INLINE f32 ivy_sqrt(f32 x) {
  return x > 0.0f ? x * ivy_inv_sqrt(x) : 0.0f;
}

IVY_FORCE_INLINE f32 ivy_pow(f32 x, i32 exp) {
  if (x == 0.0f && exp < 0) {
    return 0.0f;
  }

  f32 out = 1.0f;
  if (exp < 0) {
    x = 1.0f / x;
    exp = -exp;
  }

  for (int i = 0; i < exp; i++) {
    out *= x;
  }

  return out;
}

typedef struct {
  u32 sign;
  u32 exponent;
  u32 mantissa;
} f32_bits;

f32_bits ivy_get_f32_bits(f32 n) {
  u32 bits;
  memcpy(&bits, &n, sizeof(n));

  return (f32_bits){
      .sign = bits >> 31,
      .exponent = (bits >> 23) & 0xFF,
      .mantissa = bits & 0x7FFFFF,
  };
}

#endif

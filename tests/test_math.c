#include <math.h>

#include "../ivy_math.h"
#include "../ivy_test.h"

TEST_CASE(math_test_abs) {
  TEST_EXPECT(IVY_ABS(123), 123, "{i}");
  TEST_EXPECT(IVY_ABS(-200), 200, "{i}");

  TEST_EXPECT(IVY_ABS(0), 0, "{i}");
  TEST_EXPECT(IVY_ABS(I32_MAX), I32_MAX, "{i}");
  TEST_EXPECT(IVY_ABS(I32_MIN + 1), I32_MAX, "{i}");

  TEST_EXPECT(IVY_ABS(1234567890LL), 1234567890LL, "{i:l}");
  TEST_EXPECT(IVY_ABS(-9876546410LL), 9876546410LL, "{i:l}");
  TEST_EXPECT(IVY_ABS(0LL), 0LL, "{i:l}");
  TEST_EXPECT(IVY_ABS(I64_MAX), I64_MAX, "{i:l}");
  TEST_EXPECT(IVY_ABS(I64_MIN + 1), I64_MAX, "{i:l}");

  TEST_EXPECT(IVY_ABS(10203040U), 10203040U, "{i:u}");
  TEST_EXPECT(IVY_ABS(0), 0, "{i:u}");
  TEST_EXPECT(IVY_ABS(U32_MAX), U32_MAX, "{i:u}");
  TEST_EXPECT(IVY_ABS(70605040302010ULL), 70605040302010ULL, "{i:ul}");
  TEST_EXPECT(IVY_ABS(0LL), 0LL, "{i:ul}");
  TEST_EXPECT(IVY_ABS(U64_MAX), U64_MAX, "{i:ul}");

  TEST_OK();
}

TEST_CASE(math_test_min) {
  TEST_EXPECT(IVY_MIN(0, 0), 0, "{i}");
  TEST_EXPECT(IVY_MIN(0, 100), 0, "{i}");
  TEST_EXPECT(IVY_MIN(99, 100), 99, "{i}");

  TEST_EXPECT(IVY_MIN(0, -100), -100, "{i}");
  TEST_EXPECT(IVY_MIN(-99, 100), -99, "{i}");

  TEST_EXPECT(IVY_MIN(I32_MAX, I32_MIN), I32_MIN, "{i}");
  TEST_EXPECT(IVY_MIN(I64_MAX, I64_MIN), I64_MIN, "{i:l}");

  TEST_OK();
}

TEST_CASE(math_test_max) {
  TEST_EXPECT(IVY_MAX(0, 0), 0, "{i}");
  TEST_EXPECT(IVY_MAX(0, 100), 100, "{i}");
  TEST_EXPECT(IVY_MAX(99, 100), 100, "{i}");

  TEST_EXPECT(IVY_MAX(0, -100), 0, "{i}");
  TEST_EXPECT(IVY_MAX(-99, 100), 100, "{i}");

  TEST_EXPECT(IVY_MAX(I32_MAX, I32_MIN), I32_MAX, "{i}");
  TEST_EXPECT(IVY_MAX(I64_MAX, I64_MIN), I64_MAX, "{i:l}");

  TEST_OK();
}

TEST_CASE(math_test_clamp) {
  TEST_EXPECT(IVY_CLAMP(0, 0, 0), 0, "{i}");

  TEST_EXPECT(IVY_CLAMP(250, 100, 500), 250, "{i}");
  TEST_EXPECT(IVY_CLAMP(800, 100, 500), 500, "{i}");
  TEST_EXPECT(IVY_CLAMP(-200, 100, 500), 100, "{i}");

  TEST_EXPECT(IVY_CLAMP(250, -100, 500), 250, "{i}");
  TEST_EXPECT(IVY_CLAMP(800, -100, 500), 500, "{i}");
  TEST_EXPECT(IVY_CLAMP(-200, -100, 500), -100, "{i}");

  TEST_EXPECT(IVY_CLAMP(-250, -500, -100), -250, "{i}");
  TEST_EXPECT(IVY_CLAMP(-800, -500, -100), -500, "{i}");
  TEST_EXPECT(IVY_CLAMP(0, -500, -100), -100, "{i}");

  TEST_EXPECT(IVY_CLAMP(123456, 0, I32_MAX), 123456, "{i}");
  TEST_EXPECT(IVY_CLAMP(-654321, 0, I32_MAX), 0, "{i}");
  TEST_EXPECT(IVY_CLAMP(I32_MAX, 0, I32_MAX), I32_MAX, "{i}");
  TEST_EXPECT(IVY_CLAMP(I32_MIN, 0, I32_MAX), 0, "{i}");

  TEST_EXPECT(IVY_CLAMP(1234567890LL, I64_MIN, I64_MAX), 1234567890LL, "{i:l}");
  TEST_EXPECT(IVY_CLAMP(-987654321LL, I64_MIN, I64_MAX), -987654321LL, "{i:l}");
  TEST_EXPECT(IVY_CLAMP(I64_MIN, I64_MIN, I64_MAX), I64_MIN, "{i:l}");
  TEST_EXPECT(IVY_CLAMP(I64_MAX, I64_MIN, I64_MAX), I64_MAX, "{i:l}");

  TEST_OK();
}

TEST_CASE(math_test_lerp) {
  TEST_EXPECT_FLOAT(IVY_LERP(0.0, 0.0, 0.0), 0.0, 0.00001);

  TEST_EXPECT_FLOAT(IVY_LERP(0.0, 1.0, 0.0), 0.0, 0.00001);
  TEST_EXPECT_FLOAT(IVY_LERP(0.0, 1.0, 1.0), 1.0, 0.00001);
  TEST_EXPECT_FLOAT(IVY_LERP(0.0, 1.0, 0.5), 0.5, 0.00001);
  TEST_EXPECT_FLOAT(IVY_LERP(0.0, 1.0, 0.123), 0.123, 0.00001);
  TEST_EXPECT_FLOAT(IVY_LERP(0.0, 1.0, 0.765), 0.765, 0.00001);

  TEST_EXPECT_FLOAT(IVY_LERP(-123.0, -987.0, 0.0), -123.0, 0.00001);
  TEST_EXPECT_FLOAT(IVY_LERP(-123.0, -987.0, 1.0), -987.0, 0.00001);
  TEST_EXPECT_FLOAT(IVY_LERP(-123.0, -987.0, 0.5), -555.0, 0.00001);
  TEST_EXPECT_FLOAT(IVY_LERP(-123.0, -987.0, 0.123), -229.272, 0.00001);
  TEST_EXPECT_FLOAT(IVY_LERP(-123.0, -987.0, 0.765), -783.96, 0.00001);

  TEST_EXPECT_FLOAT(IVY_LERP(123.0, 987.0, 0.0), 123.0, 0.00001);
  TEST_EXPECT_FLOAT(IVY_LERP(123.0, 987.0, 1.0), 987.0, 0.00001);
  TEST_EXPECT_FLOAT(IVY_LERP(123.0, 987.0, 0.5), 555.0, 0.00001);
  TEST_EXPECT_FLOAT(IVY_LERP(123.0, 987.0, 0.123), 229.272, 0.00001);
  TEST_EXPECT_FLOAT(IVY_LERP(123.0, 987.0, 0.765), 783.96, 0.00001);

  TEST_EXPECT_FLOAT(IVY_LERP(-123.0, 987.0, 0.0), -123.0, 0.00001);
  TEST_EXPECT_FLOAT(IVY_LERP(-123.0, 987.0, 1.0), 987.0, 0.00001);
  TEST_EXPECT_FLOAT(IVY_LERP(-123.0, 987.0, 0.5), 432.0, 0.00001);
  TEST_EXPECT_FLOAT(IVY_LERP(-123.0, 987.0, 0.123), 13.53, 0.00001);
  TEST_EXPECT_FLOAT(IVY_LERP(-123.0, 987.0, 0.765), 726.15, 0.00001);

  TEST_OK();
}

TEST_CASE(math_test_trig) {
  for (f32 i = -IVY_2PI; i < IVY_2PI * 2; i += 0.0001) {
    TEST_EXPECT_FLOAT(ivy_sin(i), sinf(i), 0.00001f);
    TEST_EXPECT_FLOAT(ivy_cos(i), cosf(i), 0.00001f);

    if (IVY_ABS(cosf(i)) > 0.05f) {
      TEST_EXPECT_FLOAT(ivy_tan(i), tanf(i), 0.001f);
    }
  }

  TEST_OK();
}

// testing sqrt also tests inv_sqrt
TEST_CASE(math_test_sqrt) {
  for (f32 i = 0.0f; i <= 1000.0f; i += 0.01f) {
    TEST_EXPECT_FLOAT(ivy_sqrt(i), sqrtf(i), 0.00001f);
  }

  TEST_EXPECT_FLOAT(ivy_sqrt(-123.0f), 0.0f, 0.00001f);

  TEST_EXPECT_FLOAT(ivy_sqrt((f32)I32_MAX), sqrtf((f32)I32_MAX), 100.0f);
  TEST_EXPECT_FLOAT(ivy_sqrt((f32)I64_MAX), sqrtf((f32)I64_MAX), 500.0f);

  TEST_OK();
}

TEST_CASE(math_test_pow) {
  for (float base = -2.5f; base <= 2.5f; base += 0.1f) {
    for (i32 pow = -3; pow <= 3; pow++) {
      TEST_EXPECT_FLOAT(ivy_pow_f32(base, pow), powf(base, pow), 10.0f);
    }
  }

  TEST_EXPECT(ivy_pow_i64(-2, 31), powl(-2, 31), "{i:l}");
  TEST_EXPECT(ivy_pow_i64(-2, 32), powl(-2, 32), "{i:l}");
  TEST_EXPECT(ivy_pow_i64(2, 32), powl(-2, 32), "{i:l}");
  TEST_EXPECT(ivy_pow_i64(2, 10), powl(2, 10), "{i:l}");
  TEST_EXPECT(ivy_pow_i64(12345, 0), powl(12345, 0), "{i:l}");

  TEST_EXPECT(ivy_pow_u64(2, 60), powl(2, 60), "{i:lu}");
  TEST_EXPECT(ivy_pow_u64(2, 48), powl(2, 48), "{i:lu}");
  TEST_EXPECT(ivy_pow_u64(987654321, 0), powl(987654321, 0), "{i:lu}");

  TEST_OK();
}

TEST_SUITE(math_test_suite) {
  TEST_RUN(math_test_abs);
  TEST_RUN(math_test_min);
  TEST_RUN(math_test_max);
  TEST_RUN(math_test_clamp);
  TEST_RUN(math_test_lerp);
  TEST_RUN(math_test_trig);
  TEST_RUN(math_test_sqrt);
  TEST_RUN(math_test_pow);
}

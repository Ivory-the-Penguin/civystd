#include "../ivy_math.h"
#include "../ivy_test.h"

TEST_CASE(math_abs_signed) {
  TEST_ASSERT(IVY_ABS(123) == 123, "IVY_ABS failed for a 32-bit integer");
  TEST_ASSERT(IVY_ABS(-200) == 200,
              "IVY_ABS failed for a 32-bit negative integer");
  TEST_ASSERT(IVY_ABS(0) == 0, "IVY_ABS failed for a zeo 32-bit integer");
  TEST_ASSERT(IVY_ABS(I32_MAX) == I32_MAX,
              "IVY_ABS failed for a max 32-bit integer");
  TEST_ASSERT(IVY_ABS(I32_MIN + 1) == I32_MAX,
              "IVY_ABS failed for a min 32-bit integer");

  TEST_ASSERT(IVY_ABS(1234567890LL) == 1234567890LL,
              "IVY_ABS failed for a 64-bit integer");
  TEST_ASSERT(IVY_ABS(-9876546410LL) == 9876546410LL,
              "IVY_ABS failed for a 64-bit negative integer");
  TEST_ASSERT(IVY_ABS(0LL) == 0LL, "IVY_ABS failed for a zeo 64-bit integer");
  TEST_ASSERT(IVY_ABS(I64_MAX) == I64_MAX,
              "IVY_ABS failed for a max 64-bit integer");
  TEST_ASSERT(IVY_ABS(I64_MIN + 1) == I64_MAX,
              "IVY_ABS failed for a min 64-bit integer");

  TEST_OK();
}

TEST_CASE(math_abs_unsigned) {
  TEST_ASSERT(IVY_ABS(10203040U) == 10203040U,
              "IVY_ABS failed for a 32-bit unsigned integer");
  TEST_ASSERT(IVY_ABS(0) == 0,
              "IVY_ABS failed for a zeo 32-bit unsigned integer");
  TEST_ASSERT(IVY_ABS(U32_MAX) == U32_MAX,
              "IVY_ABS failed for a max 32-bit unsigned integer");

  TEST_ASSERT(IVY_ABS(70605040302010ULL) == 70605040302010ULL,
              "IVY_ABS failed for a 64-bit unsigned integer");
  TEST_ASSERT(IVY_ABS(0LL) == 0LL,
              "IVY_ABS failed for a zeo 64-bit unsigned integer");
  TEST_ASSERT(IVY_ABS(U64_MAX) == U64_MAX,
              "IVY_ABS failed for a max 64-bit unsigned integer");

  TEST_OK();
}

TEST_SUITE(math_suite) {
  TEST_RUN(math_abs_signed);
  TEST_RUN(math_abs_unsigned);
}

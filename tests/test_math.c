#include "../ivy_math.h"
#include "../ivy_test.h"

TEST_CASE(math_abs_signed) {
  TEST_EXPECT(IVY_ABS(123), 123, "{i}");
  TEST_EXPECT(IVY_ABS(-200), 200, "{i}");

  TEST_EXPECT(IVY_ABS(0), 0, "{i}");
  TEST_EXPECT(IVY_ABS(I32_MAX), I32_MAX, "{i}");
  TEST_EXPECT(IVY_ABS(I32_MIN + 1), I32_MAX, "{i}");

  TEST_EXPECT(IVY_ABS(1234567890LL), 1234567890LL, "{il}");
  TEST_EXPECT(IVY_ABS(-9876546410LL), 9876546410LL, "{il}");
  TEST_EXPECT(IVY_ABS(0LL), 0LL, "{il}");
  TEST_EXPECT(IVY_ABS(I64_MAX), I64_MAX, "{il}");
  TEST_EXPECT(IVY_ABS(I64_MIN + 1), I64_MAX, "{il}");

  TEST_OK();
}

TEST_CASE(math_abs_unsigned) {
  TEST_EXPECT(IVY_ABS(10203040U), 10203040U, "{iu}");
  TEST_EXPECT(IVY_ABS(0), 0, "{iu}");
  TEST_EXPECT(IVY_ABS(U32_MAX), U32_MAX, "{iu}");

  TEST_EXPECT(IVY_ABS(70605040302010ULL), 70605040302010ULL, "{iul}");
  TEST_EXPECT(IVY_ABS(0LL), 0LL, "{iul}");
  TEST_EXPECT(IVY_ABS(U64_MAX), U64_MAX, "{iul}");

  TEST_OK();
}

TEST_CASE(math_min) {
  TEST_EXPECT(IVY_MIN(0, 0), 0, "{i}");
  TEST_EXPECT(IVY_MIN(0, 100), 0, "{i}");
  TEST_EXPECT(IVY_MIN(99, 100), 99, "{i}");

  TEST_EXPECT(IVY_MIN(0, -100), -100, "{i}");
  TEST_EXPECT(IVY_MIN(-99, 100), -99, "{i}");

  TEST_EXPECT(IVY_MIN(I32_MAX, I32_MIN), I32_MIN, "{i}");
  TEST_EXPECT(IVY_MIN(I64_MAX, I64_MIN), I64_MIN, "{i}");

  TEST_OK();
}

TEST_CASE(math_max) {
  TEST_EXPECT(IVY_MAX(0, 0), 0, "{i}");
  TEST_EXPECT(IVY_MAX(0, 100), 100, "{i}");
  TEST_EXPECT(IVY_MAX(99, 100), 100, "{i}");

  TEST_EXPECT(IVY_MAX(0, -100), 0, "{i}");
  TEST_EXPECT(IVY_MAX(-99, 100), 100, "{i}");

  TEST_EXPECT(IVY_MAX(I32_MAX, I32_MIN), I32_MAX, "{i}");
  TEST_EXPECT(IVY_MAX(I64_MAX, I64_MIN), I64_MAX, "{i}");

  TEST_OK();
}

TEST_SUITE(math_suite) {
  TEST_RUN(math_abs_signed);
  TEST_RUN(math_abs_unsigned);
  TEST_RUN(math_min);
  TEST_RUN(math_max);
}

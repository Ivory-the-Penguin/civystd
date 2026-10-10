#define IVY_IMPL
#include "../ivy_core.h"
#include "../ivy_test.h"
#include "./test_core.c"
#include "./test_math.c"

i32 main(void) {
  TEST_SUITE_RUN(core_suite);
  TEST_SUITE_RUN(math_suite);
}

#define IVY_IMPL
#include "./test_core.c"
#include "./test_math.c"
#include "./test_sv.c"

i32 main(void) {
  TEST_SUITE_RUN(core_test_suite);
  TEST_SUITE_RUN(math_test_suite);
  TEST_SUITE_RUN(sv_test_suite);
}

#include "../ivy_sv.h"
#include "../ivy_test.h"

TEST_CASE(sv_test_compare) {
  TEST_EXPECT(sv_compare(sv("Hello"), sv("Hello")), 0, "{i}");

  TEST_OK();
}

TEST_SUITE(sv_test_suite) { TEST_RUN(sv_test_compare); }

#include "../ivy_core.h"
#include "../ivy_test.h"

TEST_CASE(core_type_sizes) {
  TEST_EXPECT(sizeof(i8), 1, "{iu}");
  TEST_EXPECT(sizeof(u8), 1, "{iu}");

  TEST_EXPECT(sizeof(i16), 2, "{iu}");
  TEST_EXPECT(sizeof(u16), 2, "{iu}");

  TEST_EXPECT(sizeof(i32), 4, "{iu}");
  TEST_EXPECT(sizeof(u32), 4, "{iu}");

  TEST_EXPECT(sizeof(i64), 8, "{iu}");
  TEST_EXPECT(sizeof(u64), 8, "{iu}");

  TEST_EXPECT(sizeof(b8), 1, "{iu}");
  TEST_EXPECT(sizeof(b16), 2, "{iu}");
  TEST_EXPECT(sizeof(b32), 4, "{iu}");

  TEST_EXPECT(sizeof(c8), 1, "{iu}");

  TEST_OK();
}

TEST_SUITE(core_suite) { TEST_RUN(core_type_sizes); }

#include "../ivy_core.h"
#include "../ivy_test.h"

TEST_CASE(core_type_sizes) {
  TEST_ASSERT(sizeof(i8) == 1, "i8 should be a byte long");
  TEST_ASSERT(sizeof(u8) == 1, "u8 should be a byte long");

  TEST_ASSERT(sizeof(i16) == 2, "i16 should be 2 bytes long");
  TEST_ASSERT(sizeof(u16) == 2, "u16 should be 2 bytes long");

  TEST_ASSERT(sizeof(i32) == 4, "i32 should be 4 bytes long");
  TEST_ASSERT(sizeof(u32) == 4, "u32 should be 4 bytes long");

  TEST_ASSERT(sizeof(i64) == 8, "i64 should be 8 bytes long");
  TEST_ASSERT(sizeof(u64) == 8, "u64 should be 8 bytes long");

  TEST_ASSERT(sizeof(b8) == 1, "b8 should be a byte long");
  TEST_ASSERT(sizeof(b16) == 2, "b16 should be 2 bytes long");
  TEST_ASSERT(sizeof(b32) == 4, "b32 should be 4 bytes long");

  TEST_ASSERT(sizeof(c8) == 1, "c8 should be a byte long");

  TEST_OK();
}

TEST_SUITE(core_suite) { TEST_RUN(core_type_sizes); }

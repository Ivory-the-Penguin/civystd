/*
  ----- Ivy Test ------
  Version: 1.2.0
  License: MIT-0

  This stb-style header has testing for the ivystd.
*/

#ifndef IVY_TEST_H
#define IVY_TEST_H

#define IVY_TEST_MAJOR 1
#define IVY_TEST_MINOR 2
#define IVY_TEST_FIX 1

#include "ivy_core.h"
#include "ivy_fb.h"
#include "ivy_fmt.h"

extern __thread u64 tests_passed;
extern __thread u64 total_tests;
extern __thread char *test_msg;
extern __thread u8 _scratch_buffer[1024];
extern __thread fixed_buffer_t _scratch_fb;
extern __thread allocator_t _scratch_alloc;

#define TEST_CASE_FMT "[ " ANSI_BOLD "{cs}" ANSI_RESET " ] {cs}\n"
#define TEST_CASE_ASSERT_FMT "\tAssert failed! {cs}\n"

#define TEST_CASE_RUNNING ANSI_COLOR_YELLOW "RUNNING" ANSI_RESET
#define TEST_CASE_PASSED ANSI_COLOR_GREEN ANSI_BOLD "PASSED" ANSI_RESET
#define TEST_CASE_FAILED ANSI_COLOR_RED ANSI_BOLD "FAILED" ANSI_RESET

#define TEST_SUITE_BEGIN_FMT \
  "----- " ANSI_COLOR_MAGENTA "{cs}" ANSI_RESET " -----\n"
#define TEST_SUITE_END                                               \
  ivy_print("{iul}/{iul} TESTS {cs}\n\n", tests_passed, total_tests, \
            TEST_CASE_PASSED);

#define TEST_CASE(name) IVY_FORCE_INLINE b8(name)(void)

#define TEST_RUN(name)                                   \
  do {                                                   \
    test_msg = NULL;                                     \
    total_tests++;                                       \
    ivy_print(TEST_CASE_FMT, TEST_CASE_RUNNING, #name);  \
    b8 result = (name)();                                \
    if (result) {                                        \
      ivy_print(TEST_CASE_FMT, TEST_CASE_PASSED, #name); \
      tests_passed++;                                    \
    } else {                                             \
      ivy_print(TEST_CASE_FMT, TEST_CASE_FAILED, #name); \
      if (test_msg) {                                    \
        ivy_print(TEST_CASE_ASSERT_FMT, test_msg);       \
      }                                                  \
    }                                                    \
  } while (0)

#define TEST_ASSERT(condition, msg) \
  do {                              \
    if (!(condition)) {             \
      test_msg = msg;               \
      return false;                 \
    }                               \
  } while (0)

#define TEST_ASSERT_FMT(condition, fmt, ...)                             \
  do {                                                                   \
    if (!(condition)) {                                                  \
      if (_scratch_fb.buffer == NULL) {                                  \
        _scratch_fb = fb_make(_scratch_buffer, 1024);                    \
        _scratch_alloc = fb_make_allocator(&_scratch_fb);                \
      }                                                                  \
      fb_clear(&_scratch_fb);                                            \
      test_msg =                                                         \
          (char *)fmt_format(_scratch_alloc, sv(fmt), __VA_ARGS__).data; \
      return false;                                                      \
    }                                                                    \
  } while (0)

#define TEST_EXPECT(a, b, fmt)                                                 \
  TEST_ASSERT_FMT(a == b,                                                      \
                  "Check for {cs} failed: Expected " fmt ", got " fmt ".", #a, \
                  b, a)

#define TEST_OK() \
  do {            \
    return true;  \
  } while (0)

#define TEST_SUITE(name) IVY_FORCE_INLINE void(name)(void)

#define TEST_SUITE_RUN(name)                \
  do {                                      \
    total_tests = 0;                        \
    tests_passed = 0;                       \
    ivy_print(TEST_SUITE_BEGIN_FMT, #name); \
    (name)();                               \
    TEST_SUITE_END                          \
  } while (0)

#ifdef IVY_IMPL

__thread u64 tests_passed;
__thread u64 total_tests;
__thread char *test_msg;
__thread u8 _scratch_buffer[1024];
__thread fixed_buffer_t _scratch_fb;
__thread allocator_t _scratch_alloc;

#endif

#endif

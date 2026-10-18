/*
  ----- Ivy Test ------
  Version: 1.3.1
  License: MIT-0

  This stb-style header has testing for the ivystd.
*/

#ifndef IVY_TEST_H
#define IVY_TEST_H

#include "ivy_core.h"
#include "ivy_fb.h"
#include "ivy_fmt.h"
#include "ivy_math.h"

extern IVY_THREAD_LOCAL u64 tests_passed;
extern IVY_THREAD_LOCAL u64 total_tests;
extern IVY_THREAD_LOCAL char *test_msg;
extern IVY_THREAD_LOCAL u8 _scratch_buffer[1024];
extern IVY_THREAD_LOCAL fixed_buffer_t _scratch_fb;
extern IVY_THREAD_LOCAL allocator_t _scratch_alloc;

#define TEST_CASE_FMT "[ " ANSI_BOLD "{cs}" ANSI_RESET " ] {cs}\n"
#define TEST_CASE_ASSERT_FMT "\tAssert failed! {cs}\n"

#define TEST_CASE_RUNNING ANSI_COLOR_YELLOW "RUNNING" ANSI_RESET
#define TEST_CASE_PASSED ANSI_COLOR_GREEN ANSI_BOLD "PASSED" ANSI_RESET
#define TEST_CASE_FAILED ANSI_COLOR_RED ANSI_BOLD "FAILED" ANSI_RESET

#define TEST_SUITE_BEGIN_FMT \
  "----- " ANSI_COLOR_MAGENTA "{cs}" ANSI_RESET " -----\n"
#define TEST_SUITE_END                                                 \
  ivy_print("{i:ul}/{i:ul} TESTS {cs}\n\n", tests_passed, total_tests, \
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

#define TEST_EXPECT_FLOAT(a, b, precision)              \
  TEST_ASSERT_FMT(IVY_COMPARE_DECIMAL(a, b, precision), \
                  "Check for {cs} failed: Expected {f}, got {f}.", #a, b, a)

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

IVY_THREAD_LOCAL u64 tests_passed;
IVY_THREAD_LOCAL u64 total_tests;
IVY_THREAD_LOCAL char *test_msg;
IVY_THREAD_LOCAL u8 _scratch_buffer[1024];
IVY_THREAD_LOCAL fixed_buffer_t _scratch_fb;
IVY_THREAD_LOCAL allocator_t _scratch_alloc;

#endif

#endif

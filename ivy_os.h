/*
  ----- Ivy Os -----
  Version: 0.1.0
  License: MIT-0
*/

#ifndef IVY_OS_H
#define IVY_OS_H

#include "ivy_core.h"

#define OS_NR_REG "rax"
#define OS_RET_REG "rax"
#define OS_ARG0_REG "rdi"
#define OS_ARG1_REG "rsi"
#define OS_ARG2_REG "rdx"
#define OS_ARG3_REG "r10"
#define OS_ARG4_REG "r8"
#define OS_ARG5_REG "r9"

#define OS_ASM __asm__

#define os_syscall0(id)                                    \
  ({                                                       \
    register u64 _result OS_ASM(OS_RET_REG);               \
    register u64 _id OS_ASM(OS_NR_REG) = (u64)id;          \
    OS_ASM volatile("syscall" : "=r"(_result) : "r"(_id)); \
    _result;                                               \
  })

#define os_syscall1(id, arg0)                                        \
  ({                                                                 \
    register u64 _result OS_ASM(OS_RET_REG);                         \
    register u64 _id OS_ASM(OS_NR_REG) = (u64)id;                    \
    register u64 _a0 OS_ASM(OS_ARG0_REG) = (u64)arg0;                \
    OS_ASM volatile("syscall" : "=r"(_result) : "r"(_id), "r"(_a0)); \
    _result;                                                         \
  })

#define os_syscall2(id, arg0, arg1)                                            \
  ({                                                                           \
    register u64 _result OS_ASM(OS_RET_REG);                                   \
    register u64 _id OS_ASM(OS_NR_REG) = (u64)id;                              \
    register u64 _a0 OS_ASM(OS_ARG0_REG) = (u64)arg0;                          \
    register u64 _a1 OS_ASM(OS_ARG1_REG) = (u64)arg1;                          \
    OS_ASM volatile("syscall" : "=r"(_result) : "r"(_id), "r"(_a0), "r"(_a1)); \
    _result;                                                                   \
  })

#define os_syscall3(id, arg0, arg1, arg2)                                     \
  ({                                                                          \
    register u64 _result OS_ASM(OS_RET_REG);                                  \
    register u64 _id OS_ASM(OS_NR_REG) = (u64)id;                             \
    register u64 _a0 OS_ASM(OS_ARG0_REG) = (u64)arg0;                         \
    register u64 _a1 OS_ASM(OS_ARG1_REG) = (u64)arg1;                         \
    register u64 _a2 OS_ASM(OS_ARG2_REG) = (u64)arg2;                         \
    OS_ASM volatile("syscall" : "=r"(_result) : "r"(_id), "r"(_a0), "r"(_a1), \
                    "r"(_a2));                                                \
    _result;                                                                  \
  })

IVY_FORCE_INLINE void os_exit(u64 return_code) {
  os_syscall1(0x3c, return_code);
}

#endif

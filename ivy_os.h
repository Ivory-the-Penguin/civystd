/*
  ----- Ivy Os -----
  Version: 0.3.0
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
    OS_ASM volatile("syscall" : "=a"(_result) : "r"(_id)); \
    _result;                                               \
  })

#define os_syscall1(id, arg0)                                        \
  ({                                                                 \
    register u64 _result OS_ASM(OS_RET_REG);                         \
    register u64 _id OS_ASM(OS_NR_REG) = (u64)id;                    \
    register u64 _a0 OS_ASM(OS_ARG0_REG) = (u64)arg0;                \
    OS_ASM volatile("syscall" : "=a"(_result) : "r"(_id), "r"(_a0)); \
    _result;                                                         \
  })

#define os_syscall2(id, arg0, arg1)                                            \
  ({                                                                           \
    register u64 _result OS_ASM(OS_RET_REG);                                   \
    register u64 _id OS_ASM(OS_NR_REG) = (u64)id;                              \
    register u64 _a0 OS_ASM(OS_ARG0_REG) = (u64)arg0;                          \
    register u64 _a1 OS_ASM(OS_ARG1_REG) = (u64)arg1;                          \
    OS_ASM volatile("syscall" : "=a"(_result) : "r"(_id), "r"(_a0), "r"(_a1)); \
    _result;                                                                   \
  })

#define os_syscall3(id, arg0, arg1, arg2)                                     \
  ({                                                                          \
    register u64 _result OS_ASM(OS_RET_REG);                                  \
    register u64 _id OS_ASM(OS_NR_REG) = (u64)id;                             \
    register u64 _a0 OS_ASM(OS_ARG0_REG) = (u64)arg0;                         \
    register u64 _a1 OS_ASM(OS_ARG1_REG) = (u64)arg1;                         \
    register u64 _a2 OS_ASM(OS_ARG2_REG) = (u64)arg2;                         \
    OS_ASM volatile("syscall" : "=a"(_result) : "r"(_id), "r"(_a0), "r"(_a1), \
                    "r"(_a2));                                                \
    _result;                                                                  \
  })

#define os_syscall4(id, arg0, arg1, arg2, arg3)                               \
  ({                                                                          \
    register u64 _result OS_ASM(OS_RET_REG);                                  \
    register u64 _id OS_ASM(OS_NR_REG) = (u64)id;                             \
    register u64 _a0 OS_ASM(OS_ARG0_REG) = (u64)arg0;                         \
    register u64 _a1 OS_ASM(OS_ARG1_REG) = (u64)arg1;                         \
    register u64 _a2 OS_ASM(OS_ARG2_REG) = (u64)arg2;                         \
    register u64 _a3 OS_ASM(OS_ARG3_REG) = (u64)arg3;                         \
    OS_ASM volatile("syscall" : "=a"(_result) : "r"(_id), "r"(_a0), "r"(_a1), \
                    "r"(_a2), "r"(_a3));                                      \
    _result;                                                                  \
  })

#define os_syscall5(id, arg0, arg1, arg2, arg3, arg4)                         \
  ({                                                                          \
    register u64 _result OS_ASM(OS_RET_REG);                                  \
    register u64 _id OS_ASM(OS_NR_REG) = (u64)id;                             \
    register u64 _a0 OS_ASM(OS_ARG0_REG) = (u64)arg0;                         \
    register u64 _a1 OS_ASM(OS_ARG1_REG) = (u64)arg1;                         \
    register u64 _a2 OS_ASM(OS_ARG2_REG) = (u64)arg2;                         \
    register u64 _a3 OS_ASM(OS_ARG3_REG) = (u64)arg3;                         \
    register u64 _a4 OS_ASM(OS_ARG4_REG) = (u64)arg4;                         \
    OS_ASM volatile("syscall" : "=a"(_result) : "r"(_id), "r"(_a0), "r"(_a1), \
                    "r"(_a2), "r"(_a3), "r"(_a4));                            \
    _result;                                                                  \
  })

#define os_syscall6(id, arg0, arg1, arg2, arg3, arg4, arg5)                   \
  ({                                                                          \
    register u64 _result OS_ASM(OS_RET_REG);                                  \
    register u64 _id OS_ASM(OS_NR_REG) = (u64)id;                             \
    register u64 _a0 OS_ASM(OS_ARG0_REG) = (u64)arg0;                         \
    register u64 _a1 OS_ASM(OS_ARG1_REG) = (u64)arg1;                         \
    register u64 _a2 OS_ASM(OS_ARG2_REG) = (u64)arg2;                         \
    register u64 _a3 OS_ASM(OS_ARG3_REG) = (u64)arg3;                         \
    register u64 _a4 OS_ASM(OS_ARG4_REG) = (u64)arg4;                         \
    register u64 _a5 OS_ASM(OS_ARG5_REG) = (u64)arg5;                         \
    OS_ASM volatile("syscall" : "=a"(_result) : "r"(_id), "r"(_a0), "r"(_a1), \
                    "r"(_a2), "r"(_a3), "r"(_a4), "r"(_a5));                  \
    _result;                                                                  \
  })

IVY_FORCE_INLINE void os_exit(u64 return_code) {
  os_syscall1(0x3c, return_code);
}

#endif

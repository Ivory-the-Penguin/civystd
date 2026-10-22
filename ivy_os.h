/*
  ----- Ivy Os -----
  Version: 0.1.0
  License: MIT-0
*/

#ifndef IVY_OS_H
#define IVY_OS_H

#include "ivy_core.h"

#define OS_ASM __asm__

#define os_syscall0(id)                                    \
  ({                                                       \
    register u64 _result OS_ASM("rax");                    \
    register u64 _id OS_ASM("rax") = (u64)id;              \
    OS_ASM volatile("syscall" : "=r"(_result) : "r"(_id)); \
    _result;                                               \
  })

#define os_syscall1(id, arg1)                                        \
  ({                                                                 \
    register u64 _result OS_ASM("rax");                              \
    register u64 _id OS_ASM("rax") = (u64)id;                        \
    register u64 _a1 OS_ASM("rdi") = (u64)arg1;                      \
    OS_ASM volatile("syscall" : "=r"(_result) : "r"(_id), "r"(_a1)); \
    _result;                                                         \
  })

IVY_FORCE_INLINE void os_exit(u64 return_code) {
  os_syscall1(0x3c, return_code);
}

#endif

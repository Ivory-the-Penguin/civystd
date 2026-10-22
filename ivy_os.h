/*
  ----- Ivy Os -----
  Version: 0.5.1
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

#define OS_NR_EXIT 0x3c
#define OS_NR_READ 0x00
#define OS_NR_WRITE 0x01
#define OS_NR_OPEN 0x02
#define OS_NR_CLOSE 0x03
#define OS_NR_CREAT 0x55
#define OS_NR_OPENAT 0x101
#define OS_NR_PREAD64 0x11
#define OS_NR_PWRITE64 0x12
#define OS_NR_STATX 0x14c
#define OS_NR_GETDENTS64 0xd9

typedef struct {
  u64 sec;
  u32 nsec;
  u32 _pad;
} os_statx_ts_t;

typedef struct {
  u32 mask;

  u32 blksize;
  u64 attributes;
  u32 nlink;
  u32 uid;
  u32 gid;
  u16 mode;
  u64 ino;
  u64 size;
  u64 blocks;
  u64 attributes_mask;

  os_statx_ts_t last_acess;
  os_statx_ts_t creation;
  os_statx_ts_t last_status_change;
  os_statx_ts_t last_mod;

  u32 rdev_major;
  u32 rdev_minor;

  u32 dev_major;
  u32 dev_minor;

  u32 mnt_id;

  u32 dio_mem_align;
  u32 dio_offset_align;

  u64 subvol;

  u32 atomic_write_unit_min;
  u32 atomic_write_unit_max;
  u32 atomic_write_segments_max;

  u32 dio_read_offset_align;

  u32 atomic_write_unit_max_opt;
} os_statx_t;

typedef struct {
  u64 ino;
  i64 offset;
  u16 reclen;
  u8 type;

  char name[];
} os_dirent_t;

IVY_FORCE_INLINE void os_exit(u64 return_code) {
  os_syscall1(OS_NR_EXIT, return_code);
}

IVY_FORCE_INLINE i64 os_open(const char *path, u64 flags, u64 mode) {
  return os_syscall3(OS_NR_OPEN, path, flags, mode);
}

IVY_FORCE_INLINE i64 os_creat(const char *path, u64 mode) {
  return os_syscall2(OS_NR_CREAT, path, mode);
}

IVY_FORCE_INLINE i64 os_openat(u64 dirfd, const char *path, u64 flags,
                               u64 mode) {
  return os_syscall4(OS_NR_OPENAT, dirfd, path, flags, mode);
}

IVY_FORCE_INLINE i64 os_pread64(u64 fd, void *buf, u64 count, i64 offset) {
  return os_syscall4(OS_NR_PREAD64, fd, buf, count, offset);
}

IVY_FORCE_INLINE i64 os_pwrite64(u64 fd, void *buf, u64 count, i64 offset) {
  return os_syscall4(OS_NR_PWRITE64, fd, buf, count, offset);
}

IVY_FORCE_INLINE i64 os_getdents64(u64 fd, os_dirent_t *dirents, u64 count) {
  return os_syscall3(OS_NR_GETDENTS64, fd, dirents, count);
}

IVY_FORCE_INLINE i64 os_write(u64 fd, const void *buf, u64 count) {
  return os_syscall3(OS_NR_WRITE, fd, buf, count);
}

IVY_FORCE_INLINE i64 os_read(u64 fd, void *buf, u64 count) {
  return os_syscall3(OS_NR_READ, fd, buf, count);
}

IVY_FORCE_INLINE i64 os_statx(u64 dirfd, const char *path, u64 flags, u64 mask,
                              os_statx_t *statx_buf) {
  return os_syscall5(OS_NR_STATX, dirfd, path, flags, mask, statx_buf);
}

IVY_FORCE_INLINE i64 os_close(u64 fd) { return os_syscall1(OS_NR_CLOSE, fd); }

#endif

/*
  ----- Ivy Build -----
  Version: 0.1.0
  License: MIT-0

  This header only library has a build system for the ivystd
*/

#ifndef IVY_BUILD_H
#define IVY_BUILD_H

#include "ivy_core.h"
#include "ivy_list.h"
#include "ivy_sb.h"
#include "ivy_sv.h"

typedef struct {
  string_view_t program;
  list_sv_t args;
} build_cmd_t;

IVY_FORCE_INLINE build_cmd_t build_cmd_make(string_view_t program) {
  build_cmd_t out;

  out.program = program;

  // temporary heap, until i implement global build arena
  list_init(&out.args, heap);

  return out;
}

IVY_FORCE_INLINE void build_cmd_add_arg(build_cmd_t *cmd, string_view_t arg) {
  list_push(&cmd->args, arg);
}

IVY_FORCE_INLINE i32 build_cmd_run(build_cmd_t *cmd) {
  u64 capacity = cmd->program.length;
  LIST_FOREACH(&cmd->args, i, 0) { capacity += 1 + cmd->args.data[i].length; }

  string_builder_t buffer = sb_make_with_reserved(heap, capacity);

  sb_append_sv(&buffer, cmd->program);

  LIST_FOREACH(&cmd->args, i, 0) {
    sb_append_char(&buffer, ' ');
    sb_append_sv(&buffer, cmd->args.data[i]);
  }

  string_view_t cmd_str = sb_to_sv(heap, &buffer);
  i32 out = system((char *)cmd_str.data);

  sb_free(&buffer);
  ivy_free(heap, (void *)cmd_str.data);

  return out;
}

#endif

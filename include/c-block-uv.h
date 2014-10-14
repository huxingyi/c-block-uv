#ifndef C_BLOCK_UV_H
#define C_BLOCK_UV_H
#include "c-block.h"
#include "uv.h"

typedef struct _c_fs_stat
{
  struct c_block block;
  uv_loop_t* loop;
  uv_fs_t req;
  const char* path;
} c_fs_stat_t;

int c_fs_stat(c_fs_stat_t *ctx);

#endif

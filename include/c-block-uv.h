/* Copyright (c) 2014, huxingyi@msn.com
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef C_BLOCK_UV_H
#define C_BLOCK_UV_H

#include "c-block.h"
#include "uv.h"

#define C_BLOCK_UV_COMMON_FIELDS \
  struct c_block block;          \
  uv_loop_t *loop;               \
  void *data;                    \
  int status

typedef struct _c_fs_stat {
  C_BLOCK_UV_COMMON_FIELDS;
  uv_fs_t req;
  const char *path;
} c_fs_stat_t;
int c_fs_stat(c_fs_stat_t *ctx);

typedef struct _c_shutdown {
  C_BLOCK_UV_COMMON_FIELDS;
  uv_shutdown_t req;
  uv_stream_t *handle;
} c_shutdown_t;
int c_shutdown(c_shutdown_t *ctx);

typedef struct _c_close {
  C_BLOCK_UV_COMMON_FIELDS;
  void *old_data;
  uv_handle_t *handle;
} c_close_t;
int c_close(c_close_t *ctx);

typedef struct _c_listen {
  C_BLOCK_UV_COMMON_FIELDS;
  void *old_data;
  uv_stream_t *stream;
  int backlog;
} c_listen_t;
int c_listen(c_listen_t *ctx);

#endif

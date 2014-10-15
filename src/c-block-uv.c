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

#include "c-block-uv.h"

static void c_fs_stat_after(uv_fs_t* req) {
  c_fs_stat_t *ctx = (c_fs_stat_t *)req->data;
  c_finished(ctx);
}
int c_fs_stat(c_fs_stat_t *ctx) {
  ctx->req.data = ctx;
  if (0 != (ctx->status=uv_fs_stat(ctx->loop, &ctx->req, ctx->path, 
                                   c_fs_stat_after))) {
    return c_unhandled(ctx);
  }
  return c_pending(ctx);
}

static void c_shutdown_after(uv_shutdown_t* req, int status) {
  c_shutdown_t *ctx = (c_shutdown_t *)req->data;
  ctx->status = status;
  c_finished(ctx);
}
int c_shutdown(c_shutdown_t *ctx) {
  ctx->req.data = ctx;
  if (0 != (ctx->status=uv_shutdown(&ctx->req, ctx->handle, 
                                    c_shutdown_after))) {
    return c_unhandled(ctx);
  }
  return c_pending(ctx);
}

static void c_close_after(uv_handle_t* handle) {
  c_close_t *ctx = (c_close_t *)handle->data;
  handle->data = ctx->old_data;
  c_finished(ctx);
}
int c_close(c_close_t *ctx) {
  ctx->old_data = ctx->handle->data;
  ctx->handle->data = ctx;
  uv_close(ctx->handle, c_close_after);
  return c_pending(ctx);
}

static void c_listen_after(uv_stream_t* server, int status) {
  c_listen_t *ctx = (c_listen_t *)server->data;
  ctx->status = status;
  server->data = ctx->old_data;
  c_finished(ctx);
}
int c_listen(c_listen_t *ctx) {
  ctx->old_data = ctx->stream->data;
  ctx->stream->data = ctx;
  if (0 != (ctx->status=uv_listen(ctx->stream, ctx->backlog, 
                                  c_listen_after))) {
    return c_unhandled(ctx);
  }
  return c_pending(ctx);
}

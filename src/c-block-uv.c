#include "c-block-uv.h"

static void c_fs_stat_after(uv_fs_t* req) {
  c_fs_stat_t *ctx = (c_fs_stat_t *)req->data;
  return c_finished(ctx);
}

int c_fs_stat(c_fs_stat_t *ctx) {
  ctx->req.data = ctx;
  if (0 != uv_fs_stat(ctx->loop, &ctx->req, ctx->path, c_fs_stat_after)) {
    return c_unhandled(ctx);
  }
  return c_pending(ctx);
}

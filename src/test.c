#include "c-block-uv.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct task {
  struct c_block block;
  union {
    c_fs_stat_t stat;
  } u;
};

int task_clousre(struct task *ctx) {

  printf("enter task_clousre\n");
  
  c_begin(ctx, task_clousre);
  
  printf("before c_fs_stat\n");
  
  ctx->u.stat.loop = uv_default_loop();
  ctx->u.stat.path = "./test.exe";
  c_call(&ctx->u.stat, c_fs_stat);
  
  printf("stat result:%d\n", ctx->u.stat.req.result);
  
  uv_fs_req_cleanup(&ctx->u.stat.req);
  
  printf("after c_fs_stat\n");
  
  c_end();
  
  printf("free ctx\n");
  free(ctx);
  
  return 0;
}

void test_c_fs_stat(void) {
  struct task *ctx = (struct task *)malloc(sizeof(struct task));
  c_init(ctx);
  task_clousre(ctx);
}

int main(int argc, char *argv[]) {

  printf("enter\n");
  
  test_c_fs_stat();
  
  uv_run(uv_default_loop(), UV_RUN_DEFAULT);
  
  printf("leave\n");
  
  return 0;
}

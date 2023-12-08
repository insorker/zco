#include "zco.h"
#include <string.h>
#include <malloc.h>
#include <assert.h>

#define zco_panic(expr, msg) \
  ({ if (expr == 0) { perror(msg); assert(0); } })
#define ZCO_POOL_SIZE (128)
#define ZCO_STACK_SIZE (64 * 1024)

int zco_gcid;
zco_t *zco_pool[ZCO_POOL_SIZE];

static zco_t *zco_pool_new()
{
  for (int i = 0; i < ZCO_POOL_SIZE; i++) {
    if (!zco_pool[i]) {
      zco_pool[i] = malloc(sizeof(zco_t));
      zco_pool[i]->cid = i;
      return zco_pool[i];
    }
  }

  zco_panic(0, "zco pool is full.");
}

static void zco_pool_free(zco_t *zco)
{
  free(zco->context.uc_stack.ss_sp);
  free(zco);
}

int zco_create(void (*fn)(void *), void *arg)
{
  zco_t *zco = zco_pool_new();

  zco->fn = fn;
  zco->arg = arg;
  zco->status = ZCO_STATUS_NEW;

  return zco->cid;
}

void zco_resume(int cid)
{
  if (0 >= cid || cid >= ZCO_POOL_SIZE) {
    return;
  }
  else if (zco_pool[cid] == NULL) {
    return;
  }

  zco_t *zco = zco_pool[cid];
  zco_t *zco_caller = zco_pool[zco_gcid];

  zco->cid_caller = zco_gcid;
  zco_gcid = zco->cid;

  if (zco->status == ZCO_STATUS_NEW) {
    getcontext(&zco->context);
    zco->context.uc_stack.ss_sp = malloc(ZCO_STACK_SIZE);
    zco->context.uc_stack.ss_size = ZCO_STACK_SIZE;
    zco->context.uc_link = &zco_caller->context;
    makecontext(&zco->context, (void (*)(void))zco->fn, 1, zco->arg);
  }

  zco->status = ZCO_STATUS_RUNNING;
  swapcontext(&zco_caller->context, &zco->context);
  zco->status = ZCO_STATUS_FINISHED;

  zco_gcid = zco->cid_caller;
}

void zco_yield()
{
  zco_t *zco = zco_pool[zco_gcid];

  zco_gcid = zco->cid_caller;

  zco->status = ZCO_STATUS_SUSPENDED;
  swapcontext(&zco_pool[zco->cid]->context, &zco_pool[zco_gcid]->context);
  zco->status = ZCO_STATUS_RUNNING;

  zco_gcid = zco->cid;
}

__attribute__((constructor)) void zco_constructor()
{
  zco_t *zco = zco_pool_new();
  zco->status = ZCO_STATUS_RUNNING;
  getcontext(&zco->context);
  zco_gcid = zco->cid;
}

__attribute__((destructor)) void zco_destructor()
{
  for (int i = 0; i < ZCO_POOL_SIZE; i++) {
    if (zco_pool[i]) {
      zco_pool_free(zco_pool[i]);
    }
  }
}
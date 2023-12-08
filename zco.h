#ifndef ZCO_H
#define ZCO_H

#include <ucontext.h>

enum zco_status {
  ZCO_STATUS_NEW,
  ZCO_STATUS_RUNNING,
  ZCO_STATUS_SUSPENDED,
  ZCO_STATUS_FINISHED
};

typedef struct {
  void (*fn)(void *);
  void *arg;

  int cid;
  int cid_caller;
  ucontext_t context;
  enum zco_status status;
} zco_t;

int zco_create(void (*fn)(void *), void *arg);
void zco_resume(int cid);
void zco_yield();

#endif
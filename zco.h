#ifndef ZCO_H
#define ZCO_H

#include <ucontext.h>
#include <stdbool.h>
#include "mutex.h"

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

typedef struct zco_queue_node_t {
  void *value;
  struct zco_queue_node_t *next;
} zco_queue_node_t;

typedef struct {
  mutex_t mutex;
  zco_queue_node_t *head;
  zco_queue_node_t *tail;
} zco_queue_t;

zco_queue_t *zco_queue_new();
void zco_queue_free(zco_queue_t *zco_queue);
bool zco_queue_empty(zco_queue_t *zco_queue);
void zco_queue_put(zco_queue_t *zco_queue, void *value);
void *zco_queue_get(zco_queue_t *zco_queue);

#endif
#include "zco_queue.h"
#include "zco_utils.h"
#include <string.h>
#include <malloc.h>

/**
 * @brief 创建 zco queue 节点
 * 
 * @param value 
 * @return zco_queue_node_t* 
 */
static zco_queue_node_t *zco_queue_node_new(void *value)
{
  zco_panic(value != NULL, "zco queue node value is empty.");

  zco_queue_node_t *zco_queue_node = malloc(sizeof(zco_queue_node_t));

  zco_queue_node->value = value;
  zco_queue_node->next = NULL;

  return zco_queue_node;
}

/**
 * @brief 释放 zco queue 节点
 * 
 * @param zco_queue_node 
 */
static void zco_queue_node_free(zco_queue_node_t *zco_queue_node)
{
  if (zco_queue_node) {
    free(zco_queue_node);
  }
}

zco_queue_t *zco_queue_new()
{
  zco_queue_t *zco_queue = malloc(sizeof(zco_queue_t));
  
  zco_queue->mutex = 0;
  zco_queue->head = NULL;
  zco_queue->tail = NULL;

  return zco_queue;
}

void zco_queue_free(zco_queue_t *zco_queue)
{
  if (zco_queue) {
    while (zco_queue->head) {
      zco_queue_node_t *oldhead = zco_queue->head;
      zco_queue->head = zco_queue->head->next;

      zco_queue_node_free(oldhead);
    }

    free(zco_queue);
  }
}

bool zco_queue_isempty(zco_queue_t *zco_queue)
{
  zco_panic(zco_queue != NULL, "zco queue is NULL.");

  return zco_queue->head == NULL;
}

void zco_queue_put(zco_queue_t *zco_queue, void *value)
{
  mutex_lock(&zco_queue->mutex);

  if (zco_queue->head == NULL) {
    zco_queue->head = zco_queue_node_new(value);
    zco_queue->tail = zco_queue->head;
  }
  else {
    zco_queue->tail->next = zco_queue_node_new(value);
    zco_queue->tail = zco_queue->tail->next;
  }

  mutex_unlock(&zco_queue->mutex);
}

void *zco_queue_get(zco_queue_t *zco_queue)
{
  mutex_lock(&zco_queue->mutex);

  if (zco_queue->head == NULL) {
    zco_panic(0, "zco queue is emty.");
  }
  else if (zco_queue->head == zco_queue->tail) {
    void *value = zco_queue->head->value;

    zco_queue_node_free(zco_queue->head);
    zco_queue->head = NULL;
    zco_queue->tail = NULL;

    mutex_unlock(&zco_queue->mutex);
    return value;
  }
  else {
    zco_queue_node_t *oldhead = zco_queue->head;
    void *value = oldhead->value;

    zco_queue->head = zco_queue->head->next;
    zco_queue_node_free(oldhead);

    mutex_unlock(&zco_queue->mutex);
    return value;
  }
}
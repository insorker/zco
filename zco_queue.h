#ifndef ZCO_QUEUE
#define ZCO_QUEUE

#include "mutex.h"
#include <stdbool.h>

/**
 * @brief zco queue 节点
 * 
 */
typedef struct zco_queue_node_t {
  void *value;
  struct zco_queue_node_t *next;
} zco_queue_node_t;

/**
 * @brief zco queue
 * 
 */
typedef struct {
  mutex_t mutex;
  zco_queue_node_t *head;
  zco_queue_node_t *tail;
} zco_queue_t;

/**
 * @brief 创建 zco queue
 * 
 * @return zco_queue_t* 
 */
zco_queue_t *zco_queue_new();

/**
 * @brief 释放 zco queue。
 * * 注意 zco queue 节点的 value 值不会释放。
 * 
 * @param zco_queue 
 */
void zco_queue_free(zco_queue_t *zco_queue);

/**
 * @brief 判断 zco queue 是否为空
 * 
 * @param zco_queue 
 * @return true 
 * @return false 
 */
bool zco_queue_isempty(zco_queue_t *zco_queue);

/**
 * @brief zco queue 加入元素
 * 
 * @param zco_queue 
 * @param value 
 * @param size 
 */
void zco_queue_put(zco_queue_t *zco_queue, void *value);

/**
 * @brief zco queue 取出元素
 * 
 * @param zco_queue 
 * @return void* 
 */
void *zco_queue_get(zco_queue_t *zco_queue);

#endif
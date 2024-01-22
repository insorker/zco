#ifndef ZCO_H
#define ZCO_H

#include <ucontext.h>

/**
 * @brief zco 当前状态
 * 
 */
enum zco_status {
  ZCO_STATUS_NEW,
  ZCO_STATUS_RUNNING,
  ZCO_STATUS_SUSPENDED,
  ZCO_STATUS_FINISHED
};

/**
 * @brief zco_t
 * 
 */
typedef struct {
  void (*fn)(void *);
  void *arg;

  int cid;
  int cid_caller;
  ucontext_t context;
  enum zco_status status;
} zco_t;

/**
 * @brief 创建协程（仅创建，不执行）
 * 
 * @param fn 协程函数
 * @param arg 协程函数参数
 * @return int 协程id
 */
int zco_create(void (*fn)(void *), void *arg);

/**
 * @brief 恢复执行协程
 * 
 * @param cid 协程id
 */
void zco_resume(int cid);

/**
 * @brief 暂停执行协程
 * 
 */
void zco_yield();

#endif
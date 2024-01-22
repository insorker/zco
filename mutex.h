#ifndef MUTEX_H
#define MUTEX_H

/**
 * @brief 自旋锁
 * 
 */
typedef int mutex_t;

/**
 * @brief 上锁
 * 
 * @param mutex_t
 */
void mutex_lock(mutex_t *mutex);

/**
 * @brief 解锁
 * 
 * @param mutex_t
 */
void mutex_unlock(mutex_t *mutex);

#endif
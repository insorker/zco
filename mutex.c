#include "mutex.h"

#define MUTEX_LOCK 1
#define MUTEX_UNLOCK 0

int xchg(volatile int *addr, int newval)
{
  int result;
  asm volatile ("lock xchg %0, %1"
    : "+m"(*addr), "=a"(result) : "1"(newval));
  return result;
}

void mutex_lock(mutex_t *mutex)
{
  int state;

  do {
   state = xchg(mutex, MUTEX_LOCK);
  } while (state == MUTEX_LOCK);
}

void mutex_unlock(mutex_t *mutex)
{
  xchg(mutex, MUTEX_UNLOCK);
}

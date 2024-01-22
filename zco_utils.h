#ifndef ZCO_UTILS_H
#define ZCO_UTILS_H

#include <assert.h>

#define zco_panic(expr, msg) \
  ({ if ((expr) == 0) { perror(msg); assert(0); } })

#endif
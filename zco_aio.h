#ifndef ZCO_AIO_H
#define ZCO_AIO_H

#include <stdio.h>

typedef struct {
  FILE *file;
  char *buffer;
  int nbytes;
} zco_aio_t;

void zco_aio_read(zco_aio_t *zco_aio);
void zco_aio_write(zco_aio_t *zco_aio);

#endif
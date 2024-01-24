#ifndef ZCO_AIO_H
#define ZCO_AIO_H

#include <stdio.h>
#include <aio.h>

typedef struct {
  int cid;
  struct aiocb aio;
} zco_aio_t;

zco_aio_t zco_aio_create(int fd, char *buffer, int nbytes);
void zco_aio_read(zco_aio_t *zco_aio);
void zco_aio_write(zco_aio_t *zco_aio);
void zco_aio_return(zco_aio_t *zco_aio);

#endif
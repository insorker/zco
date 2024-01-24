#include "zco_aio.h"
#include "zco.h"
#include "zco_utils.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

static void zco_aio_read_fn(void *arg)
{
  zco_aio_t *zco_aio = arg;
  
  zco_panic(aio_read(&zco_aio->aio) != -1, "aio read error.");

  zco_yield();

  while (aio_error(&zco_aio->aio) == EINPROGRESS)
    ;
  zco_aio->aio.aio_nbytes = aio_return(&zco_aio->aio);
}

static void zco_aio_write_fn(void *arg)
{
  zco_aio_t *zco_aio = arg;

  zco_panic(aio_write(&zco_aio->aio) != -1, "aio read error.");

  zco_yield();

  while (aio_error(&zco_aio->aio) == EINPROGRESS)
    ;
  zco_aio->aio.aio_nbytes = aio_return(&zco_aio->aio);
}

zco_aio_t zco_aio_create(int fd, char *buffer, int nbytes)
{
  zco_aio_t zco_aio;

  zco_aio.cid = -1;
  memset(&zco_aio.aio, 0, sizeof(struct aiocb));
  zco_aio.aio.aio_fildes = fd;
  zco_aio.aio.aio_buf = buffer;
  zco_aio.aio.aio_nbytes = nbytes;
  zco_aio.aio.aio_offset = 0;

  return zco_aio;
}

void zco_aio_read(zco_aio_t *zco_aio)
{
  zco_panic(zco_aio != NULL, "zco aio is NULL.");

  zco_aio->cid = zco_create(zco_aio_read_fn, zco_aio);
  zco_resume(zco_aio->cid);
}

void zco_aio_write(zco_aio_t *zco_aio)
{
  zco_panic(zco_aio != NULL, "zco aio is NULL.");

  zco_aio->cid = zco_create(zco_aio_write_fn, zco_aio);
  zco_resume(zco_aio->cid);
}

void zco_aio_return(zco_aio_t *zco_aio)
{
  zco_resume(zco_aio->cid);
}
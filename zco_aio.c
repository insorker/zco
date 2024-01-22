#include "zco_aio.h"
#include "zco.h"
#include "zco_utils.h"

static void zco_aio_read_fn(void *arg)
{
  zco_aio_t *zco_aio = arg;
  
  zco_aio->nbytes = fread(zco_aio->buffer, 1, zco_aio->nbytes, zco_aio->file);

  zco_yield();
}

void zco_aio_read(zco_aio_t *zco_aio)
{
  zco_panic(zco_aio != NULL, "zco aio is NULL.");
  zco_panic(zco_aio->buffer != NULL, "zco aio buffer is NULL.");

  int cid = zco_create(zco_aio_read_fn, zco_aio);
  zco_resume(cid);
}
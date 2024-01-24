#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <malloc.h>
#include "../zco.h"
#include "../zco_aio.h"

void test_read()
{
  int fd_read = open("test_read.txt", O_RDONLY);
  int nbytes = 1024;
  char *buffer = malloc(nbytes);

  if (fd_read == -1) {
    perror("file open failed.");
    exit(-1);
  }

  zco_aio_t zco_aio = zco_aio_create(fd_read, buffer, nbytes);
  zco_aio_read(&zco_aio);

  printf("@_@...\n");

  zco_aio_return(&zco_aio);
  printf("%ld %s\n", zco_aio.aio.aio_nbytes, (char *)zco_aio.aio.aio_buf);

  free(buffer);
  close(fd_read);
}

void test_write()
{
  int fd_write = open("test_write.txt", O_WRONLY | O_CREAT | O_TRUNC);

  if (fd_write == -1) {
    perror("file open failed.");
    exit(-1);
  }

  zco_aio_t zco_aio = zco_aio_create(fd_write, "hello", 5);
  zco_aio_write(&zco_aio);

  printf("发呆...\n");

  zco_aio_return(&zco_aio);

  close(fd_write);
}

int main()
{
  test_read();
  test_write();
}
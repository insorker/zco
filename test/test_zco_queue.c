#include <stdio.h>
#include "../zco.h"

int cid[10];


void f1(void *arg)
{
  printf("f1 start\n");

  zco_queue_t *q = arg;

  printf("channel <- msg\n");
  zco_queue_put(q, "Hello");
  zco_queue_put(q, " ");
  zco_queue_put(q, "World");
  zco_queue_put(q, "!");

  printf("f1 end\n");
}

int main()
{
  printf("main start\n");

  zco_queue_t *q1 = zco_queue_new();

  cid[1] = zco_create(f1, q1);

  printf("exec: f1 %d\n", cid[1]);
  zco_resume(cid[1]);

  printf("channel -> msg\n");
  char *str = zco_queue_get(q1);
  printf("%s", str);
  str = zco_queue_get(q1);
  printf("%s", str);
  str = zco_queue_get(q1);
  printf("%s", str);
  str = zco_queue_get(q1);
  printf("%s\n", str);

  printf("main end\n");

  zco_queue_free(q1);
}
#include <stdio.h>
#include "../zco.h"

int cid[10];

void f1(void *arg)
{
  printf("f1 start\n");
  printf("f1 end\n");
}

void f2()
{
  printf("f2 start\n");
  zco_yield();
  printf("f2 end\n");
}

void f3()
{
  printf("f3 start\n");
  zco_resume(cid[2]);
  printf("f3 end\n");
}

int main()
{
  printf("main\n");

  cid[1] = zco_create(f1, NULL);
  cid[2] = zco_create(f2, NULL);
  cid[3] = zco_create(f3, NULL);

  printf("exec: f1 %d\n", cid[1]);
  zco_resume(cid[1]);
  printf("exec: f2 %d\n", cid[2]);
  zco_resume(cid[2]);
  printf("suspended: f2\n");

  zco_resume(cid[3]);
  zco_resume(cid[3]);

  printf("end\n");
}
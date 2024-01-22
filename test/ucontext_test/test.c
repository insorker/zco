#include <stdio.h>
#include <ucontext.h>
#include <malloc.h>

typedef void (*test_fn)(void);
#define STK_SIZE (64*1024)
ucontext_t cm, cf;

void f()
{
  printf("f\n");
}

void test0()
{
  printf("%s:\n", __func__);

  getcontext(&cf);
  cf.uc_stack.ss_sp = malloc(STK_SIZE);
  cf.uc_stack.ss_size = STK_SIZE;
  cf.uc_link = &cm;
  makecontext(&cf, f, 0);
  swapcontext(&cm, &cf);
}

void test1()
{
  printf("%s:\n", __func__);
  
  getcontext(&cf);
  cf.uc_stack.ss_sp = malloc(STK_SIZE);
  cf.uc_stack.ss_size = STK_SIZE;
  cf.uc_link = NULL;
  makecontext(&cf, f, 0);
  swapcontext(&cm, &cf);
}

void test2()
{
  printf("%s:\n", __func__);

  getcontext(&cf);
  cf.uc_stack.ss_sp = malloc(STK_SIZE);
  cf.uc_stack.ss_size = STK_SIZE;
  cf.uc_link = &cf;
  makecontext(&cf, f, 0);
  swapcontext(&cm, &cf);
}

void test3()
{
  printf("%s:\n", __func__);

  cf.uc_stack.ss_sp = malloc(STK_SIZE);
  cf.uc_stack.ss_size = STK_SIZE;
  cf.uc_link = &cm;
  makecontext(&cf, f, 0);
  swapcontext(&cm, &cf);
}

int main()
{
  test_fn tf[] = {
    test0, test1, test2, NULL
  };

  int id = 0;
  for (test_fn *ptf = tf; ptf != NULL; ptf++) {
    (*ptf)();
    printf("\n");
  }
}
#ifndef TEST_THREAD_H
#define TEST_THREAD_H

#include "test_set.h"


#include <stdlib.h>
#include <pthread.h>

#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

struct TestThread{
  pid_t tid;
  pthread_t ptid;
  struct TestSet* arr;
  struct TestSet* current_set;
  int arr_size;
  int thread_count;
  int offset;
};

struct TestThread TestThread_init(struct TestSet* arr, int arr_size, int offset, int thread_count);

void TestThread_exec(struct TestThread* thread);

void TestThread_registerFailure(struct TestThread* thread);

pid_t TestThread_getTid(struct TestThread* thread);

#endif

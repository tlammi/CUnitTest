#include "test_thread.h"

#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>



struct TestThread TestThread_init(struct TestSet* arr, int arr_size,
  int offset, int thread_count){

  struct TestThread t = {
    .tid = 0,
    .ptid = 0,
    .arr = arr,
    .arr_size = arr_size,
    .current_set = NULL,
    .thread_count = thread_count,
    .offset = offset
  };

  return t;
}

void* thread_func(void* p){
  struct TestThread* pt = p;

  pt->tid = syscall(SYS_gettid);

  for(int i = pt->offset; i < pt->arr_size; i += pt->thread_count){
    pt->current_set = &pt->arr[i];
    TestSet_exec(&pt->arr[i]);
  }

  return NULL;
}

void TestThread_exec(struct TestThread* thread){
  pthread_create(&thread->ptid, NULL, thread_func, thread);
}


void TestThread_join(struct TestThread* thread){
  pthread_join(thread->ptid, NULL);
}

void TestThread_registerFailure(struct TestThread* thread,
  const char* info_str){

  TestSet_registerFailure(thread->current_set, info_str);
}

pid_t TestThread_getTid(struct TestThread* thread){
  return thread->tid;
}


#include "c_unit_test.h"

#include "test_set.h"
#include "test_func.h"

#include "util.h"

#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

struct ThreadSetTuple{
  pid_t tid;
  struct TestSet* current_set;
};

struct TestSetDatabase{
  int set_count;
  int thread_count;
  pthread_t pthreads[C_UNIT_TEST_MAX_THREADS];
  struct ThreadSetTuple tsTuples[C_UNIT_TEST_MAX_THREADS];
  struct TestSet test_sets[C_UNIT_TEST_MAX_TEST_SETS];
};

struct TestSetDatabase gtsdb = {
  .set_count = 0,
  .thread_count = C_UNIT_TEST_DEFAUL_THREADS
};

void CUnitTest_addTestSet(const char* test_set_name){
  if(gtsdb.set_count == C_UNIT_TEST_MAX_TEST_SETS){
    printErr("Error: too many test sets.\n");
    return;
  }
  struct TestSet ts = TestSet_newTestSet(test_set_name);

  gtsdb.test_sets[gtsdb.set_count] = ts;
  gtsdb.set_count++;

}

void __CUnitTest_addTestFunc(const char* test_set_name,
                test_func funcptr, const char* func_name){
  if(gtsdb.set_count == 0){
    printErr("No registered sets\n");
    return;
  }
  if(strcmp(test_set_name, TestSet_getName(&gtsdb.test_sets[gtsdb.set_count-1]))){
    printErr("Functions currently have to be added to latest set\n");
    return;
  }

  TestSet_addTestFunc(&gtsdb.test_sets[gtsdb.set_count-1], func_name, funcptr);

}


void* test_thread(void* p){
  struct ThreadSetTuple* param = (struct ThreadSetTuple*)p;
  param->tid = syscall(SYS_gettid);
  printDebug("Thread %d executing\n",param->tid);
  long long offset = ((unsigned long long) param
                      -(unsigned long long) gtsdb.tsTuples)/sizeof(*param);
  printDebug("Got offset %lld\n",offset)
  for(int i = offset; i<gtsdb.set_count; i += gtsdb.thread_count){
    printDebug("Thread %d executing:\n",param->tid);
    param->current_set = &gtsdb.test_sets[i];
    TestSet_exec(&gtsdb.test_sets[i]);
  }
  return NULL;
}


void CUnitTest_execute(void){

  pid_t tid = syscall(SYS_gettid);
  printDebug("main tid: %d\n",tid);
  printDebug("main pid:%d\n",getpid());

  int thread_count = gtsdb.thread_count;

  for(int i = 0; i<thread_count; i++){
    pthread_create(&gtsdb.pthreads[i], NULL, test_thread, &gtsdb.tsTuples[i]);
  }

  printNote("Failed test sets and functions:\n");
  int i;
  for(i=0; i<gtsdb.set_count; i++){
    if(TestSet_getFailed(&gtsdb.test_sets[i])){
      printErr("%s\n",TestSet_getName(&gtsdb.test_sets[i]))
      TestSet_printFailedFunctions(&gtsdb.test_sets[i]);
    }
  }
}

static struct TestSet* getCurrentSetForThread(){
  pid_t tid = syscall(SYS_gettid);
  long offset = tid - getpid();
  if(offset < gtsdb.thread_count && gtsdb.tsTuples[offset].tid == tid ){
    return gtsdb.tsTuples[offset].current_set;
  } else {
    for(int i = 0; i < gtsdb.thread_count; i++){
      if(gtsdb.tsTuples[i].tid == tid){
        return gtsdb.tsTuples[i].current_set;
      }
    }
  }
  return NULL;
}

void __CUnitTest_registerFailure(){
  printDebug("Registering failure\n");
  struct TestSet* pset = getCurrentSetForThread();
  TestSet_setFailed(pset, 1);
}


#include "test_set.h"
#include "test_func.h"
#include "test_thread.h"

#include "print.h"

#include <string.h>

struct TestSetDatabase{
  int set_count;
  int thread_count;
  struct TestThread test_threads[C_UNIT_TEST_MAX_THREADS];
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


int __CUnitTest_execute(void){

  pid_t tid = syscall(SYS_gettid);
  printDebug("main tid: %d\n",tid);
  printDebug("main pid:%d\n",getpid());

  int thread_count = gtsdb.thread_count;

  for(int i = 0; i<thread_count; i++){
    gtsdb.test_threads[i] = TestThread_init(gtsdb.test_sets, gtsdb.set_count, i, thread_count);
    TestThread_exec(&gtsdb.test_threads[i]);
  }

  for(int i = 0; i < thread_count; i++){
    TestThread_join(&gtsdb.test_threads[i]);
  }

  printNote("Registered test sets: %d\n", gtsdb.set_count);

  int sets_failed = 0;
  int sets_success = 0;

  for(int i = 0; i < gtsdb.set_count; i++){
    if(TestSet_getFailed(&gtsdb.test_sets[i])){
      sets_failed++;
    } else {
      sets_success++;
    }
  }
  printOK("Sets ok: %d\n", sets_success);
  printErr("Sets failed: %d\n", sets_failed);

  int i;
  int failed = 0;
  for(i=0; i<gtsdb.set_count; i++){
    if(TestSet_getFailed(&gtsdb.test_sets[i])){
      printErr("%s results:\n",TestSet_getName(&gtsdb.test_sets[i]));
      TestSet_printFailedFunctions(&gtsdb.test_sets[i]);
      failed++;
    }
  }

  return failed;

}

static struct TestThread* getTestThread(){
  // Thread id of the calling thread
  pid_t tid = syscall(SYS_gettid);
  // Guess for the offset in array
  long offset = tid - getpid();

  if(offset < gtsdb.thread_count && TestThread_getTid(&gtsdb.test_threads[offset]) == tid){
    return &gtsdb.test_threads[offset];
  } else{
    for(int i = 0; i < gtsdb.thread_count; i++){
      if(TestThread_getTid(&gtsdb.test_threads[i]) == tid) {
        return &gtsdb.test_threads[i];
      }
    }
  }

  return NULL;

}

void __CUnitTest_registerFailure(const char* info_str){
  printDebug("Registering failure\n");
  struct TestThread* thread = getTestThread();
  if(thread != NULL){
    TestThread_registerFailure(thread, info_str);
  }
  else{
    printErr("Thread panic\n");
    exit(-1);
  }
}

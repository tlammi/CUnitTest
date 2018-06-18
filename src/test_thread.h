/**
  \file test_thread.h

  \brief Contains declarations of struct TestThread used for parallel
    execution of tests

  \author tlammi
*/
#ifndef TEST_THREAD_H
#define TEST_THREAD_H

#include "test_set.h"


#include <stdlib.h>
#include <pthread.h>

/**
  \brief A structure used for managing pthreads in CUnitTest
*/
struct TestThread{
  pid_t tid; ///< Linux thread ID
  pthread_t ptid; ///< Pthread ID
  struct TestSet* arr; ///< Pointer to an array containing all TestSets of the
                       ///< CUnitTest
  struct TestSet* current_set; ///< Current TestSet of the thread
  int arr_size; ///< Size of the array arr
  int thread_count; ///< Number of threads executing tests
  int offset; ///< Offset from the beginning of the arr
};

/**
  \brief Initialize a TestThread without executing it

  \param arr - Reference to array containing all TestSets
  \param arr_size - Number of elements in arr
  \param offset - The index of first TestSet to be executed by given thread
  \param thread_count - Number of threads executing tests concurrently

  \return A new instance of TestThread
*/
struct TestThread TestThread_init(struct TestSet* arr, int arr_size,
  int offset, int thread_count);

/**
  \brief Execute a TestThread

  \param thread - Reference to a TestThread instance
    created with TestThread_init()
*/
void TestThread_exec(struct TestThread* thread);

/**
  \brief Wait for executing end for the given TestThread

  If the thread which is to be waited has already finished the
  function returns without taking any actions.

  \param thread - Reference to a TestThread instance
    created with TestThread_init()
*/
void TestThread_join(struct TestThread* thread);

/**
  \brief Register a failure for the current function executed by the thread

  \param thread - Reference to a TestThread instance
    created with TestThread_init()

  \param info_str - Info about the failure
*/
void TestThread_registerFailure(struct TestThread* thread,
  const char* info_str);

/**
  \brief Get Linux thread ID of the given TestThread

  \param thread - Reference to a TestThread instance
    created wit TestThread_init()

  \return Linux thread id of the thread
*/
pid_t TestThread_getTid(struct TestThread* thread);

#endif

/**
  \file test_set.h

  \brief Contains declarations for struct TestSet, a struct used for managing
    test sets.

  \author tlammi
*/
#ifndef TEST_SET_H
#define TEST_SET_H

#include "constants.h"
#include "test_func.h"

/**
  \brief Struct used for managing test sets
*/
struct TestSet {
  struct LinkedList list; ///< List of functions in the set
  const char* name; ///< Name of the test set
  int failed; ///< Number of failed functions in the set
};

/**
  \brief Create a new instance of TestSet

  \param name - Name of the test set

  \return A new instance of TestSet
*/
struct TestSet TestSet_newTestSet(const char* name);

/**
  \brief Destructor for TestSet

  \param handl - Reference to a TestSet instance
    created with TestSet_newTestSet()
*/
void TestSet_destroy(struct TestSet* handl);

/**
  \brief Adds a test function into a TestSet

  \param handl - Reference to a TestSet instance
    created with TestSet_newTestSet()
  \param funcname - Name of the function
  \param funcptr - Pointer to new test function
*/
void TestSet_addTestFunc(struct TestSet* handl, const char* funcname,
  test_func funcptr);

/**
  \brief Execute test functions in TestSet

  \param handl - Reference to a TestSet instance
    created with TestSet_newTestSet()
*/
void TestSet_exec(struct TestSet* handl);

/**
  \brief Get name of the test set

  \param handl - Reference to a TestSet instance
    created with TestSet_newTestSet()
*/
const char* TestSet_getName(struct TestSet* handl);

/**
  \brief Register a failure in current test function

  \param handl - Reference to a TestSet instance
    created with TestSet_newTestSet()
  \param info_str - String containing info about the failure
*/
void TestSet_registerFailure(struct TestSet* handl, const char* info_str);

/**
  \brief Get the number of failed functions in TestSet

  \param handl - Reference to a TestSet instance
    created with TestSet_newTestSet()

  \return Number of failed functions
*/
int TestSet_getFailed(struct TestSet* handl);

/**
  \brief Print all failed functions in test set

  \param handl - Reference to a TestSet instance
    created with TestSet_newTestSet()

*/
void TestSet_printFailedFunctions(struct TestSet* handl);

#endif

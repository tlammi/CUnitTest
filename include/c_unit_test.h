/** \file c_unit_test.h
    \brief Public interface for CUnitTest.

    The functions found in this interface can be used for creating unit tests.

    \author tlammi
*/
#ifndef C_UNIT_TEST_H
#define C_UNIT_TEST_H

#include <stdlib.h>

/**
  \brief Test function template

  Test functions using this interface should match this format.
*/
typedef void(*test_func)(void);

/**
  \brief Add a test set into test database

  Registers a new Test set with given name

  \param test_set_name - name of the test set
*/
void CUnitTest_addTestSet(const char* test_set_name);

/**
  \brief Add a test function into a test set

  Tests are executed in sets and sets consist of one or more functions.
  This macro is used for adding a test function into a test set.

  \param test_set_name - Name of the set to wich the function belongs to
  \param test_func_ptr - Pointer to test function
*/
#define CUnitTest_addTestFunc(test_set_name, test_func_ptr)\
do{\
  __CUnitTest_addTestFunc(test_set_name, test_func_ptr, #test_func_ptr);\
}while(0)
void __CUnitTest_addTestFunc(const char* test_set_name,
                                     test_func funcptr, const char* func_name);

/**
  \brief Add a test function to latest test set

  Works similarly to CUnitTest_addTestFunc() but automatically adds the function
  to the test set last registered.

  \param test_func_ptr - Pointer to test function
*/
#define CUnitTest_pushTestFunc(test_func_ptr)\
do{\
  __CUnitTest_pushTestFunc(test_func_ptr, #test_func_ptr);\
}while(0)
void __CUnitTest_pushTestFunc(test_func funcptr, const char* func_name);

/**
 * \brief Execute regitered tests
 *
 * Executes all test sets and test functions registered in these test sets and
 * exits the process with number of failed test sets.
*/
#define CUnitTest_execute()\
do{\
  exit(__CUnitTest_execute());\
}while(0)
int __CUnitTest_execute(void);




/**
  \brief Assert a boolean statement and log error if fail
  \param assertion - a boolean statement which is asserted to be true
*/
#define CUnitTest_assert(assertion) do{\
  __CUnitTest_assertFunc(__FILE__, __FUNCTION__,\
    __LINE__, assertion, #assertion);\
}while(0)
void __CUnitTest_assertFunc(const char* file, const char* func, int line,
  char assertion, const char* assertion_str);

/**
  \brief Assert that values (integer) are equal

  \param val1 - The first integer
  \param val2 - The second integer
*/
#define CUnitTest_assertEqual(val1, val2) do{\
  __CUnitTest_assertEqualFunc(__FILE__, __FUNCTION__, __LINE__, val1, val2,\
    #val1, #val2);\
}while(0)
void __CUnitTest_assertEqualFunc(const char* file, const char* func, int line,
  int val1, int val2, const char* val1str, const char* val2str);

/**
 * \brief Assert that values are non-equal

  \param val1 - The first integer
  \param val2 - The second integer
*/
#define CUnitTest_assertNotEqual(val1, val2)do{\
  __CUnitTest_assertNotEqualFunc(__FILE__, __FUNCTION__, __LINE__, val1, val2,\
    #val1, #val2);\
}while(0)
void __CUnitTest_assertNotEqualFunc(const char* file, const char* func,
  int line, int val1, int val2, const char* val1str, const char* val2str);

/**
 * \brief Assert that strings are equal

  \param str1 - The first string
  \param str2 - The second string
*/
#define CUnitTest_assertStrEqual(str1, str2)do{\
  __CUnitTest_assertStrEqualFunc(__FILE__, __FUNCTION__, __LINE__, str1, str2, \
    #str1, #str2);\
}while(0);
void __CUnitTest_assertStrEqualFunc(const char* file, const char* func,
  int line, const char* str1, const char* str2, const char* str1str,
  const char* str2str);

#endif

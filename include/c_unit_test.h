#ifndef C_UNIT_TEST_H
#define C_UNIT_TEST_H

#include <stdlib.h>

/*
 * \brief Test function template
*/
typedef void(*test_func)(void);

/*
 * \brief Add a test set into test database
*/
void CUnitTest_addTestSet(const char* test_set_name);

/*
 * \brief Add a test function into a test set
 * \todo Functions can currently be added only into lastly added test set
*/
#define CUnitTest_addTestFunc(test_set_name, test_func_ptr)\
do{\
  __CUnitTest_addTestFunc(test_set_name, test_func_ptr, #test_func_ptr);\
}while(0)

/*
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




/*
 * \brief Assert a boolean statement and log error if fail
 *
*/
#define CUnitTest_assert(assertion) do{\
  __CUnitTest_assertFunc(__FILE__, __FUNCTION__, __LINE__, assertion, #assertion);\
}while(0)
void __CUnitTest_assertFunc(const char* file, const char* func, int line, char assertion, const char* assertion_str);

/*
 * \brief Assert that values (integer) are equal
*/
#define CUnitTest_assertEqual(val1, val2) do{\
  __CUnitTest_assertEqualFunc(__FILE__, __FUNCTION__, __LINE__, val1, val2, #val1, #val2);\
}while(0)
void __CUnitTest_assertEqualFunc(const char* file, const char* func, int line, int val1, int val2, const char* val1str, const char* val2str);

/*
 * \brief Assert that values are non-equal
*/
#define CUnitTest_assertNotEqual(val1, val2)do{\
  __CUnitTest_assertNotEqualFunc(__FILE__, __FUNCTION__, __LINE__, val1, val2, #val1, #val2);\
}while(0)
void __CUnitTest_assertNotEqualFunc(const char* file, const char* func, int line, int val1, int val2, const char* val1str, const char* val2str);

/*
 * \brief Assert that strings are equal
*/
#define CUnitTest_assertStrEqual(str1, str2)do{\
  __CUnitTest_assertStrEqualFunc(__FILE__, __FUNCTION__, __LINE__, str1, str2, #str1, #str2);\
}while(0);
void __CUnitTest_assertStrEqualFunc(const char* file, const char* func, int line, const char* str1, const char* str2, const char* str1str, const char* str2str);



void __CUnitTest_addTestFunc(const char* test_set_name,
                                     test_func funcptr, const char* func_name);

#endif

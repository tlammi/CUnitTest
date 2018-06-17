#ifndef CONSTANTS_H
#define CONSTANTS_H

// Maximum number of test functions which can be registered into a set
#define C_UNIT_TEST_MAX_FUNCS_IN_SET 1024
// Maximum number of test sets which can be registered in one test
#define C_UNIT_TEST_MAX_TEST_SETS 1024
// Maximum number of assertions in a test function
#define C_UNIT_TEST_MAX_ASSERTS_IN_FUNC 100
// Maximum length of assertion info string
#define C_UNIT_TEST_MAX_ASSERT_INFO_STR_LEN 128
// Default number of concurrent threads
#define C_UNIT_TEST_DEFAUL_THREADS 4
// Maximum number of threads which can be set
#define C_UNIT_TEST_MAX_THREADS 64

#define DEBUG_PRINT

#endif

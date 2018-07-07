/**
  \file test_func.h

  \brief Contains declarations for TestFunc - a struct used for managing
    test functions

  \autho tlammi

*/
#ifndef TEST_FUNC_H
#define TEST_FUNC_H

#include "constants.h"
#include "linked_list.h"

/// \brief A template for test functions
typedef void (*test_func)(void);

/**
  \brief A struct used for managing test functions
*/
struct TestFunc{
  const char* name; ///< Name of the test function
  test_func test_func_ptr; ///< Pointer to the test function

  int failed;
  int succeeded;
  /**
    List containing assertions statuses. Statuses are placed in same indexes
    as the info strings in field info_list
  */
  struct LinkedList failed_list;
  struct LinkedList info_list; ///< List containing infos of failed assertions
};

/**
  \brief Create a new instance of TestFunc

  \param name - Name of the test function
  \param funcptr - Pointer to test function

  \return A new instance of TestFunc
*/
struct TestFunc TestFunc_newTestFunc(const char* name, test_func funcptr);

/**
  \brief Destructor for TestFunc

  \param handl - Reference to an instance of TestFunc
    created with TestFunc_newTestFunc()

*/
void TestFunc_destroy(struct TestFunc* handl);

/**
  \brief Executes the test function stored in TestFunc_newTestFunc()

  \param handl - Reference to a TestFunc instance
    created with TestFunc_newTestFunc()
*/
void TestFunc_exec(struct TestFunc* handl);

/**
  \brief Registers an assertions failure to given TestFunc

  \param handl - Reference to a TestFunc instance
    created with TestFunc_newTestFunc()

  \param info_str - String containing info about the failure
*/
void TestFunc_registerFailure(struct TestFunc* handl, const char* info_str);


void TestFunc_registerOk(struct TestFunc* handl, const char* info_str);

/**
  \brief Get the number of failed asserts in the function

  \param handl - Reference to a TestFunc instance
    created with TestFunc_newTestFunc()

  \return Number of failed assertions
*/
int TestFunc_getFailed(struct TestFunc* handl);


int TestFunc_getSucceeded(struct TestFunc* handl);

/**
  \brief Returns a reference to test function name stored in TestFunc

  \param handl - Referece to a TestFunc instance
    created with TestFunc_newTestFunc()

  \return Reference to name of the TestFunc instance
*/
const char* TestFunc_getName(struct TestFunc* handl);

/**
  \brief Go through and print failed assertions in TestFunc instance

  \param handl - Reference to a TestFunc instance created
    with TestFunc_newTestFunc()

*/
void TestFunc_printFailedAsserts(struct TestFunc* handl);

struct LinkedList TestFunc_getFailedList(struct TestFunc* handl);
struct LinkedList TestFunc_getInfoList(struct TestFunc* handl);

#endif

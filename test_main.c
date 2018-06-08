
#include <stdio.h>

#include "test_set_database.h"
#include "assertions.h"

void my_test_func(void){
  CUnitTest_assert(1 == 0);
  CUnitTest_assert(1 == 1);
  CUnitTest_assertEqual(1,0);
  CUnitTest_assertEqual(1,1);
  CUnitTest_assertNotEqual(1,1);
  CUnitTest_assertNotEqual(1,0);
  CUnitTest_assertStrEqual("asdf","asdfg");
  CUnitTest_assertStrEqual("asdf","asdf");

}


int main(){
  CUnitTest_addTestSet("My set");
  CUnitTest_addTestFunc("My set", my_test_func);
  
  CUnitTest_addTestSet("My set 2");
  CUnitTest_addTestFunc("My set 2", my_test_func);


  CUnitTest_execute();

}

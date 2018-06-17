
//#include <stdio.h>
#include "c_unit_test.h"

void my_test_func(void){
  CUnitTest_assert(1 == 0);
  CUnitTest_assert(1 == 1);
  int var = 1;
  CUnitTest_assertEqual(var,0);
  CUnitTest_assertEqual(1,1);
  CUnitTest_assertNotEqual(1,1);
  CUnitTest_assertNotEqual(1,0);
  CUnitTest_assertStrEqual("asdf","asdfg");
  CUnitTest_assertStrEqual("asdf","asdf");

}

void my_test_func_2(void){

  CUnitTest_assert(100 == 190);
  CUnitTest_assertEqual(100, 200);

}


int main(){
  CUnitTest_addTestSet("My set");
  CUnitTest_addTestFunc("My set", my_test_func);
  CUnitTest_addTestFunc("My set", my_test_func_2);

  CUnitTest_addTestSet("My set 2");
  CUnitTest_addTestFunc("My set 2", my_test_func);

  CUnitTest_execute();

}


//#include "registration.h"

#include <stdio.h>

#include "test_set_database.h"

#define Cunit_assert(assertion) \
do{\
  if(!(assertion)){\
    Cunit_registerFailure(__FILE__, __FUNCTION__, __LINE__, #assertion);\
  } else {\
    Cunit_registerOk();\
  }\
}while(0)



void Cunit_registerFailure(const char* file_name, const char* function_name, int line, char* assertion){
  printf("Assertion failure: \n\tfile %s\n\tfunction %s\n\tline %d\n\tassertion %s\n",file_name, function_name, line, assertion);
}
void Cunit_registerOk(){
  printf("Assertion ok\n");
}


void my_test_func(void){
  Cunit_assert(1 == 0);
  Cunit_assert(1 == 1);
}


int main(){
  CUnitTest_addTestSet("My set");
  CUnitTest_addTestFunc("My set", my_test_func);



  CUnitTest_execute();

}

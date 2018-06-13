#include <stdio.h>
//#include "c_unit_test.h"

#include "linked_list.h"
/*
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

void my_test_func_2(void){

  CUnitTest_assert(100 == 190);
  CUnitTest_assertEqual(100, 200);

}
*/

int main(){
  struct LinkedList list = LinkedList_new();
  for(int i = 0; i < 10; i++){
    LinkedList_pushBack(&list, &i, sizeof(i));
  }
  int bytes;
  int* val;
  int retval;
  LinkedList_getCurr(&list, (void**)&val, &bytes);
  do{
    printf("val: %d\n",*val);
    retval = LinkedList_getNext(&list, (void**)&val, &bytes);
  }while(retval == 0);
  while(1){
    retval = LinkedList_getPrev(&list, (void**)&val, &bytes);
    if(retval != 0) break;
    printf("val: %d\n",*val);
  }

  retval = LinkedList_getNext(&list, (void**)&val, &bytes);
  printf("val: %d\n", *val);
  int val2 = -1;
  LinkedList_pushFront(&list, &val2, sizeof(int));
  LinkedList_getPrev(&list, (void**)&val, &bytes);
  printf("val: %d\n", *val);
  LinkedList_getPrev(&list, (void**)&val, &bytes);
  printf("val: %d\n", *val);

  /*
  CUnitTest_addTestSet("My set");
  CUnitTest_addTestFunc("My set", my_test_func);
  CUnitTest_addTestFunc("My set", my_test_func_2);

  CUnitTest_addTestSet("My set 2");
  CUnitTest_addTestFunc("My set 2", my_test_func);

  CUnitTest_execute();
  */

  /*CUnitTest_addTestSet("My test set");
  CUnitTest_addTestFunc("My test set", my_test_func);
  CUnitTest_addTestFunc("My test set", my_test_func_2);

  CUnitTest_execute();
  */
}

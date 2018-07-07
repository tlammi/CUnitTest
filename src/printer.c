#include "printer.h"
#include "print.h"

#include <stdlib.h>

enum PrintType{
  PrintTypeOK = 1,
  PrintTypeWarn = 2,
  PrintTypeErr = 3,
  PrintTypeNote = 4
};

#define doPrintPlain(print_type, indent, ...) \
do{\
  printNote("%*s", indent, "");\
  switch(print_type){ \
    case PrintTypeOK: \
      printOK(__VA_ARGS__); \
      break; \
    case PrintTypeWarn: \
      printWarn(__VA_ARGS__); \
      break; \
    case PrintTypeErr: \
      printErr(__VA_ARGS__); \
      break; \
    case PrintTypeNote: \
      printNote(__VA_ARGS__); \
      break; \
    default: \
      break; \
  } \
}while(0)



void Printer_printTestSetList(struct LinkedList list, enum PrintFormat print_format){
  switch(print_format){
    case PrintPlain:
      break;
    case PrintJSON:
      printWarn("JSON print not implemented. Printing plain...\n");
      break;
    case PrintYAML:
      printWarn("YAML print not implemented. Printing plain...\n")
      break;
    default:
      printErr("Invalid print type\n");
      exit(-1);
  }

  LinkedList_setCurrToFront(&list);
  struct TestSet* pts;
  int size;

  LinkedList_getCurr(&list, (void**)&pts, &size);
  do{
    doPrintPlain(PrintTypeNote, 0, "%s\n",TestSet_getName(pts));
  }while(!LinkedList_getNext(&list, (void**)&pts, &size));

}

void Printer_printTestSetArray(struct TestSet test_sets[], int set_count, enum PrintFormat print_format){
  switch(print_format){
    case PrintPlain:
      break;
    case PrintJSON:
      printWarn("JSON print not implemented. Printing plain...\n");
      break;
    case PrintYAML:
      printWarn("YAML print not implemented. Printing plain...\n")
      break;
    default:
      printErr("Invalid print type\n");
      exit(-1);
  }

  int failed_sets = 0;

  doPrintPlain(PrintTypeNote, 0, "Failed Test Sets:\n");
  for(int i = 0; i< set_count; i++){
    // Skip successful test sets
    if(TestSet_getFailed(&test_sets[i]) == 0) continue;

    failed_sets++;
    doPrintPlain(PrintTypeErr, 4, "%s\n", TestSet_getName(&test_sets[i]));
    struct LinkedList test_list = TestSet_getTestFuncs(&test_sets[i]);

    int test_func_count = LinkedList_getCount(&test_list);
    int test_funcs_failed = TestSet_getFailed(&test_sets[i]);
    int test_funcs_success = test_func_count - test_funcs_failed;
    doPrintPlain(PrintTypeNote, 8, "Functions Executed: %d\n",test_func_count);
    doPrintPlain(PrintTypeOK, 8, "Functions OK: %d\n", test_funcs_success);
    doPrintPlain(PrintTypeErr, 8, "Functions failed: %d\n", test_funcs_failed);
    doPrintPlain(PrintTypeNote, 8, "Failed functions:\n");

    LinkedList_setCurrToFront(&test_list);

    struct TestFunc* ptest_func;
    int size;

    LinkedList_getCurr(&test_list, (void**)&ptest_func, &size);
    do{
      // Skip successfull test functions
      if(TestFunc_getFailed(ptest_func) == 0) continue;

      doPrintPlain(PrintTypeErr, 12, "%s\n", TestFunc_getName(ptest_func));

      struct LinkedList failed_list = TestFunc_getFailedList(ptest_func);
      struct LinkedList info_list = TestFunc_getInfoList(ptest_func);

      LinkedList_setCurrToFront(&failed_list);
      LinkedList_setCurrToFront(&info_list);

      const char* info_str;
      int* failed;

      LinkedList_getCurr(&failed_list, (void**)&failed, &size);
      LinkedList_getCurr(&info_list, (void**)&info_str, &size);

      do{
        if(failed){
          doPrintPlain(PrintTypeErr, 16, "%s\n", info_str);
        }
      }while(!LinkedList_getNext(&failed_list, (void**)&failed, &size) &&
                !LinkedList_getNext(&info_list, (void**)&info_str, &size));


    }while(!LinkedList_getNext(&test_list, (void**)&ptest_func, &size));

  }
  doPrintPlain(PrintTypeNote, 0, BOLD"#############################################\n"
                                 " Summary:\n"
                                 "#############################################\n"RESET);
  doPrintPlain(PrintTypeNote, 4, "%d sets executed\n", set_count);
  doPrintPlain(PrintTypeOK, 4, "%d sets successful\n", set_count-failed_sets);
  doPrintPlain(PrintTypeErr, 4, "%d sets failed\n", failed_sets);

}

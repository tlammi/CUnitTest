#include "arg_parser.c"

#include <stdio.h>


int main(int argc, char** argv){
  initGetter(argc, argv);

  int status;
  char* tmp = getNextArg(&status);
  while(status >= 0){
    printf("tmp: %s, status: %i\n", tmp, status);
    tmp = getNextArg(&status);
  }
  printf("\n");
  initGetter(argc, argv);
  do{
    tmp = getNextFlag(&status);
    printf("tmp: %s, status: %i\n", tmp, status);
  }while(status >= 0);

  printf("\n");
  
  do{
    tmp = getNextCmd(&status);
    printf("tmp: %s, status: %i\n", tmp, status);
  }while(status >= 0);

}

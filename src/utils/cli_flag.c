#include "cli_flag.h"


#include <stdio.h>


struct CliFlag CliFlag_init(const char* long_flag, const char short_flag,
  char expects_val, void(*callback)(struct CliFlag*)){
  struct CliFlag cf = {
    .long_flag = long_flag,
    .short_flag = short_flag,
    .value = "",
    .expects_val = expects_val,
    .callback = callback
  };

  return cf;
}


void CliFlag_setFlagField(struct CliFlag* handl, char* flag_field, int flag_bit){
  handl->flag_field = flag_field;
  handl->flag_bit = flag_bit;
}

void CliFlag_setCallBack(struct CliFlag* handl, void(*callback)(struct CliFlag*)){
  handl->callback = callback;
}


void CliFlag_setVal(struct CliFlag* handl, char* val_str){
  handl->value = val_str;
}

int CliFlag_expectsVal(struct CliFlag* handl){
  return (int)handl->expects_val;
}

void CliFlag_doRaiseFlag(struct CliFlag* handl){
  if(handl->flag_field != NULL){
    *handl->flag_field |= 1 < handl->flag_bit;
  }
}

void CliFlag_doCallback(struct CliFlag* handl){
  if(handl->callback != NULL){
    handl->callback(handl);
  }
}


void CliFlag_debugPrint(struct CliFlag* this, int indent){
  printf("%*s", indent*4,"");
  printf("--%s, -%c, value: %s\n", this->long_flag, this->short_flag, this->value);
}

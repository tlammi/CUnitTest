#include "cli_flag.h"


#include <stdio.h>


struct CliFlag CliFlag_init(const char* long_flag, const char short_flag, char expects_val){
  struct CliFlag cf = {
    .long_flag = long_flag,
    .short_flag = short_flag,
    .value = "",
    .expects_val = expects_val
  };

  return cf;
}


void CliFlag_doRaiseFlag(struct CliFlag* handl){
  if(handl->flag_field != NULL){
    *handl->flag_field |= 1 < handl->flag_bit;
  }
}

void CliFlag_doCallback(struct CliFlag* handl){
  if(handl->callback != NULL){
    handl->callback();
  }
}


void CliFlag_debugPrint(struct CliFlag* this, int indent){
  printf("%*s", indent*4,"");
  printf("--%s, -%c, value: %s\n", this->long_flag, this->short_flag, this->value);
}

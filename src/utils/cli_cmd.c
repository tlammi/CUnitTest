#include "cli_cmd.h"

#include <stdio.h>
#include <string.h>

#ifndef NULL
#define NULL ((void*)0)
#endif

struct CliCmd CliCmd_init(const char* cmd, void(*callback)()){
  struct CliCmd cc = {
    .cmd = cmd,
    .callback = callback,
    .child_cmd_count = 0,
    .child_cmds = NULL,
    .child_flag_count = 0,
    .child_flags = NULL,
    .flag_field = NULL,
    .flag_bit = -1
  };
  return cc;
}



void CliCmd_setChildCmds(struct CliCmd* parent, struct CliCmd children[], int child_count){
  parent->child_cmds = children;
  parent->child_cmd_count = child_count;
}


void CliCmd_setChildFlags(struct CliCmd* parent, struct CliFlag flags[], int flag_count){
  parent->child_flags = flags;
  parent->child_flag_count = flag_count;
}


void CliCmd_getChildCmds(struct CliCmd* parent, struct CliCmd** children, int* child_count){
  *children = parent->child_cmds;
  *child_count = parent->child_cmd_count;
}



struct CliFlag* CliCmd_getLongFlag(struct CliCmd* handl, const char* long_flag){
  for(int i = 0; i < handl->child_flag_count; i++){
    if(!strcmp(handl->child_flags[i].long_flag, long_flag)){
      return &handl->child_flags[i];
    }
  }
  return NULL;
}

struct CliFlag* CliCmd_getShortFlag(struct CliCmd* handl, const char short_flag){
  for(int i = 0; i < handl->child_flag_count; i++){
    if(handl->child_flags[i].short_flag == short_flag){
      return &handl->child_flags[i];
    }
  }
  return NULL;
}


struct CliCmd* CliCmd_getChildCmd(struct CliCmd* handl, const char* cmd){
  for(int i = 0; i < handl->child_cmd_count; i++){
    if(!strcmp(handl->child_cmds[i].cmd, cmd)){
      return &handl->child_cmds[i];
    }
  }
  return NULL;
}

void CliCmd_doCallback(struct CliCmd* handl){
  if(handl->callback != NULL){
    handl->callback();
  }
}



void CliCmd_debugPrintCmdsRecursive(struct CliCmd* this, int depth){
  printf("%*s", depth*4, "");
  printf("%s\n", this->cmd);
  for(int i = 0; i < this->child_flag_count; i++){
    CliFlag_debugPrint(&this->child_flags[i], depth+1);
  }
  for(int i = 0; i < this->child_cmd_count; i++){
    CliCmd_debugPrintCmdsRecursive(&this->child_cmds[i], depth+1);
  }
}

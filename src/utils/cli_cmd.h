#ifndef CLI_CMD_H
#define CLI_CMD_H

#include "cli_flag.h"

struct CliCmd{
  const char* cmd;
  void (*callback)();
  int child_cmd_count;
  struct CliCmd* child_cmds;
  int child_flag_count;
  struct CliFlag* child_flags;
  char* flag_field;
  int flag_bit;
};

struct CliCmd CliCmd_init(const char* cmd, void(*callback)());

void CliCmd_setChildCmds(struct CliCmd* parent, struct CliCmd children[], int child_count);
void CliCmd_setChildFlags(struct CliCmd* parent, struct CliFlag flags[], int flag_count);

void CliCmd_getChildCmds(struct CliCmd* parent, struct CliCmd** children, int* child_count);

struct CliFlag* CliCmd_getLongFlag(struct CliCmd* handl, const char* long_flag);
struct CliFlag* CliCmd_getShortFlag(struct CliCmd* handl, const char short_flag);

struct CliCmd* CliCmd_getChildCmd(struct CliCmd* handl, const char* cmd);

void CliCmd_doCallback(struct CliCmd* handl);

void CliCmd_debugPrintCmdsRecursive(struct CliCmd* this, int depth);
#endif

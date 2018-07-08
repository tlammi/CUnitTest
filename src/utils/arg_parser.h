#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include "cli_cmd.h"


void ArgParser_addCommand(const char* parent, const char* command);

void ArgParser_setCommands(struct CliCmd* parent, struct CliCmd cli_cmds[], int cli_cmd_count);

void ArgParser_setFlags(struct CliCmd* parent, struct CliFlag cli_flags[], int cli_flag_count);

void ArgParser_addFlag(const char* parent,
                       const char* long_flag,
                       const char short_flag,
                       void(*callback)(
                         const char*,
                         const char*,
                         const char,
                         const char*));

int ArgParser_parse(int argc, char** argv, int(*dump_callback)(int, char**));

#endif

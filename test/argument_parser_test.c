
#include "arg_parser.h"
#include "cli_cmd.h"
#include "cli_flag.h"
#include "linked_list.h"


#include <stdlib.h>
#include <stdio.h>

void run_test_cb(){
  printf("In run callback\n");
}

void flag_callback(struct CliFlag* param){
  printf("flag cb. Short flag: %c, long flag: %s, value: %s\n", param->short_flag, param->long_flag, param->value);
}


int main(int argc, char** argv){

  struct CliCmd top_cmds[] = {
    CliCmd_init("run", run_test_cb),
    CliCmd_init("exec", NULL),
    CliCmd_init("delete", NULL),
    CliCmd_init("remove", NULL)
  };

  struct CliCmd run_cmds[] = {
    CliCmd_init("quick", NULL),
    CliCmd_init("verbose", NULL),
    CliCmd_init("dummy", NULL)
  };

  struct CliFlag run_flags[] = {
    CliFlag_init("flag", 'f', 1, flag_callback),
    CliFlag_init("opt", 'o', 0, flag_callback)
  };
  ArgParser_setCommands(NULL, top_cmds, 4);
  ArgParser_setCommands(&top_cmds[0], run_cmds, 3);
  ArgParser_setFlags(&top_cmds[0], run_flags, 2);

  ArgParser_parse(argc, argv, NULL);
}

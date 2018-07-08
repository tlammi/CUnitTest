#include "arg_parser.h"
#include "cli_cmd.h"
#include "print.h"

#define isFlag(flag_candidate) ((flag_candidate)[0] == '-')
#define isLongFlag(flag_candidate) ((flag_candidate)[1] == '-')

struct ArgParserCmd{
  const char* name;
  int child_cmd_count;
  struct CliCmd* child_cmds;
  int child_flag_count;
  struct CliFlag* child_flags;
};

struct CliCmd g_exec;
struct CliCmd* gp_current_cmd = &g_exec;

static const char* arg_parser_get(int argc, char** argv){
  static int index = 0;
  if(index == argc-1) return "";

  index++;
  return argv[index];
}


void ArgParser_setCommands(struct CliCmd* parent, struct CliCmd cli_cmds[], int cli_cmd_count){
  if(parent == NULL){
    g_exec.child_cmds = cli_cmds;
    g_exec.child_cmd_count = cli_cmd_count;
  } else{
    parent->child_cmds = cli_cmds;
    parent->child_cmd_count = cli_cmd_count;
  }
}


void ArgParser_setFlags(struct CliCmd* parent, struct CliFlag cli_flags[], int cli_flag_count){
  if(parent == NULL){
    g_exec.child_flags = cli_flags;
    g_exec.child_flag_count = cli_flag_count;
  } else{
    parent->child_flags = cli_flags;
    parent->child_flag_count = cli_flag_count;
  }
}


int ArgParser_parse(int argc, char** argv, int(*dump_callback)(int, char**)){

  int argi = 1;
  while( argi < argc){
    const char* current_arg = argv[argi];
    if(current_arg[0] == '\0'){
      break;
    }

    if(isFlag(current_arg)){
      if(isLongFlag(current_arg)){

        struct CliFlag* cur_flag = CliCmd_getLongFlag(gp_current_cmd, &current_arg[2]);
        if(cur_flag != NULL){
          printf("Flag %s is registered\n", current_arg);
          CliFlag_doRaiseFlag(cur_flag);
          CliFlag_doCallback(cur_flag);
        } else{
          printf("Flag %s is not registered\n", current_arg);
          if(dump_callback == NULL) {
            return -1;
          }
          else{
            return dump_callback(argc - argi, &argv[argi]);
          }
        }
      } else{ // !isLongFlag(current_arg)

        struct CliFlag* cur_flag = CliCmd_getShortFlag(gp_current_cmd, current_arg[1]);
        if(cur_flag != NULL){
          printf("Flag -%c is registered\n", current_arg[1]);
          CliFlag_doRaiseFlag(cur_flag);
          CliFlag_doCallback(cur_flag);
        } else{
          printf("Flag -%c is not registered\n", current_arg[1]);
          if(dump_callback == NULL){
            return -2;
          } else{
            return dump_callback(argc-argi, &argv[argi]);
          }
        }
      }

    } else{// !isFlag(current_arg)
      struct CliCmd* cur_cmd = CliCmd_getChildCmd(gp_current_cmd, current_arg);
      if(cur_cmd != NULL){
        printf("Argument %s is registered\n", current_arg);
        CliCmd_doCallback(cur_cmd);
        gp_current_cmd = cur_cmd;
      } else{
        printf("Argument %s is not registered\n", current_arg);
        if(dump_callback == NULL){
          return -3;
        } else{
          return dump_callback(argc-argi, &argv[argi]);
        }
      }
    }
    argi++;
  }

}

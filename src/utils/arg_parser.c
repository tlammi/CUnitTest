#include "arg_parser.h"
#include "cli_cmd.h"
#include "print.h"

#define isFlag(flag_candidate) ((flag_candidate)[0] == '-')
#define isNFlagsInArg(flag_arg, n) ((flag_arg)[n] != '\0')
#define isLongFlag(flag_candidate) ((flag_candidate)[1] == '-')

#define ArgStatusOK 0 ///< OK
#define ArgStatusEOA -1 ///< End of Arguements
#define ArgStatusIAF -2 ///< Is a Flag
#define ArgStatusNAF -3 ///< Not a Flag
#define ArgStatusISF 1 ///< Is short flag

static int g_argi = 1;
static int g_flag_sub_index = 1;
static int g_argc = 1;
static char** g_argv;

static inline void initGetter(int argc, char* argv[]){
  g_argc = argc;
  g_argv = argv;
  g_flag_sub_index = 1;
  g_argi = 1;
}

static inline char* getNextArg(int* status){
  char* retval = NULL;
  if(g_argi < g_argc){
    retval = g_argv[g_argi];
    *status = 0;
    g_argi += 1;
  } else{
    *status = ArgStatusEOA;
    retval =  NULL;
  }
  return retval;
}

static inline char* getNextCmd(int* status){
  if(g_argi >= g_argc){
    *status = ArgStatusEOA;
    return NULL;
  }

  if(isFlag(g_argv[g_argi])){
    *status = ArgStatusIAF;
    return NULL;
  }

  *status = ArgStatusOK;
  g_argi += 1;
  return g_argv[g_argi-1];
}

static inline char* getNextFlag(int* status){
  if(g_argi >= g_argc){
    *status = ArgStatusEOA;
    return NULL;
  }

  if(!isFlag(g_argv[g_argi])){
    *status = ArgStatusNAF;
    return NULL;
  }

  if(isLongFlag(g_argv[g_argi])){
    *status = ArgStatusOK;
    g_argi += 1;
    return &g_argv[g_argi-1][2];
  } else{
    *status = ArgStatusISF;
    char* retval = &g_argv[g_argi][g_flag_sub_index];

    if(isNFlagsInArg(g_argv[g_argi], g_flag_sub_index+1)){
      g_flag_sub_index += 1;
    } else{
      g_argi += 1;
      g_flag_sub_index = 1;
    }

    return retval;

  }
}


static inline char* getNextFlagVal(int* status){
  if(g_argi >= g_argc){
    *status = ArgStatusEOA;
    return NULL;
  }

  if(isFlag(g_argv[g_argi])){
    *status = ArgStatusIAF;
    return NULL;
  }

  *status = ArgStatusOK;
  g_argi += 1;
  return g_argv[g_argi-1];
}

struct CliCmd g_exec;
struct CliCmd* gp_current_cmd = &g_exec;

/*
static const char* arg_parser_get(int argc, char** argv){
  static int index = 0;
  if(index == argc-1) return "";

  index++;
  return argv[index];
}
*/

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

  char* flag_str;
  struct CliFlag* pflag;
  char* cmd_str;
  struct CliCmd* pcmd;
  int status;
  initGetter(argc, argv);

  do{
    // Try to get a flag from arguments
    flag_str = getNextFlag(&status);
    if(flag_str != NULL){
      if(status == ArgStatusISF){
        pflag = CliCmd_getShortFlag(gp_current_cmd, *flag_str);
      } else if(status == ArgStatusOK){
        pflag = CliCmd_getLongFlag(gp_current_cmd, flag_str);
      } else{
        printf("Congratulations!!! This should never be executed...\n");
        return -1;
      }

      if(pflag != NULL){
        if(CliFlag_expectsVal(pflag)){
          char* val = getNextFlagVal(&status);
          if(status == ArgStatusOK){
            CliFlag_setVal(pflag, val);
          } else{
            printf("Expected value for flag %s, found none\n", flag_str);
            return -1;
          }
        }

        CliFlag_doRaiseFlag(pflag);
        CliFlag_doCallback(pflag);

      } else{
        printf("Invalid argument!\n");
        return -1;
      }

  } else{
    cmd_str = getNextCmd(&status);
    if(status == ArgStatusOK){
      pcmd = CliCmd_getChildCmd(gp_current_cmd, cmd_str);
      CliCmd_doCallback(pcmd);
      gp_current_cmd = pcmd;
    } else if(status == ArgStatusEOA){
      break;
    } else{
      printf("Congratulations!!! This should never be executed...\n");
      return -1;
    }
  }
  }while(status != ArgStatusEOA);

  return 0;

}

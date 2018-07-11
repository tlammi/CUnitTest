#ifndef CLI_FLAG_H
#define CLI_FLAG_H

struct CliFlag{
  const char* long_flag;
  const char* value;
  const char short_flag;
  char* flag_field;
  char flag_bit;
  char expects_val;
  void (*callback)();
};

struct CliFlag CliFlag_init(const char* long_flag, const char short_flag, char expects_val);

void CliFlag_setFlagField(struct CliFlag* handl, char* flag_field, int flag_bit);

void CliFlag_doRaiseFlag(struct CliFlag* handl);

void CliFlag_doCallback(struct CliFlag* handl);

void CliFlag_debugPrint(struct CliFlag* this, int indent);

#endif

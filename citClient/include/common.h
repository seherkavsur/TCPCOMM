#ifndef COMMON_H
#define COMMON_H

#include <sys/types.h>
#include <unistd.h>
/*********************VERSION SECTION********************************/
static constexpr char VERSION[] = "0.0.1-rc1";

/********************GENERAL DEFINES SECTION************************/


/*********************COMMON DEBUG VALUES********************************/
static constexpr int DEBUG_LENGTH = 512;
static constexpr int CMD_LINE_MAX_ARG_NUMBERS = 2;

#define DEBUG_ON 1
#define DEBUG_CLOSE 0

extern int critical_debug_value = 0;
extern int major_debug_value = 0;
extern int minor_debug_value = 0;
extern int medium_debug_value = 0;

void printLog(int *debugLevelValue, const char *cmd_expr, ...);
void printCustomLog(int *debugLevelValue, const char *cmd_expr, ...);

/*********************************************************************************/
#endif // COMMON_H
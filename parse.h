/*
 * TODO: copyright stuff...
 * NAME
 * Copyright (c) YEAR ORGANIZATION
 * ...
 */

#ifndef _PARSE__H_
#define _PARSE__H_

#define MAXLINE 1024 // max command line size
#define MAXARGS 128  // max number of arguments on a command line

struct cmd_t {
  char **cmd1_argv;
  char **cmd2_argv;
  char *cmd1_fds[3];
  char *cmd2_fds[3];
};

extern unsigned int bg; // background
extern unsigned int redir; // pipe

int parse_cmd_dynamic(char *input, struct cmd_t *cmd, int dir);
char *trim_whitespace(char *);

#endif

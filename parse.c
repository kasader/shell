/*
 * TODO: copyright stuff...
 * NAME
 * Copyright (c) YEAR ORGANIZATION
 * ...
 */

#include "parse.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//	inputs:
//		cmdline: a string of all command line arguments
//		bg: whether to run in the background
//  returns: an array of command line argument strings
int parse_cmd_dynamic(char *input, struct cmd_t *cmd, int dir) {
  char **args = 0;
  char *cmdline;
  int i, start, t, token_len;
  return 0;
}

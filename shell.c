/*
 * Swarthmore College, CS 45
 * Copyright (c) 2021 Swarthmore College Computer Science Department,
 * Swarthmore PA
 */

#include "parse.h"
#include <ctype.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#include <argp.h> 

/* The maximum size of circular history */
#define MAXHIST 10

#define NULL_PIPE    0
#define PIPE_L        1
#define PIPE_R        2
#define STDIN_REDIR   3
#define STDOUT_REDIR  4
#define STDERR_REDIR  5

#define SH_NAME      "shell"
#define SH_VERSION   0.1

// command history information
struct histlist_t {
  unsigned int cmd_num;
  char cmdline[MAXLINE];
} histlist;

struct ofiles_t {
  int cmd1_fds[3];
  int cmd2_fds[3];
} ofiles;

struct env_t {
  int mode;
  char *user;
  char *hosttype;
  char *hostname;
} env;

////////////////// GLOBAL VARIABLES //////////////////
static struct histlist_t history[MAXHIST];
unsigned int next; // the next place to insert in the history
unsigned int size; // the number of items in the history
unsigned int bg;   // background?
unsigned int redir;   // pipe?

////////////////// FUNCTION PROTOTYPES ////////////////////
void sig_handler(int);

void add_history(char *);
void print_history(void);
void get_history(char **);

void open_files(struct cmd_t, struct ofiles_t *);
void close_files(struct ofiles_t *);

int env_create(struct env_t *e);
int env_destroy(struct env_t *e);
int shell_loop();
////////////////// FUNCTIONS ////////////////////

int main(int argc, char **argv)
{
  struct env_t *e;

  parse_args();
  // Load config files, if any.
  // ...
  if (env_create(e)) {
    return EXIT_FAILURE;
  }

  // Run command loop.
  shell_loop();

  // Perform any shutdown/cleanup.
  // ...

  return EXIT_SUCCESS;
}

int env_create(struct env_t *e) {
  e = malloc(sizeof(struct env_t));
  if (!e) {
    return -ENOMEM;
  }
  e->mode = 0;
  e->user = getenv("USER");
  e->hosttype = getenv("HOSTTYPE");
  e->hostname = getenv("HOSTNAME");
  return 0;
}

int shell_loop() {
  // variables, etc.
  int quit = 1;

  while(quit) {

    // (1) print the shell prompt
    printf("%s-%f", SH_NAME, SH_VERSION, ); // makes it green!
    fflush(stdout);
    // (2) read in the next command entered by the user
    if (fgets(cmdline, MAXLINE, stdin) == NULL && ferror(stdin)) {
      perror("fgets() error\n");
    }
    if (feof(stdin)) { /* End of file (ctrl-D) */
      printf("End of file. Exiting...\n");
      fflush(stdout);
      exit(0);
    }

    // add the commandline unsigned into the history
    add_history(cmdline);

 
  }
}
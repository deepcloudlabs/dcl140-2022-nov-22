/* 
 * run_command.c :    do the fork, exec stuff, call other functions
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include "shell.h"

void run_command(char **myArgv) {
  pid_t pid;
  int stat;

  switch (pid=fork()) {

    /* Error. */
    case -1 :
      perror("fork");
      exit(errno);

    /* Parent. */
    default :
      waitpid(pid,&stat,0);
      if(WIFEXITED(stat) && WEXITSTATUS(stat)){
         fprintf(stderr, "Child %d exited with error status %d: %s\n",pid,WEXITSTATUS(stat),strerror(WEXITSTATUS(stat)));
      }
      return;

    /* Child. */
    case 0 :
      /* Run command in child process. */
      execvp(myArgv[0],myArgv);
      perror(myArgv[0]);
      exit(errno);
   }
}

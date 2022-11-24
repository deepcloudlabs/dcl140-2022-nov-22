/* 
 * pipe_command.c  :  deal with pipes
 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include "shell.h"

void pipe_and_exec(char **myArgv) {
  int pipe_argv_index = pipe_present(myArgv);
  int pipefds[2];

  switch (pipe_argv_index) {

    case -1:	/* Pipe at beginning or at end of argv;  See pipe_present(). */
      fputs ("Missing command next to pipe in commandline.\n", stderr);
      errno = EINVAL;	/* Note this is NOT shell exit. */
      return;
      break;

    case 0:	/* No pipe found in argv array or at end of argv array.
		See pipe_present().  Exec with whole given argv array. */
      execvp(myArgv[0],myArgv);
      break;

    default:	/* Pipe in the middle of argv array.  See pipe_present(). */
      myArgv[pipe_argv_index] = NULL;
      pipe(pipefds);
 
      switch(fork()) {

        case -1 :
	  break;

        /* Talking parent.  Remember this is a child forked from shell. */
        default :
  
          dup2(pipefds[1],STDOUT_FILENO); 
          close(pipefds[0]);
          close(pipefds[1]);
          execvp(myArgv[0], myArgv);
	  break;

        case 0 :

	  /* Redirect input of "child" through pipe. */
          dup2(pipefds[0],STDIN_FILENO); 
          close(pipefds[0]);
          close(pipefds[1]);
          pipe_and_exec(&myArgv[pipe_argv_index+1]);
      }
  }

  perror("Couldn't fork or exec child process");
  exit(errno);
}

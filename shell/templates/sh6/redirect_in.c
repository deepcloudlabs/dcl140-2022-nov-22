/* 
 * redirect_in.c  :  check for <
 */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "shell.h"

/*
 * Look for "<" in myArgv, then redirect input to the file.
 * Returns 0 on success, sets errno and returns -1 on error.
 */
int redirect_in(char ** myArgv) {
  int i;
  int fd;
  /* search forward for > */
  for(i=0; myArgv[i] != NULL; i++){  
      if ( strcmp(myArgv[i], "<") == 0){ 
         break;
      }   
  }
  if (myArgv[i]) {      /* found "<" in vector. */

    /* Open file. */
    if ((fd = open(myArgv[i+1], O_WRONLY | O_TRUNC | O_CREAT, 0666)) == -1){
       perror(myArgv[i+1]); 
       return -1; 
    }   
    /* Redirect to use it for output. */
    dup2(fd,STDIN_FILENO);
    close(fd);

    /* Remove the < and the filename from myArgv. */
    for(i=i+2; myArgv[i] != NULL; i++){
       myArgv[i-2] = myArgv[i];
    }
    myArgv[i-2] = NULL;
  }

  return 0;
}

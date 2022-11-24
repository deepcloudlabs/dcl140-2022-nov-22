/*
 *  pipe_present.c :  check for | 
 */

#include <stdio.h>
#include "shell.h"

/*
 * Return index offset into argv of where "|" is,
 * -1 if in an illegal position (first or last index in the array),
 * or 0 if not present.
 */
int pipe_present(char ** argv) {
  int index;

  /* Search through myCurrentArgv for a match on "|". */
  for (index=0;argv[index]!=NULL;index++){
      if ( strcmp(argv[index],"|") == 0)
         break;
  }

  if ( (index==0) || ((argv[index]!= NULL) && (argv[index+1] == NULL)) ) {
    return -1;

  } else if (argv[index]== NULL) {
    return 0;
  } else {
    return index;
  }
}

/* 
 * is_background.c :  check for & at end
 */

#include <stdio.h>
#include <string.h>
#include "shell.h"

int is_background(char ** myArgv) {

  if (*myArgv == NULL)
    return 0;

  while (*myArgv) myArgv++;
  myArgv--;
  if (strcmp(myArgv[0],"&") == 0){
     myArgv[0] = NULL;
     return TRUE;
  }
  return FALSE;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {

  struct stat buf1,buf2;
  int ask_user = 0,answer;
  char *target_path;

  if (argc != 3) {
    fprintf(stderr, "Usage: %s file1 file2\n",argv[0]);
    exit(1);
  }

  if (stat(argv[1], &buf1) == -1) {
      fprintf(stderr,"%s: %s: %s %s\n",argv[0],argv[1],strerror(errno),argv[2]);
      exit(2);
  }

  if (S_ISDIR(buf2.st_mode)){
      fprintf(stderr,"%s: %s %s: does not support directory move.\n",argv[0],argv[1],argv[2]);
      exit(1);
  }
  
  if (stat(argv[2], &buf2) == -1) {
    if(errno == ENOENT) 
      ask_user = 0;
    else {
      fprintf(stderr,"%s: %s %s: %s\n",argv[0],argv[1],argv[2],strerror(errno));
      exit(errno);
    }
  } else {
    if (S_ISDIR(buf2.st_mode)){
       target_path = (char*)malloc(strlen(argv[2]) + 1 + strlen(argv[1]) + 1);
       sprintf(target_path,"%s/%s",argv[2],argv[1]);
       argv[2] = target_path;
    } else {
      ask_user = 1;
    }
  }
  if (ask_user){
     printf("Override file %s ? : ",argv[2]);
     answer = getchar();
     if (answer != 'y' && answer != 'Y')
        return -1;
  }
  if ( rename(argv[1],argv[2]) == -1){
      fprintf(stderr,"%s: %s %s: %s\n",argv[0],argv[1],argv[2],strerror(errno));
      exit(errno);
  }  
}

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{
  char *file = argv[1];
  int fd;
  struct flock lock;
  fd = open(file, O_WRONLY);
  if(fd==-1){
    printf("*** No such file or directory\n");
    exit(1);
  }
  fcntl(fd, F_GETLK, &lock);
  if(lock.l_type!=F_UNLCK){
    printf("File is locked by %d\n", lock.l_pid);
  }else{
    printf("File is not locked\n");
    fcntl(fd, F_SETLKW, &lock);
  }
}

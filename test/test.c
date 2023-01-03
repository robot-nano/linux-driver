#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_SIZE 256
#define DEV_FILE "/dev/fg"

int fd;

void fasync_handler(int num) { printf("fasync_handler entering\n"); }

int main(void) {
  int i = 2;

  char data[256];
  int oflags = 0;
  int retval;

  signal(SIGIO, fasync_handler);

  fd = open(DEV_FILE, O_RDWR);
  if (fd == -1) {
    perror("error open\n");
    exit(-1);
  }

  printf("open " DEV_FILE " successfully\n");

  fcntl(fd, F_SETOWN, getpid());
  oflags = fcntl(fd, F_GETFL);
  fcntl(fd, F_SETFL, oflags | FASYNC);

  while (1);
  close(fd);
}
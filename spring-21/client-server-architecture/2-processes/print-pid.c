#include <stdio.h>
#include <unistd.h> 

int main() {
  printf("The process ID %d\n", getpid());
  printf("The parent process ID %d\n", (int)getppid());
  printf("Student: Néstor Iván Martínez Ostoa\n");
  return 0;
}

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(void)
{
 char *args[] = {"ls", NULL};
 if(execvp("ls", args) == -1) {
  perror("execve");
  exit(EXIT_FAILURE);
 }
 puts("shouldn't get here");
 exit(EXIT_SUCCESS);
}

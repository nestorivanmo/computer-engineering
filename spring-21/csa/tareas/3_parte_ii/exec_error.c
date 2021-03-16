#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
  char *args[] = {"ls" ,"-l", "./", NULL};
  if(execve("ls", args, NULL) == -1) {
    perror("execve");
    exit(EXIT_FAILURE);
  }
  puts("a partir de aqui no se ejecuta");
  exit(EXIT_SUCCESS);
}
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
  char envval[] = {"MYPATH=/user/local/someapp/bin"};

  /*
    int putenv(const char *varname);

    putenv se encarga de declarar el valor de una variable de entorno mediante
    la modificación de alguna existente o la creación de una nueva. *varname es 
    un apuntador a un string en donde el valor de *varname es el valor de la nueva
    variable de entorno.

    En este caso *varname es char envval[]
  */
  if (putenv(envval))
    puts("putenv failed");
  else
    puts("putenv suceeded");

  /*
    char *getenv(const char *varname);

    Regresa un apuntador a un string que contiene el valor especificado en 
    *varname en el ambiente actual. Si esta función no logra encontrar la variable
    de entorno regresa NULL. 
  */
  if (getenv("MYPATH"))
    printf("MYPATH=%s\n", getenv("MYPATH"));
  else
    puts("MYPATH unassigned");

  if (getenv("YOURPATH"))
    printf("YOURPATH=%s\n", getenv("YOURPATH"));
  else
    puts("YOURPATH unassigned");
  return 0;
}

//#include "Cello.h"
#include "narg.h"
#include <stdio.h>
#include <stdlib.h>
#include "commands.h"
#include <string.h>

defCommand(foobar, int i, int x) {
  printf("Hello!, %d, %d\n", i ,x);
  return 0;
}
  


int main(void) {
  
  cmd(foobar, 3, 4, 3);
} 

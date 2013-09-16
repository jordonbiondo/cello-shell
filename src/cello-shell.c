#include "Cello.h"

global var get_commands(void);

int main(void) {
  var commands = get_commands();
  println(commands);
} 


var get_commands(void) {
  lambda(quit, args) {
    println("quitting");
    return None;
  };
  
  lambda(change_dir, args) {
    println("changing dir");
    return None;
  };
  
  var commands = new(Array);
  push(commands, change_dir);
  push(commands, quit);
  return commands;
} 


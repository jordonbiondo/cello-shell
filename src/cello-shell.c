#include "Cello.h"
#include "narg.h"


#define CMD_NAME(name) _command_##name
#define CMD_ARGC_NAME(name) _command_##name##_argc
#define CMD_STR_NAME(name) _command_##name##_str
#define CMD_SIGNATURE_NAME(name) _command_##name##_sig
#define CMD_SIGNATURE(...) #__VA_ARGS__


/**
 * Define a command with NAME and any args
 * 
 * Example:
 *   defCommand(foo, int a, int b) {
 *     println("FOO! %d %d", a, b);
 *     return 0;
 *   }
 */
#define defCommand(name, ...)						\
  int CMD_NAME(name)(void* ctx, __VA_ARGS__);				\
		    const void* name = &CMD_NAME(name);	                \
		    const char* CMD_STR_NAME(name) = #name;		\
		    const char* CMD_SIGNATURE_NAME(name) = CMD_SIGNATURE(__VA_ARGS__); \
		    const int CMD_ARGC_NAME(name) = PP_NARG(__VA_ARGS__); \
		    int CMD_NAME(name)(void* ctx, __VA_ARGS__)

#define INCORRECT_NUMBER_OF_ARGS(name, arg_sig, expected, given) {	\
    printf("ERROR: Incorrect number of arguments to %s(%s)\n\t", name, arg_sig); \
    printf("@ %s:%d\n\t", __FILE__, __LINE__);				\
    printf("expected: %d\n\tgiven: %d\n", expected, given);		\
    exit(-1);								\
  }
  
int runtime_assert_equal_int(const char* name, const char* arg_sig, int count, int given) {		 
  if (count != given) { 
    INCORRECT_NUMBER_OF_ARGS(name, arg_sig, count, given);
    exit(-1);
  } else {
    return 0;
  }				 
}


/**
 * Run command NAME with any args, asserts correct arg count
 */
#define cmd(name, ...)							\
  ((runtime_assert_equal_int(CMD_STR_NAME(name), CMD_SIGNATURE_NAME(name), \
			     CMD_ARGC_NAME(name), PP_NARG(__VA_ARGS__))) | \
   (((int(*)(void*, ...))name)(NULL, __VA_ARGS__)))

defCommand(foobar, int i, int x) {
  return 1;
}
  
var get_commands(void);

int main(void) {
  
  /* var commands = get_commands(); */
  /* println(commands); */
  printf("Here: %d\n", cmd(foobar, 2, 2, 4));
  printf("Here: %d\n", 0 == 5);
  printf("Here: %d\n", 4 == 4);
  printf("Here: %d\n", _command_foobar_argc);
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


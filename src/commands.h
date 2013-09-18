#ifndef _COMMANDS_H_
#define _COMMANDS_H_







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

defCommand(foobar, int a, int b) { ... } ->

int _command_foobar(int a, int b);
const void* foobar = &_command_foobar;
const char* _command_foobar_str = "foobar";
const char* _command_foobar_sig = "int a, int b";
const char* _command_foobar_argc = 2;
int _command_foobar(int a, int b) {
  ...
}

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
  
/**
 * Assert correct arg count for function NAME with signature ARG_SIG
 */
int runtime_assert_equal_int(const char* name, const char* arg_sig, int needed, int given) {		 
  if (needed != given) { 
    INCORRECT_NUMBER_OF_ARGS(name, arg_sig, needed, given);
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


#endif

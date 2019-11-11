#include "../src/interpreter.h"
#include "../src/maker.h"

// static b32 compareFile(const std::string &, FILE *);

#ifndef TEST_MAKEFILE
#define TEST_MAKEFILE 0
#endif // !TEST_MAKEFILE


#if defined(TEST_MAKEFILE) && TEST_MAKEFILE
s32 main(s32 argc, char **argv) {
	// TODO: Actually write test code here...
	return 0;
}
#endif
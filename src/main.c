// #include "types.h"

#include "maker.h"
#include "interpreter.h"
#include "arraylist.h"
#include "stack.h"
#include "string.h"

#if Debug
#include <vld.h>
#endif

void error(const char *msg) {
    perror("Error interpeting args from command line!\n");

#ifdef WIN32
        system("PAUSE");
#endif

    exit(-1);
}

b32 isSourceFile(const String *);

s32 main(s32 argc, char **argv) {

#if 0
    String strInt;
    strInt.cstr = "945";
    strInt.len = strlen(strInt.cstr);

    u32 output;
    const b32 result = parseUInt(&strInt, &output);

    printf("Result: %u, value: %u\n", result, output);
#endif

#if 0
    String testStr;
    testStr.cstr = "a.c";
    testStr.len = 4;
    
    printf("Is source file %u\n", isSourceFile(&testStr));
#ifdef WIN32
    system("PAUSE");
#endif
    return 0;
#endif

    IFlags flags;
    flags.args = NULL;
    flags.numArgs = 0;
    flags.cmode = True;

    if (!interpret(argv, (u32) argc, &flags)) {
        error("Error interpeting args from command line!\n");
    }

    SRC src;
    src.len = 2;
    src.srcFiles = (String *) calloc(src.len, sizeof(String));
    constructString(&src.flags, DEFAULT_FLAGS);
    constructString(&src.srcFiles[0], "main.c");
    constructString(&src.srcFiles[1], "example.c");

    writeToFile(MAKEFILE_VAR, &src);

    desrtuctString(&src.flags);
    desrtuctString(&src.srcFiles[0]);
    desrtuctString(&src.srcFiles[1]);
    free(src.srcFiles);

#ifdef WIN32
    system("PAUSE");
#endif
    return 0;
}
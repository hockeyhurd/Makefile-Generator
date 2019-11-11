#include "MakeGen.h"
#include "BuildOptions.h"
#include "Flags.h"
#include "Target.h"
#include "StringCache.h"

#include <iostream>
#include <vector>

namespace makegen
{
    StringCache &getStringCache()
    {
        static StringCache inst;
        return inst;
    }

    void exitProgram(const s32 exitCode)
    {
        exit(exitCode);
    }
}

using namespace makegen;

static Option createOption(String &&variable, String &&value);

/*
 * ./makegen -type cpp (default; Also support "c", "java", ... ?) -name Makefile <default=makefile> \
 *      -cflags "-pipe -std=c++11 -g -O0 -Wall -Wextra -pedantic" -lflags "-pthread" \
 *      -o "hello" -src "Hello.cpp Types.c" 
 */

s32 main(s32 argc, char **argv)
{
    static StringCache &cache = makegen::getStringCache();
    const String path = "FakeMakefile";
    File file(path);

    // Configure build options:

    // Common build options
    BuildOptions commonBuildOptions;
    commonBuildOptions.addOption(createOption("CC", "g++"));
    commonBuildOptions.encode(file);

    // Compilation only build options
    BuildOptions compileOptions;
    compileOptions.addOption(createOption("CC_FLAGS", "-pipe -std=c++11 -O2 -Wall -c"));
    compileOptions.encode(file);

    // Linker only build options
    BuildOptions linkOptions;
    linkOptions.addOption(createOption("LD_FLAGS", ""));
    linkOptions.encode(file);

    // Name/output build options
    BuildOptions nameOption;
    nameOption.addOption(createOption("NAME", "-o test"));
    nameOption.encode(file);

    BuildOptions cleanOptions;
    cleanOptions.addOption(createOption("RM", "rm -f"));
    cleanOptions.encode(file);

    // Add space
    file.endl();

    // Target tracking
    std::vector<Target> targets;
    targets.reserve(0x10);

    Target testTarget(cache.intern("Test.o"));
    testTarget.addDependency(cache.intern("Test.cpp"));

    targets.emplace_back(std::move(testTarget));

    // "all" and "link" targets are "special"
    AllTarget allTarget(cache.intern("all"));
    Target linkTarget(cache.intern("link"));

    allTarget.addDependency(linkTarget.getName());

    // Add dependencies to "all" and "link" targets
    for (auto &target : targets)
    {
        const auto &dependency = target.getName();

        allTarget.addDependency(dependency);
        linkTarget.addDependency(dependency);
    }

    // Write target "all"
    allTarget.build(file);

    for (auto &target : targets)
    {
        file.endl();
        target.build(file, { commonBuildOptions, compileOptions });
    }

    // Build link targets.
    file.endl();
    linkTarget.build(file, { commonBuildOptions, linkOptions, nameOption });

    // Clean target
    file.endl();
    CleanTarget cleanTartget(cache.intern("clean"));
    cleanTartget.addDependency(cache.intern("*.o"));
    cleanTartget.build(file, { cleanOptions });

    return 0;
}

Option createOption(String &&variable, String &&value)
{
    static StringCache &inst = makegen::getStringCache();

    return Option(inst.intern(std::move(variable)), inst.intern(std::move(value)));
}
#pragma once

#ifndef MAKEGEN_PARSER_H
#define MAKEGEN_PARSER_H

#include "MakeGen.h"
#include "BuildOptions.h"
#include "SrcFile.h"

#include <unordered_map>
#include <vector>

/*
 * ./makegen -type cpp (default; Also support "c", "java", ... ?) -name Makefile <default=makefile> \
 *      -cflags "-pipe -std=c++11 -g -O0 -Wall -Wextra -pedantic" -lflags "-pthread" \
 *      -o "hello" -src "Hello.cpp Types.c" 
 */

namespace makegen
{

    class Configuration;
    class FileWriter;

    typedef bool (*ParseFunctor)(Configuration &, const char **, const s32, s32 &);

    extern StringCache &getStringCache();

    enum class EnumLangType
    {   
        CPP = 0, C, JAVA
    };

    class Configuration
    {
    private:

        String fileName;
        String outputName;
        EnumLangType langType;
        // BuildOptions commonOptions;
        BuildOptions compileOptions;
        BuildOptions linkOptions;
        std::vector<SrcFile> sourceFiles;

        static std::unordered_map<String, ParseFunctor> lookupTable;

    public:

        Configuration();
        Configuration(const Configuration &) = delete;
        Configuration(Configuration &&) = default;
        ~Configuration() = default;

        Configuration &operator= (const Configuration &) = delete;
        Configuration &operator= (Configuration &&) = default;

        BuildOptions &getCompileOptions();
        BuildOptions &getLinkOptions();

        StringView getSuggestedCompiler() const;
        StringView getSuggestedLinker() const;

        void setFileName(String name);
        void setOutputName(String name);
        void setLangType(const EnumLangType langType);

        void addSrcFile(const SrcFile &file);
        void addSrcFile(SrcFile &&file);

        bool parse(const char **argv, const s32 argc);

        bool verify();
        void build();

    private:

        void generateDefaultCompilerOptions();
        void generateDefaultLinkOptions();
    };

}

#endif //!MAKEGEN_PARSER_H
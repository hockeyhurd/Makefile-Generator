#include "Parser.h"
#include "Target.h"

#include <iostream>
#include <cstring>

namespace makegen
{

    static const String name = "-name";
    static const String outputNameFlag = "-o";
    static const String type = "-type";
    static const String ccflags = "-cflags";
    static const String ldflags = "-lflags";
    static const String src = "-src";

    static bool parseFileName(Configuration &config, const char **argv, const s32 argc, s32 &index);
    static bool parseOutputName(Configuration &config, const char **argv, const s32 argc, s32 &index);
    static bool parseType(Configuration &config, const char **argv, const s32 argc, s32 &index);
    static bool parseCCflags(Configuration &config, const char **argv, const s32 argc, s32 &index);
    static bool parseLDflags(Configuration &config, const char **argv, const s32 argc, s32 &index);
    static bool parseSrc(Configuration &config, const char **argv, const s32 argc, s32 &index);

    std::unordered_map<String, ParseFunctor> Configuration::lookupTable = 
    {
        { name, parseFileName },
        { outputNameFlag, parseOutputName },
        { type, parseType },
        { ccflags, parseCCflags },
        { ldflags, parseLDflags },
        { src, parseSrc }
    };

    bool parseFileName(Configuration &config, const char **argv, const s32 argc, s32 &index)
    {
        if (name == argv[index] && ++index < argc)
        {
            const char *nextArg = argv[index];
            config.setFileName(nextArg);

            return true;
        }

        --index;

        return false;
    }

    bool parseOutputName(Configuration &config, const char **argv, const s32 argc, s32 &index)
    {
        if (outputNameFlag == argv[index] && ++index < argc)
        {
            const char *nextArg = argv[index];
            config.setOutputName(nextArg);

            static auto &cache = getStringCache();
#if 0
            Option linkOption(cache.intern(outputNameFlag), cache.intern(outputNameFlag), false);
            Option nameOption(cache.intern("NAME"), cache.intern(nextArg));

            auto &linkOptions = config.getLinkOptions();
            linkOptions.addOption(std::move(linkOption));
            linkOptions.addOption(std::move(nameOption));
#else
            auto &linkOptions = config.getLinkOptions();
            Option nameOption(cache.intern("NAME"), cache.intern(nextArg));
            linkOptions.addOption(std::move(nameOption));

            auto findResult = linkOptions.findOption(cache.intern("LD_FLAGS"));

            if (findResult == linkOptions.end())
            {
                Option linkOption(cache.intern("LD_FLAGS"), cache.intern(outputNameFlag));
                Option linkerOption(cache.intern("LD"), config.getSuggestedLinker());
                linkOptions.addOptionFront(std::move(linkOption));
                linkOptions.addOptionFront(std::move(linkerOption));
            }

            else
            {
                Option newLinkOption = *findResult;
                String newValue = findResult->getVariable().str() + " -o";
                newLinkOption.setValue(cache.intern(newValue));
                linkOptions.removeOption(findResult);
            }
#endif

            return true;
        }

        --index;

        return false;
    }

    bool parseType(Configuration &config, const char **argv, const s32 argc, s32 &index)
    {
        if (type == argv[index] && ++index < argc)
        {
            static const char *c = "c";
            static const char *cpp = "cpp";
            static const char *java = "java";

            const char *nextArg = argv[index];
            
            if (std::strncmp(cpp, nextArg, 3) == 0)
            {
                config.setLangType(EnumLangType::CPP);
                return true;
            }

            else if (std::strncmp(c, nextArg, 1) == 0)
            {
                config.setLangType(EnumLangType::C);
                return true;
            }

            else if (std::strncmp(java, nextArg, 4) == 0)
            {
                config.setLangType(EnumLangType::JAVA);
                return true;
            }
        }

        --index;

        return false;
    }

    bool parseCCflags(Configuration &config, const char **argv, const s32 argc, s32 &index)
    {
        if (ccflags == argv[index] && ++index < argc)
        {
            static auto &cache = getStringCache();
            auto &compileOptions = config.getCompileOptions();

            compileOptions.addOption(Option(cache.intern("CC"), config.getSuggestedCompiler()));
            compileOptions.addOption(Option(cache.intern("CC_FLAGS"), cache.intern(argv[index])));

            return true;
        }

        --index;

        return false;
    }

    bool parseLDflags(Configuration &config, const char **argv, const s32 argc, s32 &index)
    {
        if (ldflags == argv[index] && ++index < argc)
        {
            static auto &cache = getStringCache();
            auto &linkOptions = config.getLinkOptions();

            linkOptions.addOption(Option(cache.intern("LD"), config.getSuggestedLinker()));
            linkOptions.addOption(Option(cache.intern("LD_FLAGS"), cache.intern(argv[index])));

            return true;
        }

        --index;

        return false;
    }

    bool parseSrc(Configuration &config, const char **argv, const s32 argc, s32 &index)
    {
        if (src == argv[index] && ++index < argc)
        {
            static auto &cache = getStringCache();

            const String arg = argv[index];
            size_t start = 0;
            size_t end = 0;

            for (auto &ch : arg)
            {
                // TODO: Could have an "off by 1 error" here...
                if (ch == ' ' /*|| end == arg.size()*/)
                {
                    auto srcFileStr = cache.intern(arg.substr(start, end));
                    config.addSrcFile(SrcFile(srcFileStr));
                    start = end;
                }

                ++end;
            }

            auto srcFileStr = cache.intern(arg.substr(start, end));
            config.addSrcFile(SrcFile(srcFileStr));

            return true;
        }

        --index;

        return false;
    }

    Configuration::Configuration() : fileName("makefile"), langType(EnumLangType::CPP)
    {
    }

    BuildOptions &Configuration::getCompileOptions()
    {
        return compileOptions;
    }

    BuildOptions &Configuration::getLinkOptions()
    {
        return linkOptions;
    }

    StringView Configuration::getSuggestedCompiler() const
    {
        static auto &cache = getStringCache();

        switch (langType)
        {
        case EnumLangType::C:
            return cache.intern("gcc");
        case EnumLangType::CPP:
            return cache.intern("g++");
        case EnumLangType::JAVA:
            return cache.intern("javac");
        }
    }

    StringView Configuration::getSuggestedLinker() const
    {
        static auto &cache = getStringCache();

        switch (langType)
        {
        case EnumLangType::C:
            return cache.intern("gcc");
        case EnumLangType::CPP:
            return cache.intern("g++");
        case EnumLangType::JAVA:
            return cache.intern("javac");
        }
    }

    void Configuration::setFileName(String name)
    {
        this->fileName = std::move(name);
    }

    void Configuration::setOutputName(String name)
    {
        this->outputName = std::move(name);
    }

    void Configuration::setLangType(const EnumLangType langType)
    {
        this->langType = langType;
    }

    void Configuration::addSrcFile(const SrcFile &file)
    {
        sourceFiles.push_back(file);
    }

    void Configuration::addSrcFile(SrcFile &&file)
    {
        sourceFiles.emplace_back(std::move(file));
    }

    bool Configuration::parse(const char **argv, const s32 argc)
    {
        for (s32 i = 1; i < argc; i++)
        {
            auto &flag = argv[i];
            auto findResult = lookupTable.find(flag);

            if (findResult == lookupTable.end())
            {
                std::cout << "Failed to parse option: \"" << flag << "\"\n";
                return false; 
            }

            findResult->second(*this, argv, argc, i);
        }

        return true;
    }

    bool Configuration::verify()
    {
        if (compileOptions.empty())
        {
            generateDefaultCompilerOptions();
        }

        if (linkOptions.empty())
        {
            generateDefaultLinkOptions();
        }

        return true;
    }

    void Configuration::build()
    {
        static auto &cache = getStringCache();

        FileWriter file(fileName);

        // Encode all options
        compileOptions.encode(file);
        linkOptions.encode(file);

        static auto createOption = [](String &&name, String &&value, const bool encodable = true)
        {
            return Option(cache.intern(name), cache.intern(value), encodable);
        };

        BuildOptions cleanOptions;
        cleanOptions.addOption(createOption("RM", "rm -f"));
        cleanOptions.addOption(createOption("NAME", "NAME", false));
        cleanOptions.encode(file);

        // Create targets
        std::vector<Target> targets;
        targets.reserve(std::min<size_t>(2, sourceFiles.size() + 2));

        for (auto &srcFile : sourceFiles)
        {
            bool result;
            auto srcFileName = srcFile.getName(result);
            auto srcFileFull = srcFile.getFile();

            if (!result)
            {
                std::cout << "Failed to create target for file: \"" << srcFileFull.str();
                std::cout << "\"\n";
                continue;
            }

            // TODO: This will only work with C/C++.  Will need to update for future Java support.
            Target target(cache.intern(srcFileName.str() + ".o"));
            target.addDependency(srcFileFull);
            targets.emplace_back(std::move(target));
        }

        Target linkTarget(cache.intern("link"));
        AllTarget allTarget(cache.intern("all"));
        allTarget.addDependency(linkTarget.getName());

        // Add dependencies to "all" and "link" targets
        for (auto &target : targets)
        {
            const auto &dependency = target.getName();

            allTarget.addDependency(dependency);
            linkTarget.addDependency(dependency);
        }

        // Write target "all"
        allTarget.build(file, nullptr);

        for (auto &target : targets)
        {
            file.endl();
            target.build(file, &compileOptions);
        }

        // Build link targets.
        file.endl();
        linkTarget.build(file, &linkOptions);

        // Clean target
        file.endl();
        CleanTarget cleanTartget(cache.intern("clean"));
        cleanTartget.addDependency(cache.intern("*.o"));
        cleanTartget.build(file, &cleanOptions);
    }

    void Configuration::generateDefaultCompilerOptions()
    {
        static auto &cache = getStringCache();

        compileOptions.addOption(Option(cache.intern("CC"), getSuggestedCompiler()));
        compileOptions.addOption(Option(cache.intern("CC_FLAGS"), cache.intern("")));
    }

    void Configuration::generateDefaultLinkOptions()
    {
        static auto &cache = getStringCache();  

        linkOptions.addOption(Option(cache.intern("LD"), getSuggestedLinker()));
        linkOptions.addOption(Option(cache.intern("LD_FLAGS"), cache.intern(""))); 
    }

}

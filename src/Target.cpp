#include "Target.h"

namespace makegen
{

    Target::Target(StringView name) : name(std::move(name))
    {
    }

    StringView Target::getName() const
    {
        return name;
    }

    void Target::addDependency(StringView dependency)
    {
        dependencies.emplace_back(std::move(dependency));
    }

    void Target::build(File &file, std::initializer_list<BuildOptions> buildOptions)
    {
        file << name.str();
        file << ':';

        for (auto &dep : dependencies)
        {
            file << ' ';
            file << dep.str();
        }

        file.endl();
        file.tab();

        // file << buildOptions.getBuildConfig().str();

        const auto len = buildOptions.size();
        std::initializer_list<BuildOptions>::size_type i = 0;

        for (auto &option : buildOptions)
        {
            file << const_cast<BuildOptions &>(option).getBuildConfig().str();

            if (i < len - 1)
                file << ' ';
        }

        for (auto &dep : dependencies)
        {
            file << ' ';
            file << dep.str();
        }

        file.endl();
    }

    AllTarget::AllTarget(StringView name) : Target(name)
    {
    }

    void AllTarget::build(File &file, std::initializer_list<BuildOptions> buildOptions)
    {
        file << name.str();
        file << ':';

        for (auto &dep : dependencies)
        {
            file << ' ';
            file << dep.str();
        }

        file.endl();
    }

    CleanTarget::CleanTarget(StringView name) : Target(name)
    {
    }

    void CleanTarget::build(File &file, std::initializer_list<BuildOptions> buildOptions)
    {
        file << name.str();
        file << ':';

        file.endl();
        file.tab();

        // file << buildOptions.getBuildConfig().str();

        const auto len = buildOptions.size();
        std::initializer_list<BuildOptions>::size_type i = 0;

        for (auto &option : buildOptions)
        {
            file << const_cast<BuildOptions &>(option).getBuildConfig().str();

            if (i < len - 1)
                file << ' ';
        }

        for (auto &dep : dependencies)
        {
            file << ' ';
            file << dep.str();
        }

        file.endl();
    }

}
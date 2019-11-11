#ifndef MAKEGEN_TARGET_H
#define MAKEGEN_TARGET_H

#include "MakeGen.h"
#include "BuildOptions.h"
#include "File.h"
#include "StringCache.h"

#include <vector>
#include <initializer_list>

namespace makegen
{

    class Target
    {
    protected:

        StringView name;

        // using DependencyList = std::forward_list<String>;
        using DependencyList = std::vector<StringView>;
        DependencyList dependencies;

    public:

        Target(StringView name);
        Target(const Target &) = delete;
        Target(Target &&) = default;
        virtual ~Target() = default;

        Target &operator= (const Target &) = delete;
        Target &operator= (Target &&) = default;

        StringView getName() const;

        // void addDependency(const String &dependency);
        // void addDependency(String &&dependency);
        void addDependency(StringView dependency);

        virtual void build(File &file, std::initializer_list<BuildOptions> buildOptions = {});

    };
    
    class AllTarget : public Target
    {
    public:

        AllTarget(StringView name);
        ~AllTarget() = default;

        void build(File &file, std::initializer_list<BuildOptions> buildOptions = {}) override;
    };

    class CleanTarget : public Target
    {
    public:

        CleanTarget(StringView name);
        ~CleanTarget() = default;

        void build(File &file, std::initializer_list<BuildOptions> buildOptions = {}) override;
    };

#if 0
    class LinkTarget : public Target
    {
    private:

    public:

        LinkTarget(StringView name);
        ~LinkTarget() = default;

        void build(File &file, std::initializer_list<BuildOptions> buildOptions) override;
    };
#endif

}

#endif //!MAKEGEN_TARGET_H
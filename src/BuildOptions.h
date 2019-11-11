#pragma once

#ifndef MAKEGEN_BUILDOPTIONS_H
#define MAKEGEN_BUILDOPTIONS_H

#include "File.h"
#include "StringCache.h"

#include <memory>
#include <vector>

namespace makegen
{

    class Option
    {
    private:

        StringView variable;
        StringView value;
        StringView useableVariable;

    public:

        Option(StringView variable, StringView value);
        Option(const Option &) = default;
        Option(Option &&) = default;
        virtual ~Option() = default;

        Option &operator= (const Option &) = default;
        Option &operator= (Option &&) = default;

        StringView getVariable() const;
        StringView getValue() const;
        StringView getUseableVariable() const;

        void encode(File &file, const u32 indentSize = 0);

    };

    class BuildOptions
    {
    private:

        std::unique_ptr<StringView> config;

        using OptionsList = std::vector<Option>;
        OptionsList options;

    public:

        // BuildOptions(StringView variable);
        BuildOptions() = default;
        BuildOptions(const BuildOptions &);
        BuildOptions(BuildOptions &&) = default;
        ~BuildOptions() = default;

        BuildOptions &operator= (const BuildOptions &);
        BuildOptions &operator= (BuildOptions &&) = default;

        StringView getBuildConfig();

        void addOption(const Option &option);
        void addOption(Option &&option);

        void encode(File &file, const u32 indentSize = 0);

    };

}

#endif //!MAKEGEN_BUILDOPTIONS_H
#pragma once

#ifndef MAKEGEN_BUILDOPTIONS_H
#define MAKEGEN_BUILDOPTIONS_H

#include "FileWriter.h"
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
        bool encodable;

    public:

        Option(StringView variable, StringView value, const bool encodable = true);
        Option(const Option &) = default;
        Option(Option &&) = default;
        virtual ~Option() = default;

        Option &operator= (const Option &) = default;
        Option &operator= (Option &&) = default;

        StringView getVariable() const;
        StringView getValue() const;
        void setValue(StringView value);
        StringView getUseableVariable() const;

        bool isEncodable() const;

        void encode(FileWriter &file, const u32 indentSize = 0);

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

        bool empty() const;
        OptionsList::size_type size() const;

        StringView getBuildConfig();

        void addOption(const Option &option);
        void addOption(Option &&option);

        void addOptionFront(const Option &option);
        void addOptionFront(Option &&option);

        inline auto begin() const
        {
            return options.begin();
        }

        inline auto end() const
        {
            return options.end();
        }

        OptionsList::iterator findOption(StringView name);
        void removeOption(OptionsList::iterator iter);

        void encode(FileWriter &file, const u32 indentSize = 0);

    };

}

#endif //!MAKEGEN_BUILDOPTIONS_H
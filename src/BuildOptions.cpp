#include "BuildOptions.h"

namespace makegen
{

    extern StringCache &getStringCache();

    static StringView createUsableVariable(StringView variable)
    {
        String result = "$(";
        result += variable.str();
        result += ')';

        return getStringCache().intern(result);
    }

    Option::Option(StringView variable, StringView value) : variable(std::move(variable)), value(std::move(value)), useableVariable(createUsableVariable(this->variable))
    {
    }

    StringView Option::getVariable() const
    {
        return variable;
    }

    StringView Option::getValue() const
    {
        return value;
    }

    StringView Option::getUseableVariable() const
    {
        return useableVariable;
    }

    void Option::encode(File &file, const u32 indentSize)
    {
        for (u32 i = 0; i < indentSize; ++i)
        {
            file.tab();
        }

        file << variable.str();
        file << '=';
        file << value.str();
        file.endl();
    }

    BuildOptions::BuildOptions(const BuildOptions &other) : config(other.config != nullptr ? std::make_unique<StringView>(*other.config) : nullptr)
    {
        for (auto &option : other.options)
        {
            options.push_back(option);
        }
    }

    BuildOptions &BuildOptions::operator= (const BuildOptions &other)
    {
        config = other.config != nullptr ? std::make_unique<StringView>(*other.config) : nullptr;
        options.clear();

        for (auto &option : other.options)
        {
            options.push_back(option);
        }

        return *this;
    }

    StringView BuildOptions::getBuildConfig()
    {
        if (config == nullptr)
        {
            String configBuilder;
            configBuilder.reserve(0x10 * options.size());

            for (auto &option : options)
            {
                configBuilder += option.getUseableVariable().str();
                configBuilder += ' ';
            }

            // Erases the trailing space character
            configBuilder.pop_back();

            config = std::make_unique<StringView>(getStringCache().intern(configBuilder));
        }

        return *config;
    }

    void BuildOptions::addOption(const Option &option)
    {
        options.push_back(option);
    }

    void BuildOptions::addOption(Option &&option)
    {
        options.emplace_back(std::move(option));
    }

    void BuildOptions::encode(File &file, const u32 indentSize)
    {
#if 0
        file << variable.str();
        file << '=';

        for (auto &option : options)
        {
            file << ' ';
            file << option.getVariable();
        }
#else
        for (auto &option : options)
        {
            option.encode(file, indentSize);
        }
#endif
    }

}
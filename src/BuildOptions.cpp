#include "BuildOptions.h"

// #include <iostream>

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

    Option::Option(StringView variable, StringView value, const bool encodable) : variable(std::move(variable)), value(std::move(value)), useableVariable(createUsableVariable(this->variable)), encodable(encodable)
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

    void Option::setValue(StringView value)
    {
        this->value = std::move(value);
    }

    StringView Option::getUseableVariable() const
    {
        return useableVariable;
    }

    bool Option::isEncodable() const
    {
        return encodable;
    }

    void Option::encode(FileWriter &file, const u32 indentSize)
    {
        if (!encodable)
            return;

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

    bool BuildOptions::empty() const
    {
        return options.empty();
    }

    BuildOptions::OptionsList::size_type BuildOptions::size() const
    {
        return options.size();
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

    void BuildOptions::addOptionFront(const Option &option)
    {
        options.insert(options.begin(), option);
    }

    void BuildOptions::addOptionFront(Option &&option)
    {
        options.emplace(options.begin(), std::move(option));
    }

    BuildOptions::OptionsList::iterator BuildOptions::findOption(StringView name)
    {
        auto theEnd = options.end();

        for (auto iter = options.begin(); iter != theEnd; ++iter)
        {
            // std::cout << iter->getVariable().str() << std::endl;
            if (iter->getVariable() == name)
            {
                return iter;
            }
        }

        return theEnd;
    }

    void BuildOptions::removeOption(BuildOptions::OptionsList::iterator iter)
    {
        options.erase(iter);
    }

    void BuildOptions::encode(FileWriter &file, const u32 indentSize)
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
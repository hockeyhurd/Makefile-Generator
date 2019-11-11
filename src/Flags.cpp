#include "Flags.h"

namespace makegen
{

    Flag::Flag(const String &key, const String &value) : key(key), value(value)
    {
    }

    Flag::Flag(String &&key, String &&value) : key(std::move(key)), value(std::move(value))
    {
    }

    String &Flag::getKey() const
    {
        return const_cast<String&>(key);
    }

    void Flag::setKey(const String &key)
    {
        this->key = key;
    }

    void Flag::setKey(String &&key)
    {
        this->key = std::move(key);
    }

    String &Flag::getValue() const
    {
        return const_cast<String&>(value);
    }

    void Flag::setValue(const String &value)
    {
        this->value = value;
    }

    void Flag::setValue(String &&value)
    {
        this->value = std::move(value);
    }

    FlagOutputName::FlagOutputName(const String &key, const String &value) : Flag(key, value)
    {
    }

    FlagOutputName::FlagOutputName(String &&key, String &&value) : Flag(std::move(key), std::move(value))
    {
    }

    bool FlagOutputName::match(const String &input)
    {
        return "-name=" == input;
    }

    bool FlagOutputName::verify() const
    {
        return !value.empty();
    }

    void FlagOutputName::encode(const File &file)
    {
        // TODO: Do encode logic.
    }

}
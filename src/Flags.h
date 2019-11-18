#pragma once

#ifndef MAKEGEN_FLAGS_H
#define MAKEGEN_FLAGS_H

#include "MakeGen.h"

namespace makegen
{

    class File;

    class Flag
    {
    protected:

        String key;
        String value;    

    public:

        Flag(const String &key, const String &value);
        Flag(String &&key, String &&value);
        
        virtual ~Flag() = default;

        String &getKey() const;
        // void setKey(const String &key);
        // void setKey(String &&key);

        String &getValue() const;
        void setValue(const String &value);
        void setValue(String &&value);

        // Override this to implement matching input parsed.
        virtual bool match(const String &input);

        // Override this to verify key-value pairs.
        virtual bool verify() const;

        // Override this for encoding.
        virtual void encode(File &file);

    };

    class FlagOutputName : public Flag
    {
    public:

        FlagOutputName(const String &key, const String &value);
        FlagOutputName(String &&key, String &&value);

        ~FlagOutputName() = default;

        bool match(const String &input) override;
        bool verify() const override;
        void encode(File &file) override;

    };

}

#endif //!MAKEGEN_FLAGS_H
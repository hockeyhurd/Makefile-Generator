#pragma once

#ifndef MAKEGEN_STRINGCACHE_H
#define MAKEGEN_STRINGCACHE_H

#include "MakeGen.h"

#include <unordered_set>

namespace makegen
{

    class StringCache;

    class StringView
    {
    public:

        // static const StringView EMPTY;

    private:

        friend class StringCache;

        String *string;

        explicit StringView(String *string);

    public:

        StringView(const StringView &) = default;
        StringView(StringView &&) = default;
        ~StringView() = default;

        StringView &operator= (const StringView &) = default;
        StringView &operator= (StringView &&) = default;

        const String &str() const;
        const char *c_str() const;

    };

    class StringCache
    {
    private:

        using Set = std::unordered_set<String>;

        Set set;

    public:

        StringCache() = default;
        StringCache(const StringCache &) = delete;
        StringCache(StringCache &&) = default;
        ~StringCache() = default;

        StringCache &operator= (const StringCache &) = delete;
        StringCache &operator= (StringCache &&) = default;

        bool find(const String &string);
        bool find(String &&string);

        StringView intern(const String &string);
        StringView intern(String &&string);

    };
}

#endif //!MAKEGEN_STRINGCACHE_H
#include "StringCache.h"

namespace makegen
{
    // /* static */ const StringView StringView::EMPTY(nullptr);

    StringView::StringView(String *string) : string(string)
    {
    }

    const String &StringView::str() const
    {
        return const_cast<String&>(*string);
    }
    const char *StringView::c_str() const
    {
        return string->c_str();
    }

    bool StringView::operator== (const StringView &other)
    {
        return string == other.string;
    }

    bool StringView::operator== (StringView &&other)
    {
        return *this == std::ref(other);
    }

    bool StringView::operator!= (const StringView &other)
    {
        return !(*this == other);
    }

    bool StringView::operator!= (StringView &&other)
    {
        return *this != std::ref(other);
    }

    bool StringCache::find(const String &string)
    {
        return set.find(string) != set.end();
    }

    bool StringCache::find(String &&string)
    {
        return set.find(string) != set.end();
    }

    StringView StringCache::intern(const String &string)
    {
        auto iter = set.find(string);

        // We have it internalized if found
        if (iter != set.end())
        {
            const String &str = *iter;
            return StringView(&const_cast<String&>(str));
        }

        else
        {
            iter = set.insert(iter, string);

            const String &str = *iter;
            return StringView(&const_cast<String&>(str));
        }
    }

    StringView StringCache::intern(String &&string)
    {
        auto iter = set.find(string);

        // We have it internalized if found
        if (iter != set.end())
        {
            const String &str = *iter;
            return StringView(&const_cast<String&>(str));
        }

        else
        {
            iter = set.emplace_hint(iter, std::move(string));

            const String &str = *iter;
            return StringView(&const_cast<String&>(str));
        }
    }

}

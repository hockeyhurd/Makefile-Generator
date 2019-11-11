#pragma once

#ifndef MAKEGEN_FILE_H
#define MAKEGEN_FILE_H

#include "MakeGen.h"

#include <fstream>

namespace makegen
{

    class File
    {
    private:

        String path;
        std::ofstream stream;

    public:

        explicit File(const String &path);
        explicit File(String &&path);
        virtual ~File() = default;

        File(const File &) = delete;
        File(File &&) = default;

        File &operator= (const File &) = delete;
        File &operator= (File &&) = default;

        const String &getPath() const;

        File &flush();
        File &endl();
        File &tab();

        template<class T>
        File &operator<< (const T &data);

        template<class T>
        File &operator<< (T &&data);

    };

    template<class T>
    File &File::operator<< (const T &data)
    {
        stream << data;
        return *this;
    }

    template<class T>
    File &File::operator<< (T &&data)
    {
        stream << std::forward<T>(data);
        return *this;
    }

}

#endif //!MAKEGEN_FILE_H
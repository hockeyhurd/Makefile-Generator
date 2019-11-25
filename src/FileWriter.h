#pragma once

#ifndef MAKEGEN_FileWriter_H
#define MAKEGEN_FileWriter_H

#include "MakeGen.h"

#include <fstream>

namespace makegen
{

    class FileWriter
    {
    private:

        String path;
        std::ofstream stream;

    public:

        explicit FileWriter(const String &path);
        explicit FileWriter(String &&path);
        virtual ~FileWriter() = default;

        FileWriter(const FileWriter &) = delete;
        FileWriter(FileWriter &&) = default;

        FileWriter &operator= (const FileWriter &) = delete;
        FileWriter &operator= (FileWriter &&) = default;

        const String &getPath() const;

        FileWriter &flush();
        FileWriter &endl();
        FileWriter &tab();
        FileWriter &tabSpaced(const u32 numSpaces);

        template<class T>
        FileWriter &operator<< (const T &data);

        template<class T>
        FileWriter &operator<< (T &&data);

    };

    template<class T>
    FileWriter &FileWriter::operator<< (const T &data)
    {
        stream << data;
        return *this;
    }

    template<class T>
    FileWriter &FileWriter::operator<< (T &&data)
    {
        stream << std::forward<T>(data);
        return *this;
    }

}

#endif //!MAKEGEN_FileWriter_H
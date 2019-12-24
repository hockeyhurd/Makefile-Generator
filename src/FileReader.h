#pragma once

#ifndef MAKEGEN_FILE_READER_H
#define MAKEGEN_FILE_READER_H

#include "MakeGen.h"

#include <fstream>

namespace makegen
{

    class FileReader
    {
    private:

        String path;
        std::ifstream stream;

    public:

        explicit FileReader(const String &path);
        explicit FileReader(String &&path);
        FileReader(const FileReader &) = delete;
        FileReader(FileReader &&) = default;

        virtual ~FileReader() = default;

        FileReader &operator= (const FileReader &) = delete;
        FileReader &operator= (FileReader &&) = default;

        template<class T>
        FileReader &operator>> (T &data);

        String readAll();
    };

    template<class T>
    FileReader &FileReader::operator>> (T &data)
    {
        stream >> data;
        return *this;
    }

}

#endif //!MAKEGEN_FILE_READER_H
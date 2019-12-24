#include "FileReader.h"

#include <vector>

namespace makegen
{

    FileReader::FileReader(const String &path) : path(path), stream(path)
    {
    }

    FileReader::FileReader(String &&path) : path(std::move(path)), stream(this->path)
    {
    }

    String FileReader::readAll()
    {
        std::vector<char> buffer;
        buffer.reserve(0x1000);

        char c;

        while (stream >> c)
        {
            buffer.push_back(c);
        }

        return String(buffer.begin(), buffer.end());
    }

}
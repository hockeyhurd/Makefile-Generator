#include "FileWriter.h"

namespace makegen
{

    FileWriter::FileWriter(const String &path) : path(path), stream(path)
    {
    }

    FileWriter::FileWriter(String &&path) : path(std::move(path)), stream(this->path)
    {
    }

    const String &FileWriter::getPath() const
    {
        return const_cast<String&>(path);
    }

    FileWriter &FileWriter::flush()
    {
        stream.flush();
        return *this;
    }

    FileWriter &FileWriter::endl()
    {
        stream << std::endl;
        return *this;
    }

    FileWriter &FileWriter::tab()
    {
        stream << '\t';
        return *this;
    }

    FileWriter &FileWriter::tabSpaced(const u32 numSpaces)
    {
        for (u32 i = 0; i < numSpaces; i++)
        {
            stream << ' ';
        }

        return *this;
    }

}
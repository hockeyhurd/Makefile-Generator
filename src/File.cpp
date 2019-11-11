#include "File.h"

namespace makegen
{

    File::File(const String &path) : path(path), stream(path)
    {
    }

    File::File(String &&path) : path(std::move(path)), stream(this->path)
    {
    }

    const String &File::getPath() const
    {
        return const_cast<String&>(path);
    }

    File &File::flush()
    {
        stream.flush();
        return *this;
    }

    File &File::endl()
    {
        stream << std::endl;
        return *this;
    }

    File &File::tab()
    {
        stream << '\t';
        return *this;
    }

}
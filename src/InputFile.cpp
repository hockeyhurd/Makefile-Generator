#include "InputFile.h"
#include "FileReader.h"
#include "Parser.h"

#include <functional>

namespace makegen
{

    InputFile::InputFile() : data("")
    {
    }

    const String &InputFile::getData() const
    {
        return const_cast<String &>(data);
    }

    bool InputFile::read(const String &path)
    {
        FileReader reader(path);
        data = reader.readAll();

        return !data.empty();
    }

    bool InputFile::read(String &&path)
    {
        return read(std::ref(path));
    }

    bool InputFile::parse(Configuration &config)
    {
        return !data.empty() && config.parse(data);
    }

}
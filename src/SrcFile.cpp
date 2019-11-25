#include "SrcFile.h"
#include "FileWriter.h"

#include <iostream>

namespace makegen
{

    extern StringCache &getStringCache();

    SrcFile::SrcFile(StringView file) : file(std::move(file))
    {
    }

    StringView SrcFile::getFile() const
    {
        return file;
    }

    StringView SrcFile::getName(bool &result)
    {
        const auto pos = file.str().find_last_of('.');

        if (pos == String::npos)
        {
            result = false;
            return file;
        }

        result = true;
        String name = file.str().substr(0, pos);

        return getStringCache().intern(std::move(name));
    }

    void SrcFile::encode(FileWriter &file)
    {
        file << this->file.str();
    }

    void SrcFile::encode(FileWriter &file, StringView extension)
    {
        bool result = false;
        auto name = getName(result);

        if (result)
        {
            std::cout << "ERROR: Getting file name for \"" << this->file.str() << "\".\n";
            exitProgram(-1);
        }
    }

}
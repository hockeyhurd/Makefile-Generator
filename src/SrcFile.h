#pragma once

#ifndef MAKEGEN_SRCFILE_H
#define MAKEGEN_SRCFILE_H

#include "MakeGen.h"
#include "StringCache.h"

namespace makegen
{

    class FileWriter;

    class SrcFile
    {
    private:

        StringView file;

    public:

        explicit SrcFile(StringView file);
        ~SrcFile() = default;

        StringView getFile() const;
        StringView getName(bool &result);
        // StringView getExtension();

        void encode(FileWriter &file);
        void encode(FileWriter &file, StringView extension);
    };

}

#endif //!MAKEGEN_SRCFILE_H
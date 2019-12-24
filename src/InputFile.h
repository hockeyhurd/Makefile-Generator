#pragma once

#ifndef MAKEGEN_INPUT_FILE_H
#define MAKEGEN_INPUT_FILE_H

// #include "FileReader.h"
#include "MakeGen.h"

namespace makegen
{

    class Configuration;

    class InputFile
    {
    private:

        String data;
    
    public:

        // explicit InputFile(const String &path);
        // explicit InputFile(String &&path);
        InputFile();
        InputFile(const InputFile &) = default;
        InputFile(InputFile &&) = default;

        ~InputFile() = default;

        InputFile &operator= (const InputFile &) = default;
        InputFile &operator= (InputFile &&) = default;

        const String &getData() const;

        bool read(const String &path);
        bool read(String &&path);

        bool parse(Configuration &config);
    };

}

#endif //!MAKEGEN_INPUT_FILE_H
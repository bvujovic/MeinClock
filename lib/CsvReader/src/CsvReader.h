#pragma once

#include <LittleFS.h>

class CsvReader
{
private:
    static const char sepParts = '|';

    /// @brief Number of parts in each line
    byte cntParts;
    File fp;

public:
    /// @brief Reads one CSV line and returns String array (parts).
    String *readLine();

    /// @brief Initializes reader object with file path and expected number of parts in each line.
    CsvReader(const char *path, byte cntParts);

    bool fileOpenSuccess() { return fp; }
};

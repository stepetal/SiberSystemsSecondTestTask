#ifndef TEXTFILEREADER_H
#define TEXTFILEREADER_H

#include "filereader.h"

class TextFileReader : public FileReader
{
    const std::string file_name;
public:
    TextFileReader(const std::string& f_name);

    // FileReader interface
    void read() override;
};

#endif // TEXTFILEREADER_H

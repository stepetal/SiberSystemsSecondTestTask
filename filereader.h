#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>

/*
 *
 * Abstract class for reading from files
 *
 */
class FileReader
{
public:
    FileReader();
    virtual void read() = 0;
};

#endif // FILEREADER_H

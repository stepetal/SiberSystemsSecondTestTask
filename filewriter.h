#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <string>

/*
 *
 * Abstract class for writing to files
 *
 */
class FileWriter
{
public:
    FileWriter();
    virtual void write() = 0;
};

#endif // FILEWRITER_H

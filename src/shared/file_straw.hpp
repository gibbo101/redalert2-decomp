// FileStraw: a Straw that draws data from a file.
//
// Name from RTTI (vtable 0x0079D9AC, base Straw); methods in XStraw.cpp
// (0x00773900+). The file is opened on first read if needed and closed again
// on destruction only when this straw opened it.
#ifndef RA2_SHARED_FILE_STRAW_HPP
#define RA2_SHARED_FILE_STRAW_HPP

#include "shared/straw.hpp"
#include "shared/raw_file_class.hpp"

class FileStraw : public Straw {
public:
    FileStraw(FileClass *file) : File(file), HasOpened(false) {}
    FileStraw(FileClass &file) : File(&file), HasOpened(false) {}
    virtual ~FileStraw();
    virtual int Get(void *buffer, int length);

    bool Valid_File() const { return File != 0; }

    FileClass *File;        // +0x0C data source
    bool HasOpened;         // +0x10 this straw opened File and must close it
};

#endif

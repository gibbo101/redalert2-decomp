// FilePipe: a Pipe that writes data to a file.
//
// Name from RTTI (vtable 0x0079D9BC, base Pipe); methods in XPipe.cpp
// (0x00773790+). The file is opened for writing on first output if needed
// and closed at End() or destruction only when this pipe opened it.
#ifndef RA2_SHARED_FILE_PIPE_HPP
#define RA2_SHARED_FILE_PIPE_HPP

#include "shared/pipe.hpp"
#include "shared/raw_file_class.hpp"

class FilePipe : public Pipe {
public:
    FilePipe(FileClass *file) : File(file), HasOpened(false) {}
    FilePipe(FileClass &file) : File(&file), HasOpened(false) {}
    virtual ~FilePipe();
    virtual int End();
    virtual int Put(void const *source, int length);

    bool Valid_File() const { return File != 0; }

    FileClass *File;        // +0x0C data destination
    bool HasOpened;         // +0x10 this pipe opened File and must close it
};

#endif

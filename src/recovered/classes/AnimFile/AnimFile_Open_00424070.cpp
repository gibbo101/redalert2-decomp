// bool AnimFile::Open(FileClass *file) (0x00424070)
// Remembers the file, opens it for reading when it is not open (and then
// closes it again itself) and reads the header.
#include "shared/anim_file.hpp"

bool AnimFile::Open(FileClass *file)
{
    File = file;
    if (file != 0) {
        if (!file->Is_Open()) {
            File->Open(FILE_RIGHTS_READ);
            OpenedFile = true;
        }
        return Initialize();
    }
    return false;
}

// CDFileClass::Set_Name (0x00470150, virtual slot 2)
// Uses the name as given when the file exists (or searching is off);
// otherwise tries each search directory in order and keeps the first
// directory + name that exists. Falls back to the plain name.
#include "shared/cd_file_class.hpp"
#include "shared/crt_string.hpp"

char const *CDFileClass::Set_Name(char const *filename)
{
    BufferIOFileClass::Set_Name(filename);
    if (IsDisabled || First == 0 || BufferIOFileClass::Is_Available()) {
        return File_Name();
    }
    for (CDSearchDrive *drive = First; drive != 0; drive = drive->Next) {
        char path[260];
        strcpy(path, drive->Path);
        strcat(path, filename);
        BufferIOFileClass::Set_Name(path);
        if (BufferIOFileClass::Is_Available()) {
            return File_Name();
        }
    }
    BufferIOFileClass::Set_Name(filename);
    return File_Name();
}

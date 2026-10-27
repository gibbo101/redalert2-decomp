// RawFileClass::Set_Name (0x00638B70, virtual slot 2)
// Replaces the file name with a private copy, freeing a previously owned one.
// Naming a file also clears any bias window. Returns the new name, or null if
// no name was given or the copy could not be allocated (reported as ENOMEM).
#include "shared/raw_file_class.hpp"

char const *RawFileClass::Set_Name(char const *filename)
{
    if (Filename != 0 && Allocated) {
        free((void *)Filename);
        Filename = 0;
        Allocated = false;
    }
    if (filename == 0) {
        return 0;
    }
    BiasStart = 0;
    BiasLength = -1;
    Filename = _strdup(filename);
    if (Filename == 0) {
        Error(FILE_ERROR_NO_MEMORY, false, filename);
        return 0;
    }
    Allocated = true;
    return Filename;
}

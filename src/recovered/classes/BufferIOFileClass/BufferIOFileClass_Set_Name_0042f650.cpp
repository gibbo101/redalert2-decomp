// BufferIOFileClass::Set_Name (0x0042F650, virtual slot 2)
// Renaming a buffered file to its current name keeps the cache; any other
// name commits pending changes and invalidates the cached data.
#include "shared/buffer_io_file_class.hpp"
#include "shared/crt_string.hpp"

char const *BufferIOFileClass::Set_Name(char const *filename)
{
    if (File_Name() && UseBuffer) {
        if (strcmp(filename, File_Name()) == 0) {
            return File_Name();
        }
        Commit();
        IsCached = false;
    }
    RawFileClass::Set_Name(filename);
    return File_Name();
}

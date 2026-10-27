#include "shared/raw_file_class.hpp"
#include "shared/crt_memory.hpp"
void *__fastcall Load_Alloc_Data(FileClass &file)
{
    void *buffer = 0;
    if (file.Is_Available()) {
        long size = file.Size();
        buffer = new char[size];
        if (buffer) file.Read(buffer, size);
    }
    return buffer;
}

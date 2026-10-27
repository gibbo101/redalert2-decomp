// void *__fastcall unknown_load_alloc_data(FileClass &file) -- 0x00495550
// Purpose: reads a whole available file into a new buffer (operator new of
// its Size()); null when the file is not available. Westwood's
// Load_Alloc_Data(FileClass &) has this shape (hypothesis; here __fastcall).
// No direct callers.
#include "shared/raw_file_class.hpp"
// @ref ??2@YAPAXI@Z=00782017

void *__fastcall unknown_load_alloc_data_00495550(FileClass &file)
{
    if (file.Is_Available()) {
        long size = file.Size();
        void *buffer = operator new(size);
        file.Read(buffer, size);
        return buffer;
    }
    return 0;
}

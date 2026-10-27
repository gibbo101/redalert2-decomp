// FileStraw::~FileStraw (0x00773900)
// Closes the file if this straw opened it.
#include "shared/file_straw.hpp"
// The scalar deleting destructor the linker kept was compiled in another
// object file, where this destructor is called rather than inlined;
// auto_inline(off) reproduces that copy here.
#pragma auto_inline(off)
FileStraw::~FileStraw()
{
    if (Valid_File() && HasOpened) {
        File->Close();
        HasOpened = false;
        File = 0;
    }
}
#pragma auto_inline(on)

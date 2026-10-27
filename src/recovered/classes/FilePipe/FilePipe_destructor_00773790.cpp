// FilePipe::~FilePipe (0x00773790)
// Closes the file if this pipe opened it.
#include "shared/file_pipe.hpp"
// The scalar deleting destructor the linker kept was compiled in another
// object file, where this destructor is called rather than inlined;
// auto_inline(off) reproduces that copy here.
#pragma auto_inline(off)
FilePipe::~FilePipe()
{
    if (Valid_File() && HasOpened) {
        HasOpened = false;
        File->Close();
        File = 0;
    }
}
#pragma auto_inline(on)

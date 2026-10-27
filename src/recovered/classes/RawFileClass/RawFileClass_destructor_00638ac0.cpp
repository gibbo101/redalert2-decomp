// RawFileClass::~RawFileClass (0x00638AC0)
// Closes the file and frees an owned name.
#include "shared/raw_file_class.hpp"

RawFileClass::~RawFileClass()
{
    Close();
    if (Allocated && Filename) {
        free((void *)Filename);
        Filename = 0;
        Allocated = false;
    }
}

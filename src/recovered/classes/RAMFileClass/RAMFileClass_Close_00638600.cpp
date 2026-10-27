// void RAMFileClass::Close() (0x00638600, slot 13)
#include "shared/ram_file_class.hpp"

void RAMFileClass::Close()
{
    IsOpen = false;
}

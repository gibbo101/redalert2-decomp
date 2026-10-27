// CDFileClass::Open(int) (0x0046FE10, virtual slot 7)
// The name was already resolved by Set_Name; open it like any buffered file.
#include "shared/cd_file_class.hpp"

int CDFileClass::Open(int rights)
{
    return BufferIOFileClass::Open(rights);
}

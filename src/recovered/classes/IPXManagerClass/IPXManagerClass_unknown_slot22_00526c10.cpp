// unsigned long IPXManagerClass::unknown_slot22(int index) (0x00526C10, slot 22)
#include "shared/ipx_manager.hpp"
// @ref ?Avg_Delay@CommBufferClass@@QAEKXZ=00480a60

unsigned long IPXManagerClass::unknown_slot22(int index)
{
    return Connection[index]->Queue->Avg_Delay();
}

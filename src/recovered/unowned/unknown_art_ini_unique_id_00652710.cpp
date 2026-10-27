// int unknown_art_ini_unique_id() -- 0x00652710
// Purpose: the CRC identifier of the art INI (0x008397F0) (CCINIClass::Get_Unique_ID,
// 0x0046C1C0), a tail call. Callers 0x005960D9, 0x00598EE2, 0x005BD089 and
// others compare it (multiplayer synchronisation; hypothesis).
// Assumptions: the function's name is a placeholder.
// @ref ?Get_Unique_ID@CCINIClass@@QBEHXZ=0046c1c0
// @ref ?ArtINI@@3VCCINIClass@@A=008397f0
#include "shared/ccini_class.hpp"

int unknown_art_ini_unique_id()
{
    return ArtINI.Get_Unique_ID();
}

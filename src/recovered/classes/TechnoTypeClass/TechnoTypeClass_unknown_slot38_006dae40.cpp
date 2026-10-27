// int TechnoTypeClass::unknown_slot38() const (0x006DAE40)
// Cameo data (hypothesis: RA1 Get_Cameo_Data): the alternate cameo for
// kinds 0x10 and 0x28 when the player's house flags allow it.
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4

int TechnoTypeClass::unknown_slot38() const
{
    if (unknown_player_a35db4 && unknown_player_a35db4->unknown_206 && Kind_Of() == 0x10 && AltCameoData && Trainable) {
        return (int)AltCameoData;
    }
    if (unknown_player_a35db4 && unknown_player_a35db4->unknown_207 && Kind_Of() == 0x28 && AltCameoData && Trainable) {
        return (int)AltCameoData;
    }
    return (int)CameoData;
}

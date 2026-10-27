// int __fastcall unknown_owner_color(UnknownTechno_00610770 *techno) -- 0x00610770
// Purpose: the owner house's +0x30 value, replaced by the player house's
// (0x00A35DB4) when the owner's 0x004F52B0 test is true.
// Assumptions: techno +0x1B4 is the owning HouseClass (as in TechnoClass);
// what +0x30 holds (a color scheme?) and the meaning of the test are
// unknown; views only.
// @ref ?Unknown_004F52B0@UnknownHouse_00610770@@QAE_NXZ=004f52b0
// @ref ?unknown_player_a35db4@@3PAUUnknownHouse_00610770@@A=00a35db4

struct UnknownHouse_00610770 {
    char unknown_00[0x30];
    int unknown_30;                         // +0x30
    bool Unknown_004F52B0();                // 0x004F52B0
};
struct UnknownTechno_00610770 {
    char unknown_000[0x1B4];
    UnknownHouse_00610770 *House;           // +0x1B4
};
extern UnknownHouse_00610770 *unknown_player_a35db4;

int __fastcall unknown_owner_color(UnknownTechno_00610770 *techno)
{
    UnknownHouse_00610770 *house = techno->House;
    int value = house->unknown_30;
    if (house->Unknown_004F52B0() && unknown_player_a35db4 != 0) {
        return unknown_player_a35db4->unknown_30;
    }
    return value;
}

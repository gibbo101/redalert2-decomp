// HouseClass as the screen and INI units see it (padded view: no AbstractClass base,
// since those units must not include shared/abstract.hpp). Same include guard
// as shared/house.hpp, the full class, so one TU only ever sees one of them.
// The player's house is the pointer at 0x00A35DB4.
#ifndef RA2_SHARED_HOUSE_HPP
#define RA2_SHARED_HOUSE_HPP

#include "shared/unknown_globals.hpp"
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"

class TechnoTypeClass;
class TechnoClass;
class SuperClass;
class HouseTypeClass;
struct UnknownBuilding;                 // shared/power.hpp (BuildingClass stand-in)

// The layout is padded from +0x000 (no AbstractClass base declared here, so
// the screen units can use it without shared/abstract.hpp).
class HouseClass {
public:
    void unknown_4ea7f0(TechnoClass *object); // proposedmirrorofsamefullHousecallback
    bool Is_Ally(HouseClass const *house) const;           // 0x004E5540 (as shared/house.hpp)
    bool Is_Ally(TechnoClass const *techno) const;         // 0x004E5580 (its owning house; as shared/house.hpp)
    // Index in Houses of the house with this name, or -1 (0x004F5B40).
    static int __fastcall Find_Index(char const *name);
    float Cost_Multiplier(TechnoTypeClass const *type);    // 0x004F5960
    bool Unknown_004F52B0();                               // 0x004F52B0 (TechnoClass slots 24, 38, 39, 80)
    bool Unknown_004F52F0();                               // 0x004F52F0
    int Unknown_004F30D0();                                // 0x004F30D0 a free waypoint path, or -1
    // A waypoint in the cell, else 0 (0x004ED200; shared/house.hpp).
    class WaypointClass *unknown_func_4ed200(Cell const &cell);

    char unknown_000[0x30];
    int ArrayIndex;                     // +0x030 index in Houses (bit in house masks; TechnoClass::Owner)
    HouseTypeClass *Type;               // +0x034 (strip sort order: Type->Side)
    char unknown_038[0x68 - 0x38];
    DynamicVectorClass<UnknownBuilding *> Buildings;    // +0x068 (PowerClass help text; Vector +0x6C, ActiveCount +0x78)
    char unknown_080[0x130 - 0x80];
    int unknown_130;                    // +0x130 (TechnoClass constructor)
    char unknown_134[0x13D - 0x134];
    bool unknown_13d;                   // +0x13D (radar: forces mode 1 in multiplayer)
    char unknown_13e[0x154 - 0x13E];
    int unknown_154;                    // +0x154 the current waypoint path (-1)
    char unknown_158[0x188 - 0x158];
    bool unknown_188;                   // +0x188 (cleared by MapClass 0x00559F10 / 0x00559FD0)
    char unknown_189[0x19C - 0x189];
    DynamicVectorClass<SuperClass *> Supers;    // +0x19C (Vector +0x1A0, ActiveCount +0x1AC)
    char unknown_1b4[0x206 - 0x1B4];
    bool unknown_206;                   // +0x206 (Get_Cameo_Data: infantry alt cameo)
    bool unknown_207;                   // +0x207 (Get_Cameo_Data: unit alt cameo)
    char unknown_208[0x230 - 0x208];
    int unknown_230;                    // +0x230 (SidebarClass::AI: the sidebar's +0x4EE5 state follows it being positive)
    char unknown_234[0x52D0 - 0x234];
    int PowerOutput;                    // +0x52D0 (power bar help text; hypothesis)
    int PowerDrain;                     // +0x52D4
    char unknown_52d8[0x5310 - 0x52D8];
    int unknown_5310[20];               // +0x5310 per house index: units, infantry, aircraft killed (as shared/house.hpp)
    int unknown_5360;                   // +0x5360
    int unknown_5364[20];               // +0x5364 per house index: buildings killed
    char unknown_53b4[0x56D0 - 0x53B4];
    int unknown_56d0[0x4204];           // +0x56D0 a value per 4 x 4 cell block (MapClass 0x0054E3A0)
    char IniName[0x15];                 // +0x15EE0 the [Houses] entry value
    char unknown_15ef5[0x15F16 - 0x15EF5];
    wchar_t UIName[21];                 // +0x15F16 the type's UIName (radar player list)
    int ColorSchemeIndex;               // +0x15F40 (as shared/house.hpp)
};

extern DynamicVectorClass<HouseClass *> Houses;             // 0x00A32298

// The player's house (0x00A35DB4).

#endif

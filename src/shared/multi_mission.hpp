// The session's multiplayer maps (a DynamicVectorClass at 0x00A3D8D8, session +0x640;
// TS/YR's SessionClass MultiMission list, name hypothesis). Only the members used by
// recovered sources are declared.
#ifndef RA2_SHARED_MULTI_MISSION_HPP
#define RA2_SHARED_MULTI_MISSION_HPP

#include "shared/vector_class.hpp"
#include "shared/type_list.hpp"

#include "shared/wstring.hpp"

// A CD the map needs (RTTI: TypeList<DiskID>, an enum; -1 any disk, -2 the map file
// itself is present).
class INIClass;

enum DiskID {
    DISK_ANY_UNKNOWN = -1
};

class MultiMission {
public:
    // The map entry of an INI section (0x00671670; called by Read_Scenario_Descriptions 0x00670C50).
    MultiMission(INIClass &ini, char const *section);
    // The map entry the session's INI reader builds (0x00671C50): file name, description
    // (null: MSG:NoDescription), digest, official flag, comma-separated game modes (null: none).
    MultiMission(char const *filename, unsigned short const *description, char const *digest, bool official,
                 char const *modes, int unknown_180, int players);
    // Whether the map is on the disk (-2: its file is present; else the disk is
    // in its disk list or the list holds -1) (0x00671F00; hypothesis).
    bool Unknown_00671F00(int cd);
    // The first disk of its list (0x00671F90).
    int Unknown_00671F90();
    // Whether the text at +0x58 is a fixed string (0x006720C0).
    bool Unknown_006720C0();
#ifdef MULTI_MISSION_ACCESSORS
    // TibSun's inline accessors (session.h MultiMission), only where shared/modem_host.hpp asks for them (the
    // WOnline.cpp unit's register ties move when MultiMission gains members). Get_Official gives
    // Send_Options 0x0059BC90 its vector-before-index load.
    char const *Get_Filename() const { return unknown_58; }
    char const *Get_Digest() const { return unknown_15c; }
    bool Get_Official() { return unknown_17c; }
#endif
    // Copies a description (at most 43 characters; null: MSG:NoDescription) into Description (0x00671FA0;
    // accepted as UnknownDescribed_00671FA0::unknown_set_description, bound by @ref; Make_Random_Map 0x005C84E0).
    void Set_Description_00671FA0(unsigned short const *text);
    // Copies the file name (null: "No File Name") into +0x58 (0x00671FF0; Red Alert's Set_Filename).
    void Set_Filename(char const *filename);
    // Copies the digest (null: "No Digest") into +0x15C (0x00672050; Red Alert's Set_Digest).
    void Set_Digest(char const *digest);
    // Sets the official flag (+0x17C) (0x006720B0; Red Alert's Set_Official; no direct caller).
    void Set_Official(bool official);
    // Whether the map allows the game mode named (0x006720E0).
    bool Unknown_006720E0(Wstring &mode);

    unsigned short Description[0x2C];      // +0x00 the map's description (ModemGuest 0x00597E50 shows it)
    char unknown_58[0x15C - 0x58];          // +0x58 the map's file name (the cooperative campaign records list it)
    char unknown_15c[0x17C - 0x15C];        // +0x15C the map's digest (ModemHost 0x0059BC90 sends it)
    bool unknown_17c;                       // +0x17C official map (sent as the options IsOfficial bit; a game mode test is skipped when false and 0x0073C370 agrees)
    char unknown_17d[0x180 - 0x17D];
    int unknown_180;                        // +0x180 (constructor argument 6)
    int unknown_184;                        // +0x184 the map's player count (MPCooperative slot 37: the computers are two fewer)
    TypeList<DiskID> DiskIDs;               // +0x188 the disks the map is on (TypeList: 0x1C bytes)
    DynamicVectorClass<Wstring> GameModes;  // +0x1A4 the game modes the map allows (vtable 0x007A9664)
};

// Whether a disk list holds the disk (inline; expanded twice in 0x00671F00).
inline bool Is_On_Disk(TypeList<DiskID> const &list, DiskID disk)
{
    for (int index = 0; index < list.Count(); index++) {
        if (list[index] == disk) {
            return true;
        }
    }
    return false;
}

// MultiMission's constructors build DiskIDs and GameModes through inline expansions of the list constructors over the
// out-of-line VectorClass constructors (0x00674AA0, 0x00674AF0): the VectorClass constructors are declared here and
// defined in their own rows, so no unit expands them.
template <>
VectorClass<DiskID>::VectorClass(unsigned size, DiskID const *array);
template <>
VectorClass<Wstring>::VectorClass(unsigned size, Wstring const *array);
template <>
inline DynamicVectorClass<DiskID>::DynamicVectorClass(unsigned size, DiskID const *array)
    : VectorClass<DiskID>(size, array)
{
    GrowthStep = 10;
    ActiveCount = 0;
}
template <>
inline DynamicVectorClass<Wstring>::DynamicVectorClass(unsigned size, Wstring const *array)
    : VectorClass<Wstring>(size, array)
{
    GrowthStep = 10;
    ActiveCount = 0;
}
template <>
inline TypeList<DiskID>::TypeList()
{
}

extern DynamicVectorClass<MultiMission *> unknown_multi_missions_a3d8d8;

#endif

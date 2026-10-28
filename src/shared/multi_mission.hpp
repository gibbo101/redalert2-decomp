// The session's multiplayer maps (a DynamicVectorClass at 0x00A3D8D8, session +0x640;
// TS/YR's SessionClass MultiMission list, name hypothesis). Only the members used by
// recovered sources are declared.
#ifndef RA2_SHARED_MULTI_MISSION_HPP
#define RA2_SHARED_MULTI_MISSION_HPP

#include "shared/vector_class.hpp"

class Wstring;

class MultiMission {
public:
    // Whether the map is on the disk (-2: its file is present; else the disk is
    // in its disk list or the list holds -1) (0x00671F00; hypothesis).
    bool Unknown_00671F00(int cd);
    // The first disk of its list (0x00671F90).
    int Unknown_00671F90();
    // Whether the text at +0x58 is a fixed string (0x006720C0).
    bool Unknown_006720C0();
    // Whether the map allows the game mode named (0x006720E0).
    bool Unknown_006720E0(Wstring &mode);

    char unknown_00[0x58];
    char unknown_58[0x17C - 0x58];          // +0x58 the map's file name (the cooperative campaign records list it)
    bool unknown_17c;                       // +0x17C (a game mode test is skipped when false and 0x0073C370 agrees)
};

extern DynamicVectorClass<MultiMission *> unknown_multi_missions_a3d8d8;

#endif

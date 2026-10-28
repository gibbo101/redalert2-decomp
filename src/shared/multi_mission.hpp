// The session's multiplayer maps (a DynamicVectorClass at 0x00A3D8D8, session +0x640;
// TS/YR's SessionClass MultiMission list, name hypothesis). Only the members used by
// recovered sources are declared.
#ifndef RA2_SHARED_MULTI_MISSION_HPP
#define RA2_SHARED_MULTI_MISSION_HPP

#include "shared/vector_class.hpp"

class MultiMission {
public:
    // Whether the map is on the disk (-2: its file is present; else the disk is
    // in its disk list or the list holds -1) (0x00671F00; hypothesis).
    bool Unknown_00671F00(int cd);
    // The first disk of its list (0x00671F90).
    int Unknown_00671F90();
};

extern DynamicVectorClass<MultiMission *> unknown_multi_missions_a3d8d8;

#endif

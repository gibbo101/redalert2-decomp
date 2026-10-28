// Radar events (RadarEvent.cpp around 0x0063B5B0).
#ifndef RA2_SHARED_RADAR_EVENT_HPP
#define RA2_SHARED_RADAR_EVENT_HPP

#include "shared/coord.hpp"

// Raises an event of a kind at a cell (hypothesis: RadarEventClass::Create;
// FootClass slot 216 uses kind 7, HouseClass::Attacked 3 for the player's base
// and 16 for an ally's).
bool __fastcall Unknown_0063B5B0(int kind, Cell cell);              // 0x0063B5B0

#endif

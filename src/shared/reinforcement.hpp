// Reinforcements (reinf.cpp, 0x00639770-0x0063AE9F; TS reinf.cpp order). Do_Reinforcements and the
// chrono variant 0x0063A880 are declared in shared/unknown_globals.hpp.
#ifndef RA2_SHARED_REINFORCEMENT_HPP
#define RA2_SHARED_REINFORCEMENT_HPP

#include "shared/coord.hpp"

class TeamTypeClass;
class FootClass;
class HouseClass;
class AbstractClass;

// Places a created group at a cell (or its waypoint when atwaypoint) and starts it.
bool __fastcall Create_Reinforcement(TeamTypeClass *teamtype, FootClass *object, Cell const &xcell, bool atwaypoint);   // 0x0063A050
// number aircraft of AircraftTypes[air] from the house's edge; returns how many arrived.
int __fastcall Create_Air_Reinforcement(HouseClass *house, int air, int number, int mission, AbstractClass *tarcom, AbstractClass *navcom, int passenger, int passenger_count);   // 0x0063A690

#endif

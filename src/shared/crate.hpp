// CrateClass: a crate the game keeps on the map (Westwood's crate.cpp; the unit at 0x00493740-0x00493DEF).
// Layout from its members: a countdown Timer (+0x00) and the crate's cell (+0x0C), invalid while it
// equals the all-zero cell (shared/unknown_geometry.hpp unknown_geometry_k).
#ifndef RA2_SHARED_CRATE_HPP
#define RA2_SHARED_CRATE_HPP

#include "shared/coord.hpp"
#include "shared/cd_timer.hpp"
#include "shared/unknown_geometry.hpp"

class CrateClass {
public:
    bool Create_Crate(Cell const &cell);    // 0x004939A0
    bool Remove_It();                       // 0x00493930
    bool Is_Valid() const { return Location != unknown_geometry_k; }

private:
    // Places a crate at cell (or fails); cell is passed in ECX (0x00493AD0).
    static bool __fastcall Put_Crate(Cell &cell);
    void Make_Invalid()
    {
        Location = unknown_geometry_k;
        Timer.Stop();
    }

    CDTimerClass<FrameTimerClass> Timer;    // +0x00
    Cell Location;                          // +0x0C
};

#endif

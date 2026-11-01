// bool CrateClass::Create_Crate(Cell const &cell) -- 0x004939A0
// Replaces the tracked crate with one placed at (or near) cell and starts its regeneration timer:
// a random time between 0.5 and 2 times Rules CrateRegen minutes.

#include "shared/crate.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/rules.hpp"
#include "shared/tactical.hpp"
#include "shared/id_source.hpp"

inline double Random_Double(double a, double b)
{
    int num = Random_Pick(0, 0x7FFFFFFE);
    return (b - a) * (num * (1.0 / 2147483646.0)) + a;
}

bool CrateClass::Create_Crate(Cell const &cell)
{
    Remove_It();
    Cell loc = cell;
    if (Put_Crate(loc)) {
        unknown_tactical_83996c->Unknown_006AADD0(&Map[cell]);
        Location = loc;
        Timer = int(Random_Double(Rules->CrateRegen * 450.0, Rules->CrateRegen * 1800.0));
        Timer.Start();
        return true;
    }
    return false;
}

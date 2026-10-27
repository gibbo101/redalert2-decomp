// One harvesting step. Operation names beyond shared types remain hypotheses.
#include "shared/unit.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/rules.hpp"
// @ref __ftol=0077f110
// @ref __real@4@3fff8000000000000000=0079b7f8
// @ref ?Get_Tiberium_Type@CellClass@@QBEHXZ=0047a220
// @ref ?unknown_475db0@CellClass@@QAEHH@Z=00475db0
// @ref ?unknown_47c040@CellClass@@QAEHXZ=0047c040
// @ref ?unknown_69ae50@UnknownQuad@@QAEMMH@Z=0069ae50
bool UnitClass::unknown_7013a0()
{
    CoordStruct position = Coord;
    CellClass *cell = &Map[position];
    if (unknown_494) {
        return true;
    }
    if (Type->Harvester && unknown_slot165() < 1.0 && cell->unknown_ec == 5) {
        if (Type->Weeder) {
            cell->unknown_47c040();
            unknown_294.unknown_69ae50(1.0f, 0);
            AnimationStage.Value = 0;
            AnimationStage.Set_Rate(Rules->unknown_1180 * 3);
            goto harvested;
        }
        int resource = cell->Get_Tiberium_Type();
        float capacity = (float)Type->Storage;
        int available = (int)(capacity - unknown_294.unknown_69ae10() > 1.0f
            ? 1.0f : (float)Type->Storage - unknown_294.unknown_69ae10());
        int taken = cell->unknown_475db0(available);
        if (taken > 0) {
            unknown_294.unknown_69ae50((float)taken, resource);
            AnimationStage.Value = 0;
            AnimationStage.Set_Rate(Rules->unknown_1180);
            goto harvested;
        }
        return false;
    }
    AnimationStage.Value = 0;
    AnimationStage.Set_Rate(0);
    return false;
harvested:
    return true;
}

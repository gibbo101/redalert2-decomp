// bool ParasiteClass::Can_Exit_00607BA0() (0x00607BA0)
// The parasite unit can be put back where its victim stands: the victim is
// alive and either the parasite is naval or the cell is land it can use (an
// aircraft parasite also needs no terrain object there).
#include "shared/foot.hpp"
#include "shared/cell.hpp"
#include "shared/parasite.hpp"

bool ParasiteClass::Can_Exit_00607BA0()
{
    if (unknown_28 == 0) {
        return false;
    }
    if (unknown_28->unknown_slot21()) {
        return false;
    }
    if (!Owner->unknown_slot32()->Naval) {
        if (Owner != 0 && Owner->Kind_Of() == 1 && ((CellClass *)unknown_28->unknown_slot105())->Cell_Terrain() != 0) {
            return false;
        }
        int land = ((CellClass *)unknown_28->unknown_slot105())->unknown_ec;
        if (land == 2 || land == 6 || land == 3) {
            return false;
        }
    }
    return true;
}

// void CellClass::unknown_47bb30() (0x0047BB30)
// Veins attack: on a grown vein cell (overlay 0x7E, data 48 or more, +0x11C
// clear) not yet marked (+0x140 bit 0x20000), each low occupant (slot 108 at
// most 5) that is a techno not immune to veins and without ability 8 gets the
// Rules VeinAttack animation at the cell's corner, and the cell is marked.
#include "shared/cell.hpp"
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"

void CellClass::unknown_47bb30()
{
    if (OverlayIndex == 0x7E && OverlayData >= 48 && !unknown_11c && !(unknown_140 & 0x20000)) {
        for (ObjectClass *object = OccupierPtr; object != 0; object = object->unknown_30) {
            if (object->unknown_slot108() <= 5) {
                bool is_techno;
                if (object != 0) {
                    is_techno = object->unknown_14_bit0;
                }
                TechnoClass *techno = (object != 0 && is_techno) ? (TechnoClass *)object : 0;
                if (techno != 0 && !techno->unknown_slot32()->ImmuneToVeins && !techno->unknown_6d7910(8)) {
                    new AnimClass(Rules->VeinAttack, unknown_475d60() - CoordStruct(128, 128, 0), 0, 1, 0x600, 0);
                    unknown_140 |= 0x20000;
                }
            }
        }
    }
}

// bool TechnoClass::unknown_slot222(HouseClass *house, int arg2) (0x006CD940, slot 222)
// Changes the owner (hypothesis: Westwood's Captured): nothing for the
// current owner; otherwise drops the target and destination, leaves the old
// owner's tracking (0x004ED440, 0x004EA800), credits the new owner with the
// type's cost (+0x5418) and a capture count by kind (+0x5364 buildings,
// +0x5310 units, aircraft and infantry), takes the cell occupation along,
// joins the new owner (0x004EA970, 0x004ED610) and, unless a weapons
// factory building is busy with mission 16 or has one as its first
// contact, resets its missions. Body 699 bytes: code to 0x006CDBDE, a
// three-entry jump table at 0x006CDBE0 and a 15-byte index table at
// 0x006CDBEC.
#include "shared/techno.hpp"
#include "shared/foot.hpp"
#include "shared/aircraft.hpp"
#include "shared/house_type.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMapClass@@A=008324e0
// @ref ?unknown_6155e0@TechnoClass@@QAEXXZ=006155e0
// @ref ?unknown_476b20@UnknownCellClass@@QAEXHH@Z=00476b20
// @ref ?Unknown_004ED610@HouseClass@@QAEXPAVTechnoClass@@_N@Z=004ed610

bool TechnoClass::unknown_slot222(HouseClass *house, int arg2)
{
    if (house != House) {
        unknown_slot220(0);
        unknown_slot260(0, 1);
        unknown_6155e0();
        House->Unknown_004ED440(this, false);
        unknown_slot55(0);
        house->unknown_5418 += unknown_slot32()->unknown_slot33((int)House);
        House->unknown_4ea800(this);
        house->unknown_4ea970(this);
        switch (Kind_Of()) {
        case 6:
            house->unknown_5364[Owner()]++;
            break;
        case 1:
        case 2:
        case 15:
            house->unknown_5310[Owner()]++;
            break;
        }
        House->unknown_53b8 = house->Type->House;
        if (!unknown_76) {
            unknown_slot71(0);
        }
        Unknown_006D7C80(this);
        if (!unknown_76) {
            unknown_slot71(3);
        }
        UnknownCellClass *cell = 0;
        if (!unknown_76) {
            bool foot;
            if (this != 0) {
                foot = unknown_14_bit2;
            }
            bool moving = this != 0 && foot;
            if (!moving) {
                cell = (UnknownCellClass *)&Map[CoordStruct(Coord)];
            } else {
                cell = (UnknownCellClass *)&Map[((FootClass *)this)->unknown_454];
            }
            unknown_6d95d0(cell);
        }
        unknown_6cdc00(house);
        if (!unknown_76) {
            unknown_6d95a0(cell);
        }
        House->Unknown_004ED610(this, true);
        if (!unknown_76) {
            if (Kind_Of() != 6 || Mission != 16 || !((BuildingClass *)this)->Type->unknown_1357) {
                TechnoClass *contact;
                if (Contact(0) == 0 || (contact = Contact(0))->Kind_Of() != 6 || !((BuildingClass *)contact)->Type->unknown_1357) {
                    unknown_slot260(0, 1);
                    unknown_slot220(0);
                    unknown_slot261(false, true);
                }
            }
            unknown_slot265();
            unknown_slot264();
        }
        return true;
    }
    return false;
}

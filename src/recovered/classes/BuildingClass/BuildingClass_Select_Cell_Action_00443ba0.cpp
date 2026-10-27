// Select an action for a cell using the base action and building-specific limits.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
#include "shared/keyboard.hpp"
#include "shared/bullet_type.hpp"
// @ref ?unknown_slot27@TechnoClass@@=006ccce0
// @ref ?Down@WWKeyboardClass@@=00532890
// @ref ?WWKeyboard@@=00832468
// @ref ?unknown_key_a40ba4@@=00a40ba4
// @ref ?unknown_key_a40ba8@@=00a40ba8
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?Unknown_004F52B0@HouseClass@@=004f52b0
inline bool Building_Key_Down(int key) { return WWKeyboard->Down(key); }
int BuildingClass::unknown_slot27(Cell const *cell,bool alternate,bool mode)
{
    if(Type->InvisibleInGame) return 0;
    int action;
    if(Type->UndeploysInto && alternate) action=TechnoClass::unknown_slot27(cell,false,mode);
    else action=TechnoClass::unknown_slot27(cell,alternate,mode);
    if(action==1 || action==2) {
        if(!unknown_slot39() && action==1) {
            action=0;
            goto owner_action;
        }
        if(unknown_slot153()) {
            if(!Building_Key_Down(unknown_key_a40ba4) && !Building_Key_Down(unknown_key_a40ba8)) {
                action=0;
                goto owner_action;
            }
            if(Type->Factory!=3) {
                CoordStruct position;
                position.X=cell->X*256+128;
                position.Y=cell->Y*256+128;
                position.Z=0;
                if(!unknown_slot171(position)) action=2;
                if(!(Map[*cell].unknown_140 & 0x100) && Map[*cell].unknown_4c) {
                    action=2;
                    goto owner_action;
                }
            }
        }
    }
    if(action==5) {
        if(!unknown_slot231(0)->WeaponType) goto result_action;
        if(!unknown_slot231(0)->WeaponType->Projectile->AG || Type->EMPulseCannon) action=0;
        if(Mission==19) action=0;
        else if(action==5) goto result_action;
    }
owner_action:
    if(unknown_slot153() && House->Unknown_004F52B0()) action=1;
result_action:
    return action;
}

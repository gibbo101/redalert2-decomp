// BuildingClass 0x0044B770: the delayed-fire countdown. At zero, action 1 fires the weapon recorded in the
// coordinate's X at the target (a prism tower's support count raises the bullet's damage), action 2 creates
// the support laser toward the recorded coordinate.
#include "shared/building.hpp"
#include "shared/bullet.hpp"
#include "shared/rules.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
void BuildingClass::unknown_44b770()
{
    if (unknown_5c8 != 0) {
        if (--unknown_5d8 <= 0) {
            unknown_5d8 = 0;
            switch (unknown_5c8) {
                case 1:
                    if (unknown_228 != 0 && unknown_slot218(unknown_228, unknown_5cc.X, true) == 0) {
                        BulletClass *bullet = unknown_slot221(unknown_228, unknown_5cc.X);
                        if (bullet != 0 && unknown_534 != 0) {
                            bullet->DamageMultiplier = (unsigned)((Rules->PrismSupportModifier * unknown_534 + 100) * 256) / 100;
                            unknown_534 = 0;
                        }
                    }
                    break;

                case 2:
                    unknown_446820(unknown_5cc);
                    break;
            }
            unknown_5c8 = 0;
        }
    }
}

// @ref ?unknown_446820@BuildingClass@@QAEXUCoordStruct@@@Z=00446820

// @ref ?Rules@@3PAVRulesClass@@A=00839848

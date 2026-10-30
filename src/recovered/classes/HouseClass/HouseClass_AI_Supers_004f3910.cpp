// AI use of ready super weapons (0x004F3910;427originalbytes).
#include "shared/techno.hpp"
#include "shared/super.hpp"
#include "shared/team.hpp"

void HouseClass::AI_Supers_004f3910()
{
    Cell target_0;
    Cell target_2;
    if (!Is_Human_Control()) {
        for (int index = 0; index < Supers.Count(); ++index) {
            SuperClass *super = Supers[index];
            if (super && super->unknown_0x57) {
                switch (super->Type->Type) {
                case 0: {
                    SuperClass *pending = super;
                    if (unknown_54f0 != -1) {
                        target_0 = unknown_cell_a40f10;
                        if (unknown_541c == 1) target_0 = unknown_func_4f65a0();
                        else target_0 = unknown_func_4f6a80(unknown_541c);
                        if (target_0 != unknown_cell_a40f10)
                            unknown_func_4e68d0(Supers.ID(pending), target_0);
                    }
                    break;
                }
                case 2: {
                    SuperClass *pending = super;
                    if (!Unknown_0051FC50() && unknown_54f0 != -1) {
                        target_2 = unknown_cell_a40f10;
                        if (unknown_541c == 1) target_2 = unknown_func_4f65a0();
                        else target_2 = unknown_func_4f6a80(unknown_541c);
                        if (target_2 != unknown_cell_a40f10)
                            unknown_func_4e68d0(Supers.ID(pending), target_2);
                    }
                    break;
                }
                case 5:
                case 6: unknown_func_4f3c50(super); break;
                }
            }
        }
    }
}

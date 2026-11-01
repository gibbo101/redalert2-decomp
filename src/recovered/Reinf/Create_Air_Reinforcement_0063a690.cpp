// int __fastcall Create_Air_Reinforcement(...) -- 0x0063A690 (TS reinf.cpp)
// Brings in number aircraft of a type from the house's edge with a mission, optional target and
// destination, and optionally loads passenger_count infantry of a type into each.
#include "shared/house.hpp"
#include "shared/aircraft.hpp"
#include "shared/infantry_type.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_geometry.hpp"

int __fastcall Create_Air_Reinforcement(HouseClass *house, int air, int number, int mission, AbstractClass *tarcom, AbstractClass *navcom, int passenger, int passenger_count)
{
    TechnoTypeClass const *type = AircraftTypes[air];

    int sub;
    for (sub = 0; sub < number; sub++) {
        unknown_a40774++;
        TechnoClass *obj = (TechnoClass *)type->unknown_slot35(house);
        unknown_a40774--;
        if (!obj) return sub;

        obj->unknown_32c = true;

        int source = house->unknown_128;
        switch (source) {
            case 0:
            case 1:
            case 2:
            case 3:
                break;

            default:
                source = 0;
                break;
        }
        Cell newcell = Map.Unknown_0049A700(source, unknown_geometry_k, unknown_geometry_k, 4, 1, 0);

        obj->unknown_slot116(mission, false);
        if (navcom != 0) {
            obj->unknown_slot260(navcom, 1);
        }
        if (tarcom != 0) {
            obj->unknown_slot220(tarcom);
        }

        unknown_a40774++;
        int placed = obj->unknown_slot53(&CoordStruct(newcell.X * 256 + 128, newcell.Y * 256 + 128, 0), 0);
        unknown_a40774--;
        if (placed) {
            if (obj->Kind_Of() == 2 && passenger != -1 && passenger_count) {
                ((AircraftClass *)obj)->unknown_5b1 = true;
                TechnoTypeClass const *ptype = InfantryTypes[passenger];
                if (ptype) {
                    for (int index = passenger_count; index; index--) {
                        FootClass *inf = (FootClass *)ptype->unknown_slot35(house);
                        if (inf) {
                            inf->unknown_slot52();
                            obj->Cargo.Unknown_00468960(inf);
                        }
                    }
                }
            }
            obj->unknown_slot117();
        } else {
            delete obj;
            sub--;
            return sub;
        }
    }
    return sub;
}

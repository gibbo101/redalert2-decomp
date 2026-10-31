// void TeamClass::unknown_func_6b9610(AbstractClass **center, AbstractClass **close_member) (0x006B9610;
// Red Alert's Calc_Center): with a hound-dog script step the nearest allied unit or infantry outside the
// team (its tube's exit cell while it is in a tube), otherwise the average position of the locked
// members that play, and the member nearest the team's target (+0x40).
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/house.hpp"
#include "shared/techno_type.hpp"
#include "shared/infantry_type.hpp"
#include "shared/map_view.hpp"
#include "shared/tube.hpp"
#include "shared/unknown_vector3.hpp"
#include "shared/unknown_geometry.hpp"
// @ref _unknown_a40774=00a40774
// @ref ?Infantry@@3V?$DynamicVectorClass@PAVInfantryClass@@@@A=00a35e48
// @ref ?Units@@3V?$DynamicVectorClass@PAVUnitClass@@@@A=00866198

// The offset from one coordinate to another (hypothesis: Westwood's Coord operator-, whose
// constructor 0x0041B630 stays out of line).
static inline UnknownVector3 Coord_Offset(CoordStruct const &to, CoordStruct const &from)
{
    return UnknownVector3(to.X - from.X, to.Y - from.Y, to.Z - from.Z);
}

// The distance between two coordinates (hypothesis: Westwood's Distance_To).
static inline int Coord_Offset_Distance(CoordStruct const &to, CoordStruct const &from)
{
    UnknownVector3 offset = Coord_Offset(to, from);
    double y = offset.Y;
    double z = offset.Z;
    double x = offset.X;
    return (int)unknown_sqrt_4ba410(x * x + z * z + y * y);
}

void TeamClass::unknown_func_6b9610(AbstractClass **center, AbstractClass **close_member)
{
    *close_member = 0;
    *center = 0;
    FootClass *member = Member;
    if (member == 0) {
        return;
    }
    if (Script->Get_Current_Mission().Mission == 10) {
        FootClass *closest = 0;
        int distance = -1;
        for (int unit_index = 0; unit_index < Units.Count(); unit_index++) {
            FootClass *unit = (FootClass *)Units[unit_index];
            if (unknown_func_6bdd80(unit) && unit->House->Is_Ally(Owner) && this != (TeamClass *)unit->Team) {
                UnknownVector3 offset = Coord_Offset(member->Center_Coord(), unit->Center_Coord());
                int trial = offset.Length();
                if (distance == -1 || trial < distance) {
                    distance = trial;
                    closest = unit;
                }
            }
        }
        for (int infantry_index = 0; infantry_index < Infantry.Count(); infantry_index++) {
            FootClass *infantry = (FootClass *)Infantry[infantry_index];
            if (unknown_func_6bdd80(infantry) && infantry->House->Is_Ally(Owner) && this != (TeamClass *)infantry->Team) {
                int trial = Coord_Offset_Distance(member->Center_Coord(), infantry->Center_Coord());
                if (distance == -1 || trial < distance) {
                    distance = trial;
                    closest = infantry;
                }
            }
        }
        if (closest != 0) {
            if (closest->unknown_574 >= 0) {
                Cell exit = unknown_TubeClass_list_008661c8[closest->unknown_574]->ExitCell;
                *center = &Map[exit];
            } else {
                *center = closest;
            }
            *close_member = Member;
        }
    } else {
        int x = 0;
        int y = 0;
        int dist = 0;
        int quantity = 0;
        FootClass *closest = 0;
        while (member != 0) {
            if (unknown_func_6bdd80(member) && (member->unknown_579 || member->Kind_Of() == 2) && member->unknown_32d) {
                x += member->Position_Coord_004f3f40().X;
                y += member->Position_Coord_004f3f40().Y;
                quantity++;
                if (Class->GuardSlower && member->unknown_slot283()) {
                    x += member->Position_Coord_004f3f40().X;
                    y += member->Position_Coord_004f3f40().Y;
                    quantity++;
                }
                if (member->unknown_slot32()->Passengers <= 0 || !member->unknown_slot32()->Naval) {
                    int try_dist = member->Distance_Squared((ObjectClass *)unknown_40);
                    if (!dist || try_dist < dist) {
                        dist = try_dist;
                        closest = member;
                    }
                }
            }
            member = (FootClass *)member->unknown_4c8;
        }
        if (quantity) {
            x /= quantity;
            y /= quantity;
            CoordStruct coord = CoordStruct(x, y, 0);
            *center = &Map[coord];
            if (closest == 0) {
                closest = Member;
            }
            if (closest->unknown_slot101((CellClass *)*center, -1, -1, 0, 1) != 0) {
                *center = closest;
            }
        }
        if (closest != 0) {
            *close_member = closest;
        }
    }
}

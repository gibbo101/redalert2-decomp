// TargetClass (Target.cpp, 0x006B54A0-0x006B6654; layout: shared/target.hpp):
// a reference to a game object by kind and ID. Kind 11 is a cell (ID = X + Y *
// 1000); kind 0x34 an object in the object index (shared/object_index.hpp).
#include "shared/building.hpp"
#include "shared/unit.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/aircraft.hpp"
#include "shared/infantry.hpp"
#include "shared/terrain.hpp"
#include "shared/bullet.hpp"
#include "shared/anim.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/trigger.hpp"
#include "shared/trigger_type.hpp"
#include "shared/tag.hpp"
#include "shared/tag_type.hpp"
#include "shared/house.hpp"
#include "shared/techno_type.hpp"
#include "shared/target.hpp"
#include "shared/object_index.hpp"

// TargetClass::TargetClass(AbstractClass *object) (0x006B54A0): a cell by its
// position, any other object by its ID; null gives no target.

TargetClass::TargetClass(AbstractClass *object)
{
    if (object != 0) {
        int kind = object->Kind_Of();
        if (kind == 11) {
            Kind = kind;
            Cell cell = ((CellClass *)object)->MapCoords;
            ID = cell.X + cell.Y * 1000;
        } else {
            Kind = 0x34;
            ID = object->Fetch_ID();
        }
    } else {
        Kind = 0;
        ID = 0;
    }
}

// bool TagClass::Spring(int event, ObjectClass *object, Cell cell, bool forced, int source) (0x006B3DF0)
// Offers the event to each attached trigger. A sprung trigger acts on object and cell; by the tag
// type's persistence (0 volatile, 1 semi-persistent, 2 persistent) the trigger and the tag are then
// queued for removal and the object and cell drop the tag. Returns whether any trigger acted.
#include "shared/object.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Spring@TriggerClass@@QAE_NHPAVObjectClass@@_N1H@Z=006ed740

bool TagClass::Spring(int event, ObjectClass *object, Cell cell, bool forced, int source)
{
    bool sprung = false;
    bool remove = false;
    bool detach = false;
    if (unknown_35) {
        return false;
    }
    unknown_35 = true;
    for (TriggerClass *trigger = AttachedTrigger; trigger != 0; trigger = trigger->Next) {
        if (trigger->Spring(event, object, forced, Class->Persistence == 2, source)) {
            switch (Class->Persistence) {
            case 0:
                trigger->Fire_Actions(object, cell);
                trigger->unknown_func_6ed990();
                sprung = true;
                remove = true;
                detach = true;
                break;
            case 1:
                if (unknown_2c == 1) {
                    trigger->Fire_Actions(object, cell);
                    trigger->unknown_func_6ed990();
                    remove = true;
                    sprung = true;
                } else {
                    detach = true;
                }
                break;
            case 2:
                trigger->Fire_Actions(object, cell);
                sprung = true;
                break;
            }
        }
    }
    unknown_35 = false;
    if (detach) {
        if (object != 0 && object->unknown_34 == this) {
            object->Attach_Tag(0);
        }
        if (cell != unknown_geometry_k) {
            Map[cell].Set_unknown_3c(0);
        }
    }
    if (remove) {
        Unknown_006ECB90(this, true);
        unknown_objects_ac0cd8.Add(this);
    }
    return sprung;
}

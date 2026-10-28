// TagClass::~TagClass() (0x006B39F0)
// Drops the tag from the scenario's tag lists and its house's counters,
// queues its triggers for removal and leaves the abstract lists.
#include "shared/object.hpp"
#include "shared/house.hpp"

// The abstract list 0x00AC0D48 (element type AbstractClass * by RTTI).
extern DynamicVectorClass<AbstractClass *> unknown_AbstractClass_list_00ac0d48;
// Two tag lists and their positions (0x00866160 / 0x00A35D44 for types
// with flag 0x10, 0x00866238 / 0x00A35E24 for flag 4; hypotheses).
extern DynamicVectorClass<TagClass *> unknown_tags_866160;
extern int unknown_tag_position_a35d44;
extern DynamicVectorClass<TagClass *> unknown_tags_866238;
extern int unknown_tag_position_a35e24;
extern bool unknown_flag_a40958;
extern bool unknown_flag_a40d04;

TagClass::~TagClass()
{
    Unknown_006ECB90(this, true);
    if (unknown_flag_a40958 && unknown_flag_a40d04 && Class != 0 && (Class->unknown_func_6b4c00() & 0x10)) {
        int index = unknown_tags_866160.ID(this);
        if (unknown_tag_position_a35d44 >= index) {
            if (--unknown_tag_position_a35d44 < 0 && unknown_tags_866160.Count() == 0) {
                unknown_tag_position_a35d44 = 0;
            }
        }
    }
    if (unknown_flag_a40958 && unknown_flag_a40d04 && Class != 0 && (Class->unknown_func_6b4c00() & 4)) {
        int index = unknown_tags_866238.ID(this);
        if (unknown_tag_position_a35e24 >= index) {
            if (--unknown_tag_position_a35e24 < 0 && unknown_tags_866238.Count() == 0) {
                unknown_tag_position_a35e24 = 0;
            }
        }
    }
    if (unknown_flag_a40958 && unknown_flag_a40d04 && AttachedTrigger != 0 && AttachedTrigger->Class != 0 &&
        AttachedTrigger->Class->unknown_a4 != 0 && Class->unknown_func_6b4c30()) {
        HouseClass *house = HouseClass::As_Pointer(((HouseTypeClass *)AttachedTrigger->Class->unknown_a4)->House);
        if (house->unknown_1c4 != 0) {
            house->unknown_1c4--;
        }
        house->unknown_1e0 = 60;
    }
    for (TriggerClass *trigger = AttachedTrigger; trigger != 0; trigger = trigger->Next) {
        unknown_objects_ac0cd8.Add(trigger);
    }
    unknown_objects_ac0cb0.Delete((ObjectClass *)this);
    unknown_AbstractClass_list_00ac0d48.Delete(this);
    unknown_TagClass_list_00abfe48.Delete(this);
    Unknown_006ECB90(this, true);
}

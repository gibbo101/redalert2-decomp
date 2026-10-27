// TActionClass: one action of a trigger type (TAction.cpp, unit 0x006AD100;
// RTTI vtables 0x007AC65C primary, 0x007AC640 IRTTITypeInfo at +4).
// Partial layout (from the constructor 0x006AD370; names are hypotheses):
//   +0x24  int ArrayIndex (-1), +0x28 TActionClass *Next, +0x2C int Type,
//   +0x30  AbstractTypeClass *unknown_30 (swizzled), +0x34..+0x48 ints,
//   +0x4C  AbstractClass *unknown_4c, +0x50 AbstractClass *unknown_50
//          (both swizzled), +0x54 char Text[32], +0x74 int Data
//   size 0x78 (slot 12)
#ifndef RA2_SHARED_TACTION_HPP
#define RA2_SHARED_TACTION_HPP

#include "shared/abstract_type.hpp"

extern "C" GUID const CLSID_TActionClass;       // 0x007A1D70
extern "C" char *__cdecl strncpy(char *destination, char const *source, unsigned int count);

class HouseClass;
class ObjectClass;
class TriggerClass;
class Cell;

class TActionClass : public AbstractClass {
public:
    TActionClass();                                                     // 0x006AD370
    TActionClass(NoInitClass const &noinit) : AbstractClass(noinit) {}
    virtual ~TActionClass();                                            // 0x006AD4F0

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x006B2C80 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x006B2CC0 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x006B2D40 slot 6
    virtual void Detach(AbstractClass *target, bool all = true);        // 0x006AD600 slot 10
    virtual int Kind_Of() const;                                        // 0x006B30B0 slot 11
    virtual int Size_Of() const;                                        // 0x006B30A0 slot 12
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x006B2D60 slot 13
    virtual int unknown_slot16() const;                                 // 0x006B30C0

    void Build_INI_Entry(char *buffer) const;                           // 0x006AD640 (appends the action's fields)
    void Read_INI();                                                    // 0x006AD860 (the next strtok fields)
    void Set_Text(char const *text);                                    // 0x006B2EC0 (trimmed)
    char const *Get_Text() const;                                       // 0x006B2F20 (0 when empty)
    // Disables every trigger of the type at +0x50; always true (an action handler; name hypothesis).
    bool unknown_func_6b1f90(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B1F90
    // Springs the triggers of the type at +0x50 (forced, no object); always true (name hypothesis).
    bool unknown_func_6b1ec0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B1EC0
    // Action handlers called by the Execute switch (names are hypotheses; each returns true).
    bool unknown_set_session_flag_222b(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006AFB40
    bool unknown_set_session_flag_222a(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006AFB60
    bool unknown_set_session_flag_222c(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006AFB80
    bool unknown_player_4e7ee0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006AFD30
    bool unknown_player_4e82c0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006AFD70
    bool unknown_map_49cc20(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B0620
    bool unknown_set_local_variable(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B0630
    bool unknown_clear_local_variable(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B0650
    bool unknown_make_ally(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B04C0
    bool unknown_make_enemy(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B0500
    bool unknown_set_house_198(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B13E0
    bool unknown_set_house_137(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B1400
    bool unknown_set_global_variable(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B2000
    bool unknown_clear_global_variable(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B2020
    bool unknown_toggle_session_flag_2229(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B2A90
    bool unknown_create_team(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B1420
    bool unknown_destroy_teams(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B1450
    bool unknown_queue_theme(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B1160
    bool unknown_play_voice(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B1180
    bool unknown_play_sound(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B0D70
    bool unknown_give_units_to_house(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B03E0
    bool unknown_give_technos_to_house(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B03E0
    bool unknown_hunt_idle_feet_not_of_house(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006AFBA0
    bool unknown_hunt_feet_mission_23_of_house(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006AFC20
    bool unknown_hunt_technos_with_tag(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006AFAB0
    bool unknown_hunt_technos_of_house_type(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006AFCA0
    bool unknown_infantry_with_tag_slot294(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B0210
    bool unknown_buildings_with_tag_power_down(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B0280
    bool unknown_map_55d990_at_waypoint(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B0800
    bool unknown_reveal_whole_map(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B09B0
    bool unknown_start_mission_timer(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B0A20
    bool unknown_map_54e580_at_waypoint(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B2830
    bool unknown_map_559fd0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B1D70
    bool unknown_63b5b0_at_waypoint(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B1FD0
    bool unknown_set_session_22a8(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell);   // 0x006B2260
    static int __fastcall Action_Flags(int type);                       // 0x006B2DF0 (hypothesis)

    int unknown_24;                         // +0x24
    TActionClass *Next;                     // +0x28
    int Type;                               // +0x2C
    AbstractTypeClass *unknown_30;          // +0x30
    int unknown_34;                         // +0x34
    int unknown_38;                         // +0x38
    int unknown_3c;                         // +0x3C
    int unknown_40;                         // +0x40
    int unknown_44;                         // +0x44
    int unknown_48;                         // +0x48
    AbstractClass *unknown_4c;              // +0x4C
    AbstractClass *unknown_50;              // +0x50
    char Text[32];                          // +0x54
    int Data;                               // +0x74
};

// Every action (0x00ABFD88; defined in this unit).
extern DynamicVectorClass<TActionClass *> unknown_TActionClass_list_00abfd88;

#endif

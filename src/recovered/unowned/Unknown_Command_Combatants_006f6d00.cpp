// @ref ??_C@_0BB@FMPO@MSG?3SelAcrossMap?$AA@=007f8c38
// @ref ??_C@_0BD@BJM@D?3?2Ra2?2UICmnds?4cpp?$AA@=007f8c10
// @ref ??_C@_0BE@GHHF@MSG?3NothingSelected?$AA@=007f8bfc
// @ref ??_C@_0BE@LMOP@MSG?3SelAcrossScreen?$AA@=007f8c24
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?Technos@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a40c20
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?unknown_flag_ac133c@@3_NA=00ac133c
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60
// @ref _wcscpy=00783689
// @ref ?unknown_int_a3d548@@3HA=00a3d548
// @ref ?unknown_state_ac132c@@3HA=00ac132c
// @ref ?unknown_flag_ac1330@@3_NA=00ac1330
// @ref ?unknown_selected_83996c@@3PAUUnknownSelection@@A=0083996c
// @ref ?Unknown_006AAD40@UnknownSelection@@QAEXXZ=006aad40
// @ref ?Unknown_006AAD70@UnknownSelection@@QAEXXZ=006aad70
// @ref ?Count@UnknownSelection@@QAEHXZ=006ac7b0
// @ref ?Get@UnknownSelection@@QAEPAVObjectClass@@H@Z=006ac7c0
// @ref ?unknown_flag_bit0@@YIEPBUUnknownFlags_006f8a70@@@Z=006f8a70
// @ref ?Unknown_006F58E0@@YIXPBGH@Z=006f58e0
// @ref ?Add@?$DynamicVectorClass@PAVTechnoClass@@@@QAE_NABQAVTechnoClass@@@Z=004137b0
// @ref ??0?$DynamicVectorClass@PAVTechnoClass@@@@QAE@IPBQAVTechnoClass@@@Z=006f8a80
// @ref ??0?$VectorClass@PAVTechnoClass@@@@QAE@IPBQAVTechnoClass@@@Z=0040bc10
// @ref ??2@YAPAXI@Z=00782017
// @ref ??_7?$DynamicVectorClass@PAVTechnoClass@@@@6B@=0079a79c
#include "shared/uicmnds.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/string_table.hpp"

extern int unknown_state_ac132c;
struct UnknownFlags_006f8a70;
unsigned char __fastcall unknown_flag_bit0(UnknownFlags_006f8a70 const *object);
void __fastcall Unknown_006F58E0(wchar_t const *text, int delay);
void __fastcall Unknown_006F6790(wchar_t *buffer);
int __fastcall Unknown_006F6FE0(TechnoClass *techno);
DynamicVectorClass<TechnoClass *> *__fastcall Unknown_006F6930(UnknownTest test, int argument);

// The selected objects (bit 0 of +0x14, 0x006F8A70) for which test(object, argument) holds, in a new list.
static DynamicVectorClass<TechnoClass *> *__fastcall Selected_Where_Flagged(UnknownTest test, int argument)
{
    DynamicVectorClass<TechnoClass *> *list = new DynamicVectorClass<TechnoClass *>(0, 0);
    int count = unknown_selected_83996c->Count();
    for (int index = 0; index < count; index++) {
        ObjectClass *object = unknown_selected_83996c->Get(index);
        if (unknown_flag_bit0((UnknownFlags_006f8a70 const *)object)) {
            TechnoClass *techno = (TechnoClass *)object;
            if (test(techno, argument)) {
                list->Add(techno);
            }
        }
    }
    return list;
}

// Whether the techno is a selectable combatant (not a building, kind 6; type flag +0xB58).
static bool Is_Combatant(TechnoClass *techno)
{
    return techno->Kind_Of() != 6 && techno->unknown_slot32()->IsSelectableCombatant;
}

// Whether no combatant of the list is on the screen (+0x77 clear on every one).
static bool None_On_Screen(DynamicVectorClass<TechnoClass *> *list)
{
    int count = list->Count();
    for (int index = 0; index < count; index++) {
        TechnoClass *techno = (*list)[index];
        if (Is_Combatant(techno) && !techno->unknown_77) {
            return false;
        }
    }
    return true;
}

// void __fastcall Unknown_006F6D00(bool flag) (0x006F6D00)
// The select-combatants command (state 1): the player's selected combatants on the screen, else (flag 0x00AC133C,
// kept while the command repeats) every player combatant on the map; selects them (slot 80) and shows 0x006F6790's
// message through 0x006F58E0.
void __fastcall Unknown_006F6D00(bool flag)
{
    if (unknown_int_a3d548 != 0) {
        return;
    }
    unknown_selected_83996c->Unknown_006AAD70();
    if (unknown_state_ac132c != 1) {
        unknown_flag_ac133c = false;
    }
    DynamicVectorClass<TechnoClass *> *list;
    if (unknown_flag_ac133c) {
        list = Unknown_006F6930((UnknownTest)Unknown_006F6FE0, 0);
    } else {
        list = Selected_Where_Flagged((UnknownTest)Unknown_006F6FE0, 0);
        if (None_On_Screen(list)) {
            unknown_flag_ac133c = true;
        }
        if (unknown_flag_ac133c) {
            delete list;
            list = Unknown_006F6930((UnknownTest)Unknown_006F6FE0, 0);
        }
    }
    if (flag) {
        unknown_selected_83996c->Unknown_006AAD40();
    }
    int total = list->Count();
    for (int item = 0; item < total; item++) {
        TechnoClass *techno = (*list)[item];
        if (Is_Combatant(techno)) {
            techno->unknown_slot80();
        }
    }
    wchar_t buffer[256];
    Unknown_006F6790(buffer);
    Unknown_006F58E0(buffer, -1);
    delete list;
    unknown_state_ac132c = 1;
    unknown_flag_ac1330 = false;
}

// @ref ??_C@_0BD@BJM@D?3?2Ra2?2UICmnds?4cpp?$AA@=007f8c10
// @ref ??_C@_0BD@EMHN@MSG?3HeavilyDamaged?$AA@=007f8c94
// @ref ??_C@_0M@EGJA@MSG?3Healthy?$AA@=007f8c88
// @ref ??_C@_0N@IEJB@MSG?3Critical?$AA@=007f8ca8
// @ref ??_C@_09NPDK@MSG?3Mixed?$AA@=007f8c7c
// @ref ?unknown_empty_wide_839d4c@@3QBGB=00839d4c
// @ref ?unknown_int_a3d548@@3HA=00a3d548
// @ref ?unknown_state_ac132c@@3HA=00ac132c
// @ref ?unknown_state_7f8bdc@@3HA=007f8bdc
// @ref ?unknown_flag_ac1330@@3_NA=00ac1330
// @ref ?unknown_list_ac1344@@3PAUUnknownPointerList@@A=00ac1344
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60
// @ref ?unknown_selected_83996c@@3PAUUnknownSelection@@A=0083996c
// @ref ?Unknown_006AAD40@UnknownSelection@@QAEXXZ=006aad40
// @ref ?unknown_713440@UnknownTechnoPair@@QBEHXZ=00713440
// @ref ??_C@_09MLOC@MSG?3Elite?$AA@=007f8cdc
// @ref ??_C@_0M@KCCB@MSG?3Veteran?$AA@=007f8cd0
// @ref ??_C@_0BF@BENO@MSG?3LittleExperience?$AA@=007f8cb8
// @ref ?Unknown_006F6AD0@@YAPAV?$DynamicVectorClass@PAVTechnoClass@@@@XZ=006f6ad0
// @ref ?Unknown_006F69F0@@YIPAV?$DynamicVectorClass@PAVTechnoClass@@@@P6I_NPAXH@ZH@Z=006f69f0
// @ref ?Unknown_006F7DF0@@YIHPAVTechnoClass@@H@Z=006f7df0
// @ref ?Unknown_006F6810@@YIXPAGPBG@Z=006f6810
// @ref ?unknown_func_5d46b0@ObjectClass@@QBEHXZ=005d46b0
// @ref ?Add@?$DynamicVectorClass@PAVTechnoClass@@@@QAE_NABQAVTechnoClass@@@Z=004137b0
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_messages_a3dc70@@3UUnknownMessageList@@A=00a3dc70
// @ref ?Add_Message@UnknownMessageList@@QAEXHHPBGHHHH@Z=005b4da0
// @ref ??0?$DynamicVectorClass@PAVTechnoClass@@@@QAE@IPBQAVTechnoClass@@@Z=006f8a80
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PAVTechnoClass@@@@UBE_NABV0@@Z=0040b870
// @ref ??_7?$DynamicVectorClass@PAVTechnoClass@@@@6B@=0079a79c
// @ref ??_7?$VectorClass@PAVTechnoClass@@@@6B@=0079a7fc
// @ref ??_E?$DynamicVectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bbc0
// @ref ??_G?$DynamicVectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bbc0
// @ref ??_E?$VectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bb70
// @ref ??_G?$VectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bb70
// @ref ?Clear@?$DynamicVectorClass@PAVTechnoClass@@@@UAEXXZ=0040b5b0
// @ref ?Clear@?$VectorClass@PAVTechnoClass@@@@UAEXXZ=0040b960
// @ref ?Fetch@?$VectorClass@PAVTechnoClass@@@@UBEPAVTechnoClass@@H@Z=0040b600
// @ref ?ID@?$DynamicVectorClass@PAVTechnoClass@@@@UAEHABQPAVTechnoClass@@@Z=0040baa0
// @ref ?ID@?$DynamicVectorClass@PAVTechnoClass@@@@UAEHPBQPAVTechnoClass@@@Z=0040b5e0
// @ref ?ID@?$VectorClass@PAVTechnoClass@@@@UAEHABQPAVTechnoClass@@@Z=0040b990
// @ref ?ID@?$VectorClass@PAVTechnoClass@@@@UAEHPBQPAVTechnoClass@@@Z=0040b9d0
// @ref ?Resize@?$DynamicVectorClass@PAVTechnoClass@@@@UAE_NHPBQPAVTechnoClass@@@Z=0040b9f0
// @ref ?Resize@?$VectorClass@PAVTechnoClass@@@@UAE_NHPBQPAVTechnoClass@@@Z=0040b8b0
#include "shared/uicmnds.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/string_table.hpp"

extern UnknownPointerList *unknown_list_ac1344;
extern int unknown_state_ac132c;
extern int unknown_state_7f8bdc;
extern bool unknown_flag_ac1330;
extern wchar_t const unknown_empty_wide_839d4c[];
void __fastcall Unknown_006F6810(wchar_t *buffer, wchar_t const *name);
int __fastcall Unknown_006F7DF0(TechnoClass *techno, int argument);
DynamicVectorClass<TechnoClass *> *Unknown_006F6AD0();
void Unknown_006F79C0();
DynamicVectorClass<TechnoClass *> *__fastcall Unknown_006F69F0(UnknownTest test, int argument);

static wchar_t const *__fastcall Veterancy_Message(int state)
{
    if (state == 0) {
        return StringTable::Load_String("MSG:Elite", 0, "D:\\Ra2\\UICmnds.cpp", 0x5f8);
    }
    if (state == 1) {
        return StringTable::Load_String("MSG:Veteran", 0, "D:\\Ra2\\UICmnds.cpp", 0x5fa);
    }
    if (state == 2) {
        return StringTable::Load_String("MSG:LittleExperience", 0, "D:\\Ra2\\UICmnds.cpp", 0x5fc);
    }
    return unknown_empty_wide_839d4c;
}

static int __fastcall Rank_Index(int state)
{
    if (state == -1) {
        return 0;
    }
    if (state == 0) {
        return 1;
    }
    return state == 1 ? 2 : 0;
}

static wchar_t const *Experience_Message(int kind)
{
    wchar_t const *text = Veterancy_Message(kind);
    DynamicVectorClass<TechnoClass *> *objects = Unknown_006F6AD0();
    int objects_count = objects->Count();
    for (int check = 0; check < objects_count; check++) {
        TechnoClass *item = (*objects)[check];
        if (item->unknown_118.unknown_713440() != kind) {
            text = StringTable::Load_String("MSG:Mixed", 0, "D:\\Ra2\\UICmnds.cpp", 0x5e4);
            break;
        }
    }
    delete objects;
    return text;
}

void __fastcall Unknown_006F7EC0(bool flag)
{
    if (unknown_int_a3d548 != 0) {
        return;
    }
    int kind;
    if (unknown_state_ac132c != 4) {
        Unknown_006F79C0();
        unknown_selected_83996c->Unknown_006AAD40();
        kind = 0;
    } else {
        kind = Rank_Index(unknown_state_7f8bdc);
        if (flag) {
            unknown_selected_83996c->Unknown_006AAD40();
        }
    }
    DynamicVectorClass<TechnoClass *> *list = (DynamicVectorClass<TechnoClass *> *)unknown_list_ac1344;
    int count = list->Count();
    for (int index = 0; index < count; index++) {
        TechnoClass *techno = (*list)[index];
        if (techno->unknown_118.unknown_713440() == kind) {
            techno->unknown_slot80();
        }
    }
    wchar_t const *text = Experience_Message(kind);
    wchar_t buffer[256];
    Unknown_006F6810(buffer, text);
    Show_Message(buffer, 0xF0);
    unknown_state_7f8bdc = kind;
    int commands = unknown_list_ac1344->Count;
    unknown_state_ac132c = 0;
    if (commands != 0) {
        unknown_state_ac132c = 4;
    }
    unknown_flag_ac1330 = false;
}

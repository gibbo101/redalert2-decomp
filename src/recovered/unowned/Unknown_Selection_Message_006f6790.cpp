// void __fastcall Unknown_006F6790(wchar_t *buffer) (0x006F6790)
// Copies the message that tells why the selection cannot be used (hypothesis:
// the cross-map / cross-screen selection commands): nothing selected, a
// selection across the map (flag 0x00AC133C) or across the screen.
#include "shared/uicmnds.hpp"
#include "shared/string_table.hpp"
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?unknown_flag_ac133c@@3_NA=00ac133c
// @ref _wcscpy=00783689
// @ref ??_C@_0BB@FMPO@MSG?3SelAcrossMap?$AA@=007f8c38
// @ref ??_C@_0BD@BJM@D?3?2Ra2?2UICmnds?4cpp?$AA@=007f8c10
// @ref ??_C@_0BE@GHHF@MSG?3NothingSelected?$AA@=007f8bfc
// @ref ??_C@_0BE@LMOP@MSG?3SelAcrossScreen?$AA@=007f8c24

extern "C" wchar_t *__cdecl wcscpy(wchar_t *destination, wchar_t const *source);

void __fastcall Unknown_006F6790(wchar_t *buffer)
{
    if (unknown_objects_a40c60.Count() == 0) {
        wcscpy(buffer, StringTable::Load_String("MSG:NothingSelected", 0, "D:\\Ra2\\UICmnds.cpp", 0x382));
        return;
    }
    if (unknown_flag_ac133c) {
        wcscpy(buffer, StringTable::Load_String("MSG:SelAcrossMap", 0, "D:\\Ra2\\UICmnds.cpp", 0x384));
        return;
    }
    wcscpy(buffer, StringTable::Load_String("MSG:SelAcrossScreen", 0, "D:\\Ra2\\UICmnds.cpp", 0x386));
}

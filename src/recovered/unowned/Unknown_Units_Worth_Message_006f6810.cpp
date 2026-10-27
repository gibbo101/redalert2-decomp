// void __fastcall Unknown_006F6810(wchar_t *buffer, wchar_t const *name) (0x006F6810)
// Words the "units worth" message (hypothesis): MSG:NavEmpty when there is
// no list at 0x00AC1344 or no name; otherwise the name is upper-cased and either
// MSG:NoUnitsSel (nothing selected) or MSG:UnitsWorth (count, name, the summed
// cost of the selected objects' types) is formatted into buffer.
#include "shared/uicmnds.hpp"
#include "shared/string_table.hpp"
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?unknown_list_ac1344@@3PAUUnknownPointerList@@A=00ac1344
// @ref _wcscpy=00783689
// @ref __wcsupr=00796ef6
// @ref _swprintf=00783764
// @ref ??_C@_0BD@BJM@D?3?2Ra2?2UICmnds?4cpp?$AA@=007f8c10
// @ref ??_C@_0N@EDCH@MSG?3NavEmpty?$AA@=007f8c4c
// @ref ??_C@_0P@GAKB@MSG?3NoUnitsSel?$AA@=007f8c6c
// @ref ??_C@_0P@ICFD@MSG?3UnitsWorth?$AA@=007f8c5c

extern UnknownPointerList *unknown_list_ac1344;
extern "C" wchar_t *__cdecl wcscpy(wchar_t *destination, wchar_t const *source);
extern "C" wchar_t *__cdecl _wcsupr(wchar_t *string);

void __fastcall Unknown_006F6810(wchar_t *buffer, wchar_t const *name)
{
    if (unknown_list_ac1344->Count == 0 || name == 0) {
        wcscpy(buffer, StringTable::Load_String("MSG:NavEmpty", 0, "D:\\Ra2\\UICmnds.cpp", 0x38F));
        return;
    }
    wchar_t upper[100];
    wcscpy(upper, name);
    _wcsupr(upper);
    int count = unknown_objects_a40c60.Count();
    if (count == 0) {
        swprintf(buffer, StringTable::Load_String("MSG:NoUnitsSel", 0, "D:\\Ra2\\UICmnds.cpp", 0x399), upper);
        return;
    }
    int total = 0;
    for (int index = 0; index < count; index++) {
        ObjectClass *object = unknown_objects_a40c60[index];
        bool flag;
        if (object != 0) {
            flag = object->unknown_14_bit0;
        }
        if (object != 0 && flag) {
            TechnoClass *techno = (TechnoClass *)object;
            HouseClass *owner = techno->House;
            total += techno->Class_Of()->unknown_slot33((int)owner);
        }
    }
    swprintf(buffer, StringTable::Load_String("MSG:UnitsWorth", 0, "D:\\Ra2\\UICmnds.cpp", 0x3AD), count, upper, total);
}

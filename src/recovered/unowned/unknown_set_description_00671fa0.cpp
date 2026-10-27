// void UnknownDescribed_00671FA0::unknown_set_description(wchar_t const *text) -- 0x00671FA0
// Purpose: copies a description (at most 43 characters) into the wide
// buffer at +0x00, or the "MSG:NoDescription" string when there is none.
// Assumptions: a Session.cpp record (the string table call passes
// "D:\Ra2\Session.CPP", line 2826); owner unidentified.
#include "shared/string_table.hpp"
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref _wcsncpy=00783622
// @ref _wcscpy=00783689
// @ref ??_C@_0BC@IPHL@MSG?3NoDescription?$AA@=007f39c0
// @ref ??_C@_0BD@OFLC@D?3?2Ra2?2Session?4CPP?$AA@=007f33c8

extern "C" wchar_t *__cdecl wcsncpy(wchar_t *dest, wchar_t const *source, unsigned int count);
extern "C" wchar_t *__cdecl wcscpy(wchar_t *dest, wchar_t const *source);

struct UnknownDescribed_00671fa0 {
    wchar_t Description[44];                // +0x00
    void unknown_set_description(wchar_t const *text);
};

void UnknownDescribed_00671fa0::unknown_set_description(wchar_t const *text)
{
    if (text != 0) {
        wcsncpy(Description, text, 44);
        Description[43] = 0;
        return;
    }
    wcscpy(Description, StringTable::Load_String("MSG:NoDescription", 0, "D:\\Ra2\\Session.CPP", 2826));
}

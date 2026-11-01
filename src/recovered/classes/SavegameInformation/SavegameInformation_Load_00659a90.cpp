// long SavegameInformation::Load(IStorage *storage) (0x00659A90)
// Reads the summary from the summary property set when the storage has one
// and its description property reads; otherwise from the storage's streams
// (Read_Stream_Int/Time expand inline here until the inline budget runs out:
// the stream-name lookup, Checked and _Release then go out of line, the last
// Read_Stream_Int is called). The `result < 0` tests (not FAILED's cast) and
// `(void **)&set` (comip operator&) are what give the original's budget.
#include "shared/savegame_info.hpp"
#include "shared/com_ptr.hpp"
extern "C" wchar_t *__cdecl wcscpy(wchar_t *dest, wchar_t const *source);   // 0x00783689
extern "C" char *__cdecl strcpy(char *destination, char const *source);
#pragma intrinsic(strcpy)


long SavegameInformation::Load(IStorage *storage)
{
    if (storage == 0) {
        return E_POINTER;
    }
    UnknownComPtr<IPropertySetStorage, &unknown_uuid_IPropertySetStorage> set;
    wchar_t wide[256];
    char text[256];
    HRESULT result;
    if (SUCCEEDED(storage->QueryInterface(IID_IPropertySetStorage, (void **)&set))
        && SUCCEEDED(result = Read_Property_Wide(set, 2, wide))) {
        wcscpy(Description, wide);
        result = Read_Property_Wide(set, 3, wide);
        if (result < 0) {
            return result;
        }
        wcscpy(PlayerName, wide);
        result = Read_Property_Int(set, 9, &unknown_04);
        if (result < 0) {
            return result;
        }
        result = Read_Property_Int(set, 16, &unknown_00);
        if (result < 0) {
            return result;
        }
        result = Read_Property_Time(set, 12, &StartTime);
        if (result < 0) {
            return result;
        }
        result = Read_Property_Time(set, 13, &PlayTime);
        if (result < 0) {
            return result;
        }
        result = Read_Property_Time(set, 10, &SaveTime);
        if (result < 0) {
            return result;
        }
        result = Read_Property_String(set, 18, text);
        if (result < 0) {
            return result;
        }
        strcpy(unknown_2d4, text);
        result = Read_Property_String(set, 4, text);
        if (result < 0) {
            return result;
        }
        strcpy(unknown_294, text);
        result = Read_Property_Int(set, 100, &unknown_18c);
        if (result < 0) {
            return result;
        }
        result = Read_Property_Int(set, 101, &unknown_188);
        if (result < 0) {
            return result;
        }
        result = Read_Property_Int(set, 102, &GameType);
        if (result < 0) {
            return result;
        }
    } else {
    result = Read_Stream_Wide(storage, 2, wide);
    if (result < 0) {
        return result;
    }
    wcscpy(Description, wide);
    result = Read_Stream_Wide(storage, 3, wide);
    if (result < 0) {
        return result;
    }
    wcscpy(PlayerName, wide);
    result = Read_Stream_Int(storage, 9, &unknown_04);
    if (result < 0) {
        return result;
    }
    result = Read_Stream_Int(storage, 16, &unknown_00);
    if (result < 0) {
        return result;
    }
    result = Read_Stream_Time(storage, 12, &StartTime);
    if (result < 0) {
        return result;
    }
    result = Read_Stream_Time(storage, 13, &PlayTime);
    if (result < 0) {
        return result;
    }
    result = Read_Stream_Time(storage, 10, &SaveTime);
    if (result < 0) {
        return result;
    }
    result = Read_Stream_String(storage, 18, text);
    if (result < 0) {
        return result;
    }
    strcpy(unknown_2d4, text);
    result = Read_Stream_String(storage, 4, text);
    if (result < 0) {
        return result;
    }
    strcpy(unknown_294, text);
    result = Read_Stream_Int(storage, 100, &unknown_18c);
    if (result < 0) {
        return result;
    }
    result = Read_Stream_Int(storage, 101, &unknown_188);
    if (result < 0) {
        return result;
    }
    result = Read_Stream_Int(storage, 102, &GameType);
    if (result < 0) {
        return result;
    }
    }
    return S_OK;
}

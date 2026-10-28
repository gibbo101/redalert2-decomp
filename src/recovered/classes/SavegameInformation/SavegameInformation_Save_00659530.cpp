// long SavegameInformation::Save(IStorage *storage) (0x00659530)
// Writes the summary twice: as properties of the summary property set (when
// the storage has one) and as streams of the storage. Both "Player Name"
// entries (4 and 8) take +0x294.
#include "shared/savegame_info.hpp"
// @ref _IID_IPropertySetStorage=007afd50
#include "shared/com_ptr.hpp"


long SavegameInformation::Save(IStorage *storage)
{
    if (storage == 0) {
        return E_POINTER;
    }
    UnknownComPtr<IPropertySetStorage, &unknown_uuid_IPropertySetStorage> set;
    HRESULT result;
    if (SUCCEEDED(storage->QueryInterface(IID_IPropertySetStorage, (void **)&set.Pointer))) {
        result = Write_Property_Wide(set, 2, Description);
        if (FAILED(result)) {
            return result;
        }
        result = Write_Property_Wide(set, 3, PlayerName);
        if (FAILED(result)) {
            return result;
        }
        result = Write_Property_Int(set, 9, unknown_04);
        if (FAILED(result)) {
            return result;
        }
        result = Write_Property_Int(set, 16, unknown_00);
        if (FAILED(result)) {
            return result;
        }
        result = Write_Property_Time(set, 12, &StartTime);
        if (FAILED(result)) {
            return result;
        }
        result = Write_Property_Time(set, 13, &PlayTime);
        if (FAILED(result)) {
            return result;
        }
        result = Write_Property_Time(set, 10, &SaveTime);
        if (FAILED(result)) {
            return result;
        }
        result = Write_Property_String(set, 18, unknown_2d4);
        if (FAILED(result)) {
            return result;
        }
        result = Write_Property_String(set, 4, unknown_294);
        if (FAILED(result)) {
            return result;
        }
        result = Write_Property_String(set, 8, unknown_294);
        if (FAILED(result)) {
            return result;
        }
        result = Write_Property_Int(set, 100, unknown_18c);
        if (FAILED(result)) {
            return result;
        }
        result = Write_Property_Int(set, 101, unknown_188);
        if (FAILED(result)) {
            return result;
        }
        result = Write_Property_Int(set, 102, GameType);
        if (FAILED(result)) {
            return result;
        }
    }
    result = Write_Stream_Wide(storage, 2, Description);
    if (FAILED(result)) {
        return result;
    }
    result = Write_Stream_Wide(storage, 3, PlayerName);
    if (FAILED(result)) {
        return result;
    }
    result = Write_Stream_Int(storage, 9, unknown_04);
    if (FAILED(result)) {
        return result;
    }
    result = Write_Stream_Int(storage, 16, unknown_00);
    if (FAILED(result)) {
        return result;
    }
    result = Write_Stream_Time(storage, 12, &StartTime);
    if (FAILED(result)) {
        return result;
    }
    result = Write_Stream_Time(storage, 13, &PlayTime);
    if (FAILED(result)) {
        return result;
    }
    result = Write_Stream_Time(storage, 10, &SaveTime);
    if (FAILED(result)) {
        return result;
    }
    result = Write_Stream_String(storage, 18, unknown_2d4);
    if (FAILED(result)) {
        return result;
    }
    result = Write_Stream_String(storage, 4, unknown_294);
    if (FAILED(result)) {
        return result;
    }
    result = Write_Stream_String(storage, 8, unknown_294);
    if (FAILED(result)) {
        return result;
    }
    result = Write_Stream_Int(storage, 100, unknown_18c);
    if (FAILED(result)) {
        return result;
    }
    result = Write_Stream_Int(storage, 101, unknown_188);
    if (FAILED(result)) {
        return result;
    }
    result = Write_Stream_Int(storage, 102, GameType);
    if (FAILED(result)) {
        return result;
    }
    return S_OK;
}

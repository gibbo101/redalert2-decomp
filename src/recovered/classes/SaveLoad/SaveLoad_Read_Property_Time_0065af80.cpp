// HRESULT SavegameInformation::Read_Property_Time(IPropertySetStorage *storage, int id, FILETIME *time) (0x0065AF80; name hypothesis)
// Reads a FILETIME property (VT_FILETIME) of the summary property set.
#include "shared/savegame_info.hpp"
#include "shared/com_ptr.hpp"

HRESULT SavegameInformation::Read_Property_Time(IPropertySetStorage *storage, int id, FILETIME *time)
{
    time->dwLowDateTime = 0;
    time->dwHighDateTime = 0;
    UnknownComPtr<IPropertyStorage, &unknown_uuid_IPropertyStorage> property;
    HRESULT result = storage->Open(unknown_fmtid_7afd60, 0x12, &property);
    if (FAILED(result)) {
        return result;
    }
    PROPSPEC spec;
    spec.ulKind = 1;
    spec.propid = id;
    PROPVARIANT variant;
    result = property.Checked()->ReadMultiple(1, &spec, &variant);
    if (FAILED(result)) {
        return result;
    }
    if (variant.vt == 0x40) {
        *time = variant.filetime;
    }
    return result;
}

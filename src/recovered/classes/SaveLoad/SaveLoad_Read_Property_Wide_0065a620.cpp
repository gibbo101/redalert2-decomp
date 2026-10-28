// HRESULT SavegameInformation::Read_Property_Wide(IPropertySetStorage *storage, int id, wchar_t *buffer) (0x0065A620; name hypothesis)
// Reads a wide-string property of the summary property set.
#include "shared/savegame_info.hpp"
#include "shared/com_ptr.hpp"

HRESULT SavegameInformation::Read_Property_Wide(IPropertySetStorage *storage, int id, wchar_t *buffer)
{
    buffer[0] = 0;
    UnknownComPtr<IPropertyStorage, &unknown_uuid_IPropertyStorage> property;
    HRESULT result = storage->Open(unknown_fmtid_7afd60, 0x12, &property);
    if (FAILED(result)) {
        return result;
    }
    PROPSPEC spec;
    spec.ulKind = 1;
    spec.propid = id;
    PROPVARIANT value;
    result = property.Checked()->ReadMultiple(1, &spec, &value);
    if (FAILED(result)) {
        return result;
    }
    if (value.vt == 0x1F) {
        wcsncpy(buffer, value.pwszVal, 0x80);
    }
    return result;
}

// HRESULT SavegameInformation::Read_Property_String(IPropertySetStorage *storage, int id, char *buffer) (0x0065A540; name hypothesis)
// Reads a wide-string property of the summary property set.
#include "shared/savegame_info.hpp"
#include "shared/com_ptr.hpp"

HRESULT SavegameInformation::Read_Property_String(IPropertySetStorage *storage, int id, char *buffer)
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
        WideCharToMultiByte(0, 0, value.pwszVal, -1, buffer, 0x80, 0, 0);
    }
    return result;
}

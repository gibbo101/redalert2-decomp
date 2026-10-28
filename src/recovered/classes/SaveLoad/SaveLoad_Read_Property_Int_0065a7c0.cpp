// HRESULT SavegameInformation::Read_Property_Int(IPropertySetStorage *storage, int id, int *value) (0x0065A7C0; name hypothesis)
// Reads a 4-byte integer property (VT_I4) of the summary property set.
#include "shared/savegame_info.hpp"
#include "shared/com_ptr.hpp"

HRESULT SavegameInformation::Read_Property_Int(IPropertySetStorage *storage, int id, int *value)
{
    *value = 0;
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
    if (variant.vt == 3) {
        *value = variant.lVal;
    }
    return result;
}

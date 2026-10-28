// HRESULT SavegameInformation::Write_Property_Wide(IPropertySetStorage *storage, int id, wchar_t const *text) (0x0065ABF0; name hypothesis)
// Writes a property of the summary property set (creating the set when
// it cannot be opened).
#include "shared/savegame_info.hpp"
#include "shared/com_ptr.hpp"

HRESULT SavegameInformation::Write_Property_Wide(IPropertySetStorage *storage, int id, wchar_t const *text)
{
    UnknownComPtr<IPropertyStorage, &unknown_uuid_IPropertyStorage> property;
    if (FAILED(storage->Open(unknown_fmtid_7afd60, 0x12, &property))) {
        HRESULT result = storage->Create(unknown_fmtid_7afd60, 0, 0, 0x1012, &property);
        if (FAILED(result)) {
            return result;
        }
    }
    PROPSPEC spec;
    PROPVARIANT variant;
    spec.ulKind = 1;
    spec.propid = id;
    variant.vt = 0x1F;
    variant.pwszVal = (wchar_t *)text;
    HRESULT result = property.Checked()->WriteMultiple(1, &spec, &variant, 2);
    if (FAILED(result)) {
        return result;
    }
    return result;
}

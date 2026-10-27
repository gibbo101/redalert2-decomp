// HRESULT __stdcall BuildingTypeClass::Save(IStream *stream, BOOL clear_dirty) (0x0045E020)
// The techno part, then the docking offsets (count and points).
#include "shared/building_type.hpp"
// @ref ?Save@TechnoTypeClass@@UAGJPAUIStream@@H@Z=006dec10

HRESULT __stdcall BuildingTypeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = TechnoTypeClass::Save(stream, clear_dirty);
    if (FAILED(result)) {
        return result;
    }
    int count = DockingOffsets.Length();
    result = stream->Write(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    for (int index = 0; index < count; index++) {
        result = stream->Write(&DockingOffsets[index], sizeof(TPoint3D<int>), 0);
        if (FAILED(result)) {
            return result;
        }
    }
    return S_OK;
}

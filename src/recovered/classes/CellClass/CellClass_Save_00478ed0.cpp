// HRESULT __stdcall CellClass::Save(IStream *stream, BOOL clear_dirty)
// (0x00478ED0, slot 6): saves the abstract part, then the fogged-object list
// (when there is one) as a count and its pointers; a failed pointer write
// still reports success.
#include "shared/cell.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall CellClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (FAILED(result)) {
        return result;
    }
    if (FoggedObjects != 0) {
        int count = FoggedObjects->Count();
        result = stream->Write(&count, sizeof(count), 0);
        if (FAILED(result)) {
            return result;
        }
        for (int index = 0; index < count; index++) {
            if (FAILED(stream->Write(&(*FoggedObjects)[index], sizeof(FoggedObjectClass *), 0))) {
                break;
            }
        }
    }
    return S_OK;
}

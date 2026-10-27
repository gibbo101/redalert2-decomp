// HRESULT __stdcall WaveClass::Save(IStream *stream, BOOL clear_dirty) (0x00722330)
// AbstractClass::Save (its result is not used), then the cell count and the cell pointers.
#include "shared/wave.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall WaveClass::Save(IStream *stream, BOOL clear_dirty)
{
    AbstractClass::Save(stream, clear_dirty);
    int count = Cells.Count();
    HRESULT result = stream->Write(&count, sizeof(count), 0);
    if (SUCCEEDED(result)) {
        for (int index = 0; index < count; index++) {
            result = stream->Write(&Cells[index], sizeof(CellClass *), 0);
            if (FAILED(result)) {
                break;
            }
        }
    }
    return result;
}

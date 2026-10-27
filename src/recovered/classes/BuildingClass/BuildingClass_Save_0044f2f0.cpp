// HRESULT __stdcall BuildingClass::Save(IStream *stream, BOOL clear_dirty) (0x0044F2F0, slot 6)
// TechnoClass::Save, then each infantry list as a count and its pointers.
#include "shared/building.hpp"
// @ref ?Save@TechnoClass@@UAGJPAUIStream@@H@Z=006d6a80

HRESULT __stdcall BuildingClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = TechnoClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        int count = unknown_53c.Count();
        HRESULT write = stream->Write(&count, sizeof(count), 0);
        if (FAILED(write)) {
            return write;
        }
        for (int index = 0; index < count; index++) {
            write = stream->Write(&unknown_53c[index], sizeof(InfantryClass *), 0);
            if (FAILED(write)) {
                return write;
            }
        }
        count = unknown_554.Count();
        write = stream->Write(&count, sizeof(count), 0);
        if (FAILED(write)) {
            return write;
        }
        for (index = 0; index < count; index++) {
            write = stream->Write(&unknown_554[index], sizeof(InfantryClass *), 0);
            if (FAILED(write)) {
                return write;
            }
        }
    }
    return result;
}

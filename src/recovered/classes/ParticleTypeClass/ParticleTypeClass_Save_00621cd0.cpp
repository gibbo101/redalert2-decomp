// HRESULT __stdcall ParticleTypeClass::Save(IStream *stream, BOOL clear_dirty) (0x00621CD0)
// Saves the object type, then the colour list as a count and its colours
// (a failed colour write still reports success).
#include "shared/particle_system.hpp"
// @ref ?Save@ObjectTypeClass@@UAGJPAUIStream@@H@Z=005d7e60

HRESULT __stdcall ParticleTypeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = ObjectTypeClass::Save(stream, clear_dirty);
    if (FAILED(result)) {
        return result;
    }
    int count = ColorList.Count();
    result = stream->Write(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    for (int index = 0; index < count; index++) {
        if (FAILED(stream->Write(&ColorList[index], sizeof(RGBClass), 0))) {
            return S_OK;
        }
    }
    return S_OK;
}

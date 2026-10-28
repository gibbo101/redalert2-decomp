// HRESULT __stdcall RadioClass::Load(IStream *stream) (0x00636C60, slot 5)
// MissionClass's part, then the contact vector: rebuilt empty, resized to
// the saved count and filled with the saved pointers, which are swizzled.
#include "shared/radio.hpp"
#include "shared/techno.hpp"
// @ref ?Load@ObjectClass@@UAGJPAUIStream@@@Z=005d4760
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT __stdcall RadioClass::Load(IStream *stream)
{
    HRESULT result = MissionClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (&RadioLinks) VectorClass<TechnoClass *>;
    int count;
    result = stream->Read(&count, 4, 0);
    if (FAILED(result)) {
        return result;
    }
    RadioLinks.Resize(count);
    TechnoClass *link;
    for (int index = 0; index < count; index++) {
        result = stream->Read(&link, 4, 0);
        if (FAILED(result)) {
            return result;
        }
        RadioLinks[index] = link;
    }
    for (int fix = 0; fix < count; fix++) {
        SwizzleManager.Swizzle((void **)&RadioLinks[fix]);
    }
    return S_OK;
}

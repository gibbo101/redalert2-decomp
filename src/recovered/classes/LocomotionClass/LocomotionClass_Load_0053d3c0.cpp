// HRESULT __stdcall LocomotionClass::Load(IStream *stream) (0x0053D3C0)
// Reads the saved address (registered with the swizzle manager) and the
// object's Size() bytes, keeping the reference count; then fixes up the
// owner and linked object.
#include "shared/locomotion.hpp"
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ?Here_I_Am@SwizzleManagerClass@@QAGJJPAX@Z=0069fba0
// @ref ?Swizzle@SwizzleManagerClass@@QAGJPAPAX@Z=0069fb20

HRESULT __stdcall LocomotionClass::Load(IStream *stream)
{
    if (stream == 0) {
        return E_POINTER;
    }
    long id;
    HRESULT result = stream->Read(&id, sizeof(id), 0);
    if (FAILED(result)) {
        return result;
    }
    SwizzleManager.Here_I_Am(id, this);
    long count = RefCount;
    result = stream->Read(this, Size(), 0);
    RefCount = count;
    SwizzleManager.Swizzle((void **)&LinkedTo);
    SwizzleManager.Swizzle((void **)&Owner);
    return result;
}

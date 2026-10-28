// HRESULT __stdcall TaskForceClass::Load(IStream *stream) (0x006B7060)
// Restores the task force in place and swizzles the entry types.
#include "shared/task_force.hpp"
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT __stdcall TaskForceClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) TaskForceClass(NoInitClass());
        for (int index = 0; index < 6; index++) {
            SwizzleManager.Swizzle((void **)&Entries[index].Type);
        }
        result = S_OK;
    }
    return result;
}

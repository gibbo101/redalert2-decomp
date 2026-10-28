// HRESULT SpawnManagerClass::Save(IStream *stream, BOOL clear_dirty) (0x0068A970, slot 6)
#include "shared/spawn_manager.hpp"
// @ref ??_7SpawnManagerClass@@6BIPersistStream@@@=007ab8c8
// @ref ??_7SpawnManagerClass@@6BIRTTITypeInfo@@@=007ab8ac
// @ref ??_7SpawnManagerClass@@6BINoticeSink@@@=007ab8a4
// @ref ??_7SpawnManagerClass@@6BINoticeSource@@@=007ab89c
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall SpawnManagerClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (FAILED(result)) {
        return result;
    }
    int count = SpawnedNodes.Count();
    result = stream->Write(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    for (int i = 0; i < count; i++) {
        result = stream->Write(SpawnedNodes[i], sizeof(SpawnControl), 0);
        if (FAILED(result)) {
            return result;
        }
    }
    return result;
}

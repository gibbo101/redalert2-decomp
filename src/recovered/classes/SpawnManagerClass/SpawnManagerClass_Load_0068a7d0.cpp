// HRESULT SpawnManagerClass::Load(IStream *stream) (0x0068A7D0, slot 5)
// The record count, then each record whole.
#include "shared/spawn_manager.hpp"
// @ref ??_7SpawnManagerClass@@6BIPersistStream@@@=007ab8c8
// @ref ??_7SpawnManagerClass@@6BIRTTITypeInfo@@@=007ab8ac
// @ref ??_7SpawnManagerClass@@6BINoticeSink@@@=007ab8a4
// @ref ??_7SpawnManagerClass@@6BINoticeSource@@@=007ab89c
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ??0AbstractClass@@QAE@ABVNoInitClass@@@Z=0040ff60
// @ref ??0?$VectorClass@PAUSpawnControl@@@@QAE@IPBQAUSpawnControl@@@Z=0068b0e0
// @ref ??_7?$DynamicVectorClass@PAUSpawnControl@@@@6B@=007ab92c
// @ref ??0?$CDTimerClass@VFrameTimerClass@@@@QAE@J@Z=00463f80
// @ref ??2@YAPAXI@Z=00782017
// @ref ?Frame@@3HA=00a40d2c
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT __stdcall SpawnManagerClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) SpawnManagerClass(NoInitClass());
        int count;
        result = stream->Read(&count, sizeof(count), 0);
        if (SUCCEEDED(result)) {
            new (&SpawnedNodes) DynamicVectorClass<SpawnControl *>;
            for (int i = 0; i < count; i++) {
                SpawnControl *node = new SpawnControl;
                result = stream->Read(node, sizeof(SpawnControl), 0);
                if (FAILED(result)) {
                    return result;
                }
                Swizzle_Pointer(node->Unit);
                SpawnedNodes.Add(node);
            }
            Swizzle_Pointer(Owner);
            Swizzle_Pointer(SpawnType);
            Swizzle_Pointer(Destination);
            Swizzle_Pointer(Target);
        }
    }
    return result;
}

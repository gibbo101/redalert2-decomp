// HRESULT __stdcall BaseClass::Load(IStream *stream) (0x0042C6A0)
// Restores the plan in place (the NoInit constructor), then each list from
// its count and elements, and swizzles the house. Every path answers 0.
#include "shared/base.hpp"
#include "shared/swizzle.hpp"
// @ref ??0?$VectorClass@VBaseNodeClass@@@@QAE@IPBVBaseNodeClass@@@Z=0042d430
// @ref ??_7?$DynamicVectorClass@VBaseNodeClass@@@@6B@=0079c5c0
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT __stdcall BaseClass::Load(IStream *stream)
{
    HRESULT result = stream->Read(this, sizeof(*this), 0);
    if (FAILED(result)) {
        return 0;
    }
    new (this) BaseClass(NoInitClass());
    int count = 0;
    result = stream->Read(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return 0;
    }
    for (int index = 0; index < count; index++) {
        BaseNodeClass node;
        result = stream->Read(&node, sizeof(node), 0);
        if (FAILED(result)) {
            return 0;
        }
        Nodes.Add(node);
    }
    result = stream->Read(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return 0;
    }
    for (index = 0; index < count; index++) {
        Cell cell;
        result = stream->Read(&cell, sizeof(cell), 0);
        if (FAILED(result)) {
            return 0;
        }
        unknown_20.Add(cell);
    }
    result = stream->Read(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return 0;
    }
    for (index = 0; index < count; index++) {
        Cell cell;
        result = stream->Read(&cell, sizeof(cell), 0);
        if (FAILED(result)) {
            return 0;
        }
        unknown_38.Add(cell);
    }
    SwizzleManager.Swizzle((void **)&House);
    return 0;
}

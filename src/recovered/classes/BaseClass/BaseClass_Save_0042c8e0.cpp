// HRESULT BaseClass::Save(IStream *stream) (0x0042C8E0)
// The object's bytes, then each list as a count and its elements. A failed
// write answers 0 (the original does not pass the error on).
#include "shared/base.hpp"

HRESULT __stdcall BaseClass::Save(IStream *stream)
{
    HRESULT result = stream->Write(this, sizeof(*this), 0);
    if (FAILED(result)) {
        return 0;
    }
    int count = Nodes.Count();
    result = stream->Write(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return 0;
    }
    for (int index = 0; index < count; index++) {
        result = stream->Write(&Nodes[index], sizeof(BaseNodeClass), 0);
        if (FAILED(result)) {
            return 0;
        }
    }
    count = unknown_20.Count();
    result = stream->Write(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return 0;
    }
    for (index = 0; index < count; index++) {
        result = stream->Write(&unknown_20[index], sizeof(Cell), 0);
        if (FAILED(result)) {
            return 0;
        }
    }
    count = unknown_38.Count();
    result = stream->Write(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return 0;
    }
    for (index = 0; index < count; index++) {
        result = stream->Write(&unknown_38[index], sizeof(Cell), 0);
        if (FAILED(result)) {
            return 0;
        }
    }
    return result;
}

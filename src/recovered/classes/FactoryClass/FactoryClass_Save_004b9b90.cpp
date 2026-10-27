#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/factory_class.hpp"
// @ref ?Save@AbstractClass@@=004100c0
// Original element-write failure returns S_OK; base/count-write errors propagate.
HRESULT __stdcall FactoryClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        int count = Queue.Count();
        result = stream->Write(&count, 4, 0);
        if (SUCCEEDED(result)) {
            for (int index = 0; index < count; ++index) {
                result = stream->Write(&Queue[index], 4, 0);
                if (FAILED(result)) return S_OK;
            }
            return S_OK;
        }
    }
    return result;
}

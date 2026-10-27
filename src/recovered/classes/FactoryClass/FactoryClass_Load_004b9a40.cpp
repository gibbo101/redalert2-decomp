#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/factory_class.hpp"
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ??0AbstractClass@@QAE@ABVNoInitClass@@@Z=0040ff60
// @ref ??0StageTimerClass@@QAE@ABVNoInitClass@@@Z=00423f60
// @ref ??_7FactoryClass@@6BIPersistStream@@@=007a0ee0
// @ref ??_7FactoryClass@@6BIRTTITypeInfo@@@=007a0ec4
// @ref ??_7FactoryClass@@6BINoticeSink@@@=007a0ebc
// @ref ??_7FactoryClass@@6BINoticeSource@@@=007a0eb4
// @ref ??_7?$DynamicVectorClass@PAVTechnoTypeClass@@@@6B@=007a0f44
// @ref ??0?$VectorClass@PAVTechnoTypeClass@@@@QAE@IPBQAVTechnoTypeClass@@@Z=004ba3c0
HRESULT __stdcall FactoryClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) FactoryClass(NoInitClass());
        int count = 0;
        result = stream->Read(&count, 4, 0);
        if (SUCCEEDED(result)) {
            for (int i = 0; i < count; ++i) {
                TechnoTypeClass *type = 0;
                result = stream->Read(&type, 4, 0);
                if (FAILED(result)) return result;
                Queue.Add(type);
            }
            for (i = 0; i < count; ++i) Swizzle_Pointer(Queue[i]);
            Swizzle_Pointer(Owner);
            Swizzle_Pointer(Object);
            return S_OK;
        }
    }
    return result;
}

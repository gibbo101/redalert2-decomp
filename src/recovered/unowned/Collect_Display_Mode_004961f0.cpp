#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/vector_class.hpp"
#include "shared/directdraw.hpp"
HRESULT __stdcall Collect_Display_Mode_004961f0(DDSURFACEDESC *description,void *context)
{
    DDSURFACEDESC *copy=new DDSURFACEDESC;
    *copy=*description;
    ((DynamicVectorClass<DDSURFACEDESC *> *)context)->Add(copy);
    return 1;
}

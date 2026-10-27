// TechnoTypeClass::~TechnoTypeClass() (0x006DA950)
// Frees the owned cameo shapes, leaves the object list (0x00AC0CB0) and
// TechnoTypes; the member lists and the object type part follow.
#include "shared/techno_type.hpp"
#include "shared/object.hpp"
// @ref ??1ObjectTypeClass@@UAE@XZ=005d5b60
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Delete@?$DynamicVectorClass@PAVTechnoTypeClass@@@@QAE_NH@Z=006dfa70

// Frees the cameo shapes the type owns (inline).
static inline void Free_Cameo(TechnoTypeClass *type)
{
    if (type->CameoAllocated && type->CameoData) {
        delete type->CameoData;
        type->CameoData = 0;
        type->CameoAllocated = false;
    }
}
static inline void Free_Alt_Cameo(TechnoTypeClass *type)
{
    if (type->AltCameoAllocated && type->AltCameoData) {
        delete type->AltCameoData;
        type->AltCameoData = 0;
        type->AltCameoAllocated = false;
    }
}

TechnoTypeClass::~TechnoTypeClass()
{
    Free_Cameo(this);
    Free_Alt_Cameo(this);
    unknown_objects_ac0cb0.Delete(this);
    TechnoTypes.Delete(this);
}

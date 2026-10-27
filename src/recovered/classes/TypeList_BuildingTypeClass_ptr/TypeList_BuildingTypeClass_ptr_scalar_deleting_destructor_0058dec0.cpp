// TypeList<BuildingTypeClass *> scalar deleting destructor (0x0058DEC0; vtable 0x007A5E4C slot 0).
// Layout and behaviour: shared/type_list.hpp. ~TypeList is implicit; the
// expanded ~VectorClass stores the VectorClass vtable 0x007A2F08. The
// constructor below only makes the unit emit the vtable and with it this
// destructor; it is the copy at 0x0058DC70.
// @ref ??0?$TypeList@PAVBuildingTypeClass@@@@QAE@XZ=0058dc70
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PAVBuildingTypeClass@@@@UBE_NABV0@@Z=004f7010
// @ref ??_7?$TypeList@PAVBuildingTypeClass@@@@6B@=007a5e4c
// @ref ??_7?$VectorClass@PAVBuildingTypeClass@@@@6B@=007a2f08
// @ref ??_E?$TypeList@PAVBuildingTypeClass@@@@UAEPAXI@Z=0058dec0
// @ref ??_E?$VectorClass@PAVBuildingTypeClass@@@@UAEPAXI@Z=004f8490
// @ref ??_G?$TypeList@PAVBuildingTypeClass@@@@UAEPAXI@Z=0058dec0
// @ref ??_G?$VectorClass@PAVBuildingTypeClass@@@@UAEPAXI@Z=004f8490
// @ref ?Clear@?$DynamicVectorClass@PAVBuildingTypeClass@@@@UAEXXZ=004f6c00
// @ref ?Clear@?$VectorClass@PAVBuildingTypeClass@@@@UAEXXZ=004f7100
// @ref ?Fetch@?$VectorClass@PAVBuildingTypeClass@@@@UBEPAVBuildingTypeClass@@H@Z=004f6c50
// @ref ?ID@?$DynamicVectorClass@PAVBuildingTypeClass@@@@UAEHABQAVBuildingTypeClass@@@Z=004f7240
// @ref ?ID@?$DynamicVectorClass@PAVBuildingTypeClass@@@@UAEHPBQAVBuildingTypeClass@@@Z=004f6c30
// @ref ?ID@?$VectorClass@PAVBuildingTypeClass@@@@UAEHABQAVBuildingTypeClass@@@Z=004f7130
// @ref ?ID@?$VectorClass@PAVBuildingTypeClass@@@@UAEHPBQAVBuildingTypeClass@@@Z=004f7170
// @ref ?Resize@?$DynamicVectorClass@PAVBuildingTypeClass@@@@UAE_NHPBQAVBuildingTypeClass@@@Z=004f7190
// @ref ?Resize@?$VectorClass@PAVBuildingTypeClass@@@@UAE_NHPBQAVBuildingTypeClass@@@Z=004f7050
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#include "shared/type_list.hpp"

class BuildingTypeClass;

// An empty list growing by 10.
template <>
TypeList<BuildingTypeClass *>::TypeList()
{
}

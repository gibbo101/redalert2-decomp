// TypeList<VoxelAnimTypeClass *> scalar deleting destructor (0x00652FF0; vtable 0x007A90F8 slot 0).
// Layout and behaviour: shared/type_list.hpp. ~TypeList is implicit; the
// expanded ~VectorClass stores the VectorClass vtable 0x007A9118. The
// constructor below only makes the unit emit the vtable and with it this
// destructor; it is the copy at 0x00652A70.
// @ref ??0?$TypeList@PAVVoxelAnimTypeClass@@@@QAE@XZ=00652a70
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PAVVoxelAnimTypeClass@@@@UBE_NABV0@@Z=006531c0
// @ref ??_7?$TypeList@PAVVoxelAnimTypeClass@@@@6B@=007a90f8
// @ref ??_7?$VectorClass@PAVVoxelAnimTypeClass@@@@6B@=007a9118
// @ref ??_E?$TypeList@PAVVoxelAnimTypeClass@@@@UAEPAXI@Z=00652ff0
// @ref ??_E?$VectorClass@PAVVoxelAnimTypeClass@@@@UAEPAXI@Z=00654390
// @ref ??_G?$TypeList@PAVVoxelAnimTypeClass@@@@UAEPAXI@Z=00652ff0
// @ref ??_G?$VectorClass@PAVVoxelAnimTypeClass@@@@UAEPAXI@Z=00654390
// @ref ?Clear@?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@UAEXXZ=00652af0
// @ref ?Clear@?$VectorClass@PAVVoxelAnimTypeClass@@@@UAEXXZ=006532b0
// @ref ?Fetch@?$VectorClass@PAVVoxelAnimTypeClass@@@@UBEPAVVoxelAnimTypeClass@@H@Z=00652b40
// @ref ?ID@?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@UAEHABQAVVoxelAnimTypeClass@@@Z=006534a0
// @ref ?ID@?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@UAEHPBQAVVoxelAnimTypeClass@@@Z=00652b20
// @ref ?ID@?$VectorClass@PAVVoxelAnimTypeClass@@@@UAEHABQAVVoxelAnimTypeClass@@@Z=006532e0
// @ref ?ID@?$VectorClass@PAVVoxelAnimTypeClass@@@@UAEHPBQAVVoxelAnimTypeClass@@@Z=00653320
// @ref ?Resize@?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@UAE_NHPBQAVVoxelAnimTypeClass@@@Z=006533a0
// @ref ?Resize@?$VectorClass@PAVVoxelAnimTypeClass@@@@UAE_NHPBQAVVoxelAnimTypeClass@@@Z=00653200
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#include "shared/type_list.hpp"

class VoxelAnimTypeClass;

// An empty list growing by 10.
template <>
TypeList<VoxelAnimTypeClass *>::TypeList()
{
}

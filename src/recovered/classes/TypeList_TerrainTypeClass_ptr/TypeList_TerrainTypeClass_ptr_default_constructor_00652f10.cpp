// TypeList<TerrainTypeClass *>::TypeList, default constructor (0x00652F10; vtable 0x007A90B8).
// Layout and behaviour: shared/type_list.hpp.
// @ref ??0?$TypeList@PAVTerrainTypeClass@@@@QAE@XZ=00652f10
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PAVTerrainTypeClass@@@@UBE_NABV0@@Z=006538c0
// @ref ??_7?$TypeList@PAVTerrainTypeClass@@@@6B@=007a90b8
// @ref ??_7?$VectorClass@PAVTerrainTypeClass@@@@6B@=007a9158
// @ref ??_E?$TypeList@PAVTerrainTypeClass@@@@UAEPAXI@Z=00653090
// @ref ??_E?$VectorClass@PAVTerrainTypeClass@@@@UAEPAXI@Z=006544d0
// @ref ??_G?$TypeList@PAVTerrainTypeClass@@@@UAEPAXI@Z=00653090
// @ref ??_G?$VectorClass@PAVTerrainTypeClass@@@@UAEPAXI@Z=006544d0
// @ref ?Clear@?$DynamicVectorClass@PAVTerrainTypeClass@@@@UAEXXZ=00652f90
// @ref ?Clear@?$VectorClass@PAVTerrainTypeClass@@@@UAEXXZ=006539b0
// @ref ?Fetch@?$VectorClass@PAVTerrainTypeClass@@@@UBEPAVTerrainTypeClass@@H@Z=00652fe0
// @ref ?ID@?$DynamicVectorClass@PAVTerrainTypeClass@@@@UAEHABQAVTerrainTypeClass@@@Z=00653ba0
// @ref ?ID@?$DynamicVectorClass@PAVTerrainTypeClass@@@@UAEHPBQAVTerrainTypeClass@@@Z=00652fc0
// @ref ?ID@?$VectorClass@PAVTerrainTypeClass@@@@UAEHABQAVTerrainTypeClass@@@Z=006539e0
// @ref ?ID@?$VectorClass@PAVTerrainTypeClass@@@@UAEHPBQAVTerrainTypeClass@@@Z=00653a20
// @ref ?Resize@?$DynamicVectorClass@PAVTerrainTypeClass@@@@UAE_NHPBQAVTerrainTypeClass@@@Z=00653aa0
// @ref ?Resize@?$VectorClass@PAVTerrainTypeClass@@@@UAE_NHPBQAVTerrainTypeClass@@@Z=00653900
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#include "shared/type_list.hpp"

class TerrainTypeClass;

// An empty list growing by 10.
template <>
TypeList<TerrainTypeClass *>::TypeList()
{
}

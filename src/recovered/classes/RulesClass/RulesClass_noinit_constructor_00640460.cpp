// RulesClass::RulesClass(NoInitClass const &) (0x00640460)
// @ref ??0?$DynamicVectorClass@PAVSmudgeTypeClass@@@@QAE@IPBQAVSmudgeTypeClass@@@Z=00653730
// @ref ??0?$DynamicVectorClass@PAVTerrainTypeClass@@@@QAE@IPBQAVTerrainTypeClass@@@Z=00653a40
// The load constructor: only the members with their own constructors (the lists
// and colours) are built; RulesClass::Load then reads the rest.
// @ref ??_7?$DynamicVectorClass@H@@6B@=0079da94
// @ref ??_7?$DynamicVectorClass@PAVAircraftTypeClass@@@@6B@=007a31b8
// @ref ??_7?$DynamicVectorClass@PAVAnimTypeClass@@@@6B@=007a3b7c
// @ref ??_7?$DynamicVectorClass@PAVInfantryTypeClass@@@@6B@=007a3178
// @ref ??_7?$DynamicVectorClass@PAVUnitTypeClass@@@@6B@=007a3198
// @ref ??_7?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@6B@=007a9184
// @ref ??_E?$DynamicVectorClass@H@@UAEPAXI@Z=0046cf50
// @ref ??_E?$DynamicVectorClass@PAVAircraftTypeClass@@@@UAEPAXI@Z=004fb290
// @ref ??_E?$DynamicVectorClass@PAVAnimTypeClass@@@@UAEPAXI@Z=0050b260
// @ref ??_E?$DynamicVectorClass@PAVInfantryTypeClass@@@@UAEPAXI@Z=004faaf0
// @ref ??_E?$DynamicVectorClass@PAVUnitTypeClass@@@@UAEPAXI@Z=004faec0
// @ref ??_E?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@UAEPAXI@Z=006543e0
// @ref ??_G?$DynamicVectorClass@H@@UAEPAXI@Z=0046cf50
// @ref ??_G?$DynamicVectorClass@PAVAircraftTypeClass@@@@UAEPAXI@Z=004fb290
// @ref ??_G?$DynamicVectorClass@PAVAnimTypeClass@@@@UAEPAXI@Z=0050b260
// @ref ??_G?$DynamicVectorClass@PAVInfantryTypeClass@@@@UAEPAXI@Z=004faaf0
// @ref ??_G?$DynamicVectorClass@PAVUnitTypeClass@@@@UAEPAXI@Z=004faec0
// @ref ??_G?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@UAEPAXI@Z=006543e0
// @ref ??_7?$DynamicVectorClass@PAVSmudgeTypeClass@@@@6B@=007a91a4
// @ref ??_E?$DynamicVectorClass@PAVSmudgeTypeClass@@@@UAEPAXI@Z=00654480
// @ref ??_G?$DynamicVectorClass@PAVSmudgeTypeClass@@@@UAEPAXI@Z=00654480
// @ref ??_7?$DynamicVectorClass@PAVTerrainTypeClass@@@@6B@=007a91c4
// @ref ??_E?$DynamicVectorClass@PAVTerrainTypeClass@@@@UAEPAXI@Z=00654520
// @ref ??_G?$DynamicVectorClass@PAVTerrainTypeClass@@@@UAEPAXI@Z=00654520
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"

RulesClass::RulesClass(NoInitClass const &noinit) :
    RadColor(noinit),
    LineTrailColorOverride(noinit),
    ChronoBeamColor(noinit)
{
}

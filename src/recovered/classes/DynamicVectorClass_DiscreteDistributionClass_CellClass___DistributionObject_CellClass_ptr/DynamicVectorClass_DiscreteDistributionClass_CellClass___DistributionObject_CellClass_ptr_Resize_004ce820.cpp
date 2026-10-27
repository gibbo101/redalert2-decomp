// DynamicVectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass *>>::Resize (0x004CE820).
// Layout and behaviour: shared/vector_class.hpp.
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ??_I@YGXPAXIHP6EX0@Z@Z=0040af00
// @ref ??1?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@QAE@XZ=004ce940
// @ref ??_E?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@QAEPAXI@Z=004ceaf0
// @ref ??_E?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@QAEPAXI@Z=006c0890
// @ref ??_E?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@QAEPAXI@Z=004f8860
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"
#include "shared/discrete_distribution.hpp"
class AITriggerTypeClass;
class CellClass;
class BuildingTypeClass;


template class DynamicVectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass *> >;

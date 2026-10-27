// MapClass::MapClass() (0x00547960)
// Constructs the base screen and the member vectors (the zone, subzone and
// first cell-list vectors through their out-of-line constructors), clears
// the entry cells and sets +0x144 to 13.
#include "shared/map.hpp"
// @ref ??0GScreenClass@@QAE@XZ=004e08d0
// @ref ??_7MapClass@@6B@=007a593c

MapClass::MapClass()
{
    unknown_144 = 13;
}
// @ref ??0?$VectorClass@VCell@@@@QAE@IPBVCell@@@Z=0042d4a0
// @ref ??0?$VectorClass@USubzoneTrackingStruct@@@@QAE@IPBUSubzoneTrackingStruct@@@Z=0056cc40
// @ref ??0?$VectorClass@UZoneConnectionClass@@@@QAE@IPBUZoneConnectionClass@@@Z=0056cb90
// @ref ??_7?$DynamicVectorClass@VCell@@@@6B@=0079c5a0
// @ref ??_7?$DynamicVectorClass@USubzoneTrackingStruct@@@@6B@=007a59d8
// @ref ??_7?$DynamicVectorClass@UZoneConnectionClass@@@@6B@=007a59f8
// @ref ??_7?$VectorClass@PAVCellClass@@@@6B@=007a59b8
// @ref ??0SubzoneTrackingStruct@@QAE@XZ=0056b9b0
// @ref ??0ZoneConnectionClass@@QAE@XZ=0056b460
// @ref ??4?$DynamicVectorClass@USubzoneConnectionStruct@@@@QAEAAV0@ABV0@@Z=0056c9b0

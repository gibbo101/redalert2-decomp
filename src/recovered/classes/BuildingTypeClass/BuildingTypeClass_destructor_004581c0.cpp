// BuildingTypeClass::~BuildingTypeClass() (0x004581C0)
// Frees the owned images and leaves BuildingTypes.
#include "shared/building_type.hpp"
// @ref ??_7BuildingTypeClass@@6BIPersistStream@@@=0079d1f8
// @ref ??_7BuildingTypeClass@@6BIRTTITypeInfo@@@=0079d1dc
// @ref ??_7BuildingTypeClass@@6BINoticeSink@@@=0079d1d4
// @ref ??_7BuildingTypeClass@@6BINoticeSource@@@=0079d1cc
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ?BuildingTypes@@3V?$DynamicVectorClass@PAVBuildingTypeClass@@@@A=00a35cd8
// @ref ??_7?$VectorClass@U?$TPoint3D@H@@@@6B@=0079d2c0
// @ref ??1TechnoTypeClass@@UAE@XZ=006da950

BuildingTypeClass::~BuildingTypeClass()
{
    if (BuildupDataAllocated && BuildupData) {
        operator delete(BuildupData);
        BuildupData = 0;
        BuildupDataAllocated = false;
    }
    if (unknown_11d0 && unknown_11cc) {
        operator delete(unknown_11cc);
        unknown_11cc = 0;
        unknown_11d0 = false;
    }
    if (unknown_11a4 && unknown_11a0) {
        operator delete(unknown_11a0);
        unknown_11a0 = 0;
        unknown_11a4 = false;
    }
    if (unknown_11ac && unknown_11a8) {
        operator delete(unknown_11a8);
        unknown_11a8 = 0;
        unknown_11ac = false;
    }
    if (unknown_11b4 && unknown_11b0) {
        operator delete(unknown_11b0);
        unknown_11b0 = 0;
        unknown_11b4 = false;
    }
    if (unknown_11bc && unknown_11b8) {
        operator delete(unknown_11b8);
        unknown_11b8 = 0;
        unknown_11bc = false;
    }
    Unknown_006ECB90(this, true);
    BuildingTypes.Delete(this);
}

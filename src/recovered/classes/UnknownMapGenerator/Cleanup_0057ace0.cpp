// @ref ??_7?$VectorClass@VCell@@@@6B@=0079c5e0
// @ref ??_E?$VectorClass@VCell@@@@UAEPAXI@Z=0042d390
// @ref ??8?$VectorClass@VCell@@@@UBE_NABV0@@Z=0042ce10
// @ref ?Resize@?$VectorClass@VCell@@@@UAE_NHPBVCell@@@Z=0042cee0
// @ref ?Clear@?$VectorClass@VCell@@@@UAEXXZ=0042cfb0
// @ref ?ID@?$VectorClass@VCell@@@@UAEHABVCell@@@Z=0042cfe0
// @ref ?ID@?$VectorClass@VCell@@@@UAEHPBVCell@@@Z=0042d030
// @ref ?Fetch@?$VectorClass@VCell@@@@UBE?AVCell@@H@Z=0042cc60
// @ref ??_7MapSelect@@6B@=007a608c
// @ref ??_EMapSelect@@UAEPAXI@Z=0058fda0
// @ref ?Unknown_Slot1@MSEngine@@UAEXPAVSurface@@@Z=0058fd90
// @ref ?Unknown_Slot2@MapSelect@@UAEXXZ=0058fcc0
// @ref ??_7?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@6B@=007a8824
// @ref ??_E?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UAEPAXI@Z=00635040
// @ref ??8?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UBE_NABV0@@Z=00634c40
// @ref ?Resize@?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UAE_NHPBU?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@Z=00634ca0
// @ref ?Clear@?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UAEXXZ=00634da0
// @ref ?ID@?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UAEHABU?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@Z=00634dd0
// @ref ?ID@?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UAEHPBU?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@Z=00634e20
// @ref ?Fetch@?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UBE?AU?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@H@Z=00634c10
// @ref ??_7?$VectorClass@USubzoneConnectionStruct@@@@6B@=0079a76c
// @ref ??_E?$VectorClass@USubzoneConnectionStruct@@@@UAEPAXI@Z=0040b230
// @ref ??8?$VectorClass@USubzoneConnectionStruct@@@@UBE_NABV0@@Z=0040b070
// @ref ?Resize@?$VectorClass@USubzoneConnectionStruct@@@@UAE_NHPBUSubzoneConnectionStruct@@@Z=0040b0b0
// @ref ?Clear@?$VectorClass@USubzoneConnectionStruct@@@@UAEXXZ=0040b1a0
// @ref ?ID@?$VectorClass@USubzoneConnectionStruct@@@@UAEHABUSubzoneConnectionStruct@@@Z=0040b1d0
// @ref ?ID@?$VectorClass@USubzoneConnectionStruct@@@@UAEHPBUSubzoneConnectionStruct@@@Z=0040b210
// @ref ?Fetch@?$VectorClass@USubzoneConnectionStruct@@@@UBE?AUSubzoneConnectionStruct@@H@Z=0040b050
// @ref ??_7?$VectorClass@VCell@@@@6B@=0079c5e0
// @ref ??_E?$VectorClass@VCell@@@@UAEPAXI@Z=0042d390
// @ref ??8?$VectorClass@VCell@@@@UBE_NABV0@@Z=0042ce10
// @ref ?Resize@?$VectorClass@VCell@@@@UAE_NHPBVCell@@@Z=0042cee0
// @ref ?Clear@?$VectorClass@VCell@@@@UAEXXZ=0042cfb0
// @ref ?ID@?$VectorClass@VCell@@@@UAEHABVCell@@@Z=0042cfe0
// @ref ?ID@?$VectorClass@VCell@@@@UAEHPBVCell@@@Z=0042d030
// @ref ?Fetch@?$VectorClass@VCell@@@@UBE?AVCell@@H@Z=0042cc60
#include "shared/radar.hpp"
// Complete cleanup: 57ACE0..57ADF1, followed by14 NOP bytes through57ADFF.
#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/debug_printf.hpp"
extern DynamicVectorClass<MapRegionClass *> unknown_map_regions_a6fd28;
extern "C" char unknown_rmg_radar_message[];
// @ref ?unknown_map_regions_a6fd28@@=00a6fd28
// @ref _unknown_rmg_radar_message=007e1898
// @ref ??1MapRegionClass@@QAE@XZ=0056d970
void UnknownMapGenerator::Cleanup_0057ace0()
{
    unknown_304=0;
    unknown_308=0;
    if(unknown_map_cells_a70a24!=0) {
        delete [] unknown_map_cells_a70a24;
        unknown_map_cells_a70a24=0;
    }
    for(int index=(int)((unsigned int)unknown_map_regions_a6fd28.Count()-1u);index>=0;--index) {
        MapRegionClass *region=unknown_map_regions_a6fd28[index];
        if(region!=0)delete region;
    }
    unknown_map_region_next_index_a70a28=0;
    Map.Unknown_0054B2E0();
    Debug_Printf(unknown_rmg_radar_message);
    Map.RadarClass::unknown_slot29(Map.MapLocalSize);
    Map.Unknown_00630A00();
}

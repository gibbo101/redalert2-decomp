// Tactical.CPP file statics after the header statics: the tactical area
// rectangle (0x00ABE560, initializer 0x006A22D0), the dirty areas (0x00ABE5B0,
// 0x006A22F0, exit 0x006A2330), the object pixel table (0x00ABE5F8, empty
// initializer 0x006A2390), the shadow controls (0x00ABE528, 0x006A23A0, exit
// 0x006A23E0) and three scale factors from the cell diagonal and the 60 degree
// sine (0x006A2440, 0x006A2480; names hypotheses).
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/tactical.hpp"
#include "shared/tactical_lists.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/fast_math.hpp"
// @ref ?unknown_rect_abe560@@3VRect@@A=00abe560
// @ref ?DirtyAreas@TacticalLists@@2V?$DynamicVectorClass@UDirtyAreaStruct@@@@A=00abe5b0
// @ref ?unknown_tactical_pixels_abe5f8@@3PAUTacticalObjectPixel@@A=00abe5f8
// @ref ?ShadowControls@TacticalLists@@2V?$DynamicVectorClass@PAVShadowControlClass@@@@A=00abe528
// @ref ??_7?$DynamicVectorClass@UDirtyAreaStruct@@@@6B@=007ac4c4
// @ref ??_7?$VectorClass@UDirtyAreaStruct@@@@6B@=007ac4e4
// @ref ??_7?$DynamicVectorClass@PAVShadowControlClass@@@@6B@=007ac504
// @ref ??_7?$VectorClass@PAVShadowControlClass@@@@6B@=007ac524
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Fast_Sin@@YAMN@Z=004ba480
// @ref ??_E?$DynamicVectorClass@UDirtyAreaStruct@@@@UAEPAXI@Z=006ad010
// @ref ??_G?$DynamicVectorClass@UDirtyAreaStruct@@@@UAEPAXI@Z=006ad010
// @ref ?Resize@?$DynamicVectorClass@UDirtyAreaStruct@@@@UAE_NHPBUDirtyAreaStruct@@@Z=006acbe0
// @ref ?Clear@?$DynamicVectorClass@UDirtyAreaStruct@@@@UAEXXZ=006ac870
// @ref ?ID@?$DynamicVectorClass@UDirtyAreaStruct@@@@UAEHABUDirtyAreaStruct@@@Z=006acd00
// @ref ?ID@?$DynamicVectorClass@UDirtyAreaStruct@@@@UAEHPBUDirtyAreaStruct@@@Z=006ac8a0
// @ref ??_E?$VectorClass@UDirtyAreaStruct@@@@UAEPAXI@Z=006acfc0
// @ref ??_G?$VectorClass@UDirtyAreaStruct@@@@UAEPAXI@Z=006acfc0
// @ref ?Resize@?$VectorClass@UDirtyAreaStruct@@@@UAE_NHPBUDirtyAreaStruct@@@Z=006ac9f0
// @ref ?Clear@?$VectorClass@UDirtyAreaStruct@@@@UAEXXZ=006acb10
// @ref ?ID@?$VectorClass@UDirtyAreaStruct@@@@UAEHABUDirtyAreaStruct@@@Z=006acb40
// @ref ?ID@?$VectorClass@UDirtyAreaStruct@@@@UAEHPBUDirtyAreaStruct@@@Z=006acbb0
// @ref ??_E?$DynamicVectorClass@PAVShadowControlClass@@@@UAEPAXI@Z=006ad0b0
// @ref ??_G?$DynamicVectorClass@PAVShadowControlClass@@@@UAEPAXI@Z=006ad0b0
// @ref ?Resize@?$DynamicVectorClass@PAVShadowControlClass@@@@UAE_NHPBQAVShadowControlClass@@@Z=006acee0
// @ref ?Clear@?$DynamicVectorClass@PAVShadowControlClass@@@@UAEXXZ=006ac910
// @ref ?ID@?$DynamicVectorClass@PAVShadowControlClass@@@@UAEHABQAVShadowControlClass@@@Z=006acf90
// @ref ?ID@?$DynamicVectorClass@PAVShadowControlClass@@@@UAEHPBQAVShadowControlClass@@@Z=006ac940
// @ref ??_E?$VectorClass@PAVShadowControlClass@@@@UAEPAXI@Z=006ad060
// @ref ??_G?$VectorClass@PAVShadowControlClass@@@@UAEPAXI@Z=006ad060
// @ref ?Resize@?$VectorClass@PAVShadowControlClass@@@@UAE_NHPBQAVShadowControlClass@@@Z=006acda0
// @ref ?Clear@?$VectorClass@PAVShadowControlClass@@@@UAEXXZ=006ace50
// @ref ?ID@?$VectorClass@PAVShadowControlClass@@@@UAEHABQAVShadowControlClass@@@Z=006ace80
// @ref ?ID@?$VectorClass@PAVShadowControlClass@@@@UAEHPBQAVShadowControlClass@@@Z=006acec0
// @ref ??8?$VectorClass@UDirtyAreaStruct@@@@UBE_NABV0@@Z=006ac970
// @ref ?Fetch@?$VectorClass@UDirtyAreaStruct@@@@UBE?AUDirtyAreaStruct@@H@Z=006ac8d0
// @ref ??8?$VectorClass@PAVShadowControlClass@@@@UBE_NABV0@@Z=006acd60
// @ref ?Fetch@?$VectorClass@PAVShadowControlClass@@@@UBEPAVShadowControlClass@@H@Z=006ac960
// @ref _$E46=006a2330
// @ref _$E55=006a23e0
// @ref _$S47=00abe498
// @ref _$S56=00abe499
// @ref _unknown_scale_abe550=00abe550
// @ref _unknown_scale_abe490=00abe490
// @ref _unknown_scale_abe520=00abe520

Rect unknown_rect_abe560(0, 0, 0, 0);
DynamicVectorClass<DirtyAreaStruct> TacticalLists::DirtyAreas;
TacticalObjectPixel unknown_tactical_pixels_abe5f8[500];
DynamicVectorClass<ShadowControlClass *> TacticalLists::ShadowControls;
static double unknown_scale_abe550 = 60.0 / unknown_geometry_diagonal, unknown_scale_abe490 = Fast_Sin(unknown_geometry_angle60) * unknown_scale_abe550;
static double unknown_scale_abe520 = unknown_geometry_diagonal / (Fast_Sin(unknown_geometry_angle60) * 60.0);

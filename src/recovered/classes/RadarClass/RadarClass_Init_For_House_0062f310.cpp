// @ref ??_C@_0BO@NALL@RadarClass?3?3Init_For_House?$CI?$CJ?6?$AA@=007ee19c
// @ref ?unknown_name_7ee064@@3PBDB=007ee064
// @ref ?unknown_name_7ee068@@3PBDB=007ee068
// @ref ?unknown_int_ab6470@@3HA=00ab6470
// @ref ?unknown_int_ab6474@@3HA=00ab6474
// @ref ?unknown_int_ac1070@@3HA=00ac1070
// @ref ?unknown_int_ab6340@@3HA=00ab6340
// @ref ?unknown_int_ab6344@@3HA=00ab6344
// Radar Init_For_House0062F310, independent372+12.
#include "shared/radar.hpp"
#include "shared/shape_file.hpp"
#include "shared/hicolor.hpp"
#include "shared/id_source.hpp"
#include "shared/debug_printf.hpp"
// @ref ?RadarButton@RadarClass@@2VRTacticalClass@@A=00ab6478
void RadarClass::unknown_slot53()
{
    Debug_Printf("RadarClass::Init_For_House()\n");
    unknown_slot50();
    if(unknown_id_source_a3d290->unknown_2239) {
        unknown_11ec=(unknown_int_7add80-144)/2+4;
        unknown_int_ab6468=unknown_11e0+11;
        unknown_int_ab646c=unknown_11e4+4;
        unknown_int_ab6338=unknown_11e0+83;
    } else {
        unknown_11ec=(unknown_int_7add80-145)/2+5;
        unknown_int_ab6468=unknown_11e0+14;
        unknown_int_ab646c=unknown_11e4+5;
        unknown_int_ab6338=unknown_11e0+86;
    }
    unknown_int_ab633c=unknown_int_ab646c;
    RadarButton.X=unknown_11ec;
    unknown_shape_ab6350=Unknown_Load_Shape_00495270(unknown_name_7ee064,unknown_shape_ab6350_allocated);
    unknown_shape_ab6318=Unknown_Load_Shape_00495270(unknown_name_7ee068,unknown_shape_ab6318_allocated);
    unknown_int_ab6470=((ShapeFileStruct const *)unknown_shape_ab6350)->Width;
    unknown_int_ab6474=((ShapeFileStruct const *)unknown_shape_ab6350)->Height;
    unknown_int_ab6340=((ShapeFileStruct const *)unknown_shape_ab6318)->Width;
    unknown_int_ab6344=((ShapeFileStruct const *)unknown_shape_ab6318)->Height;
    RadarButton.unknown_28=(void *)unknown_int_ac1070;
    unknown_1204=Build_Hicolor_Pixel(unknown_color_ac1028.Get_Red(),unknown_color_ac1028.Get_Green(),unknown_color_ac1028.Get_Blue());
}

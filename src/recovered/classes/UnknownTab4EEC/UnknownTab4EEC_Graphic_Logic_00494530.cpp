// UnknownTab4EEC::Unknown_00494530(bool forced) (0x00494530): TibSun's CreditClass::Graphic_Logic.

void UnknownTab4EEC::Unknown_00494530(bool forced)
{
    if (forced || unknown_08) {
        int xx = unknown_surface_839948->Get_Width() / 2;

        if (unknown_0a && Rules->CreditTicks.Count() >= 2) {
            if (unknown_09) {
                Voc_Play(Rules->CreditTicks[0], 0.5f, 0x2000, 0);
            } else {
                Voc_Play(Rules->CreditTicks[1], 0.5f, 0x2000, 0);
            }
        }

        Map.Unknown_006A1710();

        int color = Build_Hicolor_Pixel(unknown_color_ac1028.Red, unknown_color_ac1028.Green, unknown_color_ac1028.Blue);
        Plain_Text_Print(L"%ld", unknown_surface_839948, &unknown_surface_839948->Get_Rect(), &Point2D(xx, 2), color, 0, 0x4108, unknown_04);

        unknown_08 = false;
        unknown_0a = false;
    }
}
// @ref ?Unknown_006A1710@TabClass@@QAEXXZ=006a1710
// @ref ??_C@_17EFBD@?$AA?$CF?$AAl?$AAd?$AA?$AA@=007d5904
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Plain_Text_Print@@YA?AUPoint2D@@PBGPAVSurface@@PBVRect@@PAU1@IIIZZ=00497a60
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Voc_Play@@YIPAUAudioEvent@@HMHPAUAudioEventHandle@@@Z=00713db0
// @ref ?unknown_color_ac1028@@3VRGBClass@@A=00ac1028
// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc
// @ref ?unknown_surface_839948@@3PAVSurface@@A=00839948

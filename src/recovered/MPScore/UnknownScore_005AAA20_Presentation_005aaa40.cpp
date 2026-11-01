// UnknownScore_005AAA20::Presentation_005AAA40() (0x005AAA40): loads the score art, draws the backdrop,
// runs the score dialog 0x108, draws the backdrop again and frees the art.

void UnknownScore_005AAA20::Presentation_005AAA40()
{
    Unknown_Load_Art_Pair_006F2A30(unknown_id_source_a3d290->unknown_2239 == false);
    Rect rect(0, 0, unknown_8523e0, unknown_8523e4);
    Unknown_6F3CD0(unknown_surface_839954, rect);
    Unknown_004E0C90(true, unknown_surface_839954, 0);
    unknown_dialog_box_5eab60(0x108, MP_Score_Dialog_Proc_005AAE40, 0);
    Unknown_6F3CD0(unknown_surface_839954, rect);
    Unknown_004E0C90(true, unknown_surface_839954, 0);
    Unknown_006F2AB0();
}
// @ref ?Unknown_004E0C90@@YIX_NPAVSurface@@H@Z=004e0c90
// @ref ?Unknown_006F2AB0@@YIXXZ=006f2ab0
// @ref ?Unknown_6F3CD0@@YIXPAVSurface@@ABVRect@@@Z=006f3cd0
// @ref ?Unknown_Load_Art_Pair_006F2A30@@YIXH@Z=006f2a30
// @ref ?unknown_8523e0@@3HA=008523e0
// @ref ?unknown_8523e4@@3HA=008523e4
// @ref ?unknown_dialog_box_5eab60@@YIHHP6GHPAUHWND__@@IIJ@Z_N@Z=005eab60
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_surface_839954@@3PAVDSurface@@A=00839954
// @ref ?MP_Score_Dialog_Proc_005AAE40@@YGHPAUHWND__@@IIJ@Z=005aae40

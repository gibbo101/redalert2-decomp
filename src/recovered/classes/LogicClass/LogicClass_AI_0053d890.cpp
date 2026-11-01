void LogicClass::AI()
{
    int index;

    unknown_frames_this_second_a6eb18++;

    for (LogicTriggerID = 0; LogicTriggerID < unknown_tags_866160.Count(); LogicTriggerID++) {
        TagClass *trig = unknown_tags_866160[LogicTriggerID];

        if (unknown_id_source_a3d290->unknown_223c) {
            if (trig->Spring(0x32, 0, unknown_geometry_k)) continue;
        }
        if (unknown_id_source_a3d290->unknown_222e) {
            if (trig->Spring(0x1B, 0, unknown_geometry_k)) continue;
            if (trig->Spring(0x1C, 0, unknown_geometry_k)) continue;
            if (trig->Spring(0x24, 0, unknown_geometry_k)) continue;
            if (trig->Spring(0x25, 0, unknown_geometry_k)) continue;
        }
        if (unknown_id_source_a3d290->unknown_222f) {
            if (trig->Spring(0x2D, 0, unknown_geometry_k)) continue;
            if (trig->Spring(0x2E, 0, unknown_geometry_k)) continue;
        }
        if (trig->Spring(0x0D, 0, unknown_geometry_k)) continue;
        if (trig->Spring(0x33, 0, unknown_geometry_k)) continue;

        if (unknown_id_source_a3d290->MissionTimer.Is_Active() && unknown_id_source_a3d290->MissionTimer == 0) {
            if (trig->Spring(0x0E, 0, unknown_geometry_k)) continue;
        }
    }

    if (unknown_id_source_a3d290->MissionTimer.Is_Active() && unknown_id_source_a3d290->MissionTimer == 0) {
        unknown_id_source_a3d290->MissionTimer.Stop();
        Map.Flag_To_Redraw(2);
    }
    unknown_id_source_a3d290->unknown_222e = false;
    unknown_id_source_a3d290->unknown_222d = false;
    unknown_id_source_a3d290->unknown_222f = false;
    unknown_id_source_a3d290->unknown_223c = false;

    if (Rules->ShroudGrow && Rules->ShroudRate != 0 && unknown_id_source_a3d290->unknown_7f8 == 0) {
        unknown_id_source_a3d290->unknown_7f8 = 900 * Rules->ShroudRate;
        Map.Unknown_0049CC20();
    }
    if (Frame % 120 == 0) {
        Map.Unknown_0055A300();
    }
    if (((SpecialClass *)unknown_id_source_a3d290)->FogOfWar && Rules->FogRate != 0 && unknown_id_source_a3d290->unknown_804 == 0) {
        unknown_id_source_a3d290->unknown_804 = 900 * Rules->FogRate;
        Map.Unknown_0049CD20();
    }

    if (unknown_id_source_a3d290->unknown_22b0 != unknown_id_source_a3d290->unknown_22ac && Rules->AmbientChangeRate != 0 && unknown_id_source_a3d290->unknown_828 == 0) {
        if (Unknown_0051FC60() || Unknown_0051FC70()) {
            unknown_id_source_a3d290->unknown_828 = unknown_id_source_a3d290->NukeAmbientChangeRate;
        } else {
            unknown_id_source_a3d290->unknown_828 = 900 * Rules->AmbientChangeRate;
        }
        unknown_id_source_a3d290->unknown_22b0 = MAX(unknown_id_source_a3d290->unknown_22b0, 0);
        int value = 100.0 * Rules->AmbientChangeStep;
        if (unknown_id_source_a3d290->unknown_22b0 < unknown_id_source_a3d290->unknown_22ac) {
            unknown_id_source_a3d290->unknown_22ac -= value;
            unknown_id_source_a3d290->unknown_22ac = MAX(unknown_id_source_a3d290->unknown_22ac, unknown_id_source_a3d290->unknown_22b0);
        } else {
            unknown_id_source_a3d290->unknown_22ac += value;
            unknown_id_source_a3d290->unknown_22ac = MIN(unknown_id_source_a3d290->unknown_22ac, unknown_id_source_a3d290->unknown_22b0);
        }
        unknown_id_source_a3d290->unknown_222f = true;
        Map.Unknown_0049E5E0();
        Map.Flag_To_Redraw(1);
    }

    TiberiumClass::Growth_AI();
    TiberiumClass::Spread_AI();
    BombList.Unknown_004361F0();
    KamikazeTracker.AI();

    DynamicVectorClass<TeamClass *> teams;
    for (index = 0; index < Teams.Count(); index++) {
        teams.Add(Teams[index]);
    }
    for (index = 0; index < teams.Count(); index++) {
        teams[index]->AI();
    }

    SpotLightClass::Update_All();
    LaserDrawClass::Update_All();
    Update_Storm_00520200();
    for (index = unknown_RadSiteClass_list_00ab6620.Count() - 1; index >= 0; index--) {
        unknown_RadSiteClass_list_00ab6620[index]->AI();
    }
    LightSourceClass::Unknown_00537830(6, false);
    EMPulseClass::Expire_004B4DF0();

    for (index = 0; index < Count(); index++) {
        ObjectClass *obj = (*this)[index];
        obj->AI();
    }

    if (unknown_game_mode_a3d298 != 0 && unknown_game_mode_a3d298 != 5) {
        for (index = 0; index < unknown_anims_a35e60.Count(); index++) {
            unknown_anims_a35e60[index]->AI();
        }
    }

    Unknown_00521A70();
    AlphaShapeClass::Update_All();

    Map.unknown_slot27();
    unknown_tactical_83996c->AI();

    for (index = 0; index < Factories.Count(); index++) {
        Factories[index]->AI();
    }

    for (index = 0; index < Houses.Count(); index++) {
        HouseClass *hptr = Houses[index];
        if (hptr) {
            hptr->AI();
        }
    }

    if (Map.Unknown_0049EC40() != 0) {
        CoordStruct coord = Map.Unknown_0049EC40()->Coord;
        unknown_tactical_83996c->Unknown_006A66B0(coord);
    }
}
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??_7?$DynamicVectorClass@PAVTeamClass@@@@6B@=007a24a4
// @ref ??_7?$VectorClass@PAVTeamClass@@@@6B@=007a24c4
// @ref ?AI@KamikazeTrackerClass@@QAEXXZ=005317c0
// @ref ?BombList@@3VBombListClass@@A=008322e0
// @ref ?Expire_004B4DF0@EMPulseClass@@SAXXZ=004b4df0
// @ref ?Factories@@3V?$DynamicVectorClass@PAVFactoryClass@@@@A=00a35e90
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0
// @ref ?Growth_AI@TiberiumClass@@SAXXZ=006e9f20
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?KamikazeTracker@@3VKamikazeTrackerClass@@A=00a6e428
// @ref ?LogicTriggerID@@3HA=00a35d44
// @ref ?Spread_AI@TiberiumClass@@SAXXZ=006e9490
// @ref ?Spring@TagClass@@QAE_NHPAVObjectClass@@VCell@@_NH@Z=006b3df0
// @ref ?Teams@@3V?$DynamicVectorClass@PAVTeamClass@@@@A=00866178
// @ref ?Unknown_004361F0@BombListClass@@QAEXXZ=004361f0
// @ref ?Unknown_0049E5E0@DisplayClass@@QAEXXZ=0049e5e0
// @ref ?Unknown_0049EC40@DisplayClass@@QAEPAVObjectClass@@XZ=0049ec40
// @ref ?Unknown_0051FC60@@YA_NXZ=0051fc60
// @ref ?Unknown_0051FC70@@YA_NXZ=0051fc70
// @ref ?Unknown_00521A70@@YAXXZ=00521a70
// @ref ?Unknown_00537830@LightSourceClass@@SIXH_N@Z=00537830
// @ref ?Unknown_0055A300@MapClass@@QAEXXZ=0055a300
// @ref ?Unknown_006A66B0@Tactical@@QAEXABUCoordStruct@@@Z=006a66b0
// @ref ?Update_All@AlphaShapeClass@@SAXXZ=0041f110
// @ref ?Update_All@LaserDrawClass@@SAXXZ=005333f0
// @ref ?Update_All@SpotLightClass@@SAXXZ=005dd6d0
// @ref ?Update_Storm_00520200@@YIXXZ=00520200
// @ref ?unknown_RadSiteClass_list_00ab6620@@3V?$DynamicVectorClass@PAVRadSiteClass@@@@A=00ab6620
// @ref ?unknown_anims_a35e60@@3V?$DynamicVectorClass@PAVAnimClass@@@@A=00a35e60
// @ref ?unknown_frames_this_second_a6eb18@@3IA=00a6eb18
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_slot27@MapClass@@QAEXXZ=0054e300
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref __real@8@4005c800000000000000=0079b7f0
// @ref ??0?$VectorClass@PAVTeamClass@@@@QAE@IPBQAVTeamClass@@@Z=0053e3d0

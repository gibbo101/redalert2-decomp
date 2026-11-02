void LogicClass::Environment_AI()
{
    if (Rules->ShroudGrow && Rules->ShroudRate != 0) {
        if (unknown_id_source_a3d290->unknown_7f8 == 0) {
            unknown_id_source_a3d290->unknown_7f8 = 900 * Rules->ShroudRate;
            Map.Unknown_0049CC20();
        }
    }
    if (((SpecialClass *)unknown_id_source_a3d290)->FogOfWar && Rules->FogRate != 0) {
        if (unknown_id_source_a3d290->unknown_804 == 0) {
            unknown_id_source_a3d290->unknown_804 = 900 * Rules->FogRate;
            Map.Unknown_0049CD20();
        }
    }
    for (int index = 0; index < Count(); index++) {
        FootClass *foot = (FootClass *)(*this)[index];
        bool is_foot;
        if (foot != 0) is_foot = foot->AbstractFlags.IsFoot;
        if (foot != 0 && is_foot && foot->Locomotor != 0 && !foot->unknown_325) {
            foot->Locomotor.Checked()->Process();
        }
    }
}
// @ref ?Frame@@3HA=00a40d2c
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_0049CC20@DisplayClass@@QAEXXZ=0049cc20
// @ref ?Unknown_0049CD20@DisplayClass@@QAEXXZ=0049cd20
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref __real@8@00000000000000000000=0079b610
// @ref __real@8@4008e100000000000000=0079b608

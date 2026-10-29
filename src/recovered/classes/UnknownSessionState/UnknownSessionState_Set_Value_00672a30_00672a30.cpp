// Sets the player's country (+0x134/+0x138; -2: random, a Multiplay country when update is set, else 0) and
// copies it to +0x124/+0x128.
void UnknownSessionState::Set_Value_00672a30(int value, bool update)
{
    if (value == -2) {
        if (update) {
            unknown_134 = Unknown_00672940();
        } else {
            unknown_134 = 0;
        }
        unknown_138 = -2;
    } else {
        unknown_134 = value;
        unknown_138 = -1;
    }
    unknown_124 = unknown_134;
    unknown_128 = unknown_138;
}
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?HouseTypes@@3V?$DynamicVectorClass@PAVHouseTypeClass@@@@A=00a35d08

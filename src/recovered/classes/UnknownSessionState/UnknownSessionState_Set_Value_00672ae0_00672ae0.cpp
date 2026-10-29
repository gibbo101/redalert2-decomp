// Sets the player's colour (+0x12C/+0x130; -2: random, an unused colour when update is set, else 0) and
// copies it to +0x11C/+0x120.
void UnknownSessionState::Set_Value_00672ae0(int value, bool update)
{
    if (value == -2) {
        if (update) {
            unknown_12c = Unknown_00672980();
        } else {
            unknown_12c = 0;
        }
        unknown_130 = -2;
    } else {
        unknown_12c = value;
        unknown_130 = -1;
    }
    unknown_11c = unknown_12c;
    unknown_120 = unknown_130;
}
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0

// Draws random colours (0-7) from the scenario's generator until one is not in use and returns it (expanded
// into 0x00672AE0).
int UnknownSessionState::Unknown_00672980()
{
    int color;
    do {
        color = unknown_id_source_a3d290->Random()(0, 7);
    } while (Unknown_006728D0(color));
    return color;
}
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0

// HRESULT __stdcall CNetUtilEventSink::OnGameresSent(HRESULT result) (0x0075D300, slot 5)
// In game mode 4 with online state 2, a pending game-results flag
// (0x00B2A7EC) is set to 1 and 0x00698D00 is told.
#include "shared/wol_sink.hpp"
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_a3d2a4@@3HA=00a3d2a4
// @ref ?unknown_b2a7ec@@3HA=00b2a7ec
// @ref ?Unknown_00698D00@@YIXH@Z=00698d00

HRESULT __stdcall CNetUtilEventSink::OnGameresSent(HRESULT result)
{
    if (unknown_game_mode_a3d298 == 4 && unknown_a3d2a4 == 2 && unknown_b2a7ec) {
        unknown_b2a7ec = 1;
        Unknown_00698D00(1);
    }
    return S_OK;
}

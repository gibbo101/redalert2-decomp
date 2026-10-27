#include "shared/wol_sink.hpp"
// @ref ?unknown_b2aaf8=00b2aaf8
// @ref ?unknown_b26568=00b26568
// @ref ?unknown_b29828=00b29828
// @ref ?unknown_b26898=00b26898
// @ref ?unknown_b299c0=00b299c0
// @ref ?unknown_b2a630=00b2a630
// @ref ?unknown_b2abd9=00b2abd9
// @ref ?unknown_a3d2a4=00a3d2a4
// @ref Unknown_0073FEE0=0073fee0
// @ref ?Unknown_0075B590=0075b590
// @ref ?Unknown_0075B2D0=0075b2d0
// @ref Debug_Printf=004068f0
HRESULT __stdcall CNetUtilEventSink::OnPing(HRESULT result, int time, unsigned long ip, int handle)
{
    if (unknown_b2abd9 && unknown_b2a630) {
        if (result == 0 && time >= 0 && time < 1000) {
            ++unknown_b2aaf8;
            return 0;
        }
    } else if (Is_Online_Session()) {
        Debug_Printf("Received Ping\n");
        ++unknown_b26568;
        if (unknown_b26568 >= unknown_b29828) {
            if (unknown_b26898 == 4 || unknown_b26898 == 5) Unknown_0075B590();
            Unknown_0075B2D0();
            return 0;
        }
    } else if (unknown_b299c0) {
        Unknown_0073FEE0(0, false);
    }
    return 0;
}

// @ref ??_C@_0P@DKFA@Received?5Ping?6?$AA@=007fdbc4

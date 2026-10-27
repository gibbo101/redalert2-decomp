#include "shared/wol_sink.hpp"
// @ref ?Create@WDTState@@=0072beb0
// @ref ?Is_Valid@WDTState@@=0072c390
// @ref ?Is_Previous_Cycle@WDTState@@=0072c3a0
// @ref ?unknown_b2650c=00b2650c
// @ref ?unknown_b26524=00b26524
// @ref ?unknown_b292dc=00b292dc
// @ref ?WDT_Store_Current_00769520=00769520
// @ref ?WDT_Store_Previous_007695a0=007695a0
// @ref ??_7?$rc_ptr@VWDTState@@@@6B@=007af1a4
// @ref ??1rc_ptr_base@@=00639510
HRESULT __stdcall CNetUtilEventSink::OnWDTState(HRESULT result, unsigned char *data, int length)
{
    if (result >= 0 && length > 0) {
        rc_ptr<WDTState> state = WDTState::Create(data);
        if (state.Get() && state->Is_Valid()) {
            if (state->Is_Previous_Cycle()) {
                Debug_Printf("OnWDTState: Previous cycle data received\n");
                WDT_Store_Previous_007695a0(state);
                SetEvent(unknown_b26524);
            } else {
                Debug_Printf("OnWDTState: Current cycle data received\n");
                unknown_b292dc = time(0) + state->unknown_28;
                WDT_Store_Current_00769520(state);
                SetEvent(unknown_b26524);
            }
        } else {
            Debug_Printf("OnWDTState: NACK received from server\n");
            SetEvent(unknown_b26524);
        }
        return S_OK;
    }
    SetEvent(unknown_b2650c);
    return S_OK;
}
// @ref ??_C@_0CH@MEIK@OnWDTState?3?5NACK?5received?5from?5s@=007fdaf8
// @ref ??_C@_0CJ@PDBB@OnWDTState?3?5Current?5cycle?5data?5r@=007fdb20
// @ref ??_C@_0CK@ILJO@OnWDTState?3?5Previous?5cycle?5data?5@=007fdb4c

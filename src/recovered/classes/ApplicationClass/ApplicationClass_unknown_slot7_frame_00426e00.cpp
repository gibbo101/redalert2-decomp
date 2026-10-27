// HRESULT __stdcall ApplicationClass::unknown_slot7_frame(long *frame) -- 0x00426E00
// IApplication slot: the scenario's elapsed-time timer value (+0x614).
#include "shared/application.hpp"
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430

HRESULT __stdcall ApplicationClass::unknown_slot7_frame(long *frame)
{
    if (frame == 0) {
        return E_POINTER;
    }
    *frame = unknown_id_source_a3d290->Elapsed_Time().Time();
    return S_OK;
}

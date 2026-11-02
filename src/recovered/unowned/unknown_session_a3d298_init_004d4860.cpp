// Dynamic initializer of unknown_session_a3d298 (0x004D4860, _$E; Westwood's Session):
// runs the constructor 0x0066E380, then registers the atexit destructor (0x004D4880, the
// following _$E draft, emitted by this definition) that runs ~UnknownSessionState
// 0x0066EB20. Owning unit: the global-object block around 0x004D4500.
#define RA2_SESSION_STATE_DEFINED
#include "shared/session_state.hpp"
#include "shared/unknown_globals.hpp"
// @ref ??0UnknownSessionState@@QAE@XZ=0066e380
// @ref ??1UnknownSessionState@@QAE@XZ=0066eb20
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref _atexit=0078298a

UnknownSessionState unknown_session_a3d298;

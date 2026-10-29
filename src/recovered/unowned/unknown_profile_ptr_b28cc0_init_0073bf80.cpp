// Dynamic initializer of a global rc_ptr<PlayerProfile> (0x0073BF80, _$E):
// constructs unknown_profile_ptr_b28cc0 (0x00B28CC0) and registers its atexit
// destructor (0x0073BFA0, the following _$E draft, emitted by this
// definition). Its pointer (+0x04) is what the WOL code reads as
// unknown_profile_b28cc4 (shared/wol_sink.hpp). The owning unit is not
// identified yet.
#include "shared/reference_counted.hpp"
class PlayerProfile;
// @ref ??0rc_ptr_base@@QAE@XZ=006394e0
// @ref ??1rc_ptr_base@@UAE@XZ=00639510
// @ref ??_7?$rc_ptr@VPlayerProfile@@@@6B@=007af54c
// @ref ??_G?$rc_ptr@VPlayerProfile@@@@UAEPAXI@Z=0073a0c0
// @ref ??_E?$rc_ptr@VPlayerProfile@@@@UAEPAXI@Z=0073a0c0
// @ref _atexit=0078298a
// @ref _$E2=0073bfa0
// @ref ?unknown_profile_ptr_b28cc0@@3V?$rc_ptr@VPlayerProfile@@@@A=00b28cc0

rc_ptr<PlayerProfile> unknown_profile_ptr_b28cc0;

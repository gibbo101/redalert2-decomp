// The World Domination Tour state and campaign last stored by the WOL
// callbacks (WDT_Store_Current 0x00769520 and WDT_Store_Previous 0x007695A0
// set them). Their dynamic initializers and atexit destructors (_$E,
// 0x00769410-0x00769503) are emitted by these definitions; the other rows of
// the unit have no source of their own. The owning unit is not identified yet.
#include "shared/wdt_state.hpp"
namespace WorldDominationTour { class Campaign; }
// @ref ??0rc_ptr_base@@QAE@XZ=006394e0
// @ref ??1rc_ptr_base@@UAE@XZ=00639510
// @ref ??_7?$rc_ptr@VWDTState@@@@6B@=007af1a4
// @ref ??_G?$rc_ptr@VWDTState@@@@UAEPAXI@Z=00728fa0
// @ref ??_E?$rc_ptr@VWDTState@@@@UAEPAXI@Z=00728fa0
// @ref ??_7?$rc_ptr@VCampaign@WorldDominationTour@@@@6B@=007aefdc
// @ref ??_G?$rc_ptr@VCampaign@WorldDominationTour@@@@UAEPAXI@Z=00726b40
// @ref ??_E?$rc_ptr@VCampaign@WorldDominationTour@@@@UAEPAXI@Z=00726b40
// @ref _atexit=0078298a
// @ref _$E2=00769430
// @ref _$E7=00769470
// @ref _$E12=007694b0
// @ref _$E17=007694f0
// @ref _$E2=00769430
// @ref _$E7=00769470
// @ref _$E12=007694b0
// @ref _$E17=007694f0
// @ref ?WDT_Current_State_b2ad68@@3V?$rc_ptr@VWDTState@@@@A=00b2ad68
// @ref ?WDT_Previous_State_b2ad80@@3V?$rc_ptr@VWDTState@@@@A=00b2ad80
// @ref ?WDT_Current_Campaign_b2ad78@@3V?$rc_ptr@VCampaign@WorldDominationTour@@@@A=00b2ad78
// @ref ?WDT_Previous_Campaign_b2ad88@@3V?$rc_ptr@VCampaign@WorldDominationTour@@@@A=00b2ad88

rc_ptr<WDTState> WDT_Current_State_b2ad68;
rc_ptr<WDTState> WDT_Previous_State_b2ad80;
rc_ptr<WorldDominationTour::Campaign> WDT_Current_Campaign_b2ad78;
rc_ptr<WorldDominationTour::Campaign> WDT_Previous_Campaign_b2ad88;

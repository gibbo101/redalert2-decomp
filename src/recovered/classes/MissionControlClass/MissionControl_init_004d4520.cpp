// Dynamic initializer of MissionControl (0x004D4520, _$E): constructs the 30 mission
// control entries (0x20 bytes each) in place; MissionControlClass has no destructor, so no
// atexit row follows. Owning unit: the global-object block around 0x004D4500.
#include "shared/mission.hpp"
// @ref ??0MissionControlClass@@QAE@XZ=00594dd0
// @ref ?MissionControl@@3PAVMissionControlClass@@A=00a403b0

MissionControlClass MissionControl[30];

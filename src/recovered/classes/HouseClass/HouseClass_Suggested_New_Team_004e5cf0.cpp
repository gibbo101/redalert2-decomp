// TypeList<TeamTypeClass const *> HouseClass::Suggested_New_Team(bool alerted) (0x004E5CF0)
// The team types this house may make now (RA's HouseClass::Suggested_New_Team,
// which returned one type; the list comes from TeamTypeClass 0x006BED50; AI
// expands it).
#include "shared/techno.hpp"
#include "shared/team_type.hpp"
// @ref ??_7?$TypeList@PBVTeamTypeClass@@@@6B@=007a2ec4
// @ref ??_7?$VectorClass@PBVTeamTypeClass@@@@6B@=007a2ee4
// @ref ??_E?$TypeList@PBVTeamTypeClass@@@@UAEPAXI@Z=004f6ee0
// @ref ??_G?$TypeList@PBVTeamTypeClass@@@@UAEPAXI@Z=004f6ee0
// @ref ??_E?$VectorClass@PBVTeamTypeClass@@@@UAEPAXI@Z=004f8710
// @ref ??_G?$VectorClass@PBVTeamTypeClass@@@@UAEPAXI@Z=004f8710
// @ref ??8?$VectorClass@PBVTeamTypeClass@@@@UBE_NABV0@@Z=004f7be0
// @ref ?Resize@?$DynamicVectorClass@PBVTeamTypeClass@@@@UAE_NHPBQBVTeamTypeClass@@@Z=004f7d60
// @ref ?Clear@?$DynamicVectorClass@PBVTeamTypeClass@@@@UAEXXZ=004f6da0
// @ref ?ID@?$DynamicVectorClass@PBVTeamTypeClass@@@@UAEHABQBVTeamTypeClass@@@Z=004f7e10
// @ref ?ID@?$DynamicVectorClass@PBVTeamTypeClass@@@@UAEHPBQBVTeamTypeClass@@@Z=004f6dd0
// @ref ?Fetch@?$VectorClass@PBVTeamTypeClass@@@@UBEPBVTeamTypeClass@@H@Z=004f6df0
// @ref ?Resize@?$VectorClass@PBVTeamTypeClass@@@@UAE_NHPBQBVTeamTypeClass@@@Z=004f7c20
// @ref ?Clear@?$VectorClass@PBVTeamTypeClass@@@@UAEXXZ=004f7cd0
// @ref ?ID@?$VectorClass@PBVTeamTypeClass@@@@UAEHABQBVTeamTypeClass@@@Z=004f7d00
// @ref ?ID@?$VectorClass@PBVTeamTypeClass@@@@UAEHPBQBVTeamTypeClass@@@Z=004f7d40
// @ref ?Suggested_New_Teams@TeamTypeClass@@SI?AV?$TypeList@PBVTeamTypeClass@@@@PAVHouseClass@@_N@Z=006bed50

TypeList<TeamTypeClass const *> HouseClass::Suggested_New_Team(bool alerted)
{
    TypeList<TeamTypeClass const *> list = TeamTypeClass::Suggested_New_Teams(this, alerted);
    return list;
}

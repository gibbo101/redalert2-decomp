// Construct the campaign's disputed territories and restore progress for the current cycle (0x00725F40).
#include "shared/wdt_campaign.hpp"
#include "shared/crt_string.hpp"
// @ref ??_7?$DynamicVectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@6B@=007af004
namespace WorldDominationTour {
Campaign::Campaign(Wstring const &name, rc_ptr<CampaignProperties> const &properties)
    : Properties(properties), TheHistory(History::Create(properties->TheWDTState)),
      Conflicts(4), PlayerFaction(0), Name(name)
{
    memset(LastDay, 0, sizeof(LastDay));
    if (properties->TheWDTState.Get() != 0) {
        rc_ptr<State> state = TheHistory->Get_State(properties->Last_Conflict());
        unsigned index = properties->TheWDTState->unknown_20;
        while (index--) {
            if (state->Owner_Of(index) == 1) {
                DynamicVectorClass<rc_ptr<WDTTerritory> > &territories = properties->TheWDTState->Territories;
                rc_ptr<WDTTerritory> territory = index < (unsigned)territories.Count()
                    ? territories[index] : rc_ptr<WDTTerritory>();
                if (territory.Get() != 0) {
                    rc_ptr<Conflict> conflict = Conflict::Create(territory);
                    Conflicts.Add(conflict);
                }
            }
        }
    }
    CDFileClass file("WDTHist.INI");
    if (file.Is_Available()) {
        INIClass ini;
        ini.Load(file, false);
        file.Close();
        int saved_id;
        {
            Wstring key("CampaignID");
            saved_id = ini.Get_Int(Name, key, -1);
        }
        ID = saved_id < 0 ? 0 : saved_id;
        if (ID == properties->unknown_18()) {
            for (int faction = 0; faction < 4; faction++) {
                Wstring key = Wstring("LastDay") + Faction_Code(faction);
                int day = ini.Get_Int(Name, key, 0);
                LastDay[faction] = day < 0 ? 0 : day;
            }
            {
                Wstring key("PlayerFaction");
                PlayerFaction = ini.Get_Int(Name, key, PlayerFaction);
            }
        } else {
            memset(LastDay, 0, sizeof(LastDay));
        }
    }
}
}
// @ref ??0?$VectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@QAE@IPBV?$rc_ptr@VConflict@WorldDominationTour@@@@@Z=00727040

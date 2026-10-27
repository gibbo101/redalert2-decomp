// void WorldDominationTour::Campaign::Set_Player_Faction(int faction) (0x007267C0)
// Keeps a changed faction and writes it to WDTHist.ini as PlayerFaction.
#include "shared/wdt_campaign.hpp"

namespace WorldDominationTour {

void Campaign::Set_Player_Faction(int faction)
{
    if (PlayerFaction != faction) {
        PlayerFaction = faction;
        INIClass ini;
        Load_History(ini);
        {
            Wstring key("PlayerFaction");
            ini.Put_Int(Name, key, PlayerFaction);
        }
        CDFileClass file;
    file.Open("WDTHist.ini", FILE_RIGHTS_WRITE);
    ini.Save(file);
    }
}

}

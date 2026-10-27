// void WorldDominationTour::Campaign::Reset_Progress() (0x00726580)
// Writes CampaignID 0 and LastDay 0 for every faction to WDTHist.ini.
// No callers in the executable.
#include "shared/wdt_campaign.hpp"

namespace WorldDominationTour {

void Campaign::Reset_Progress()
{
    INIClass ini;
    Load_History(ini);
    {
        Wstring key("CampaignID");
        ini.Put_Int(Name, key, 0);
    }
    for (int faction = 0; faction < 4; faction++) {
        Wstring key = Wstring("LastDay") + Faction_Code(faction);
        ini.Put_Int(Name, key, 0);
    }
    CDFileClass file;
    file.Open("WDTHist.ini", FILE_RIGHTS_WRITE);
    ini.Save(file);
}

}

// void WorldDominationTour::Campaign::Save_Progress(int faction) (0x007263B0)
// Takes the properties' CampaignID and last conflict as the saved progress
// of the faction and writes both to WDTHist.ini.
#include "shared/wdt_campaign.hpp"

namespace WorldDominationTour {

void Campaign::Save_Progress(int faction)
{
    ID = Properties->unknown_18();
    LastDay[faction] = Properties->Last_Conflict();
    INIClass ini;
    Load_History(ini);
    Wstring key = Wstring("LastDay") + Faction_Code(faction);
    {
        Wstring id_key("CampaignID");
        ini.Put_Int(Name, id_key, ID);
    }
    ini.Put_Int(Name, key, LastDay[faction]);
    CDFileClass file;
    file.Open("WDTHist.ini", FILE_RIGHTS_WRITE);
    ini.Save(file);
}

}

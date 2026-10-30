// WorldDominationTour::Campaign (Campaign.cpp, unit 0x00725BF0-0x007270FF),
// separate from shared/world_domination_tour.hpp so that the other units do
// not instantiate DynamicVectorClass<rc_ptr<Conflict>> (its delete[] would
// turn their rc_ptr<Conflict> scalar deleting destructor into a vector one).
#ifndef RA2_SHARED_WDT_CAMPAIGN_LAYOUT_HPP
#define RA2_SHARED_WDT_CAMPAIGN_LAYOUT_HPP

#include "shared/reference_counted.hpp"
#include "shared/vector_class.hpp"
#include "shared/vector_cursor.hpp"
#include "shared/wstring.hpp"

namespace WorldDominationTour {
class Conflict;
class History;
class CampaignProperties;

typedef DynamicVectorClass<rc_ptr<Conflict> > ConflictList;
typedef VectorCursor<rc_ptr<Conflict>, ConflictList> ConflictCursor;

// RTTI vtable 0x007AEFF4; Campaign.cpp (unit 0x00725BF0-0x007270FF).
// The progress of one campaign, saved in WDTHist.ini under the campaign's
// name: CampaignID, LastDay<faction code> (four factions), PlayerFaction.
//   +0x08 rc_ptr<CampaignProperties> Properties
//   +0x10 rc_ptr<History> TheHistory  (History::Create of the properties' WDTState)
//   +0x18 DynamicVectorClass<rc_ptr<Conflict>> Conflicts  (the territories
//         the last state gives owner 1, in reverse order)
//   +0x30 int ID (CampaignID), +0x34 int LastDay[4], +0x44 int PlayerFaction
//   +0x48 Wstring Name
//   size 0x4C
class Campaign : public ReferenceCounted {
public:
    Campaign(Wstring const &name, rc_ptr<CampaignProperties> const &properties);   // 0x00725F40
    virtual ~Campaign();                                            // 0x007262E0

    static rc_ptr<Campaign> __fastcall Create(Wstring const &name, rc_ptr<CampaignProperties> const &properties);   // 0x00725EE0
    static int __fastcall Saved_ID(Wstring const &name);            // 0x00725DE0 (-1 without WDTHist.INI)
    bool ID_Differs() const;                                        // 0x00726350 (saved ID is not the properties' one)
    bool Progress_Differs(int faction) const;                       // 0x00726370
    int Last_Day(int faction) const;                                // 0x007263A0
    void Save_Progress(int faction);                                // 0x007263B0
    void Reset_Progress();                                          // 0x00726580
    ConflictCursor Find_Conflict(int index);                        // 0x00726730
    void Set_Player_Faction(int faction);                           // 0x007267C0
    void Load_History(INIClass &ini);                               // 0x00726930
    int Player_Faction() const { return PlayerFaction; }

    rc_ptr<CampaignProperties> Properties;                          // +0x08
    rc_ptr<History> TheHistory;                                     // +0x10
    ConflictList Conflicts;                                         // +0x18
    int ID;                                                         // +0x30
    int LastDay[4];                                                 // +0x34
    int PlayerFaction;                                              // +0x44
    Wstring Name;                                                   // +0x48
};


}

#endif

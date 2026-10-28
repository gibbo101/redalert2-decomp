// The cooperative campaign score screens (RTTI CampaignScoreClass, vtable 0x0079D724,
// 8 bytes; CampaignEndScoreClass, vtable 0x0079D730, 4 bytes). Each has a virtual
// destructor and one virtual that shows the screen for the players' scores.
#ifndef RA2_SHARED_CAMPAIGN_SCORE_HPP
#define RA2_SHARED_CAMPAIGN_SCORE_HPP

#include "shared/vector_class.hpp"

class MPlayerScoreType;

// Shown after each cooperative campaign map.
class CampaignScoreClass {
public:
    CampaignScoreClass();                                        // 0x00465BF0
    virtual ~CampaignScoreClass();                               // 0x00465C10 (scalar deleting 0x00467B00)
    // Shows the map's scores: the game time, whether more maps follow, the difficulty
    // (0-2, -1 unknown) and the campaign name.
    virtual void Presentation(DynamicVectorClass<MPlayerScoreType *> scores, int time, bool more,
        int difficulty, wchar_t const *name);                    // 0x00466A50

    int unknown_04;                                              // +0x04
};

// Shown when the cooperative campaign ends.
class CampaignEndScoreClass {
public:
    CampaignEndScoreClass();                                     // 0x00467200
    virtual ~CampaignEndScoreClass();                            // 0x00467230 (scalar deleting 0x00467B20)
    // Shows the campaign's total scores: the time, the difficulty, the campaign type + 1
    // and the campaign name.
    virtual void Presentation(DynamicVectorClass<MPlayerScoreType *> scores, int time, int difficulty,
        int campaign, wchar_t const *name);                      // 0x00467A20
};

// Set by the score screens (read and cleared by MPCooperative slot 36; 0x00850504).
extern bool unknown_score_850504;

#endif

// Original name: RTTI DynamicVectorClass<MPlayerScoreType*> at007A68E4;
// caller005A560A passes that vector to0048E710, which allocates these0x70 records.
#ifndef RA2_SHARED_SCORE_SNAPSHOT_HPP
#define RA2_SHARED_SCORE_SNAPSHOT_HPP
class MPlayerScoreType {
public:
    unsigned short Name[20];
    int Scheme;                 // +28
    int Winner;                 // +2C
    union { int Lost; int LostCounts[4]; };     // +0x30 per game (Red Alert's Lost[MAX_MULTI_GAMES])
    union { int Kills; int KillCounts[4]; };    // +0x40
    union { int Built; int BuiltCounts[4]; };   // +0x50
    union { int Score; int ScoreCounts[4]; };   // +0x60
};
typedef char MPlayerScoreType_size[(sizeof(MPlayerScoreType)==0x70)?1:-1];
#endif

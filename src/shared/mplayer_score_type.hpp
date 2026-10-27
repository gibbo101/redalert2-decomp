// Original name: RTTI DynamicVectorClass<MPlayerScoreType*> at007A68E4;
// caller005A560A passes that vector to0048E710, which allocates these0x70 records.
#ifndef RA2_SHARED_SCORE_SNAPSHOT_HPP
#define RA2_SHARED_SCORE_SNAPSHOT_HPP
class MPlayerScoreType {
public:
    unsigned short Name[20];
    int Scheme;                 // +28
    int Winner;                 // +2C
    int Lost;
    char unknown_34[0x40-0x34];
    int Kills;
    char unknown_44[0x50-0x44];
    int Built;
    char unknown_54[0x60-0x54];
    int Score;
    char unknown_64[0x70-0x64];
};
typedef char MPlayerScoreType_size[(sizeof(MPlayerScoreType)==0x70)?1:-1];
#endif

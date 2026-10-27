#ifndef RA2_SHARED_WWCRC_ENGINE_HPP
#define RA2_SHARED_WWCRC_ENGINE_HPP
// CRC accumulator (hypothesis: Westwood's WWCRCEngine).
class WWCRCEngine {
public:
    void operator()(char datum);                // 0x00493DF0
    void operator()(bool datum);                // 0x00493E80 (stores datum != 0)
    void operator()(short datum);               // 0x00493F10 (FootClass::Compute_CRC)
    void operator()(long datum);                // 0x00493F30
    void operator()(char const *string);        // 0x00493F90
    long operator()(void const *buffer, int length);   // 0x00493FC0
    void operator()(float datum);               // 0x00493F50 (ParticleSystemClass::Compute_CRC; hypothesis)
    void operator()(double datum);              // 0x00493F70 (AnimTypeClass, VoxelAnimTypeClass Compute_CRC; hypothesis)
};

#endif

// RandomStraw: a Straw that produces cryptographically scrambled random
// bytes.
//
// Name from RTTI (vtable 0x007A8EBC, base Straw); methods in RndStraw.cpp
// (0x0063D2D0+). The 32 generators are seeded bit by bit (2048 bits in all,
// e.g. from timing noise); when the seed is complete it is scrambled with
// SHA-1. Get draws one byte from each generator in turn.
#ifndef RA2_SHARED_RANDOM_STRAW_HPP
#define RA2_SHARED_RANDOM_STRAW_HPP

#include "shared/straw.hpp"
#include "shared/random3.hpp"

class RandomStraw : public Straw {
public:
    RandomStraw();                                      // 0x0063D2D0
    virtual ~RandomStraw();                             // 0x0063D320
    virtual int Get(void *buffer, int length);          // 0x0063D830

    void Reset();                                       // 0x0063D350
    void Seed_Bit(int seed);                            // 0x0063D390
    void Seed_Byte(char seed);                          // 0x0063D470
    void Seed_Short(short seed);                        // 0x0063D580
    void Seed_Long(long seed);                          // 0x0063D680
    int Seed_Bits_Needed() const;                       // 0x0063D370

    int SeedBits;               // +0x0C seed bits supplied so far
    int Current;                // +0x10 generator for the next byte
    Random3Class Random[32];    // +0x14 generators (their state is the seed)

private:
    void Scramble_Seed();                               // 0x0063D790
};

// The generator Init_Random seeds from the system time (0x00A40778; Red Alert's CryptRandom).
extern RandomStraw CryptRandom;

#endif

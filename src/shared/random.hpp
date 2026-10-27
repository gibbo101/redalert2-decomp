// Westwood's pseudo-random number generators (Random.cpp, 0x00638700+).
//
// RandomClass: 32-bit linear congruential generator returning 15 bits.
// Random2Class: 250-entry XOR lagged-Fibonacci table seeded from a
//   Random3Class (YRpp calls it Randomizer).
// Random3Class: counter-based generator using the "psdes" mixing function
//   with the Mix1/Mix2 constant tables (original data at 0x007EE4AC and
//   0x007EE4FC).
// The ranged operator()(min, max) of each class expands the
// Pick_Random_Number template inline.
#ifndef RA2_SHARED_RANDOM_HPP
#define RA2_SHARED_RANDOM_HPP

// A random number in [minval, maxval] drawn with rejection sampling from the
// generator's low bits.
template<class T>
int Pick_Random_Number(T &generator, int minval, int maxval)
{
    if (minval == maxval) {
        return minval;
    }

    if (minval > maxval) {
        int temp = minval;
        minval = maxval;
        maxval = temp;
    }

    int magnitude = maxval - minval;
    int highbit = T::SIGNIFICANT_BITS - 1;
    while ((magnitude & (1 << highbit)) == 0 && highbit > 0) {
        highbit--;
    }

    int mask = ~((~0L) << (highbit + 1));
    int pick = magnitude + 1;
    while (pick > magnitude) {
        pick = generator() & mask;
    }
    return pick + minval;
}

class RandomClass {
public:
    RandomClass(unsigned seed = 0) : Seed(seed) {}

    operator int() { return operator()(); }
    int operator()();                               // 0x00638700
    int operator()(int minval, int maxval);         // 0x00638720

    enum {
        SIGNIFICANT_BITS = 15
    };

protected:
    enum {
        MULT_CONSTANT = 0x41C64E6D,
        ADD_CONSTANT = 0x00003039,
        THROW_AWAY_BITS = 10
    };

public:
    unsigned long Seed;     // +0x00
};

class Random3Class {
public:
    Random3Class(unsigned seed1 = 0, unsigned seed2 = 0);  // 0x00638950

    operator int() { return operator()(); }
    int operator()();                                       // 0x00638970
    int operator()(int minval, int maxval);                 // 0x006389D0

    enum {
        SIGNIFICANT_BITS = 32
    };

    int Seed;       // +0x00
    int Index;      // +0x04

private:
    static unsigned long Mix1[20];      // 0x007EE4AC
    static unsigned long Mix2[20];      // 0x007EE4FC
};

class Random2Class {
public:
    Random2Class(unsigned seed = 0);                // 0x00638790

    operator int() { return operator()(); }
    int operator()();                               // 0x00638840
    int operator()(int minval, int maxval);         // 0x006388A0

    enum {
        SIGNIFICANT_BITS = 32
    };

    bool unknown_0x00;      // +0x00 while set, the generator returns 0
    int Index1;             // +0x04 table entry updated next
    int Index2;             // +0x08 table entry mixed in (103 ahead)
    int Table[250];         // +0x0C
};

extern Random2Class unknown_random_839218;      // 0x00839218 the generator audio and techno use

#endif

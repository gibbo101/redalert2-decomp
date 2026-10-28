// Random2Class (moved out of shared/random.hpp so a class header can hold one
// as a member: random.hpp's Random3Class static members take compiler counter
// values and renumber a unit's static initializers).
#ifndef RA2_SHARED_RANDOM2_HPP
#define RA2_SHARED_RANDOM2_HPP

// Random2Class: 250-entry XOR lagged-Fibonacci table seeded from a
// Random3Class (YRpp calls it Randomizer); shared/random.hpp holds the
// Pick_Random_Number template its ranged operator() expands.
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

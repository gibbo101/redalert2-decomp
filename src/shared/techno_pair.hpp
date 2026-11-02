// Existing eight-byte experience helper; class identity remains a hypothesis.
#ifndef RA2_SHARED_TECHNO_PAIR_HPP
#define RA2_SHARED_TECHNO_PAIR_HPP

class NoInitClass;

// Two words cleared together (constructor 0x00713340, destructor
// 0x00713350 are out of line).
class UnknownTechnoPair {
public:
    UnknownTechnoPair();                // 0x00713340
    UnknownTechnoPair(NoInitClass const &noinit) {}
    ~UnknownTechnoPair();               // 0x00713350
    int unknown_713440() const;         // 0x00713440 (rank 0, 1 or 2 from the experience value)
    int unknown_713580() const;         // 0x00713580 (hypothesis: written to the [Units] line)
    // Sets the first word to 0 and the second to 2.0f with the flag, else 0
    // (0x00713550; Create_Units with InitialVeteran).
    void Unknown_00713550(bool flag);
    void Unknown_00713590(int value);    // 0x00713590: signed int * 0.01 stored as an 8-byte FP value
    bool unknown_713420() const;        // 0x00713420
    void Unknown_00713360(int cost, int points);   // 0x00713360 (gains experience; TechnoClass slot 55)
    void unknown_713520(bool value);    // 0x00713520 (UnitClass constructor: veteran owners)
#ifdef RA2_TECHNO_PAIR_ROOKIE
    void Unknown_007134E0(bool flag);   // 0x007134E0 (VeteranLevel 0 reinforcements, reinf.cpp; TS Set_Dumbass)
#endif
    bool unknown_7133a0() const;        // 0x007133A0 (veteran; hypothesis)
    bool unknown_713400() const;        // 0x00713400 (a third rank; TechnoClass slot 250 draws frame 18)
    int unknown_00;
    int unknown_04;
};

#endif

// UnknownTechnoPair: a techno's experience (TechnoClass +0x118; Tiberian Sun's VeterancyClass in
// veteran.cpp, the unit 0x00713300-0x0071359F: Experience is one double, 1.0 veteran, 2.0
// elite). The class name stays a hypothesis until RTTI or strings show it.
#ifndef RA2_SHARED_TECHNO_PAIR_HPP
#define RA2_SHARED_TECHNO_PAIR_HPP

class NoInitClass;

class UnknownTechnoPair {
public:
    UnknownTechnoPair();                // 0x00713340 (Experience 0)
    UnknownTechnoPair(NoInitClass const &noinit) {}
    ~UnknownTechnoPair();               // 0x00713350
    int unknown_713440() const;         // 0x00713440 (rank 0, 1 or 2 from the experience value)
    int unknown_713580() const;         // 0x00713580 (Experience * 100: TS To_Integer, the [Units] line)
    // Sets the experience to 2.0 with the flag, else 0 (0x00713550; TS Set_Elite;
    // Create_Units with InitialVeteran).
    void Unknown_00713550(bool flag);
    void Unknown_00713590(int value);    // 0x00713590: value / 100 (TS From_Integer)
    bool unknown_713420() const;        // 0x00713420 (TS Is_Elite: Experience >= 2)
    void Unknown_00713360(int cost, int points);   // 0x00713360 (TS Made_A_Kill; TechnoClass slot 55)
    void unknown_713520(bool value);    // 0x00713520 (TS Set_Veteran; UnitClass constructor: veteran owners)
#ifdef RA2_TECHNO_PAIR_ROOKIE
    void Unknown_007134E0(bool flag);   // 0x007134E0 (VeteranLevel 0 reinforcements, reinf.cpp; TS Set_Dumbass)
#endif
    bool unknown_7133a0() const;        // 0x007133A0 (TS Is_Veteran: 1 <= Experience < 2)
#ifdef RA2_CELL_GOODIE_CHECK
    bool unknown_7133d0() const;        // 0x007133D0 (CellClass::Goodie_Check; hypothesis)
    void unknown_713510(bool value);    // 0x00713510 (CellClass::Goodie_Check; hypothesis)
#endif
    bool unknown_713400() const;        // 0x00713400 (TS Is_Dumbass: Experience < 0; TechnoClass slot 250 draws frame 18)
#ifdef RA2_VETERANCY_UNIT
    // Declared only in the veteran unit (new declarations here reach most of the tree).
    bool Is_Rookie() const;             // 0x007133D0 (0 <= Experience < 1)
    double Modify(double value);        // 0x00713470 (the experience-scaled multiplier)
    void Set_Rookie(bool set);          // 0x00713510
#endif
    double Experience;                  // +0x00
};

#endif

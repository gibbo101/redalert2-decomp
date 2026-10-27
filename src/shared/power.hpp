// PowerClass: the power bar layer of the screen chain (Power.CPP,
// 0x0061C260-0x0061D240; RTTI vtable 0x007A832C, 54 slots), derived from
// RadarClass.
//
// Layout from the constructor 0x0061C450 and Init_Clear 0x0061C4D0: two
// countdown timers on the system clock with a counter each, three counters,
// a flag and two -1 sentinels. Names are hypotheses unless stated.
#ifndef RA2_SHARED_POWER_HPP
#define RA2_SHARED_POWER_HPP
#ifdef RA2_SHARED_MAP_VIEW_HPP
#error "shared/map_view.hpp declares light screen layers: include the full layer headers before it"
#endif

#include "shared/radar.hpp"
#include "shared/house_screen.hpp"

// Retrieves a shape from the mix files, or loads it (allocated set) when it
// is not cached (0x00495270).
void const *__fastcall Unknown_Load_Shape_00495270(char const *filename, bool &allocated);

// The player's buildings (stand-ins; +0x52D0 output and +0x52D4 drain of
// HouseClass by the TXT_POWER_DRAIN format order, a hypothesis).
struct UnknownBuildingType {
    char unknown_00[0xC68];
    int unknown_c68;                // +0xC68 power the building adds
    int PowerDrain_c6c;                // +0xC6C power the building takes
};
struct UnknownBuilding {
    char unknown_00[0x418];
    UnknownBuildingType *Type;      // +0x418
};
// The player's house: shared/house.hpp (HouseClass Buildings, PowerOutput, PowerDrain).

// Unidentified globals used by the power bar's help region (0x00A3D290 is
// also shared/abstract.hpp's unknown_id_source_a3d290).
// (0x00A3D290: unknown_id_source_a3d290->unknown_2239 shifts the region 5 pixels down.)
extern int unknown_int_839620;      // 0x00839620 sidebar origin X
extern int unknown_int_839624;      // 0x00839624 sidebar origin Y
extern int unknown_int_abcd70;      // 0x00ABCD70

// The shared help-text buffer the help slots return (0x00A767E0).
extern wchar_t unknown_text_a767e0[];

class PowerClass : public RadarClass {
public:
    PowerClass();                                       // 0x0061C450
    // Restore-in-place form: only the second timer restarts.
    PowerClass(NoInitClass const &noinit) : RadarClass(noinit), unknown_150c(noinit) {}

    virtual void One_Time();                            // slot 5  0x0061C550
    virtual void Init_Clear();                          // slot 7  0x0061C4D0
    virtual void AI(int &input, Point2D const &xy);     // slot 10 0x0061CC30
    virtual void Draw_It(bool complete = false);        // slot 16 0x0061C8C0
    virtual wchar_t const *unknown_slot33(int id);      // slot 33 0x0061D1C0
    virtual void unknown_slot34();                      // slot 34 0x0061D130
    virtual void unknown_slot50();                      // slot 50 0x0061C580
    virtual void unknown_slot53();                      // slot 53 0x0061C560

    // Number of power bar segments for the bar height (0x0061C6E0; no direct
    // callers, inlined elsewhere).
    static int Unknown_0061C6E0();
    // Segments left unlit for the player's building power (0x0061C5F0).
    static int Unknown_0061C5F0();
    // The counters' share of the unlit segments, times 5 (0x0061C690; no
    // direct callers).
    int Unknown_0061C690();

    // The three counters' targets (0x0061C700; meaning not recovered; the
    // arguments receive the targets of +0x1528, +0x152C and +0x1530).
    void Unknown_0061C700(int &target_1528, int &target_152c, int &target_1530);
    // Steps one counter down toward its target: +0x1528 first, then
    // +0x1530, then +0x152C (0x0061CB50).
    void Unknown_0061CB50();
    // Steps one counter up toward its target: +0x1530 first, then +0x1528,
    // then +0x152C (0x0061CBC0; no direct callers).
    void Unknown_0061CBC0();
    // Restarts the first timer at 3 ticks with 10 on its counter (0x0061C5B0).
    void Unknown_0061C5B0();

    // "POWERP.SHP" and whether it was loaded rather than retrieved
    // (0x00A7691C, 0x00A76920).
    static void const *PowerShape;
    static bool PowerShapeAllocated;

    bool unknown_1508;                                  // +0x1508
    CDTimerClass<SystemTimerClass> unknown_150c;        // +0x150C
    int unknown_1518;                                   // +0x1518
    CDTimerClass<SystemTimerClass> unknown_151c;        // +0x151C
    int unknown_1528;                                   // +0x1528
    int unknown_152c;                                   // +0x152C
    int unknown_1530;                                   // +0x1530
    bool unknown_1534;                                  // +0x1534
    int unknown_1538;                                   // +0x1538 -1
    int unknown_153c;                                   // +0x153C -1
};

#endif

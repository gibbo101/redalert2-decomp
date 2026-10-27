#ifndef RA2_SHARED_ID_SOURCE_HPP
#define RA2_SHARED_ID_SOURCE_HPP
#include "shared/cd_timer.hpp"
// The source of new object IDs (hypothesis; the pointer at 0x00A3D290).
// Hypothesis: the scenario (ScenarioClass): its random generator is at +0x218
// (shared/random.hpp's Random2Class; declared by accessor because including
// random.hpp here renumbers every unit's static initializers: Random3Class's
// static members take compiler counter values), the difficulty at +0x60C
// (Trigger.cpp), the theater at +0x838 (AnimType.cpp).
template <class T> class TypeList;
class TechnoTypeClass;
class Random2Class;
class Cell;
template <class T> class TTimerClass;
class SystemTimerClass;
class CellClass;
// Only the41-byte stride and final value byte are observed by the checkpoint.
struct UnknownScenarioVariable_004B5AB0 { char unknown_00[40]; bool Value; };
typedef char ScenarioVariable_stride_check[(sizeof(UnknownScenarioVariable_004B5AB0)==41)?1:-1];
class UnknownIDSource {
public:
    bool Unknown_0051FC50();                    // 0x0051FC50
    long Next_ID();                             // 0x00663170 (name hypothesis)
    CellClass *unknown_6631a0(int waypoint);            // 0x006631A0 (the map cell of a waypoint; hypothesis)
    bool unknown_6612c0(unsigned index, bool value);    // 0x006612C0 (sets one of the 50 local variables; returns the old value; hypothesis)
    bool unknown_661560(unsigned index, bool value);    // 0x00661560 (sets one of the 50 global variables; returns the old value; hypothesis)
    void Set_Waypoint_Location(int waypoint, Cell cell);   // 0x00663400
    bool Unknown_00663240(int waypoint) const;        // 0x00663240 (whether the waypoint is set; hypothesis)
    Cell Get_Waypoint_Location(int waypoint) const;   // 0x00663180 (the cell at +0x632 + 4*waypoint; hypothesis)
    Random2Class &Random() { return *(Random2Class *)((char *)this + 0x218); }   // +0x218
    // The elapsed game-time timer (ApplicationClass slot 7, 0x00426E00; declared by
    // accessor like Random(): the template lives in shared/comm_buffer.hpp).
    TTimerClass<SystemTimerClass> &Elapsed_Time() { return *(TTimerClass<SystemTimerClass> *)((char *)this + 0x614); }   // +0x614

    // Original TypeList vptrs/28-byte stride verified at0066112F/1187/11DF.
    // Complete types and inline definitions stay in the collection unit;
    // this widely included header keeps the original opaque physical storage.
    TypeList<TechnoTypeClass *> &Loadout_Types_2254();
    TypeList<int> &Loadout_Limits_2270();
    TypeList<int> &Loadout_Counts_228c();

    int unknown_000;                            // +0x000 flags (0x1000: AircraftClass slot 70)
    char unknown_004[0x60C - 0x4];
    int Difficulty;                             // +0x60C (0 easy, 1 normal, 2 hard; hypothesis)
    int unknown_610;                            // +0x610 (the difficulty of computer houses; hypothesis)
    char unknown_614[0x7C8 - 0x614];
    CDTimerClass<FrameTimerClass> MissionTimer; // +7c8,original countdown
    char unknown_7d4[0x838 - 0x7D4];
    int Theater;                                // +0x838 (theater index; hypothesis)
    char unknown_83c[0x1208 - 0x83C]; // scenario name remains at+83c
    int unknown_1208;
    char unknown_120c[4];
    UnknownScenarioVariable_004B5AB0 Variables[50]; // +1210,value bytes+1238 atstride41
    char unknown_1a12[0x2229 - 0x1A12];
    char unknown_2229;                          // +0x2229 (toggled by a trigger action 0x006ADB18)
    char unknown_222a;                          // +0x222A (set from a trigger action's data, 0x006AFB60)
    char unknown_222b;                          // +0x222B (set from a trigger action's data, 0x006AFB40)
    char unknown_222c;                          // +0x222C (set from a trigger action's data, 0x006AFB80)
    char unknown_222d[0x2231 - 0x222D];
    bool unknown_2231;
    char unknown_2232[6];
    bool unknown_2238;                          // +0x2238 (AITriggerType 0x0041C990: global AI triggers off)
    bool unknown_2239;                          // +0x2239 (PowerClass: shifts the help region5 pixels down)
    char unknown_223a[0x22A8 - 0x223A];
    int unknown_22a8;                           // +0x22A8 (set from a trigger action's data, 0x006B2260)
    char unknown_22ac[4];
    int unknown_22b0;                           // +0x22B0 (receives +0x22A8 unless 0x0051FC50 holds)
    char unknown_22b4[0x22FC - 0x22B4];
    bool unknown_22fc; // observed byte read by serial progress poll00481F00
    char unknown_22fd[0x2304 - 0x22FD];
    unsigned short unknown_2304;
};
extern UnknownIDSource *unknown_id_source_a3d290;    // 0x00A3D290

#endif

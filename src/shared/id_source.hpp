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
class SpecialClass;
class CCINIClass;
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
    // The scenario's SpecialClass options are its first word (+0x000; declared by
    // accessor like Random()).
    SpecialClass &Special() { return *(SpecialClass *)this; }
    // Writes [Basic] (the player and campaign settings unless skip_player),
    // [VariableNames], [Ranking] and [Lighting] (0x006625B0; always true).
    bool Write_Basic(CCINIClass &ini, bool skip_player);

    int unknown_000;                            // +0x000 flags (0x1000: AircraftClass slot 70)
    char NextScenario[0x104];                   // +0x004 [Basic] NextScenario
    char AltNextScenario[0x104];                // +0x108 [Basic] AltNextScenario
    int HomeCell;                               // +0x20C [Basic] HomeCell
    int AltHomeCell;                            // +0x210 [Basic] AltHomeCell
    char unknown_214[0x60C - 0x214];
    int Difficulty;                             // +0x60C (0 easy, 1 normal, 2 hard; hypothesis)
    int unknown_610;                            // +0x610 (the difficulty of computer houses; hypothesis)
    char unknown_614[0x7C8 - 0x614];
    CDTimerClass<FrameTimerClass> MissionTimer; // +7c8,original countdown
    char unknown_7d4[0x834 - 0x7D4];
    int TechLevel;                              // +0x834 (the houses' default TechLevel; hypothesis)
    int Theater;                                // +0x838 (theater index; hypothesis)
    char unknown_83c[0x940 - 0x83C]; // scenario name remains at+83c
    unsigned short Name[45];                         // +0x940 [Basic] Name
    char UIName[34];                            // +0x99A [Basic] UIName
    int IntroMovie;                             // +0x9BC [Basic] Intro (movie index)
    int BriefMovie;                             // +0x9C0 [Basic] Brief
    int WinMovie;                               // +0x9C4 [Basic] Win
    int LoseMovie;                              // +0x9C8 [Basic] Lose
    int ActionMovie;                            // +0x9CC [Basic] Action
    int PostScoreMovie;                         // +0x9D0 [Basic] PostScore
    int PreMapSelectMovie;                      // +0x9D4 [Basic] PreMapSelect
    char unknown_9d8[0x11D8 - 0x9D8];
    char Briefing[32];                          // +0x11D8 [Basic] Briefing
    int Theme;                                  // +0x11F8 [Basic] Theme
    char unknown_11fc[0x1200 - 0x11FC];
    double CarryOverMoney;                      // +0x1200 [Basic] CarryOverMoney
    int unknown_1208;                           // +0x1208 [Basic] CarryOverCap (percent; stored times 100)
    int Percent;                                // +0x120C [Basic] Percent
    UnknownScenarioVariable_004B5AB0 Variables[50]; // +1210,value bytes+1238 atstride41
    UnknownScenarioVariable_004B5AB0 LocalVariables[50]; // +0x1A12 [VariableNames] (name, value byte at +0x28)
    char unknown_2214[0x2228 - 0x2214];
    bool FreeRadar;                             // +0x2228 [Basic] FreeRadar
    bool unknown_2229;                          // +0x2229 (toggled by a trigger action 0x006ADB18)
    bool unknown_222a;                          // +0x222A (set from a trigger action's data, 0x006AFB60)
    bool unknown_222b;                          // +0x222B (set from a trigger action's data, 0x006AFB40)
    bool unknown_222c;                          // +0x222C (set from a trigger action's data, 0x006AFB80)
    char unknown_222d[0x2230 - 0x222D];
    bool EndOfGame;                             // +0x2230 [Basic] EndOfGame
    bool unknown_2231;                          // +0x2231 [Basic] TimerInherit
    bool SkipScore;                             // +0x2232 [Basic] SkipScore
    bool OneTimeOnly;                           // +0x2233 [Basic] OneTimeOnly
    bool SkipMapSelect;                         // +0x2234 [Basic] SkipMapSelect
    bool TruckCrate;                            // +0x2235 [Basic] TruckCrate
    bool FillSilos;                             // +0x2236 [Basic] FillSilos
    bool TiberiumDeathToVisceroid;              // +0x2237 [Basic] TiberiumDeathToVisceroid
    bool unknown_2238;                          // +0x2238 (AITriggerType 0x0041C990: global AI triggers off)
    bool unknown_2239;                          // +0x2239 (PowerClass: shifts the help region5 pixels down)
    bool MultiplayerOnly;                       // +0x223A [Basic] MultiplayerOnly (written as a number)
    char unknown_223b[0x2250 - 0x223B];
    int StartingDropships;                      // +0x2250 [Basic] StartingDropships
    char unknown_2254[0x22A8 - 0x2254];         // +0x2254 TypeLists (Loadout_Types_2254, ...)
    int unknown_22a8;                           // +0x22A8 [Lighting] Ambient, hundredths (set from a trigger action's data, 0x006B2260)
    char unknown_22ac[4];
    int unknown_22b0;                           // +0x22B0 (receives +0x22A8 unless 0x0051FC50 holds)
    int AmbientRed;                             // +0x22B4 [Lighting] Red, hundredths
    int AmbientGreen;                           // +0x22B8 [Lighting] Green
    int AmbientBlue;                            // +0x22BC [Lighting] Blue
    int AmbientGround;                          // +0x22C0 [Lighting] Ground, thousandths
    int AmbientLevel;                           // +0x22C4 [Lighting] Level, thousandths
    int IonAmbient;                             // +0x22C8 [Lighting] IonAmbient, hundredths
    int IonRed;                                 // +0x22CC [Lighting] IonRed
    int IonGreen;                               // +0x22D0 [Lighting] IonGreen
    int IonBlue;                                // +0x22D4 [Lighting] IonBlue
    int IonGround;                              // +0x22D8 [Lighting] IonGround, thousandths
    int IonLevel;                               // +0x22DC [Lighting] IonLevel, thousandths
    char unknown_22e0[0x22FC - 0x22E0];
    bool unknown_22fc; // observed byte read by serial progress poll00481F00
    char unknown_22fd[0x2300 - 0x22FD];
    int InitTime;                               // +0x2300 [Basic] InitTime
    unsigned short unknown_2304;
    char unknown_2306[2];
    int ParTimeEasy;                            // +0x2308 [Ranking] ParTimeEasy
    int ParTimeMedium;                          // +0x230C [Ranking] ParTimeMedium
    int ParTimeHard;                            // +0x2310 [Ranking] ParTimeHard
    char UnderParTitle[31];                     // +0x2314 [Ranking] UnderParTitle
    char UnderParMessage[31];                   // +0x2333 [Ranking] UnderParMessage
    char OverParTitle[31];                      // +0x2352 [Ranking] OverParTitle
    char OverParMessage[31];                    // +0x2371 [Ranking] OverParMessage
};
extern UnknownIDSource *unknown_id_source_a3d290;    // 0x00A3D290
// The scenario INI section names (pointers at 0x007A9204 "Basic" and
// 0x007A9200 "VariableNames").
extern char const *unknown_basic_section_7a9204;
extern char const *unknown_variable_names_section_7a9200;

#endif

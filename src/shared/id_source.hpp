#ifndef RA2_SHARED_ID_SOURCE_HPP
#define RA2_SHARED_ID_SOURCE_HPP
#include "shared/coord.hpp"
#include "shared/cd_timer.hpp"
#include "shared/system_timer.hpp"
#include "shared/t_timer.hpp"
#include "shared/fixed_string.hpp"
#include "shared/type_list_decl.hpp"
#include "shared/random2.hpp"
// The source of new object IDs (hypothesis; the pointer at 0x00A3D290).
// Hypothesis: the scenario (ScenarioClass): its random generator is at +0x218
// (shared/random2.hpp's Random2Class), the difficulty at +0x60C
// (Trigger.cpp), the theater at +0x838 (AnimType.cpp).
class TechnoTypeClass;
class CellClass;
class SpecialClass;
class CCINIClass;
class WWCRCEngine;
// Only the41-byte stride and final value byte are observed by the checkpoint.
struct UnknownScenarioVariable_004B5AB0 { char unknown_00[40]; bool Value; };
typedef char ScenarioVariable_stride_check[(sizeof(UnknownScenarioVariable_004B5AB0)==41)?1:-1];
class UnknownIDSource {
public:
    // Builds the scenario with its defaults (0x0065B4F0; Set_Defaults, the
    // special options, no waypoints, names or variables).
    UnknownIDSource();
    // Restores a saved scenario in place: the generator and the +0x620 timer
    // and loadout lists are rebuilt, the mission timer text reloaded from its
    // label (0x0065B780).
    UnknownIDSource(NoInitClass const &noinit);
    // 0x0051FC50 is a free function (shared/team.hpp): it reads the byte at 0x00A51934.
    // Adds the scenario's state to a CRC (0x00662E00; Game_CRC).
    void Compute_CRC(WWCRCEngine &crc) const;
    long Next_ID();                             // 0x00663170 (name hypothesis)
    CellClass *unknown_6631a0(int waypoint);            // 0x006631A0 (the map cell of a waypoint; hypothesis)
    bool unknown_6612c0(unsigned index, bool value);    // 0x006612C0 (sets one of the 50 local variables; returns the old value; hypothesis)
    bool unknown_661560(unsigned index, bool value);    // 0x00661560 (sets one of the 50 global variables; returns the old value; hypothesis)
    // The variables by name and index (+0x1210 global, +0x1A12 local;
    // 0x00661310-0x00661710; name hypotheses).
    bool Set_Global_Variable(char const *name, bool value);       // 0x00661310
    bool Get_Global_Variable(int index, bool *value);             // 0x006613B0
    bool Get_Global_Variable(char const *name, bool *value);      // 0x006613E0
    int Find_Global_Variable(char const *name);                   // 0x00661470
    bool Read_Global_Variables(CCINIClass &ini);                  // 0x006614D0 ([VariableNames] names)
    bool Set_Local_Variable(char const *name, bool value);        // 0x006615B0
    bool Get_Local_Variable(int index, bool *value);              // 0x00661650
    bool Get_Local_Variable(char const *name, bool *value);       // 0x00661680
    int Find_Local_Variable(char const *name);                    // 0x00661710
    void Set_Waypoint_Location(int waypoint, Cell cell);   // 0x00663400
    bool Unknown_00663240(int waypoint) const;        // 0x00663240 (whether the waypoint is set; hypothesis)
    Cell Get_Waypoint_Location(int waypoint) const;   // 0x00663180 (the cell at +0x632 + 4*waypoint; hypothesis)
    // The centre of a waypoint's cell, raised on a bridge (0x006631C0).
    CoordStruct Waypoint_Coord(int waypoint) const;
    // Reads [Waypoints] and marks the waypoint cells (0x00663280).
    void Read_Waypoints(CCINIClass &ini);
    // Rewrites [Waypoints] (0x00663350).
    void Write_Waypoints(CCINIClass &ini);
    // The name of the first unset waypoint, or "" (0x00663440).
    char const *Free_Waypoint_Name() const;
    Random2Class &Random() { return RandomNumber; }
    // The elapsed game-time timer (ApplicationClass slot 7, 0x00426E00).
    TTimerClass<SystemTimerClass> &Elapsed_Time() { return ElapsedTime; }

    // The scenario's SpecialClass options are its first word (+0x000; declared by
    // accessor like Random()).
    SpecialClass &Special() { return *(SpecialClass *)this; }
    // Writes [Basic] (the player and campaign settings unless skip_player),
    // [VariableNames], [Ranking] and [Lighting] (0x006625B0; always true).
    bool Write_Basic(CCINIClass &ini, bool skip_player);
    // Reads [VariableNames] into the 50 local variables ("name,value" by
    // index; 0x00661770, always true).
    bool Read_Variables(CCINIClass &ini);
    // Rewrites [VariableNames] from the named local variables (0x006618B0,
    // always true).
    bool Write_Variables(CCINIClass &ini);
    // Reads [Basic] (movies, flags, loadout lists), the local variables,
    // [Ranking] and [Lighting], then picks the player's house (0x00661980;
    // always true).
    bool Read_Basic(CCINIClass &ini);
    // Puts the scenario settings back to their defaults: timers stopped at
    // zero, no movies, theme or theater, default lighting and par times,
    // empty loadout lists; a skirmish takes the "GUI:SkirmishGame" name
    // (0x0065B830; called by the constructor 0x0065B4F0 and Clear_Scenario;
    // name hypothesis).
    void Set_Defaults();

    int unknown_000;                            // +0x000 flags (0x1000: AircraftClass slot 70)
    char NextScenario[0x104];                   // +0x004 [Basic] NextScenario
    char AltNextScenario[0x104];                // +0x108 [Basic] AltNextScenario
    int HomeCell;                               // +0x20C [Basic] HomeCell
    int AltHomeCell;                            // +0x210 [Basic] AltHomeCell
    long UniqueID;                              // +0x214 the last object ID given out (Next_ID; 1000000 by default; name hypothesis)
    Random2Class RandomNumber;                  // +0x218 the scenario's generator (Random())
    int Difficulty;                             // +0x60C (0 easy, 1 normal, 2 hard; hypothesis)
    int unknown_610;                            // +0x610 (the difficulty of computer houses; hypothesis)
    TTimerClass<SystemTimerClass> ElapsedTime;  // +0x614 the elapsed game time
    CDTimerClass<SystemTimerClass> unknown_620; // +0x620
    int unknown_62c;                            // +0x62C
    bool unknown_630;                           // +0x630
    Cell Waypoints[101];                        // +0x632 the waypoint cells (Get_Waypoint_Location; set to the empty cell by the constructor)
    CDTimerClass<FrameTimerClass> MissionTimer; // +7c8,original countdown
    unsigned short const *MissionTimerText;     // +0x7D4 the text of MissionTimerLabel (empty without one; 0x0065B780)
    FixedString<32> MissionTimerLabel;          // +0x7D8 its string-table label
    CDTimerClass<FrameTimerClass> unknown_7f8;  // +0x7F8
    CDTimerClass<FrameTimerClass> unknown_804;  // +0x804
    CDTimerClass<FrameTimerClass> unknown_810;  // +0x810
    CDTimerClass<FrameTimerClass> unknown_81c;  // +0x81C
    CDTimerClass<FrameTimerClass> unknown_828;  // +0x828
    int TechLevel;                              // +0x834 (the houses' default TechLevel; hypothesis)
    int Theater;                                // +0x838 (theater index; hypothesis)
    char FileName[0x104];                       // +0x83C the scenario's name (its MISSION.INI section; Read_Scenario_INI)
    unsigned short Name[45];                         // +0x940 [Basic] Name
    char UIName[34];                            // +0x99A [Basic] UIName
    int IntroMovie;                             // +0x9BC [Basic] Intro (movie index)
    int BriefMovie;                             // +0x9C0 [Basic] Brief
    int WinMovie;                               // +0x9C4 [Basic] Win
    int LoseMovie;                              // +0x9C8 [Basic] Lose
    int ActionMovie;                            // +0x9CC [Basic] Action
    int PostScoreMovie;                         // +0x9D0 [Basic] PostScore
    int PreMapSelectMovie;                      // +0x9D4 [Basic] PreMapSelect
    unsigned short BriefingText[0x400];         // +0x9D8 the briefing (MISSION.INI Briefing through the string table)
    char Briefing[32];                          // +0x11D8 [Basic] Briefing
    int Theme;                                  // +0x11F8 [Basic] Theme
    int unknown_11fc;                           // +0x11FC (the player's HouseType index, set by Read_Basic)
    double CarryOverMoney;                      // +0x1200 [Basic] CarryOverMoney
    int unknown_1208;                           // +0x1208 [Basic] CarryOverCap (percent; stored times 100)
    int Percent;                                // +0x120C [Basic] Percent
    UnknownScenarioVariable_004B5AB0 Variables[50]; // +1210,value bytes+1238 atstride41
    UnknownScenarioVariable_004B5AB0 LocalVariables[50]; // +0x1A12 [VariableNames] (name, value byte at +0x28)
    Cell Views[4];                              // +0x2214 the remembered views, all the home waypoint at the start (Fill_In_Data)
    int unknown_2224;                           // +0x2224
    bool FreeRadar;                             // +0x2228 [Basic] FreeRadar
    bool unknown_2229;                          // +0x2229 (toggled by a trigger action 0x006ADB18)
    bool unknown_222a;                          // +0x222A (set from a trigger action's data, 0x006AFB60)
    bool unknown_222b;                          // +0x222B (set from a trigger action's data, 0x006AFB40)
    bool unknown_222c;                          // +0x222C (set from a trigger action's data, 0x006AFB80)
    bool unknown_222d;                          // +0x222D
    bool unknown_222e;                          // +0x222E (set when a variable changes, 0x0065B4F0)
    bool unknown_222f;                          // +0x222F
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
    bool unknown_223b;                          // +0x223B (cleared by the constructor)
    bool unknown_223c;                          // +0x223C
    char unknown_223d[0x2240 - 0x223D];
    CDTimerClass<FrameTimerClass> unknown_2240; // +0x2240
    int unknown_224c;                           // +0x224C the campaign (Campaigns index; -1: none)
    int StartingDropships;                      // +0x2250 [Basic] StartingDropships
    // The loadout lists (TypeList vptrs and the 28-byte stride at 0x0066112F,
    // 0x00661187, 0x006611DF; padded by Read_Basic to one limit and one count
    // per type).
    TypeList<TechnoTypeClass *> AllowableUnits; // +0x2254 [Basic] AllowableUnits
    TypeList<int> AllowableUnitMaximums;        // +0x2270 [Basic] AllowableUnitMaximums (-1: no limit)
    TypeList<int> AllowableUnitCounts;          // +0x228C the number taken of each type (Unknown4A6AE0Owner; name hypothesis)
    int unknown_22a8;                           // +0x22A8 [Lighting] Ambient, hundredths (set from a trigger action's data, 0x006B2260)
    int unknown_22ac;                           // +0x22AC (receives the [Lighting] Ambient level too)
    int unknown_22b0;                           // +0x22B0 (receives +0x22A8 unless Unknown_0051FC50 holds)
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
    int unknown_22e0;                           // +0x22E0 (200 by default)
    int unknown_22e4;                           // +0x22E4 (175)
    int unknown_22e8;                           // +0x22E8 (150)
    int unknown_22ec;                           // +0x22EC (125)
    int unknown_22f0;                           // +0x22F0 (100)
    int unknown_22f4;                           // +0x22F4 (100)
    int NukeAmbientChangeRate;                  // +0x22F8 [Lighting] NukeAmbientChangeRate
    bool unknown_22fc; // observed byte read by serial progress poll00481F00
    char unknown_22fd[0x2300 - 0x22FD];
    int InitTime;                               // +0x2300 [Basic] InitTime
    unsigned short unknown_2304;
    bool unknown_2306;                          // +0x2306 the game is paused (Pause_Game_0065c3d0)
    char unknown_2307;
    int ParTimeEasy;                            // +0x2308 [Ranking] ParTimeEasy
    int ParTimeMedium;                          // +0x230C [Ranking] ParTimeMedium
    int ParTimeHard;                            // +0x2310 [Ranking] ParTimeHard
    char UnderParTitle[31];                     // +0x2314 [Ranking] UnderParTitle
    char UnderParMessage[31];                   // +0x2333 [Ranking] UnderParMessage
    char OverParTitle[31];                      // +0x2352 [Ranking] OverParTitle
    char OverParMessage[31];                    // +0x2371 [Ranking] OverParMessage
    char LSLoadMessage[31];                     // +0x2390 MISSION.INI LSLoadMessage (loading screen)
    char LSLoadBriefing[31];                    // +0x23AF MISSION.INI LSLoadBriefing
    char unknown_23ce[2];
    int LS640BriefLocX;                         // +0x23D0 MISSION.INI LS640BriefLocX
    int LS640BriefLocY;                         // +0x23D4
    int LS800BriefLocX;                         // +0x23D8
    int LS800BriefLocY;                         // +0x23DC
    char LS640BkgdName[64];                     // +0x23E0 MISSION.INI LS640BkgdName
    char LS800BkgdName[64];                     // +0x2420 MISSION.INI LS800BkgdName
};
extern UnknownIDSource *unknown_id_source_a3d290;    // 0x00A3D290
// Assigns the houses of a multiplayer game to the players (0x0065FBB0; Read_Basic
// calls it instead of reading [Basic] Player; name hypothesis).
void __fastcall Assign_Houses_0065fbb0();
// Resets the scenario before a new one is read (0x0065D370; name hypothesis).
void Clear_Scenario_0065d370();
// Completes a freshly read scenario: view, tags, silos, map overlays and zones,
// the gas cloud system and ore twinkles (0x0065CDD0; Westwood's Fill_In_Data).
void Fill_In_Data_0065cdd0();
// Pauses and resumes the game: drag select aborted, mouse hidden or shown,
// keyboard cleared (0x0065C3D0, 0x0065C420; names hypotheses).
void Pause_Game_0065c3d0();
void Resume_Game_0065c420();
// Counted pauses (scripted and dialog pauses): the first pauses the sound, the
// elapsed time (campaign and skirmish) and, unless already paused, the game;
// a positive seconds also (re)starts the +0x620 timer, once (0x0065C1F0). The
// last release undoes them (0x0065C310). Names hypotheses.
void __fastcall Pause_Count_0065c1f0(int seconds);
void Release_Pause_0065c310();
// The game window lost or regained the focus: sound, elapsed time (campaign and
// skirmish), radar movie, tooltips and the mouse (0x0065C040, 0x0065C140; Westwood's
// Focus_Loss and Focus_Restore).
void __fastcall Focus_Loss_0065c040();
void Focus_Restore_0065c140();
// Whether the game was already paused when the pause count rose from zero (0x00AB6EF4).
extern bool unknown_was_paused_ab6ef4;
// With [Video] AllowModeToggle, switches to the RA2.INI screen size or back to
// 640 x 480 (0x0065C480).
void __fastcall Toggle_Display_Mode_0065c480(bool preferred);
// Reads the named scenario file into an INI and through Read_Scenario_INI
// (0x0065E760; Westwood's Read_Scenario; false on failure).
bool __fastcall Read_Scenario_0065e760(char const *name);
// Starts a scenario by name (0x0065BC70; reads it, optionally plays the
// briefing movie, sets the campaign; false on failure; Westwood's Start_Scenario).
bool __fastcall Start_Scenario_0065bc70(char const *name, bool briefing, int campaign);
// Restarts the current scenario (0x0065E440; Westwood's Do_Restart, hypothesis).
void __fastcall Do_Restart_0065e440();
// Ends the scenario with "battle control terminated" (0x0065E590; reached
// through a function pointer; name not recovered).
void __fastcall Unknown_0065e590();
// Makes the multiplayer units (0x00660320; Westwood's Create_Units, hypothesis).
void __fastcall Create_Units_00660320(bool official);
// Multiplayer setup after an unofficial map is read (0x0065E8C0; meaning not recovered).
void __fastcall Unknown_0065e8c0(bool official);
// Reads a scenario INI: MISSION.INI texts, rules, houses, [Basic] and every
// object list (0x0065EB40; false when the player side or [Basic] fails).
bool __fastcall Read_Scenario_INI(CCINIClass &ini, bool official);
// The scenario INI section names (pointers at 0x007A9204 "Basic" and
// 0x007A9200 "VariableNames").
extern char const *unknown_basic_section_7a9204;
extern char const *unknown_variable_names_section_7a9200;
// The [Waypoints] section name (pointer at 0x007A9218; Write_Waypoints).
extern char const *unknown_waypoints_section_7a9218;

#endif

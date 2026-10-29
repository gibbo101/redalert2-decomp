// Ion.cpp (source path 0x007DDB84): the lightning (ion) storm and the
// dominator lighting state. File statics 0x00A51878-0x00A51944 and
// 0x007DDB10-0x007DDB1C (initialized -1). Names are hypotheses: the storm
// fields follow the strings TXT_LIGHTNING_STORM / EVA_LightningStormCreated,
// the dominator fields the scenario's +0x22E0 lighting (shared/id_source.hpp).
#ifndef RA2_SHARED_LIGHTNING_STORM_HPP
#define RA2_SHARED_LIGHTNING_STORM_HPP

#include "shared/coord.hpp"
#include "shared/vector_class_decl.hpp"

class AnimClass;
class HouseClass;
struct IStream;

// The storm's target cell (0x00A51878; its dynamic initializer 0x0051F100
// copies unknown_geometry_k).
extern Cell StormCoords;
// Clouds drawn over the storm (0x00A51880), bolts striking (0x00A518C8) and
// clouds that strike once half played (0x00A51908).
extern DynamicVectorClass<AnimClass *> StormCloudsPresent;
extern DynamicVectorClass<AnimClass *> StormBoltsPresent;
extern DynamicVectorClass<AnimClass *> StormCloudsManifesting;
extern bool StormActive;                    // 0x00A51934
extern int StormDeferment;                  // 0x00A51938 frames before a deferred storm starts
extern int unknown_dominator_state_a5193c;  // 0x00A5193C (1 dominator lighting, 2 returning)
extern HouseClass *StormOwner;              // 0x00A51940
extern bool StormTimeToEnd;                 // 0x00A51944
extern int StormStartTime;                  // 0x007DDB10
extern int StormDuration;                   // 0x007DDB14
extern int unknown_dominator_start_7ddb18;  // 0x007DDB18
extern int unknown_dominator_delay_7ddb1c;  // 0x007DDB1C

// Resets the storm and dominator state and the ambient light (0x0051F2F0).
void __fastcall Init_Storm_0051F2F0();
// Writes and reads the state above and the three lists (0x0051F3F0, 0x0051F5E0).
long __fastcall Save_Storm_0051F3F0(IStream *stream);
long __fastcall Load_Storm_0051F5E0(IStream *stream);
void __fastcall Set_Storm_Active_0051F920(bool active);
// Starts the storm at cell for owner (a random cell the map accepts when cell
// is unknown_geometry_k); a nonzero deferment only arms it (0x0051F930).
void __fastcall Unknown_0051F930(int duration, int deferment, Cell cell, int owner);
void Unknown_0051FBB0();                    // 0x0051FBB0 (sets StormTimeToEnd while active)
// Ends an active storm (0x0051FBD0).
void __fastcall Stop_Storm_0051FBD0();
int __fastcall Is_Storm_Pending_0051FC30(); // 0x0051FC30 active, or a deferment left
// Adds a storm cloud over cell (a random WeatherConClouds type, raised by half
// the first bolt image) to the manifesting and present lists (0x0051FC90).
void __stdcall Unknown_0051FC90(Cell cell);
// A bolt strikes the cell under coord: bolt anim, thunder, the warhead's
// damage anim, explosion and damage, and metal debris when the cell's
// contents changed or its land breaks (0x0051FE50).
void __fastcall Storm_Strike_0051FE50(CoordStruct coord);
bool Unknown_0051FC50();                    // 0x0051FC50 (StormActive)
bool Unknown_0051FC60();                    // 0x0051FC60 (dominator state 1)
// Tints every light converter and the colour schemes (and redraws the cells)
// to red, green, blue in thousandths, -1 for the scenario ambient (0x00520B00).
void __fastcall Set_Lighting_00520B00(int red, int green, int blue, bool unknown4);
// The same tint for the converters of the colour-scheme lists only (0x00520A80).
void __fastcall Set_Scheme_Lighting_00520A80(int red, int green, int blue, bool unknown4);
void Unknown_00520770();                    // 0x00520770 (reapplies the dominator or storm lighting)
// The storm's frame logic: dominator state timeouts, finished bolts and clouds,
// strikes of half-played clouds, the end of the storm, new clouds near the cell
// and the deferred start with its warnings (0x00520200).
void __fastcall Update_Storm_00520200();
void __fastcall Start_Dominator_Lighting_005208A0();
void __fastcall End_Dominator_Lighting_00520980();
void __fastcall Storm_Active_Message_00520BF0();

#endif

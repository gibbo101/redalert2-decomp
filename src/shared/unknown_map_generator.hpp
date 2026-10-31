// Research layout of the nonpolymorphic owner constructed at00577010.
// The original name and composition spelling are hypotheses. TypeList fields
// have original RTTI identities; MapSeedClass occupies the first0x178 bytes.
#ifndef RA2_UNKNOWN_MAP_GENERATOR_HPP
#define RA2_UNKNOWN_MAP_GENERATOR_HPP
#include "shared/type_list.hpp"
#include "shared/coord.hpp"
#include "shared/map_seed.hpp"
class BuildingTypeClass;
class CellClass;
class UnknownMapGenerator {
public:
    void Init_Regions();
    void Init_Map_0057ae00(int fullInit);
    void Generate_Neutral_Tech_Buildings_0058ad90();
    void Create_Resources_00583b80();
    void Generate_Hills_00584dd0();
    void Generate_Vegetation_005852c0();
    // Controller0057A0D0 restores this owner in ECX before both calls; neither callee reads it.
    void Grow_Adjacent_Empty_Tiles_0057cf20();
    void Randomize_Tile_Group_0057de10();
    bool Init_Start_Points_00583790();
    void Generate_Lights_0058a9c0();
    void Generate_Vegetation_00585a60();
    void Place_Tile_Patch_00586340(CellClass *cell,int tile,int count,int origin,bool flag);
    int Place_Forest_00585dc0(CellClass *cell,int count,double density);
    void Generate_Urban_Areas_00586800();
    DynamicVectorClass<Cell> *Create_Urban_Area_00586b40(Cell const &position,int count);
    void Generate_Urban_Roads_00587330(DynamicVectorClass<Cell> &cells);
    void Generate_Urban_Buildings_00587cf0(DynamicVectorClass<Cell> &cells);
    void Generate_Urban_Units_00588100(DynamicVectorClass<Cell> &cells);
    void Generate_Rural_Areas_00589890();
    void Generate_Rural_Buildings_00589ac0(Cell const &position);
    void Generate_Rural_Units_00589f00(Cell const &position);
    bool Generate_Rural_Roads_0058a1b0(Cell const &position);
    double Angle_Score_00582970(Cell const &from,Cell const &to,double heading);
    void Cleanup_0057ace0();
    void unknown_005835f0();
    void unknown_00582fd0();
    void Read_Settings_00579960();
    int Randomize_Ramp_Tile_00582b30(int tile); // caller ECXowner/RET4; operation name hypothesis
    bool Clear_Region_Border_00581bf0(int region,int rings,int newRegion); // ECXowner,RET12; ALpredicate
    DynamicVectorClass<Cell> *Build_Region_Border_Cell_List_00581ee0(int region); // ECXowner,RET4; existingprivateevidence
    void Generate_Urban_Pavement_005890b0(DynamicVectorClass<Cell> &cells); // pendingr198
    void Adjust_Ramp_Junctions_005831c0(); // caller0058360A restores complete-owner ECX
    bool Expand_All_High_Ground_00583740(); //ALresult/RET0, receiver notread
    UnknownMapGenerator(); //00577010 remains parked, no body promoted
    // Proposed rename-only owner correction; same int,int/ECX/RET8 physical ABI.
    void Unknown_0057A0D0(int arg1,int arg2); //0057A0D0, operation unchanged; no body promoted
    void Run_Region_Attempts_0057dd60();
    // Observed ECX/plain-RET/ignored-result contracts; unobserved stack aliases and source intent remain hypotheses.
    void Initialize_Region_Map_0057bea0();
    void unknown_0057c4f0();
    void unknown_0057c0d0(DynamicVectorClass<Rect> *regions,int count,Rect const &area); //0057C5B7 ECX owner, RET12
    int unknown_0057d3a0(int count,Rect const &area,Point2D const &seed,bool flag,Cell const &origin,double weight,bool last); //RET32; source intent hypotheses
    void unknown_0057c780();
    void unknown_0057c9e0();
    bool unknown_0057ecf0(Cell const &point,double value,bool flag); //actualcallee, sourceintentqualified
    bool unknown_0057e100(Cell const &point); //actualcallee, sourceintentqualified
    int Compute_Water_Cell_Count_0057ec20() const; //name/constness hypotheses
    void Remap_Region_Tiles_0057e060(int source_index,int target_index,int level,int tile);
    MapSeedClass SeedOptions;
    int unknown_178,unknown_17c,unknown_180,unknown_184;
    TypeList<int> unknown_188,unknown_1a4,unknown_1c0,unknown_1dc,unknown_1f8;
    TypeList<int> unknown_214,unknown_230,unknown_24c,unknown_268,unknown_284,unknown_2a0;
    int unknown_2bc,unknown_2c0;
    TypeList<BuildingTypeClass const *> unknown_2c4,unknown_2e0;
    int unknown_2fc;
    bool unknown_300;
    int unknown_304;
    unsigned int unknown_308; //32-bit increment counter; signedness unknown, unsignedpreserveswrap
    int unknown_30c;
    bool unknown_310;
};
typedef char UnknownMapGenerator_dim180[(((unsigned int)&(((UnknownMapGenerator*)0)->unknown_180))==0x180)?1:-1];
typedef char UnknownMapGenerator_dim184[(((unsigned int)&(((UnknownMapGenerator*)0)->unknown_184))==0x184)?1:-1];
typedef char UnknownMapGenerator_counter308[(((unsigned int)&(((UnknownMapGenerator*)0)->unknown_308))==0x308)?1:-1];
typedef char UnknownMapGenerator_level30c[(((unsigned int)&(((UnknownMapGenerator*)0)->unknown_30c))==0x30c)?1:-1];
typedef char UnknownMapGenerator_size[(sizeof(UnknownMapGenerator)==0x314)?1:-1];
typedef char UnknownMapGenerator_seed_prefix[(((unsigned int)&(((UnknownMapGenerator*)0)->SeedOptions))==0)?1:-1];
// Proposed complete global view; original constructor/lifetime scaffolding stays in place.
// Declares storage elsewhere; no global definition or new initializer is introduced.
extern UnknownMapGenerator unknown_map_generator_a6fd68; //00A6FD68, nominal type/name hypotheses
#endif

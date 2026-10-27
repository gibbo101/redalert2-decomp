// InfantryTypeClass::InfantryTypeClass(char const *ini_name) (0x00509B20)
// The infantry defaults (crawls, no sounds), a new ID, registration in the
// infantry type list (its index), the techno-type values infantry override,
// and the 38 empty animation sequences.
#include "shared/infantry_type.hpp"
// @ref ??0TechnoTypeClass@@QAE@PBDH@Z=006d9b40
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?InfantryTypes@@3V?$DynamicVectorClass@PAVInfantryTypeClass@@@@A=00a40350
// @ref ??0?$VectorClass@PAVAnimTypeClass@@@@QAE@IPBQAVAnimTypeClass@@@Z=0050b860
// @ref ??0?$VectorClass@H@@QAE@IPBH@Z=0046d020

// An unused animation sequence.
static inline void Clear_Sequence(DoInfoStruct *&sequences, int index)
{
    sequences[index].Frame = 0;
    sequences[index].Count = 0;
    sequences[index].Jump = 0;
    sequences[index].Facing = -1;
}

InfantryTypeClass::InfantryTypeClass(char const *ini_name) :
    TechnoTypeClass(ini_name, 0),
    ArrayIndex(-1),
    Pip(1),
    DoControls(0),
    FireUp(0),
    FireProne(0),
    EnterWaterSound(-1),
    LeaveWaterSound(-1),
    Cyborg(false),
    NotHuman(false),
    Ivan(false),
    DetectionDistance(0),
    Occupier(false),
    Assaulter(false),
    Fearless(false),
    Crawls(true),
    Infiltrate(false),
    Fraidycat(false),
    TiberiumProof(false),
    Civilian(false),
    C4(false),
    Engineer(false),
    Agent(false),
    Thief(false),
    VehicleThief(false),
    Doggie(false),
    Deployer(false)
{
    Create_ID();
    InfantryTypes.Add(this);
    ArrayIndex = InfantryTypes.ID(this);
    RotCount = 8;
    RadarVisible = false;
    unknown_1fd = true;
    Repairable = false;
    Crewed = false;
    ImmuneToPsionics = false;
    Parasiteable = true;
    Organic = true;
    ConsideredAircraft = false;
    DoControls = new DoInfoStruct[38];
    for (int index = 0; index < 38; index++) {
        Clear_Sequence(DoControls, index);
    }
}

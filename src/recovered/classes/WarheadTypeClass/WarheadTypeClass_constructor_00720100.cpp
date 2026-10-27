// WarheadTypeClass::WarheadTypeClass(char const *ini_name) (0x00720100)
#include "shared/warhead_type.hpp"

WarheadTypeClass::WarheadTypeClass(char const *ini_name) :
    AbstractTypeClass(ini_name),
    Deform(0),
    ProneDamage(1.0),
    DeformThreshhold(0),
    InfDeath(0),
    CellSpread(0),
    CellInset(0),
    PercentAtMax(1.0f),
    CausesDelayKill(false),
    DelayKillFrames(5),
    DelayKillAtMax(1.0f),
    CombatLightSize(0),
    Particle(0),
    Wall(false),
    WallAbsoluteDestroyer(false),
    Wood(false),
    Tiberium(false),
    unknown_148(false),
    Sparky(false),
    Sonic(false),
    Fire(false),
    Conventional(false),
    Rocker(false),
    Bright(false),
    CLDisableRed(false),
    CLDisableGreen(false),
    CLDisableBlue(false),
    EMEffect(false),
    MindControl(false),
    IvanBomb(false),
    ElectricAssault(false),
    Parasite(false),
    Temporal(false),
    BombDisarm(false),
    Paralyzes(0),
    Culling(false),
    MakesDisguise(false),
    NukeMaker(false),
    Radiation(false),
    PsychicDamage(false),
    Bullets(false),
    Veinhole(false),
    ShakeXlo(0),
    ShakeXhi(0),
    ShakeYlo(0),
    ShakeYhi(0)
{
    Create_ID();
    unknown_WarheadTypeClass_list_00839b00.Add(this);
    unknown_objects_ac0cb0.Add(this);
    double *verses = Verses;
    verses[0] = 1.0;
    memcpy(verses + 1, verses, sizeof(Verses) - sizeof(Verses[0]));
}

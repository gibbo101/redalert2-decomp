// WWCRCEngine __fastcall Game_CRC() (0x00654C90; name hypothesis)
// The game-state CRC: the scenario, every object and type list (each
// object's Compute_CRC, AbstractClass slot 13), the player's house index,
// the frame and the count of the 0x00A40C60 list.
#include "shared/abstract.hpp"
#include "shared/cell.hpp"
#include "shared/building_class.hpp"
#include "shared/unit.hpp"
#include "shared/infantry.hpp"
#include "shared/aircraft.hpp"
#include "shared/house_type.hpp"
#include "shared/house.hpp"
#include "shared/unit_type.hpp"
#include "shared/infantry_type.hpp"
#include "shared/building_type_list.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/ai_trigger_type.hpp"
#include "shared/anim.hpp"
#include "shared/anim_type.hpp"
#include "shared/task_force.hpp"
#include "shared/team_type.hpp"
#include "shared/team.hpp"
#include "shared/script.hpp"
#include "shared/tag_type.hpp"
#include "shared/tag.hpp"
#include "shared/trigger_type.hpp"
#include "shared/trigger.hpp"
#include "shared/taction.hpp"
#include "shared/tevent.hpp"
#include "shared/factory_class.hpp"
#include "shared/voxel_anim_type.hpp"
#include "shared/voxel_anim.hpp"
#include "shared/warhead_type.hpp"
#include "shared/weapon_type.hpp"
#include "shared/particle_system.hpp"
#include "shared/particle.hpp"
#include "shared/bullet_type.hpp"
#include "shared/bullet.hpp"
#include "shared/waypoint_path.hpp"
#include "shared/smudge_type.hpp"
#include "shared/overlay_type.hpp"
#include "shared/light_source.hpp"
#include "shared/building_light.hpp"
#include "shared/tube.hpp"
#include "shared/side.hpp"
#include "shared/tiberium.hpp"
#include "shared/empulse_class.hpp"
#include "shared/super_weapon_type.hpp"
#include "shared/super.hpp"
#include "shared/terrain_type.hpp"
#include "shared/terrain.hpp"
#include "shared/object.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Compute_CRC@UnknownIDSource@@QBEXAAVWWCRCEngine@@@Z=00662e00
// @ref ??_EWaypointClass@@QAEPAXI@Z=0041b890

WWCRCEngine __fastcall Game_CRC()
{
    WWCRCEngine crc;
    int index;
    unknown_id_source_a3d290->Compute_CRC(crc);
    for (index = 0; index < HouseTypes.Count(); index++) {
        HouseTypes[index]->Compute_CRC(crc);
    }
    for (index = 0; index < Houses.Count(); index++) {
        Houses[index]->Compute_CRC(crc);
    }
    for (index = 0; index < UnitTypes.Count(); index++) {
        UnitTypes[index]->Compute_CRC(crc);
    }
    for (index = 0; index < Units.Count(); index++) {
        Units[index]->Compute_CRC(crc);
    }
    for (index = 0; index < InfantryTypes.Count(); index++) {
        InfantryTypes[index]->Compute_CRC(crc);
    }
    for (index = 0; index < Infantry.Count(); index++) {
        Infantry[index]->Compute_CRC(crc);
    }
    for (index = 0; index < BuildingTypes.Count(); index++) {
        BuildingTypes[index]->Compute_CRC(crc);
    }
    for (index = 0; index < unknown_BuildingClass_list_00a40af8.Count(); index++) {
        unknown_BuildingClass_list_00a40af8[index]->Compute_CRC(crc);
    }
    for (index = 0; index < AircraftTypes.Count(); index++) {
        AircraftTypes[index]->Compute_CRC(crc);
    }
    for (index = 0; index < Aircraft.Count(); index++) {
        Aircraft[index]->Compute_CRC(crc);
    }
    for (index = 0; index < AITriggerTypes.Count(); index++) {
        AITriggerTypes[index]->Compute_CRC(crc);
    }
    for (index = 0; index < Anims.Count(); index++) {
        Anims[index]->Compute_CRC(crc);
    }
    for (index = 0; index < AnimTypes.Count(); index++) {
        AnimTypes[index]->Compute_CRC(crc);
    }
    for (index = 0; index < TaskForces.Count(); index++) {
        TaskForces[index]->Compute_CRC(crc);
    }
    for (index = 0; index < TeamTypes.Count(); index++) {
        TeamTypes[index]->Compute_CRC(crc);
    }
    for (index = 0; index < Teams.Count(); index++) {
        Teams[index]->Compute_CRC(crc);
    }
    for (index = 0; index < ScriptTypes.Count(); index++) {
        ScriptTypes[index]->Compute_CRC(crc);
    }
    for (index = 0; index < Scripts.Count(); index++) {
        Scripts[index]->Compute_CRC(crc);
    }
    for (index = 0; index < unknown_TagTypeClass_list_00abfea0.Count(); index++) {
        unknown_TagTypeClass_list_00abfea0[index]->Compute_CRC(crc);
    }
    for (index = 0; index < unknown_TagClass_list_00abfe48.Count(); index++) {
        unknown_TagClass_list_00abfe48[index]->Compute_CRC(crc);
    }
    for (index = 0; index < TriggerTypes.Count(); index++) {
        TriggerTypes[index]->Compute_CRC(crc);
    }
    for (index = 0; index < unknown_TriggerClass_list_00a40aa0.Count(); index++) {
        unknown_TriggerClass_list_00a40aa0[index]->Compute_CRC(crc);
    }
    for (index = 0; index < unknown_TActionClass_list_00abfd88.Count(); index++) {
        unknown_TActionClass_list_00abfd88[index]->Compute_CRC(crc);
    }
    for (index = 0; index < unknown_TEventClass_list_00ac0808.Count(); index++) {
        unknown_TEventClass_list_00ac0808[index]->Compute_CRC(crc);
    }
    for (index = 0; index < Factories.Count(); index++) {
        Factories[index]->Compute_CRC(crc);
    }
    for (index = 0; index < VoxelAnimTypes.Count(); index++) {
        VoxelAnimTypes[index]->Compute_CRC(crc);
    }
    for (index = 0; index < unknown_VoxelAnimClass_list_008399d0.Count(); index++) {
        unknown_VoxelAnimClass_list_008399d0[index]->Compute_CRC(crc);
    }
    for (index = 0; index < unknown_WarheadTypeClass_list_00839b00.Count(); index++) {
        unknown_WarheadTypeClass_list_00839b00[index]->Compute_CRC(crc);
    }
    for (index = 0; index < unknown_WeaponTypeClass_list_00839b90.Count(); index++) {
        unknown_WeaponTypeClass_list_00839b90[index]->Compute_CRC(crc);
    }
    for (index = 0; index < ParticleTypes.Count(); index++) {
        ParticleTypes[index]->Compute_CRC(crc);
    }
    for (index = 0; index < unknown_ParticleClass_list_00a35e28.Count(); index++) {
        unknown_ParticleClass_list_00a35e28[index]->Compute_CRC(crc);
    }
    for (index = 0; index < ParticleSystems.Count(); index++) {
        ParticleSystems[index]->Compute_CRC(crc);
    }
    for (index = 0; index < ParticleSystemTypes.Count(); index++) {
        ParticleSystemTypes[index]->Compute_CRC(crc);
    }
    for (index = 0; index < BulletTypes.Count(); index++) {
        BulletTypes[index]->Compute_CRC(crc);
    }
    for (index = 0; index < unknown_BulletClass_list_00a40ce8.Count(); index++) {
        unknown_BulletClass_list_00a40ce8[index]->Compute_CRC(crc);
    }
    for (index = 0; index < unknown_WaypointPathClass_list_00b25590.Count(); index++) {
        unknown_WaypointPathClass_list_00b25590[index]->Compute_CRC(crc);
    }
    for (index = 0; index < SmudgeTypes.Count(); index++) {
        SmudgeTypes[index]->Compute_CRC(crc);
    }
    for (index = 0; index < OverlayTypes.Count(); index++) {
        OverlayTypes[index]->Compute_CRC(crc);
    }
    for (index = 0; index < unknown_LightSourceClass_list_00a6e818.Count(); index++) {
        unknown_LightSourceClass_list_00a6e818[index]->Compute_CRC(crc);
    }
    for (index = 0; index < BuildingLights.Count(); index++) {
        BuildingLights[index]->Compute_CRC(crc);
    }
    for (index = 0; index < unknown_TubeClass_list_008661c8.Count(); index++) {
        unknown_TubeClass_list_008661c8[index]->Compute_CRC(crc);
    }
    for (index = 0; index < Sides.Count(); index++) {
        Sides[index]->Compute_CRC(crc);
    }
    for (index = 0; index < unknown_TiberiumClass_list_00ac0b30.Count(); index++) {
        unknown_TiberiumClass_list_00ac0b30[index]->Compute_CRC(crc);
    }
    for (index = 0; index < EMPulseClass::Array.Count(); index++) {
        EMPulseClass::Array[index]->Compute_CRC(crc);
    }
    for (index = 0; index < SuperWeaponTypes.Count(); index++) {
        SuperWeaponTypes[index]->Compute_CRC(crc);
    }
    for (index = 0; index < Supers.Count(); index++) {
        Supers[index]->Compute_CRC(crc);
    }
    for (index = 0; index < TerrainTypes.Count(); index++) {
        TerrainTypes[index]->Compute_CRC(crc);
    }
    for (index = 0; index < Terrains.Count(); index++) {
        Terrains[index]->Compute_CRC(crc);
    }
    if (unknown_player_a35db4 != 0) {
        crc((long)unknown_player_a35db4->ArrayIndex);
    }
    crc((long)Frame);
    crc((long)unknown_objects_a40c60.Count());
    return crc;
}

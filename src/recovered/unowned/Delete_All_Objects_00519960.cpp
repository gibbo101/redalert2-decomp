// void __fastcall Delete_All_Objects_00519960() (0x00519960)
// Deletes every game object (name not recovered): the indexed objects, then each class list
// (deleting its first entry until it is empty; bullets through Release) with Unknown_006ecf10
// after each, the bolts, line trails and laser draws, the abstract types, the tactical view and
// the map's cells (MapClass slot 23), with the live-object counter raised meanwhile.
// __fastcall: as cdecl the epilogue's pop ebx is scheduled before the counter's dec.
// @ref ?Unknown_0042E150@Unknown84E8D0@@QAEXXZ=0042e150
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"
#include "shared/house.hpp"
#include "shared/mouse_class.hpp"
#include "shared/object_lists.hpp"
#include "shared/object.hpp"
#include "shared/terrain_object_index.hpp"
#include "shared/bullet.hpp"
#include "shared/tag.hpp"
#include "shared/trigger.hpp"
#include "shared/tube.hpp"
#include "shared/building_light.hpp"
#include "shared/overlay.hpp"
#include "shared/particle_system.hpp"
#include "shared/wave.hpp"
#include "shared/factory_class.hpp"
#include "shared/side.hpp"
#include "shared/team.hpp"
#include "shared/house.hpp"
#include "shared/anim.hpp"
#include "shared/script.hpp"
#include "shared/radsite.hpp"
#include "shared/light_source.hpp"
#include "shared/empulse_class.hpp"
#include "shared/capture_manager.hpp"
#include "shared/parasite.hpp"
#include "shared/temporal.hpp"
#include "shared/spawn_manager.hpp"
#include "shared/spawn_manager_list.hpp"
#include "shared/spot_light.hpp"
#include "shared/fogged_object.hpp"
#include "shared/alpha_shape.hpp"
#include "shared/alpha_shape_list.hpp"
#include "shared/terrain.hpp"
#include "shared/abstract_type.hpp"
#include "shared/ebolt.hpp"
#include "shared/line_trail.hpp"
#include "shared/laser_draw.hpp"
#include "shared/tactical.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_globals.hpp"

void __fastcall Delete_All_Objects_00519960()
{
    unknown_a40774++;
    unknown_objects_ac0cd8.Clear();
    while (unknown_object_index_abff58.Count()) {
        delete unknown_object_index_abff58.Fetch_By_Position(0);
    }
    Unknown_006ecf10();
    while (unknown_BulletClass_list_00a40ce8.Count()) {
        unknown_BulletClass_list_00a40ce8[0]->Release();
    }
    Unknown_006ecf10();
    while (unknown_objects_a40368.Count()) {
        delete unknown_objects_a40368[0];
    }
    Unknown_006ecf10();
    while (unknown_TagClass_list_00abfe48.Count()) {
        delete unknown_TagClass_list_00abfe48[0];
    }
    Unknown_006ecf10();
    while (unknown_TriggerClass_list_00a40aa0.Count()) {
        delete unknown_TriggerClass_list_00a40aa0[0];
    }
    Unknown_006ecf10();
    while (unknown_TubeClass_list_008661c8.Count()) {
        delete unknown_TubeClass_list_008661c8[0];
    }
    Unknown_006ecf10();
    while (BuildingLights.Count()) {
        delete BuildingLights[0];
    }
    Unknown_006ecf10();
    while (unknown_OverlayClass_list_00a40c00.Count()) {
        delete unknown_OverlayClass_list_00a40c00[0];
    }
    Unknown_006ecf10();
    while (ParticleSystems.Count()) {
        delete ParticleSystems[0];
    }
    Unknown_006ecf10();
    while (Waves.Count()) {
        delete Waves[0];
    }
    Unknown_006ecf10();
    while (Factories.Count()) {
        delete Factories[0];
    }
    Unknown_006ecf10();
    while (Sides.Count()) {
        delete Sides[0];
    }
    Unknown_006ecf10();
    while (Teams.Count()) {
        delete Teams[0];
    }
    Unknown_006ecf10();
    while (Houses.Count()) {
        delete Houses[0];
    }
    Unknown_006ecf10();
    while (Anims.Count()) {
        delete Anims[0];
    }
    Unknown_006ecf10();
    while (Scripts.Count()) {
        delete Scripts[0];
    }
    Unknown_006ecf10();
    while (unknown_RadSiteClass_list_00ab6620.Count()) {
        delete unknown_RadSiteClass_list_00ab6620[0];
    }
    Unknown_006ecf10();
    while (unknown_LightSourceClass_list_00a6e818.Count()) {
        delete unknown_LightSourceClass_list_00a6e818[0];
    }
    Unknown_006ecf10();
    while (EMPulseClass::Array.Count()) {
        delete EMPulseClass::Array[0];
    }
    Unknown_006ecf10();
    while (unknown_CaptureManagerClass_list_008505a0.Count()) {
        delete unknown_CaptureManagerClass_list_008505a0[0];
    }
    Unknown_006ecf10();
    while (unknown_ParasiteClass_list_00a76430.Count()) {
        delete unknown_ParasiteClass_list_00a76430[0];
    }
    Unknown_006ecf10();
    while (unknown_TemporalClass_list_00ac02e0.Count()) {
        delete unknown_TemporalClass_list_00ac02e0[0];
    }
    Unknown_006ecf10();
    while (unknown_SpawnManagerClass_list_00abd028.Count()) {
        delete unknown_SpawnManagerClass_list_00abd028[0];
    }
    Unknown_006ecf10();
    while (unknown_BombClass_list_0084eb78.Count()) {
        delete unknown_BombClass_list_0084eb78[0];
    }
    Unknown_006ecf10();
    while (unknown_SpotLightClass_list_00a731c0.Count()) {
        delete unknown_SpotLightClass_list_00a731c0[0];
    }
    Unknown_006ecf10();
    while (FoggedObjectClass::Array.Count()) {
        delete FoggedObjectClass::Array[0];
    }
    Unknown_006ecf10();
    while (unknown_AlphaShapeClass_list_0083c648.Count()) {
        delete unknown_AlphaShapeClass_list_0083c648[0];
    }
    Unknown_006ecf10();
    while (Terrains.Count()) {
        delete Terrains[0];
    }
    Unknown_006ecf10();
    EBolt::Delete_All_004B23B0();
    LineTrail::Delete_All();
    LaserDrawClass::Clear_All();
    while (AbstractTypes.Count()) {
        delete AbstractTypes[0];
    }
    Unknown_006ecf10();
    delete unknown_tactical_83996c;
    unknown_tactical_83996c = 0;
    Map.unknown_slot23();
    Unknown_006ecf10();
    unknown_object_84e8d0.Unknown_0042E150();
    unknown_a40774--;
}

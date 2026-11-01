void AI_Submitted_Objects()
{
    int index;
    for (index = Anims.Count() - 1; index >= 0; index--) {
        AnimClass *anim = Anims[index];
        if (anim->unknown_84) anim->AI();
    }
    for (index = BuildingLights.Count() - 1; index >= 0; index--) {
        BuildingLightClass *blight = BuildingLights[index];
        if (blight->unknown_84) blight->AI();
    }
    for (index = unknown_BulletClass_list_00a40ce8.Count() - 1; index >= 0; index--) {
        BulletClass *bullet = unknown_BulletClass_list_00a40ce8[index];
        if (bullet->unknown_84) bullet->AI();
    }
    for (index = unknown_BuildingClass_list_00a40af8.Count() - 1; index >= 0; index--) {
        BuildingClass *building = unknown_BuildingClass_list_00a40af8[index];
        if (building->unknown_84) building->AI();
    }
    for (index = Aircraft.Count() - 1; index >= 0; index--) {
        AircraftClass *aircraft = Aircraft[index];
        if (aircraft->unknown_84) aircraft->AI();
    }
    for (index = Infantry.Count() - 1; index >= 0; index--) {
        InfantryClass *infantry = Infantry[index];
        if (infantry->unknown_84) infantry->AI();
    }
    for (index = Units.Count() - 1; index >= 0; index--) {
        UnitClass *unit = Units[index];
        if (unit->unknown_84) unit->AI();
    }
    for (index = ParticleSystems.Count() - 1; index >= 0; index--) {
        ParticleSystemClass *partsys = ParticleSystems[index];
        if (partsys->unknown_84) partsys->AI();
    }
    for (index = Terrains.Count() - 1; index >= 0; index--) {
        TerrainClass *terrain = Terrains[index];
        if (terrain->unknown_84) terrain->AI();
    }
    for (index = unknown_VoxelAnimClass_list_008399d0.Count() - 1; index >= 0; index--) {
        VoxelAnimClass *voxelanim = unknown_VoxelAnimClass_list_008399d0[index];
        if (voxelanim->unknown_84) voxelanim->AI();
    }
    for (index = Waves.Count() - 1; index >= 0; index--) {
        WaveClass *wave = Waves[index];
        if (wave->unknown_84) wave->AI();
    }
}
// @ref ?Aircraft@@3V?$DynamicVectorClass@PAVAircraftClass@@@@A=00a40398
// @ref ?Anims@@3V?$DynamicVectorClass@PAVAnimClass@@@@A=00a40960
// @ref ?BuildingLights@@3V?$DynamicVectorClass@PAVBuildingLightClass@@@@A=00866220
// @ref ?Infantry@@3V?$DynamicVectorClass@PAVInfantryClass@@@@A=00a35e48
// @ref ?ParticleSystems@@3V?$DynamicVectorClass@PAVParticleSystemClass@@@@A=00a32280
// @ref ?Terrains@@3V?$DynamicVectorClass@PAVTerrainClass@@@@A=00a40940
// @ref ?Units@@3V?$DynamicVectorClass@PAVUnitClass@@@@A=00866198
// @ref ?Waves@@3V?$DynamicVectorClass@PAVWaveClass@@@@A=00a40be8
// @ref ?unknown_BuildingClass_list_00a40af8@@3V?$DynamicVectorClass@PAVBuildingClass@@@@A=00a40af8
// @ref ?unknown_BulletClass_list_00a40ce8@@3V?$DynamicVectorClass@PAVBulletClass@@@@A=00a40ce8
// @ref ?unknown_VoxelAnimClass_list_008399d0@@3V?$DynamicVectorClass@PAVVoxelAnimClass@@@@A=008399d0

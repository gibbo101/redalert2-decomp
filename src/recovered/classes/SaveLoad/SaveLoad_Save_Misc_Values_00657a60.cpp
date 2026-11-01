// HRESULT __fastcall Save_Misc_Values(IStream *stream) (0x00657A60; TibSun saveload.cpp)
// Writes the gas system, the player's house, the frame, the selected objects,
// the land types, the lightning storm, the two scenario tag lists, the crate
// tables, the mission table and 0x00AB9174.
#include "shared/com_persist.hpp"
#include "shared/particle_system.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/cd_timer.hpp"
#include "shared/object.hpp"
#include "shared/ground_type.hpp"
#include "shared/lightning_storm.hpp"
#include "shared/scenario_tags.hpp"
#include "shared/rules.hpp"
#include "shared/mission.hpp"

HRESULT __fastcall Save_Misc_Values(IStream *stream)
{
    int i;
    int count;
    HRESULT res;

    res = stream->Write(&unknown_gas_cloud_system_a40d20, sizeof(unknown_gas_cloud_system_a40d20), 0);
    if (FAILED(res)) {
        return res;
    }
    res = stream->Write(&unknown_player_a35db4, sizeof(unknown_player_a35db4), 0);
    if (FAILED(res)) {
        return res;
    }
    res = stream->Write(&Frame, sizeof(Frame), 0);
    if (FAILED(res)) {
        return res;
    }
    count = unknown_objects_a40c60.Count();
    res = stream->Write(&count, sizeof(count), 0);
    if (FAILED(res)) {
        return res;
    }
    for (i = 0; i < count; i++) {
        res = stream->Write(&unknown_objects_a40c60[i], sizeof(unknown_objects_a40c60[i]), 0);
        if (FAILED(res)) {
            return res;
        }
    }
    res = stream->Write(&Ground, sizeof(Ground), 0);
    if (FAILED(res)) {
        return res;
    }
    Save_Storm_0051F3F0(stream);
    count = unknown_tags_866160.Count();
    res = stream->Write(&count, sizeof(count), 0);
    if (FAILED(res)) {
        return res;
    }
    for (i = 0; i < count; i++) {
        res = stream->Write(&unknown_tags_866160[i], sizeof(unknown_tags_866160[i]), 0);
        if (FAILED(res)) {
            return res;
        }
    }
    count = unknown_tags_866238.Count();
    res = stream->Write(&count, sizeof(count), 0);
    if (FAILED(res)) {
        return res;
    }
    for (i = 0; i < count; i++) {
        res = stream->Write(&unknown_tags_866238[i], sizeof(unknown_tags_866238[i]), 0);
        if (FAILED(res)) {
            return res;
        }
    }
    res = stream->Write(&CrateShares, sizeof(CrateShares), 0);
    if (FAILED(res)) {
        return res;
    }
    res = stream->Write(&CrateAnims, sizeof(CrateAnims), 0);
    if (FAILED(res)) {
        return res;
    }
    res = stream->Write(&CrateData, sizeof(CrateData), 0);
    if (FAILED(res)) {
        return res;
    }
    res = stream->Write(&CrateWater, sizeof(CrateWater), 0);
    if (FAILED(res)) {
        return res;
    }
    res = stream->Write(&MissionControl, sizeof(MissionControl), 0);
    if (FAILED(res)) {
        return res;
    }
    res = stream->Write(&unknown_ab9174, sizeof(unknown_ab9174), 0);
    if (FAILED(res)) {
        return res;
    }
    return S_OK;
}

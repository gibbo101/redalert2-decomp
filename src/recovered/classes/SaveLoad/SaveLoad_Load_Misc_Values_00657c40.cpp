// HRESULT __fastcall Load_Misc_Values(IStream *stream) (0x00657C40; TibSun saveload.cpp)
// Reads what Save_Misc_Values 0x00657A60 writes, re-adding the saved selected
// objects and tags and swizzling every saved pointer.
#include "shared/com_persist.hpp"
#include "shared/swizzle.hpp"

HRESULT __fastcall Load_Misc_Values(IStream *stream)
{
    int i;
    int count;
    void *ptr;
    HRESULT res;

    res = stream->Read(&unknown_gas_cloud_system_a40d20, sizeof(unknown_gas_cloud_system_a40d20), 0);
    if (FAILED(res)) {
        return res;
    }
    SwizzleManager.Swizzle((void **)&unknown_gas_cloud_system_a40d20);
    res = stream->Read(&unknown_player_a35db4, sizeof(unknown_player_a35db4), 0);
    if (FAILED(res)) {
        return res;
    }
    SwizzleManager.Swizzle((void **)&unknown_player_a35db4);
    res = stream->Read(&Frame, sizeof(Frame), 0);
    if (FAILED(res)) {
        return res;
    }
    res = stream->Read(&count, sizeof(count), 0);
    if (FAILED(res)) {
        return res;
    }
    for (i = 0; i < count; i++) {
        res = stream->Read(&ptr, sizeof(ptr), 0);
        if (FAILED(res)) {
            return res;
        }
        unknown_objects_a40c60.Add(*(ObjectClass **)&ptr);
    }
    for (i = 0; i < unknown_objects_a40c60.Count(); i++) {
        SwizzleManager.Swizzle((void **)&unknown_objects_a40c60[i]);
    }
    res = stream->Read(&Ground, sizeof(Ground), 0);
    if (FAILED(res)) {
        return res;
    }
    Load_Storm_0051F5E0(stream);
    res = stream->Read(&count, sizeof(count), 0);
    if (FAILED(res)) {
        return res;
    }
    for (i = 0; i < count; i++) {
        res = stream->Read(&ptr, sizeof(ptr), 0);
        if (FAILED(res)) {
            return res;
        }
        unknown_tags_866160.Add(*(TagClass **)&ptr);
    }
    for (i = 0; i < unknown_tags_866160.Count(); i++) {
        SwizzleManager.Swizzle((void **)&unknown_tags_866160[i]);
    }
    res = stream->Read(&count, sizeof(count), 0);
    if (FAILED(res)) {
        return res;
    }
    for (i = 0; i < count; i++) {
        res = stream->Read(&ptr, sizeof(ptr), 0);
        if (FAILED(res)) {
            return res;
        }
        unknown_tags_866238.Add(*(TagClass **)&ptr);
    }
    for (i = 0; i < unknown_tags_866238.Count(); i++) {
        SwizzleManager.Swizzle((void **)&unknown_tags_866238[i]);
    }
    res = stream->Read(&CrateShares, sizeof(CrateShares), 0);
    if (FAILED(res)) {
        return res;
    }
    res = stream->Read(&CrateAnims, sizeof(CrateAnims), 0);
    if (FAILED(res)) {
        return res;
    }
    res = stream->Read(&CrateData, sizeof(CrateData), 0);
    if (FAILED(res)) {
        return res;
    }
    res = stream->Read(&CrateWater, sizeof(CrateWater), 0);
    if (FAILED(res)) {
        return res;
    }
    res = stream->Read(&MissionControl, sizeof(MissionControl), 0);
    if (FAILED(res)) {
        return res;
    }
    res = stream->Read(&unknown_ab9174, sizeof(unknown_ab9174), 0);
    if (FAILED(res)) {
        return res;
    }
    return S_OK;
}

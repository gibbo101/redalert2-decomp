// HRESULT __stdcall HouseClass::Load(IStream *stream) (0x004EDA60, slot 5)
// The counterpart of Save 0x004EE440: empties the lists (releasing the
// connection points and deleting the super weapons), restores the house in
// place, loads the base plan and counters, fixes up the pointers, reads the
// lists back (count, then elements) and finally the +0x56CC object.
// The scout swizzle loop fixes up the last node's house each pass, as the
// original does. The body after the base Load is the SUCCEEDED block with
// one shared count (as in BuildingClass::Load): count's scope then covers
// the placement new, whose NoInitClass temporary holds the dead this slot,
// so count takes the stream slot and each list element the this slot.
#include "shared/techno.hpp"
#include "shared/house_views.hpp"
// @ref ?Load@UnknownHouseCounter@@QAEXPAUIStream@@@Z=00491e10
// @ref ?unknown_func_4a6b10@UnknownHouseBase@@QAEXXZ=004a6b10
// @ref _unknown_iid_7a2030=007a2030

extern "C" GUID const unknown_iid_7a2030;   // 0x007A2030 the +0x56CC object's interface

// Reads a list saved by SAVE_LIST: its count, then each element; returns a failure.
#define LOAD_LIST(stream, list, type)                                       \
    {                                                                       \
        count = 0;                                                          \
        result = (stream)->Read(&count, sizeof(count), 0);                  \
        if (FAILED(result)) {                                               \
            return result;                                                  \
        }                                                                   \
        while (count--) {                                                   \
            type value = 0;                                                 \
            result = (stream)->Read(&value, sizeof(value), 0);              \
            if (FAILED(result)) {                                           \
                return result;                                              \
            }                                                               \
            (list).Add(value);                                              \
        }                                                                   \
    }

HRESULT __stdcall HouseClass::Load(IStream *stream)
{
    unknown_50.Clear();
    Buildings.Clear();
    unknown_80.Clear();
    unknown_98.Clear();
    unknown_b0.Clear();
    for (int point = 0; point < ConnectionPoints.Count(); point++) {
        while (ConnectionPoints[point]->Release() > 0) {
        }
        ConnectionPoints[point] = 0;
    }
    ConnectionPoints.Clear();
    while (Supers.Count()) {
        delete Supers[0];
        Supers.Delete(0);
    }

    HRESULT result = AbstractClass::Load(stream);
    if (SUCCEEDED(result)) {
        int count;
        new (this) HouseClass(NoInitClass());
        unknown_55f0.Load(stream);
        unknown_5420.Load(stream);
        unknown_5430.Load(stream);
        unknown_5440.Load(stream);
        unknown_5450.Load(stream);
        unknown_5460.Load(stream);
        unknown_5470.Load(stream);
        unknown_5480.Load(stream);
        unknown_5490.Load(stream);
        unknown_54a0.Load(stream);
        unknown_54b0.Load(stream);
        unknown_54c0.Load(stream);
        unknown_54d0.Load(stream);

        SwizzleManager.Swizzle((void **)&Type);
        SwizzleManager.Swizzle((void **)&unknown_52dc);
        SwizzleManager.Swizzle((void **)&unknown_52e0);
        SwizzleManager.Swizzle((void **)&unknown_52d8);
        SwizzleManager.Swizzle((void **)&unknown_52e4);
        SwizzleManager.Swizzle((void **)&unknown_52e8);
        SwizzleManager.Swizzle((void **)&unknown_52ec);
        SwizzleManager.Swizzle((void **)&unknown_52f0);
        SwizzleManager.Swizzle((void **)&unknown_52f4);
        SwizzleManager.Swizzle((void **)&unknown_52f8);
        SwizzleManager.Swizzle((void **)&unknown_5410);
        int index;
        for (index = 0; index < 12; index++) {
            SwizzleManager.Swizzle((void **)&WaypointPaths[index]);
        }
        for (index = 0; index < 3; index++) {
            unknown_5560[index].unknown_func_4a6b10();
        }

        LOAD_LIST(stream, Supers, SuperClass *);
        LOAD_LIST(stream, unknown_38, TagClass *);
        {
            count = 0;
            result = stream->Read(&count, sizeof(count), 0);
            if (FAILED(result)) {
                return result;
            }
            while (count--) {
                AngerStruct anger;
                result = stream->Read(&anger, sizeof(anger), 0);
                if (FAILED(result)) {
                    return result;
                }
                AngerNodes.Add(anger);
            }
        }
        for (index = 0; index < AngerNodes.Count(); index++) {
            SwizzleManager.Swizzle((void **)&AngerNodes[index].House);
        }
        {
            count = 0;
            result = stream->Read(&count, sizeof(count), 0);
            if (FAILED(result)) {
                return result;
            }
            while (count--) {
                ScoutStruct scout;
                result = stream->Read(&scout, sizeof(scout), 0);
                if (FAILED(result)) {
                    return result;
                }
                ScoutNodes.Add(scout);
            }
        }
        for (index = 0; index < ScoutNodes.Count(); index++) {
            SwizzleManager.Swizzle((void **)&ScoutNodes[ScoutNodes.Count() - 1].House);
        }
        LOAD_LIST(stream, unknown_50, BuildingClass *);
        LOAD_LIST(stream, Buildings, BuildingClass *);
        LOAD_LIST(stream, unknown_80, BuildingClass *);
        LOAD_LIST(stream, unknown_98, BuildingClass *);
        LOAD_LIST(stream, unknown_b0, BuildingClass *);

        for (index = 0; index < Supers.Count(); index++) {
            SwizzleManager.Swizzle((void **)&Supers[index]);
        }
        for (index = 0; index < unknown_38.Count(); index++) {
            SwizzleManager.Swizzle((void **)&unknown_38[index]);
        }
        for (index = 0; index < unknown_50.Count(); index++) {
            SwizzleManager.Swizzle((void **)&unknown_50[index]);
        }
        for (index = 0; index < Buildings.Count(); index++) {
            SwizzleManager.Swizzle((void **)&Buildings[index]);
        }
        for (index = 0; index < unknown_80.Count(); index++) {
            SwizzleManager.Swizzle((void **)&unknown_80[index]);
        }
        for (index = 0; index < unknown_98.Count(); index++) {
            SwizzleManager.Swizzle((void **)&unknown_98[index]);
        }
        for (index = 0; index < unknown_b0.Count(); index++) {
            SwizzleManager.Swizzle((void **)&unknown_b0[index]);
        }

        BOOL present = 0;
        result = stream->Read(&present, sizeof(present), 0);
        if (SUCCEEDED(result) && present) {
            result = OleLoadFromStream(stream, unknown_iid_7a2030, (void **)&unknown_56cc);
        }
    }
    return result;
}

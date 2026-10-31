// TechnoClass as the Map unit sees it (stand-in, like shared/map_cell.hpp for
// CellClass): the real shared/techno.hpp brings headers the Map unit has not.
// Only the members MapClass touches; slots 24-103 other than 70 are
// placeholders (slot numbers and offsets as shared/object.hpp / techno.hpp).
// Units that include shared/techno.hpp must not include this stand-in.
#ifndef RA2_SHARED_MAP_TECHNO_HPP
#define RA2_SHARED_MAP_TECHNO_HPP

#include "shared/abstract_class.hpp"
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"

class HouseClass;
class CellClass;
// ObjectClass as the Map unit sees it: only the virtual destructor (slot 8,
// AbstractClass), which deletes the display's pending object (0x0055B060).
class ObjectClass : public AbstractClass {
};

class TechnoClass : public AbstractClass {
public:
    virtual void unknown_slot24(); virtual void unknown_slot25(); virtual void unknown_slot26(); virtual void unknown_slot27(); virtual void unknown_slot28(); virtual void unknown_slot29();
    virtual void unknown_slot30(); virtual void unknown_slot31(); virtual void unknown_slot32(); virtual void unknown_slot33(); virtual void unknown_slot34(); virtual void unknown_slot35();
    virtual void unknown_slot36(); virtual void unknown_slot37(); virtual void unknown_slot38(); virtual void unknown_slot39(); virtual void unknown_slot40(); virtual void unknown_slot41();
    virtual void unknown_slot42(); virtual void unknown_slot43(); virtual void unknown_slot44(); virtual void unknown_slot45(); virtual void unknown_slot46(); virtual void unknown_slot47();
    virtual void unknown_slot48(); virtual void unknown_slot49(); virtual void unknown_slot50(); virtual void unknown_slot51(); virtual void unknown_slot52(); virtual void unknown_slot53();
    virtual void unknown_slot54(); virtual void unknown_slot55(); virtual void unknown_slot56(); virtual void unknown_slot57(); virtual void unknown_slot58(); virtual void unknown_slot59();
    virtual void unknown_slot60(); virtual void unknown_slot61(); virtual void unknown_slot62(); virtual void unknown_slot63(); virtual void unknown_slot64(); virtual void unknown_slot65();
    virtual void unknown_slot66(); virtual void unknown_slot67(); virtual void unknown_slot68(); virtual void unknown_slot69();
    virtual void unknown_slot70(bool arg1, bool arg2);              // slot 70 (+0x118; as shared/techno.hpp)
    virtual void unknown_slot71(); virtual void unknown_slot72(); virtual void unknown_slot73(); virtual void unknown_slot74(); virtual void unknown_slot75(); virtual void unknown_slot76();
    virtual void unknown_slot77(); virtual void unknown_slot78(); virtual void unknown_slot79(); virtual void unknown_slot80(); virtual void unknown_slot81(); virtual void unknown_slot82();
    virtual void unknown_slot83(); virtual void unknown_slot84(); virtual void unknown_slot85(); virtual void unknown_slot86(); virtual void unknown_slot87(); virtual void unknown_slot88();
    virtual void unknown_slot89(); virtual void unknown_slot90(); virtual void unknown_slot91(); virtual void unknown_slot92(); virtual void unknown_slot93(); virtual void unknown_slot94();
    virtual void unknown_slot95();
    virtual void unknown_slot96(HouseClass *house);                  // slot 96 (+0x180; MapClass 0x00568520: reveals the techno to a house)
    virtual void unknown_slot97(); virtual void unknown_slot98(); virtual void unknown_slot99(); virtual void unknown_slot100();
    virtual void unknown_slot101(); virtual void unknown_slot102(); virtual void unknown_slot103();
    virtual Cell unknown_slot104() const;                            // slot 104 (+0x1A0) the object's cell (as shared/object.hpp)

    // The distance to a cell (ObjectClass 0x005D4C00 takes an AbstractClass *; the Map
    // unit's CellClass stand-in has no AbstractClass base).
    int unknown_5d4c00(CellClass *target);

    char unknown_24[0x30 - 0x24];
    ObjectClass *unknown_30;                // +0x30 the next object in the cell (as shared/object.hpp)
    char unknown_34[0x74 - 0x34];
    bool unknown_74;                        // +0x74 (as shared/object.hpp)
    char unknown_75;
    bool unknown_76;                        // +0x76 (as shared/object.hpp)
    char unknown_77[0x7D - 0x77];
    bool unknown_7d;                        // +0x7D (as shared/object.hpp)
    char unknown_7e[0x1B4 - 0x7E];
    HouseClass *House;                      // +0x1B4 (as shared/techno.hpp)
    char unknown_1b8[0x32D - 0x1B8];
    bool unknown_32d;                       // +0x32D (as shared/techno.hpp)
};

// A building type as MapClass 0x0055ACD0 sees it (stand-in; shared/building_type_class.hpp).
class BuildingTypeClass {
public:
    char unknown_000[0x1351];
    bool Gate;                              // +0x1351
    char unknown_1352[0x135A - 0x1352];
    bool FirestormWall;                     // +0x135A (TibSun IsFirestormWall; Map 0x00569FB0)
};

// A building as MapClass 0x00567380 and 0x0055ACD0 see it (stand-in).
class BuildingClass : public TechnoClass {
public:
    bool unknown_44d880();                  // 0x0044D880 (as shared/building_class.hpp)
    bool unknown_44d7d0();                  // 0x0044D7D0 (as shared/building_class.hpp)

    char unknown_330[0x418 - 0x330];
    BuildingTypeClass *Type;                // +0x418
};

// Every building (0x00A40AF8; as shared/techno.hpp).
extern DynamicVectorClass<BuildingClass *> unknown_BuildingClass_list_00a40af8;

// A house type as MapClass 0x00567380 sees it (stand-in; shared/house_type.hpp).
class HouseTypeClass {
public:
    char unknown_000[0xB8];
    int House;                              // +0xB8 the index in HouseTypes (as shared/house_type.hpp)
    char unknown_bc[0x1A7 - 0xBC];
    bool WallOwner;                         // +0x1A7
};

// Every techno (0x00A40C20; as shared/planning.hpp).
extern DynamicVectorClass<TechnoClass *> unknown_list_a40c20;

// AnimClass as the Map unit sees it (stand-in; shared/anim.hpp brings headers whose types
// the stand-ins above redefine): the constructor and the size operator new allocates
// (MapClass 0x005576A0 and its three twins place bridge explosions with it).
class AnimTypeClass;
class AnimClass : public ObjectClass {
public:
    AnimClass(AnimTypeClass *type, CoordStruct const &coord, int loop_delay, int loops, int flags, int zadjust);   // 0x00420110 (as shared/anim.hpp)
    virtual HRESULT __stdcall GetClassID(GUID *classid);
    virtual HRESULT __stdcall Load(IStream *stream);
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);
    virtual int Kind_Of() const;
    virtual int Size_Of() const;
    char unknown_24[0x177 - sizeof(AbstractClass)];
    bool unknown_177;                       // +0x177 deleted by the map's Overpass (0x0054B2E0)
    char unknown_178[0x1A8 - 0x178];        // sizeof(AnimClass) 0x1A8 (as shared/anim.hpp)
};
typedef char AnimClass_stand_in_size[(sizeof(AnimClass) == 0x1A8) ? 1 : -1];
extern DynamicVectorClass<AnimClass *> Anims;     // 0x00A40960 (as shared/anim.hpp)

// TagClass as the Map unit sees it (stand-in; shared/tag.hpp brings the type and trigger
// headers whose types the stand-ins above redefine): the cross-line tests as shared/tag.hpp declares them
// (MapClass 0x0054B2E0 tests the cross-line kinds of cell tags).
class TagClass {
public:
    bool unknown_func_6b3d90() const;       // 0x006B3D90 (as shared/tag.hpp; TibSun Is_Cross_Vertical)
    bool unknown_func_6b3da0() const;       // 0x006B3DA0 (as shared/tag.hpp; TibSun Is_Cross_Horizontal)
};

#endif

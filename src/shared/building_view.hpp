// A view of BuildingClass for BuildingType.cpp: the constructor slots 32 and
// 35 call and the ObjectClass virtuals slot 32 uses (0x5E0 bytes). The full class is in
// shared/building.hpp, which BuildingType.cpp cannot include: its techno
// chain pulls in shared/random.hpp, whose static members take compiler
// counter values and renumber the unit's static initializers (the slot 36
// exit thunk is _$E41 in the original). Never include both headers in one
// unit.
#ifndef RA2_BUILDING_VIEW_HPP
#define RA2_BUILDING_VIEW_HPP
// This existing view supplies the unit's BuildingClass definition.
#define RA2_BUILDING_FULL

#include "shared/building_type.hpp"

class BuildingClass : public ObjectClass {
public:
    virtual ~BuildingClass(); // original439240; existing full-class declaration
    BuildingClass(BuildingTypeClass *type, HouseClass *house);         // 0x00438CE0

    virtual HRESULT __stdcall GetClassID(GUID *clsid);
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);
    virtual int Kind_Of() const;
    virtual int Size_Of() const;

    bool unknown_44d900(BuildingTypeClass const *upgrade,HouseClass *house); // identified0044D900

    char unknown_098[0x418 - 0x98];
    BuildingTypeClass *Type; // existing full-class member +418
    char unknown_41c[0x5E0 - 0x41C];         // TechnoClass and BuildingClass members
};

#endif

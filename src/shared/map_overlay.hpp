// OverlayClass layout as the Map unit sees it. Constructor005DA7D0 and allocation9C
// are independently visible at54B560; the full declaration lives in overlay.hpp.
#ifndef RA2_SHARED_MAP_OVERLAY_HPP
#define RA2_SHARED_MAP_OVERLAY_HPP
#include "shared/map_techno.hpp"
class OverlayTypeClass;
class OverlayClass : public ObjectClass {
public:
    OverlayClass(OverlayTypeClass *type, Cell const &cell, int house = -1);
    virtual ~OverlayClass();
    virtual HRESULT __stdcall GetClassID(GUID *classid);
    virtual HRESULT __stdcall Load(IStream *stream);
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);
    virtual int Kind_Of() const;
    virtual int Size_Of() const;
    char unknown_24[0x98 - sizeof(ObjectClass)];
    OverlayTypeClass *Class;
};
typedef char OverlayClass_map_size[(sizeof(OverlayClass) == 0x9c) ? 1 : -1];
extern DynamicVectorClass<OverlayTypeClass *> OverlayTypes;
#endif

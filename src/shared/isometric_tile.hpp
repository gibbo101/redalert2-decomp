// IsometricTileClass: a placed isometric map tile object (IsoTile.cpp, unit
// 0x00527890-0x0052837E; RTTI vtables 0x007A47D0 primary, 0x007A47B4
// IRTTITypeInfo at +4, 0x007A47AC INoticeSink, 0x007A47A4 INoticeSource).
//
// Layout (constructor 0x00527ED0, Load 0x005280E0): ObjectClass (0x98) and
//   +0x98  IsometricTileTypeClass *Type   IsoTileTypes[type index]
//   size 0x9C (Size_Of)
// Every tile is added to IsoTiles (0x00832448). Hypotheses throughout.
#ifndef RA2_SHARED_ISOMETRIC_TILE_HPP
#define RA2_SHARED_ISOMETRIC_TILE_HPP

#include "shared/unknown_globals.hpp"
#include "shared/object.hpp"

class IsometricTileClass;
class IsometricTileTypeClass;

extern "C" GUID const CLSID_IsometricTileClass;       // 0x007A1BB0
extern Cell const unknown_cell_a52520;           // 0x00A52520 (the "no cell" value; hypothesis)

extern DynamicVectorClass<IsometricTileClass *> IsoTiles;               // 0x00832448
extern DynamicVectorClass<IsometricTileTypeClass *> IsoTileTypes;       // 0x00A40CD0

class IsometricTileClass : public ObjectClass {
public:
    IsometricTileClass(int type, Cell const &cell);           // 0x00527ED0
    IsometricTileClass(NoInitClass const &noinit) : ObjectClass(noinit) {}   // (inlined into Load)
    virtual ~IsometricTileClass();                                  // 0x00527FD0

    virtual HRESULT __stdcall GetClassID(GUID *clsid)               // 0x00528200 slot 3 (inline)
    {
        if (clsid == 0) {
            return E_POINTER;
        }
        *clsid = CLSID_IsometricTileClass;
        return S_OK;
    }
    virtual HRESULT __stdcall Load(IStream *stream);                // 0x005280E0 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x00528140 slot 6
    virtual int Kind_Of() const { return 0x11; }                    // 0x005281F0 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(IsometricTileClass); }  // 0x005281E0 slot 12 (inline)
    virtual ObjectTypeClass *Class_Of() const { return (ObjectTypeClass *)Type; }  // 0x00528240 slot 33 (inline)
    virtual bool unknown_slot52();                                 // 0x00528190
    virtual bool unknown_slot53(CoordStruct const *coord, int dir);   // 0x00528160
    virtual void unknown_slot67(int arg1, int arg2) {}              // 0x00528250 (inline)
    virtual bool unknown_slot71(int arg1);                          // 0x00527A80

    IsometricTileTypeClass *Type;   // +0x98
};

#endif

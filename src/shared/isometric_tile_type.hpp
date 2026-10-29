// IsometricTileTypeClass: an isometric map tile type (IsoTileType.cpp, unit
// 0x00528380-0x0052EF6F; RTTI vtables 0x007A51A8 primary (40 slots),
// 0x007A518C IRTTITypeInfo at +4, 0x007A5184 INoticeSink, 0x007A517C
// INoticeSource).
//
// Partial layout (NoInitClass constructor 0x00529120, destructor 0x00529190,
// Load 0x0052E1C0; names are hypotheses):
//   +0x000  ObjectTypeClass (0x264)
//   +0x264  int ArrayIndex                 (slot 16 answers it)
//   +0x274  DynamicVectorClass<unsigned short *> unknown_274
//           (constructed even by the NoInitClass constructor; Load rebuilds it)
//   +0x28C  AbstractClass *unknown_28c     (owned: deleted by the destructor,
//                                           swizzled by Load)
//   size 0x2DC (Size_Of)
// The light converters (0x00832398) are released before a load.
#ifndef RA2_SHARED_ISOMETRIC_TILE_TYPE_HPP
#define RA2_SHARED_ISOMETRIC_TILE_TYPE_HPP

#include "shared/object_type.hpp"
#include "shared/light_convert.hpp"

// Every light converter (0x00832398): shared/light_convert.hpp.

extern "C" GUID const CLSID_IsometricTileTypeClass;

// The colour table list's constructor expands in place while its base
// constructor stays a call (0x0052ED90) in this unit.
template <>
VectorClass<unsigned short *>::VectorClass(unsigned size, unsigned short * const *array);
template <>
inline DynamicVectorClass<unsigned short *>::DynamicVectorClass(unsigned size, unsigned short * const *array)
    : VectorClass<unsigned short *>(size, array)
{
    GrowthStep = 10;
    ActiveCount = 0;
}

// The image of an isometric tile type (a TMP file): a 16-byte header, then
// one offset per cell of the grid, 0 where the cell has no tile (slot 36).
struct IsoTileImageStruct {
    int unknown_00[4];                                  // +0x00 header (hypothesis: sizes)
    int Tiles[1];                                       // +0x10 per-cell tile offsets
};

// One cell's tile in the image (the Tiles entries point at it; hypothesis).
struct IsoTileCellStruct {
    char unknown_00[0x28];
    char unknown_28;                                    // +0x28 height (IsometricTileClass slot 71)
    char unknown_29;
    char unknown_2a;                                    // +0x2A (0x0052B6F0)
};

class IsometricTileTypeClass : public ObjectTypeClass {
public:
    class TileInsertType;

    IsometricTileTypeClass(NoInitClass const &noinit) : ObjectTypeClass(noinit) {}
    virtual ~IsometricTileTypeClass();                                  // 0x00529190

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x0052E2D0 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x0052E1C0 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x0052E2B0 slot 6
    virtual void Detach(AbstractClass *target, bool all = true);        // 0x0052E310 slot 10
    virtual int Kind_Of() const;                                        // 0x0052E680 slot 11
    virtual int Size_Of() const;                                        // 0x0052E690 slot 12
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x0052E0B0 slot 13
    virtual int unknown_slot16() const;                                 // 0x0052E6A0 (ArrayIndex)
    virtual CoordStruct unknown_slot27(CoordStruct const &coord) const; // 0x0052E090
    virtual bool unknown_slot32(Cell const &cell, HouseClass *house) const;   // 0x0052DFE0
    virtual ObjectClass *unknown_slot35(HouseClass *house) const;       // 0x0052E020
    virtual Cell const *unknown_slot36(int arg1) const;           // 0x00529450
    virtual void *unknown_slot39() const;                               // 0x005293D0

    void unknown_func_52b560();                                         // 0x0052B560 (loads the image)
    void unknown_func_52e3d0();                                         // 0x0052E3D0 (rebuilds unknown_274)
    char unknown_func_52b6f0(int index);                               // 0x0052B6F0 (a cell's +0x2A byte of the image; hypothesis)
    unsigned short unknown_func_52e360(int index, int value, bool second) const;    // 0x0052E360

    int ArrayIndex;                                     // +0x264
    char unknown_268[0x274 - 0x268];                    // +0x268
    DynamicVectorClass<unsigned short *> unknown_274;   // +0x274
    AbstractClass *unknown_28c;                         // +0x28C
    char unknown_290[0x298 - 0x290];                    // +0x290
    int unknown_298;                                    // +0x298 AnimTypes index (-1: none)
    char unknown_29c[0x2B0 - 0x29C];                    // +0x29C
    bool unknown_2b0;                                   // +0x2B0 (smudges allowed; map_cell_view.hpp)
    char unknown_2b1[0x2B4 - 0x2B1];                    // +0x2B1
    int unknown_2b4;                                    // +0x2B4 cells across (the image's tile grid; slot 36)
    int unknown_2b8;                                    // +0x2B8 cells down
    char unknown_2bc[0x2C4 - 0x2BC];                    // +0x2BC
    bool unknown_2c4;                                   // +0x2C4 (image loads on demand; hypothesis)
    char unknown_2c5[0x2DC - 0x2C5];                    // +0x2C5
};

#endif

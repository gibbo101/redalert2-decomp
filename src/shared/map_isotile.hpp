// IsometricTileTypeClass as the Map unit sees it (stand-in, like
// shared/map_techno.hpp): the real shared/isometric_tile_type.hpp brings
// ObjectTypeClass and headers the Map unit has not. Only the members MapClass
// touches; slots 24-38 are placeholders (slot numbers and offsets as
// shared/isometric_tile_type.hpp). Units that include shared/isometric_tile_type.hpp
// must not include this stand-in.
#ifndef RA2_SHARED_MAP_ISOTILE_HPP
#define RA2_SHARED_MAP_ISOTILE_HPP

#include "shared/abstract_class.hpp"
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
// Bridge tile set offsets the Map unit's bridge code compares with (the other
// start indices are in shared/tileset_index.hpp).
extern int unknown_tileset_a6e0e4;      // 0x00A6E0E4
extern int unknown_tileset_a52f80;      // 0x00A52F80
extern int unknown_tileset_a53394;      // 0x00A53394
extern int unknown_tileset_a52588;      // 0x00A52588

#endif
#include "shared/vector_class.hpp"

// The image of an isometric tile type (as shared/isometric_tile_type.hpp).
struct IsoTileImageStruct {
    int unknown_00[4];                                  // +0x00 header (hypothesis: sizes)
    int Tiles[1];                                       // +0x10 per-cell tile offsets, 0 where the cell has no tile
};

class IsometricTileTypeClass : public AbstractClass {
public:
    virtual void unknown_slot24(); virtual void unknown_slot25(); virtual void unknown_slot26(); virtual void unknown_slot27(); virtual void unknown_slot28(); virtual void unknown_slot29();
    virtual void unknown_slot30(); virtual void unknown_slot31(); virtual void unknown_slot32(); virtual void unknown_slot33(); virtual void unknown_slot34(); virtual void unknown_slot35();
    virtual void unknown_slot36(); virtual void unknown_slot37(); virtual void unknown_slot38();
    virtual void *unknown_slot39() const;               // slot 39 (+0x9C) the image (0x005293D0)

    // The tile type a map file's index stands for (0xFFFF, no tile, unchanged; 0x00529550;
    // hypothesis: TibSun Fixup_Tile_Type).
    static int __fastcall Unknown_00529550(int type);
    // Whether a sub tile of the type is one of its random variants (0x0052B730; hypothesis:
    // TibSun Is_Randomized).
    bool unknown_func_52b730(int subtile);

    char unknown_24[0x2B4 - 0x24];
    int unknown_2b4;                                    // +0x2B4 cells across
    int unknown_2b8;                                    // +0x2B8 cells down
};

// Every isometric tile type (0x00A40CD0; as shared/isometric_tile.hpp).
extern DynamicVectorClass<IsometricTileTypeClass *> IsoTileTypes;

// Bridge tile set offsets the Map unit's bridge code compares with (the other
// start indices are in shared/tileset_index.hpp).
extern int unknown_tileset_a6e0e4;      // 0x00A6E0E4
extern int unknown_tileset_a52f80;      // 0x00A52F80
extern int unknown_tileset_a53394;      // 0x00A53394
extern int unknown_tileset_a52588;      // 0x00A52588

#endif

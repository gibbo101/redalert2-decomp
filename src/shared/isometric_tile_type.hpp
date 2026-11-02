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

class IsometricTileTypeClass;
// The tile art's palette (0x00A6DD10; defined with its initializer in this class's unit).
extern PaletteClass IsoTilePalette;

// Every isometric tile type (0x00A40CD0; also shared/isometric_tile.hpp).
extern DynamicVectorClass<IsometricTileTypeClass *> IsoTileTypes;

// The image of an isometric tile type (a TMP file): a 16-byte header, then
// one offset per cell of the grid, 0 where the cell has no tile (slot 36).
struct IsoTileImageStruct {
    int unknown_00[4];                                  // +0x00 header (hypothesis: sizes)
    int Tiles[1];                                       // +0x10 per-cell tile offsets
};

// One cell's tile in the image (the Tiles entries point at it; TibSun IsoTileRecord: names
// from +0x24 on are its hypotheses).
struct IsoTileCellStruct {
    int X;                                              // +0x00 the cell's pixel position in the set
    int Y;                                              // +0x04
    int ExtraOffset;                                    // +0x08 from the record to the extra (cliff) image
    int ZDataOffset;                                    // +0x0C
    int ExtraZOffset;                                   // +0x10
    int ExtraX;                                         // +0x14 the extra image's bounds
    int ExtraY;                                         // +0x18
    int ExtraWidth;                                     // +0x1C
    int ExtraHeight;                                    // +0x20
    unsigned IsHasExtraData : 1;                        // +0x24 bit 0
    unsigned IsHasZData : 1;                            // +0x24 bit 1
    unsigned IsRandomized : 1;                          // +0x24 bit 2 (0x0052B730)
    char unknown_28;                                    // +0x28 height (IsometricTileClass slot 71)
    char unknown_29;
    char unknown_2a;                                    // +0x2A (0x0052B6F0)
    unsigned char LowRed;                               // +0x2B the preview colours (TibSun LowColor/HighColor)
    unsigned char LowGreen;
    unsigned char LowBlue;
    unsigned char HighRed;                              // +0x2E
    unsigned char HighGreen;
    unsigned char HighBlue;
};

class IsometricTileTypeClass : public ObjectTypeClass {
public:
    // A tile set that grew since the map's tile numbering: the first index it moves and by how
    // much (RTTI: a struct; TibSun TileInsertType field names are hypotheses).
    struct TileInsertType {
        int Count;                                      // +0x0
        int Offset;                                     // +0x4
    };
#ifdef ISOMETRIC_TILE_TYPE_DECLARE_STATICS
    // Static data members (declared only for the class's own unit: each one renumbers the
    // _$E initializers of every unit that sees it).
    static DynamicVectorClass<TileInsertType *> TileInsertTypes;    // 0x00A52EC8
    // The first tile of each cliff set that casts shadows (0x00A52E74; TibSun ShadowCasterTiles).
    static int ShadowCasterTiles[5];
#endif

    // A tile type at IsoTileTypes index `type` (0x00528EE0; the two small arguments are kept
    // as Unused1/Unused2; registration in IsoTileTypes is skipped on request).
    IsometricTileTypeClass(int type, int unknown1, unsigned char unknown2, char const *ini_name, bool skip_registration);
    IsometricTileTypeClass(NoInitClass const &noinit);                  // 0x00529120
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

    // Whether the image holds sub tile `tile`, loading it first when asked (0x00529340; TibSun
    // Is_Tile_Index_Valid).
    bool Is_Tile_Index_Valid(int tile, bool load);
    // Loads a demand-loaded image that is not resident yet (0x005293A0; TibSun Load_Tile_Image).
    bool Load_Tile_Image();
    // The IsoTileTypes index of the type with this INI name, 0xFFFF if none (0x00529400; TibSun From_Name).
    static int __fastcall From_Name(char const *name);
    // Variation `index` of the type's chain through unknown_28c, wrapping (0x00529520; TibSun
    // Next_Tile_From_Set).
    IsometricTileTypeClass *Next_Tile_From_Set(int index);
    // A tile type index recorded before TileInsertTypes grew the sets, brought up to date
    // (0x00529550; TibSun Fixup_Tile_Type; 0xFFFF is no tile).
    static int __fastcall Fixup_Tile_Type(int type);
    // Whether sub tile `tile` (wrapping) is one of the type's random variants (0x0052B730; TibSun
    // Is_Randomized).
    bool Is_Randomized(int tile) const;
    // Zeroes UseCount of every tile type and its variations (0x0052B650; TibSun Clear_Use_Counts).
    static void Clear_Use_Counts();
    // The pixel size of sub tile `tile` (wrapping), taller by its extra image; false without an
    // image (0x0052B690; TibSun Get_Tile_Pixel_Dimensions).
    bool Get_Tile_Pixel_Dimensions(int tile, int &width, int &height);
    // Unpacks sub tile `tile` (wrapping) into a cleared width x height byte image through the
    // diamond mask, then its extra image; false when it does not fit (0x0052DD70; TibSun
    // Get_Tile_Image).
    bool Get_Tile_Image(int tile, unsigned char **buffer, int width, int height);
    // Draws the shadow a slope or cliff tile casts on cell part `index` (0x0052B770; TibSun
    // Draw_Shadow_Caster; slopes from ShadowCasterSlopeInfo, cliffs from ShadowCasterCliffInfo).
    void Draw_Shadow_Caster(int index, Surface *surface, Point2D point, Rect cliprect, int offset);
    int unknown_func_52b560();                                          // 0x0052B560 (loads the image; TibSun Load_Tile_Data: returns its size)
    void unknown_func_52e3d0();                                         // 0x0052E3D0 (rebuilds unknown_274)
    char unknown_func_52b6f0(int index);                               // 0x0052B6F0 (a cell's +0x2A byte of the image; hypothesis)
    unsigned short unknown_func_52e360(int index, int value, bool second) const;
    // The preview colour pair of sub tile `tile` at light level `level`, loading the image first
    // (0x0052E390; TibSun Preview_Tile).
    unsigned short *Preview_Tile(int tile, int level);    // 0x0052E360
    // Draws one cell of the tile image (0x0052C230; arguments are hypotheses: a light converter,
    // a cell index, the surface, the screen point, the clip rectangle, a height and a level).
    // The light converter with these tints, made when there is none yet (0x00529590; Westwood's
    // Find_Or_Make_Drawer; 0 without a palette).
    static LightConvertClass *__fastcall Find_Or_Make_Drawer(int red, int green, int blue);
    // Frees every light converter and makes the normal-light one again; every cell picks its
    // drawer anew (0x00529720; TibSun Init_Drawers).
    static void Init_Drawers();
    // Counts every map cell's tile variation as used, then loads the used images and frees the
    // rest (all of them when skipping the count; random maps keep the RMG ones) (0x0052B2E0;
    // TibSun Load_Tiles).
    static void __fastcall Load_Tiles(bool skip_iteration, bool is_random);
    // The cells this cliff tile's shadow darkens, relative to the tile and ending in the
    // 0x7FFF end marker, or 0 for a tile that casts none (0x0052B8B0; TibSun Shadow_Caster_List).
    Cell const *Shadow_Caster_List() const;
    void unknown_func_52c230(LightConvertClass *drawer, int arg2, Surface *surface, int x, int y, Rect rect,
        int arg7, int arg8, int arg9, int arg10, int arg11, int arg12, int arg13, int arg14);

    int ArrayIndex;                                     // +0x264 (TibSun HeapID)
    int MarbleMadness;                                  // +0x268 0xFFFF: none (TibSun names from here; hypotheses)
    int NonMarbleMadness;                               // +0x26C 0xFFFF: none
    int TileSetBaseID;                                  // +0x270
    DynamicVectorClass<unsigned short *> unknown_274;   // +0x274 the preview colour tables (TibSun PreviewTiles)
    AbstractClass *unknown_28c;                         // +0x28C next variation (TibSun NextTileTypeInSet)
    int ToSnowTheater;                                  // +0x290 -1: none
    int ToTemperateTheater;                             // +0x294 -1: none
    int unknown_298;                                    // +0x298 AnimTypes index (-1: none)
    Point2D Offset;                                     // +0x29C the animation's offset
    int AttachesTo;                                     // +0x2A4 -1: none
    int ZAdjust;                                        // +0x2A8
    int Unused1;                                        // +0x2AC the constructor's second argument
    bool unknown_2b0;                                   // +0x2B0 (smudges allowed; map_cell_view.hpp; TibSun IsMorphable)
    bool IsShadowCaster;                                // +0x2B1
    bool IsAllowToPlace;                                // +0x2B2
    bool IsRequiredForRMG;                              // +0x2B3
    int unknown_2b4;                                    // +0x2B4 cells across (the image's tile grid; slot 36)
    int unknown_2b8;                                    // +0x2B8 cells down
    int Unused2;                                        // +0x2BC the constructor's third argument
    int NumTileTypesInSet;                              // +0x2C0 the unknown_28c chain's length
    bool unknown_2c4;                                   // +0x2C4 image loads on demand (TibSun IsFileLoaded)
    char Filename[16];                                  // +0x2C5 the image file's name
    bool unknown_2d5;                                   // +0x2D5 (map_cell_view.hpp; TibSun IsAllowBurrowing)
    bool unknown_2d6;                                   // +0x2D6 (map_cell_view.hpp: tiberium may grow; TibSun IsAllowTiberium)
    int UseCount;                                       // +0x2D8
};

#endif

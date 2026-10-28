// FoggedObjectClass: what a fogged cell still shows of an object
// (FoggedObject.cpp, 0x004BFCD0 unit; RTTI vtables 0x007A1148 primary,
// 0x007A112C at +4, 0x007A1124, 0x007A111C). Layout from the default
// constructor 0x004C0020 and Save 0x004C1C10: DrawRecords (16-byte records)
// at +0x5C; Size_Of 0x78, Kind_Of 0x3D. Member names are placeholders.
#ifndef RA2_SHARED_FOGGED_OBJECT_HPP
#define RA2_SHARED_FOGGED_OBJECT_HPP

#include "shared/abstract.hpp"
#include "shared/vector_class.hpp"

#ifndef E_POINTER
#define E_POINTER ((HRESULT)0x80004003L)
#endif

extern "C" GUID const CLSID_FoggedObjectClass;     // 0x007A1ED0

#include "shared/ini_class.hpp"     // IndexClass
class ObjectTypeClass;
class AnimClass;
class BuildingClass;

class FoggedObjectClass : public AbstractClass {
public:
    // One drawn piece (16 bytes; fields not recovered).
    struct DrawRecord {
        DrawRecord() : Type(0), unknown_04(0), unknown_08(0), unknown_0c(0) {}
        DrawRecord(DrawRecord const &that)
            : Type(that.Type), unknown_04(that.unknown_04),
              unknown_08(that.unknown_08), unknown_0c(that.unknown_0c) {}
        bool operator==(DrawRecord const &that) const
        {
            return Type == that.Type && unknown_04 == that.unknown_04;
        }
        bool operator!=(DrawRecord const &that) const { return !(*this == that); }
        ObjectTypeClass *Type;    // +0x00 the drawn object's type (a fogged building's first record: its cells, slot 36)
        int unknown_04;
        unsigned char unknown_08; // original byte copy; semantic meaning unknown
        int unknown_0c;           // copy construction skips padding +09..0B; implicit assignment copies DWORD8 including padding
    };

    FoggedObjectClass(NoInitClass const &noinit);                // 0x004BFFD0
    FoggedObjectClass();                                        // 0x004C0020
    FoggedObjectClass(CoordStruct const &coord, int arg24, int arg2c);  // 0x004C00F0
    FoggedObjectClass(CoordStruct const &coord, int arg54, unsigned int arg58);  // 0x004C03B0
    FoggedObjectClass(AnimClass *anim);                         // 0x004C0AF0
    FoggedObjectClass(BuildingClass *building, bool arg);       // 0x004C0670
    virtual ~FoggedObjectClass();                               // 0x004C0DD0 (leaves Array and Index, clears a building's fog marks)
    // The cells a fogged building covers (its type's slot 36 list, ending
    // at 0x7FFF,0x7FFF); null for other kinds (0x004C1F00).
    Cell const *unknown_4c1f00() const;

    virtual HRESULT __stdcall GetClassID(GUID *classid);        // 0x004C1F40
    virtual HRESULT __stdcall Load(IStream *stream);             // 0x004C1C80
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x004C1C10
    virtual int Kind_Of() const;                                // 0x004C1F20
    virtual int Size_Of() const;                                // 0x004C1F30
    virtual void Compute_CRC(WWCRCEngine &crc) const;             // 0x004C1F80; body unrecovered
    virtual Cell unknown_slot24() const;                        // slot 24 (+0x60) 0x004C2040: the cell the object stands on
    // Marks (+0x140 bit 22) the cells of every listed fogged object (0x004C1AE0).
    static void unknown_4c1ae0();
    // The cell holding a coordinate (hypothesis: Westwood's Coord_Cell as a class helper;
    // the 0x004C00F0 constructor needs this extra inline level to keep Increase_Table_Size out of line).
    static Cell unknown_coord_cell(CoordStruct const &coord) { return XY_Cell(coord.X / 256, coord.Y / 256); }
    // The key the object is listed under in Index (inlined by the constructors,
    // 0x004C0DD0 and Load): the cell's diagonal order, then the kind.
    static int unknown_index_key(Cell cell, int kind)
    {
        return (-(cell.X + cell.Y) * 512 + cell.Y - cell.X) * 0x47 - kind + 0x7FFFFFFF;
    }

    static DynamicVectorClass<FoggedObjectClass *> Array;       // 0x00865E90
    static IndexClass<int, FoggedObjectClass *> Index; // original865E40; static-member ownership hypothesis

    int unknown_24;                                 // +0x24 (-1)
    AbstractClass *unknown_28;                      // +0x28 (swizzled by Load)
    int unknown_2c;                                 // +0x2C
    int unknown_30;                                 // +0x30
    CoordStruct Coord;                              // +0x34 where the object stood (CellClass 0x0047BE60 copies it whole)
    Rect unknown_40;                                // +0x40 the redraw rectangle (view coordinates)
    int unknown_50;                                 // +0x50 (the bridge height of the cell under it at construction)
    int unknown_54;                                 // +0x54 (-1)
    int unknown_58;                                 // +0x58
    DynamicVectorClass<DrawRecord> DrawRecords;     // +0x5C
    bool unknown_74;                                // +0x74 (true)
};

#endif

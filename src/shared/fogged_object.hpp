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

template<class INDEX, class T> class IndexClass;
class ObjectTypeClass;

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
    virtual ~FoggedObjectClass();                               // 0x004C0DD0
    // The cells a fogged building covers (its type's slot 36 list, ending
    // at 0x7FFF,0x7FFF); null for other kinds (0x004C1F00).
    Cell const *unknown_4c1f00() const;

    virtual HRESULT __stdcall GetClassID(GUID *classid);        // 0x004C1F40
    virtual HRESULT __stdcall Load(IStream *stream);             // 0x004C1C80; body unrecovered
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x004C1C10
    virtual int Kind_Of() const;                                // 0x004C1F20
    virtual int Size_Of() const;                                // 0x004C1F30
    virtual void Compute_CRC(WWCRCEngine &crc) const;             // 0x004C1F80; body unrecovered
    virtual Cell unknown_slot24() const;                        // slot 24 (+0x60): the cell the object stands on; body unrecovered
    // Marks (+0x140 bit 22) the cells of every listed fogged object (0x004C1AE0).
    static void unknown_4c1ae0();

    static DynamicVectorClass<FoggedObjectClass *> Array;       // 0x00865E90
    static IndexClass<int, FoggedObjectClass *> Index; // original865E40; static-member ownership hypothesis

    int unknown_24;                                 // +0x24 (-1)
    int unknown_28;                                 // +0x28
    int unknown_2c;                                 // +0x2C
    int unknown_30;                                 // +0x30
    CoordStruct Coord;                              // +0x34 where the object stood (CellClass 0x0047BE60 copies it whole)
    int unknown_40;                                 // +0x40
    int unknown_44;                                 // +0x44
    int unknown_48;                                 // +0x48
    int unknown_4c;                                 // +0x4C
    // +0x50 / +0x54 (0 / -1); the constructor sets the second first.
    struct UnknownPair {
        UnknownPair() : Second(-1) { First = 0; }
        UnknownPair(NoInitClass const &) {}
        int First;
        int Second;
    } unknown_50;
    int unknown_58;                                 // +0x58
    DynamicVectorClass<DrawRecord> DrawRecords;     // +0x5C
    bool unknown_74;                                // +0x74 (true)
};

#endif

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

class FoggedObjectClass : public AbstractClass {
public:
    // One drawn piece (16 bytes; fields not recovered).
    struct DrawRecord {
        DrawRecord() : unknown_00(0), unknown_04(0), unknown_08(0), unknown_0c(0) {}
        DrawRecord(DrawRecord const &that)
            : unknown_00(that.unknown_00), unknown_04(that.unknown_04),
              unknown_08(that.unknown_08), unknown_0c(that.unknown_0c) {}
        bool operator==(DrawRecord const &that) const
        {
            return unknown_00 == that.unknown_00 && unknown_04 == that.unknown_04;
        }
        bool operator!=(DrawRecord const &that) const { return !(*this == that); }
        int unknown_00;
        int unknown_04;
        unsigned char unknown_08; // original byte copy; semantic meaning unknown
        int unknown_0c;           // copy construction skips padding +09..0B; implicit assignment copies DWORD8 including padding
    };

    FoggedObjectClass(NoInitClass const &noinit);                // 0x004BFFD0
    FoggedObjectClass();                                        // 0x004C0020
    virtual ~FoggedObjectClass();                               // 0x004C0DD0

    virtual HRESULT __stdcall GetClassID(GUID *classid);        // 0x004C1F40
    virtual HRESULT __stdcall Load(IStream *stream);             // 0x004C1C80; body unrecovered
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x004C1C10
    virtual int Kind_Of() const;                                // 0x004C1F20
    virtual int Size_Of() const;                                // 0x004C1F30
    virtual void Compute_CRC(WWCRCEngine &crc) const;             // 0x004C1F80; body unrecovered

    static DynamicVectorClass<FoggedObjectClass *> Array;       // 0x00865E90
    static IndexClass<int, FoggedObjectClass *> Index; // original865E40; static-member ownership hypothesis

    int unknown_24;                                 // +0x24 (-1)
    int unknown_28;                                 // +0x28
    int unknown_2c;                                 // +0x2C
    int unknown_30;                                 // +0x30
    int unknown_34;                                 // +0x34
    int unknown_38;                                 // +0x38
    int unknown_3c;                                 // +0x3C
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

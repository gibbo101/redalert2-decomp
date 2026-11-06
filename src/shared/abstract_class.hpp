// AbstractClass's declaration without shared/abstract.hpp's other headers:
// abstract.hpp includes shared/unknown_geometry.hpp, whose header statics would
// add initializers to the screen units (Display, Radar, Map, Power, GScreen),
// so those units reach AbstractClass (the base of Tactical, shared/tactical.hpp)
// through this header. Layout and history: shared/abstract.hpp.
#ifndef RA2_SHARED_ABSTRACT_CLASS_HPP
#define RA2_SHARED_ABSTRACT_CLASS_HPP

#include "shared/com_persist.hpp"
#include "shared/coord.hpp"

class NoInitClass;
class HouseClass;
class TechnoClass;
class WWCRCEngine;

// The game's run-time type interface (IID {170DAC82-12E4-11D2-8175-006008055BB5}).
struct __declspec(novtable) IRTTITypeInfo : public IUnknown {
    virtual int __stdcall What_Am_I() = 0;      // slot 3
    virtual long __stdcall Fetch_ID() = 0;      // slot 4
    virtual void __stdcall Create_ID() = 0;     // slot 5
};
extern "C" GUID const IID_IRTTITypeInfo;       // 0x007A2020

#include "shared/notice.hpp"

class AbstractClass : public IPersistStream, public IRTTITypeInfo, public INoticeSink, public INoticeSource {
public:
#ifdef RA2_ABSTRACT_ASSIGN_SOURCE
    AbstractClass &operator=(AbstractClass const &other); // original0056A9F0
#endif
    // IUnknown
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);   // 0x00410000
    virtual unsigned long __stdcall AddRef();                                    // 0x004100A0
    virtual unsigned long __stdcall Release();                                   // 0x004100B0

    // IPersistStream (Load and Save stay pure but have the bodies derived
    // classes call)
    virtual HRESULT __stdcall IsDirty();                                         // 0x004101F0
    virtual HRESULT __stdcall Load(IStream *stream) = 0;                         // 0x00410120
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty) = 0;       // 0x004100C0
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER *size);                  // 0x00410180

    // IRTTITypeInfo
    virtual int __stdcall What_Am_I();                                           // 0x0040FFB0
    virtual long __stdcall Fetch_ID();                                           // 0x0040FFC0
    virtual void __stdcall Create_ID();                                          // 0x0040FFD0

    // INoticeSink, INoticeSource
    virtual bool INoticeSink_Unknown(int code, int arg);                         // 0x00410320
    virtual void __stdcall INoticeSource_Unknown();                              // 0x00410330

    AbstractClass();                                                             // 0x0040FF10
    AbstractClass(NoInitClass const &noinit);                                    // 0x0040FF60
    virtual ~AbstractClass();                                                    // 0x0040FF90 (slot 8)

    virtual void Init();                                                         // 0x00410210 slot 9
    virtual void Detach(AbstractClass *target, bool all = true);                 // 0x00410220 slot 10
    virtual int Kind_Of() const = 0;                                             // slot 11
    virtual int Size_Of() const = 0;                                             // slot 12
    virtual void Compute_CRC(WWCRCEngine &crc) const;                            // 0x004101B0 slot 13
    virtual int Owner() const;                                                   // 0x00410230 slot 14 (-1)
    virtual HouseClass *Owning_House() const;                                    // 0x00410240 slot 15
    // This object as a techno, or null for other kinds (0x0040DC20).
    TechnoClass *As_Techno();
    virtual int unknown_slot16() const;                                          // 0x00410250
    virtual bool unknown_slot17() const;                                         // 0x004101E0 (true)
    virtual CoordStruct Center_Coord() const;                                    // 0x00410260 slot 18
    virtual CoordStruct unknown_slot19(TechnoClass *techno) const;               // 0x00410290 (Center_Coord)
    virtual bool unknown_slot20() const;                                         // 0x004102C0 (false)
    virtual bool unknown_slot21() const;                                         // 0x004102D0 (false)
    virtual CoordStruct unknown_slot22() const;                                  // 0x004102E0 (Center_Coord)
    virtual void AI();                                                           // 0x00410310 slot 23

    long UniqueID;                  // +0x10
#ifndef RA2_ABSTRACT_FLAGS_UNNAMED
    // A named member: the implicit copy constructor 0x006B69D0 (TaskForceClass)
    // copies the flag byte whole, which it does not for direct bitfields.
    struct {
        unsigned char IsTechno : 1;     // set by TechnoClass's constructor
        unsigned char IsObject : 1;     // set by ObjectClass's constructor
        unsigned char IsFoot : 1;       // set by FootClass's constructor
    } AbstractFlags;                    // +0x14
#ifdef RA2_CELL_GOODIE_CHECK
    // TibSun's inline flag tests (CellClass::Goodie_Check 0x00476CC0).
    bool Is_Techno() const { bool is_techno; if (this != 0) is_techno = AbstractFlags.IsTechno; return is_techno; }
    bool Is_Foot() const { bool is_foot; if (this != 0) is_foot = AbstractFlags.IsFoot; return is_foot; }
#endif
#else
    // The same bits without the struct type, for a unit that never reads the
    // flags and holds a row whose register tie follows the count of struct
    // types declared before it (Pick_Lobby 0x00744090, through the wonline
    // unit's house_type.hpp; VC6_MATCHING_NOTES "Type-count sensitivity").
    unsigned char IsTechno : 1;         // +0x14
    unsigned char IsObject : 1;
    unsigned char IsFoot : 1;
#endif
    int unknown_18;                 // +0x18
    long RefCount;                  // +0x1C
    bool Dirty;                     // +0x20
};

#endif

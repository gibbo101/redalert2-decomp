// AbstractClass: the root of the game-object hierarchy (Abstract.cpp,
// 0x0040FF10-0x004103A5; RTTI vtables 0x0079ADD8 primary, 0x0079ADBC for the
// IRTTITypeInfo base at +4, 0x0079ADB4 INoticeSink at +8, 0x0079ADAC
// INoticeSource at +0xC).
//
// Bases from RTTI: IPersistStream < IPersist < IUnknown (+0), IRTTITypeInfo
// < IUnknown (+4), INoticeSink (+8), INoticeSource (+0xC). The constructors
// store vtables for INoticeSink (0x0079AE44) and INoticeSource (0x0079AE3C)
// before their own, but none for the COM interfaces, so those are novtable.
//
// Layout (from the constructor 0x0040FF10, Save/Load/IsDirty/Fetch_ID):
//   +0x00..+0x0C  four vtable pointers
//   +0x10  long UniqueID      -1 when constructed; Fetch_ID/Create_ID
//   +0x14  three flag bits    cleared when constructed (meaning unknown)
//   +0x18  int unknown_18     0 when constructed
//   +0x1C  long RefCount      0 when constructed; kept across Load
//   +0x20  bool Dirty         IsDirty; cleared by Save(stream, TRUE)
//   size 0x24 (AbstractTypeClass members start at +0x24)
//
// Virtual names follow Westwood's TS/RA2 vocabulary where the behaviour
// agrees (Init, Detach, Kind_Of, Size_Of, Compute_CRC, Owner, Owning_House,
// Center_Coord, AI); the others keep unknown_ names. Hypotheses throughout.
#ifndef RA2_SHARED_ABSTRACT_HPP
#define RA2_SHARED_ABSTRACT_HPP

#include "shared/com_persist.hpp"
// CoordStruct and the per-unit header statics (Abstract.cpp's zero
// coordinate is unknown_geometry_l, 0x00839CA8).
#include "shared/unknown_geometry.hpp"
#include "shared/cd_timer.hpp"

class NoInitClass;
class HouseClass;
class TechnoClass;

#include "shared/wwcrc_engine.hpp"

// The save-game pointer fixup service (hypothesis: SwizzleManagerClass).
class SwizzleManagerClass {
public:
    HRESULT __stdcall Swizzle(void **pointer);              // 0x0069FB20
    HRESULT __stdcall Here_I_Am(long id, void *pointer);   // 0x0069FBA0
};
extern SwizzleManagerClass SwizzleManager;     // 0x00ABD868

// Requests the fix-up of a loaded pointer (an inline wrapper; each use is an
// inline expansion in the caller, which counts against /Ob2's per-function
// inline limit).
template<class T>
inline HRESULT Swizzle_Pointer(T *&pointer)
{
    return SwizzleManager.Swizzle((void **)&pointer);
}

#include "shared/id_source.hpp"

// Flags an object or type in its owner's lists (0x006ECB90; hypothesis).
class AbstractClass;
void __fastcall Unknown_006ECB90(AbstractClass *object, bool value);

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
    unsigned char unknown_14_bit0 : 1;  // +0x14
    unsigned char unknown_14_bit1 : 1;
    unsigned char unknown_14_bit2 : 1;
    int unknown_18;                 // +0x18
    long RefCount;                  // +0x1C
    bool Dirty;                     // +0x20
};

#endif

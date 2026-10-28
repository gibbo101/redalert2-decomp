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
    HRESULT __stdcall Reset();                               // 0x0069FB10 (Read_Scenario_INI)
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

#include "shared/abstract_class.hpp"

#endif

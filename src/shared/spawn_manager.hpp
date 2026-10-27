// SpawnManagerClass: the spawner of carrier-launched units (SpawnManager.cpp,
// 0x00689690-0x0068AA1D; RTTI vtables 0x007AB8C8 primary, 0x007AB8AC at +4,
// 0x007AB8A4, 0x007AB89C). Layout from the constructors 0x00689710 /
// 0x00689910 and Compute_CRC 0x0068A6A0; Size_Of 0x74, Kind_Of 0x41. Names
// are hypotheses (Owner, SpawnType, SpawnCount and the two rate fields come
// from the constructor arguments).
#ifndef RA2_SHARED_SPAWN_MANAGER_HPP
#define RA2_SHARED_SPAWN_MANAGER_HPP

#include "shared/abstract.hpp"
#include "shared/cd_timer.hpp"
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"

#ifndef E_POINTER
#define E_POINTER ((HRESULT)0x80004003L)
#endif

extern "C" GUID const CLSID_SpawnManagerClass;     // 0x007A1DD0

// One spawned unit's record (0x18 bytes, allocated by the constructor).
struct SpawnControl {
    AbstractClass *Unit;                        // +0x00
    int Status;                                 // +0x04
    CDTimerClass<FrameTimerClass> Timer;        // +0x08
    int unknown_14;                             // +0x14
};

class AircraftTypeClass;

class SpawnManagerClass : public AbstractClass {
public:
    SpawnManagerClass(AbstractClass *owner, AircraftTypeClass *type, int count, int regen, int reload);   // 0x00689710 (TechnoClass::Init)
    virtual HRESULT __stdcall GetClassID(GUID *classid);        // 0x0068A790
    virtual HRESULT __stdcall Load(IStream *stream);            // (overridden; address not looked up)
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // (overridden; address not looked up)
    virtual int Kind_Of() const;                                // 0x0068A9F0
    virtual int Size_Of() const;                                // 0x0068A9E0
    virtual void Compute_CRC(WWCRCEngine &crc) const;           // 0x0068A6A0

    AbstractClass *Owner;                           // +0x24
    AbstractClass *SpawnType;                       // +0x28
    int SpawnCount;                                 // +0x2C
    int RegenRate;                                  // +0x30
    int ReloadRate;                                 // +0x34
    DynamicVectorClass<SpawnControl *> SpawnedNodes;   // +0x38
    CDTimerClass<FrameTimerClass> unknown_50;       // +0x50
    CDTimerClass<FrameTimerClass> unknown_5c;       // +0x5C
    AbstractClass *Destination;                     // +0x68
    AbstractClass *Target;                          // +0x6C
    int Status;                                     // +0x70
};

#endif

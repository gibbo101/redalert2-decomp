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

class AircraftClass;
class TechnoClass;
class AircraftTypeClass;

// One spawned unit's record (0x18 bytes; read and written whole by Load/Save).
// Status 7 is a dead slot waiting for its timer (Kill_Nodes 0x00689B70);
// 6 and 0 are docked states, 1 is launching and 2 flying (hypotheses).
struct SpawnControl {
    AircraftClass *Unit;                        // +0x00
    int Status;                                 // +0x04
    CDTimerClass<FrameTimerClass> Timer;        // +0x08
    int IsMissile;                              // +0x14 (the type is Rules' V3 or Dread missile)
};

class SpawnManagerClass : public AbstractClass {
public:
    SpawnManagerClass(TechnoClass *owner, AircraftTypeClass *type, int count, int regen, int reload);   // 0x00689710 (TechnoClass::Init)
    SpawnManagerClass();                                        // 0x00689910 (class factory)
    SpawnManagerClass(NoInitClass const &noinit);               // 0x00689A10
    virtual ~SpawnManagerClass();                               // 0x00689A80 (deleting 0x0068AA00)
    virtual HRESULT __stdcall GetClassID(GUID *classid);        // 0x0068A790
    virtual HRESULT __stdcall Load(IStream *stream);            // 0x0068A7D0
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x0068A970
    virtual int Kind_Of() const;                                // 0x0068A9F0
    virtual int Size_Of() const;                                // 0x0068A9E0
    virtual void Compute_CRC(WWCRCEngine &crc) const;           // 0x0068A6A0
    virtual void AI();                                          // slot 23 0x00689C90

    void Kill_Nodes();                                          // 0x00689B70
    void Set_Target(AbstractClass *target);                     // 0x0068A490 (unless it is the destination)
    void Abandon_Target();                                      // 0x0068A4B0
    bool Next_Target();                                         // 0x0068A540 (the queued target becomes the destination)
    void Unlink(AbstractClass *object);                         // 0x0068A560 (TechnoClass::Detach)
    int Alive_Count() const;                                    // 0x0068A630 (records not in status 7)
    int Docked_Count() const;                                   // 0x0068A650 (status 6 or 0)
    int Launching_Count() const;                                // 0x0068A680 (status 1)

    TechnoClass *Owner;                             // +0x24 (AI calls its techno slots)
    AircraftTypeClass *SpawnType;                   // +0x28
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

// FlyLocomotionClass (Fly.cpp, 0x004BBF20-0x004BFCCF; RTTI vtables
// 0x007A10CC IPersistStream, 0x007A1004 ILocomotion at +4). Size 0x60.
// Layout from the constructor 0x004BC110 (names are hypotheses):
//   +0x18  bool (the linked aircraft is airport bound)
//   +0x1C, +0x28  CoordStruct (from the unit's zero 0x00865DF8)
//   +0x34  bool moving, +0x38..+0x44 ints, +0x48 double speed fraction
//   +0x50..+0x53 bools, +0x54 int (a random drift), +0x58 int, +0x5C bool
#ifndef RA2_SHARED_FLY_LOCOMOTION_HPP
#define RA2_SHARED_FLY_LOCOMOTION_HPP

#include "shared/locomotion.hpp"
#include "shared/com_ptr.hpp"

extern CoordStruct unknown_coord_865df8;            // 0x00865DF8
extern "C" GUID const CLSID_FlyLocomotionClass;     // 0x007A1FC0

// The aircraft members Fly.cpp reads (views until AircraftClass and
// AircraftTypeClass are shared).
struct UnknownFlyAircraftType {
    char unknown_000[0xBA3];
    bool AirportBound;                  // +0xBA3
};
struct UnknownFlyAircraft {
    char unknown_000[0x5AC];
    UnknownFlyAircraftType *Type;       // +0x5AC
};

// The interface with IID 0x007D80A8 the aircraft answers (slot 3 returns an int: the
// aircraft's current height, hypothesis). Fly.cpp holds it in a smart pointer whose
// Release_Held is out of line (0x004BFBC0).
extern "C" GUID const unknown_uuid_7d80a8;          // 0x007D80A8
struct UnknownFlyInterface : IUnknown {
    virtual int __stdcall unknown_slot3() = 0;
};
typedef UnknownComPtr<UnknownFlyInterface, &unknown_uuid_7d80a8> UnknownFlyPtrBase;
class FootClass;
// The converting constructor as Fly.cpp expands it (Release_Held out of line on both outcomes).
struct UnknownFlyPtr : UnknownFlyPtrBase {
    template <class Other>
    UnknownFlyPtr(Other const &other)
    {
        if (other) {
            HRESULT result = Query_Held(other);
            if (FAILED(result) && result != E_NOINTERFACE) {
                _com_issue_error(result);
            }
        }
    }
};

class FlyLocomotionClass : public LocomotionClass {
public:
    FlyLocomotionClass();                                                       // 0x004BC110
    FlyLocomotionClass(NoInitClass const &noinit) : LocomotionClass(noinit) {}  // inline (Load)
    virtual ~FlyLocomotionClass();                                              // 0x004BC1E0

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                          // 0x004BF400
    virtual HRESULT __stdcall Load(IStream *stream);                            // 0x004BF440
    virtual int Size() { return sizeof(FlyLocomotionClass); }                   // 0x004BFAF0 (inline)

    virtual HRESULT __stdcall Link_To_Object(void *object);                     // 0x004BC190
    virtual bool __stdcall Is_Moving();                                         // 0x004BC200
    virtual CoordStruct __stdcall Destination();                                // 0x004BC250
    virtual Matrix3D * __stdcall Draw_Matrix(Matrix3D *matrix, int *key);                           // 0x004BED90
    virtual Matrix3D * __stdcall Shadow_Matrix(Matrix3D *matrix, int *key);                         // 0x004BF280
    virtual Point2D __stdcall Draw_Point();                                     // 0x004BEFB0
    virtual Point2D __stdcall Shadow_Point();                                   // 0x004BF0C0
    virtual bool __stdcall Process();                                           // 0x004BC2B0
    virtual void __stdcall Move_To(CoordStruct to);                             // 0x004BC3E0
    virtual void __stdcall Stop_Moving();                                       // 0x004BC730
    virtual void __stdcall Do_Turn(UnknownFacingDir dir);                       // 0x004BF390
    virtual bool __stdcall Power_Off();                                         // 0x004BF4A0
    virtual bool __stdcall Is_Powered();                                        // 0x004BF510
    virtual bool __stdcall Is_Ion_Sensitive();                                  // 0x004BF520
    virtual int __stdcall Layer();                                              // 0x004BF470
    virtual bool __stdcall Is_Moving_Now();                                     // 0x004BC230
    virtual int __stdcall Apparent_Speed();                                     // 0x004BF5A0
    virtual int __stdcall Get_Status();                                         // 0x004BF5D0
    virtual void __stdcall Acquire_Hunter_Seeker_Target();                      // 0x004BF600

    // Helpers Fly.cpp defines and expands (names hypotheses).
    bool unknown_4bf3c0();                                                      // 0x004BF3C0 (not +0x51, and not +0x50 or at least half +0x38 high)
    void Start_Drift();                                                         // 0x004BF550 (a drift of 20..30 either way; Power_Off)
    void unknown_4bf1f0();                                                      // 0x004BF1F0 (unless on mission 7 or the techno check 0x006D1470 holds: an airport-bound aircraft out of radio contact with the building in its cell calls slot 261, else the flight state resets)
    bool unknown_4bcc60();                                                      // 0x004BCC60 (landed carrier unloads its passengers)

    bool unknown_18;                    // +0x18
    CoordStruct unknown_1c;             // +0x1C
    CoordStruct unknown_28;             // +0x28
    bool unknown_34;                    // +0x34
    int unknown_38;                     // +0x38
    int unknown_3c;                     // +0x3C
    double unknown_40;                  // +0x40
    double unknown_48;                  // +0x48
    bool unknown_50;                    // +0x50
    bool unknown_51;                    // +0x51
    bool unknown_52;                    // +0x52
    bool unknown_53;                    // +0x53
    int unknown_54;                     // +0x54
    int unknown_58;                     // +0x58
    bool unknown_5c;                    // +0x5C
};

#endif

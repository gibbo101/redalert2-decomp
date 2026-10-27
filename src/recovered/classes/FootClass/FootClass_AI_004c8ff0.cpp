// void FootClass::AI() (0x004C8FF0, slot 23)
// TechnoClass's AI, then the unit's own: tiberium damage every rules
// +0x144C frames, a balloon unit settles, a moving unit on the map refreshes
// its sight every 15 frames, the locomotor runs (Process) and the idle and
// walk frame counter +0x430 advances, the move sound (+0x434 playing, +0x438
// frames of grace) and the falling, sinking and crashing sounds start and
// stop, the audio controller follows the unit, an idle unit in an
// impassable spot is moved off it, a finished piggyback hands the
// locomotor back, and the parasite riding the unit runs.
#include "shared/foot.hpp"
#include "shared/locomotion.hpp"
#include "shared/parasite.hpp"
#include "shared/techno_map.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_0054A550@MapClass@@QAEXABUCoordStruct@@HHH@Z=0054a550
// @ref ?Unknown_0055A740@MapClass@@QAE_NPAVCellClass@@_N@Z=0055a740
// @ref ?AI@TechnoClass@@UAEXXZ=006c74c0
// @ref ?Frame@@3HA=00a40d2c
// @ref ?Unknown_0047CE70@UnknownCellClass@@QAEHXZ=0047ce70
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Unknown_00405D50@UnknownAudioController@@QAEXXZ=00405d50
// @ref ?Unknown_00406070@UnknownAudioController@@QAEXXZ=00406070
// @ref ?Unknown_00713E60@@YIXHABUCoordStruct@@H@Z=00713e60
// @ref ?Unknown_007141B0@@YIXABUCoordStruct@@PAVUnknownAudioController@@@Z=007141b0
// @ref ?unknown_random_839218@@3VRandom2Class@@A=00839218
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref ?unknown_6d7f70@TechnoClass@@QAE_NXZ=006d7f70
// @ref _unknown_uuid_IPiggyback_7cfc30=007cfc30
// @ref __com_issue_error@4=00795940
// @ref ?unknown_slot164@TechnoClass@@UAEHXZ=006d6e60

// The audio controller follows a coordinate (0x007141B0; fastcall).
void __fastcall Unknown_007141B0(CoordStruct const &coord, UnknownAudioController *controller);
// IPiggyback's interface ID (a copy at 0x007CFC30; IID_IPiggyback is 0x007A2050).
extern "C" GUID const unknown_uuid_IPiggyback_7cfc30;

// An IPiggyback pointer queried from the locomotor (the compiler's
// _com_ptr_t<IPiggyback> as comip.h expands it: Attach(SUCCEEDED(hr) ?
// pointer : NULL) on a fresh pointer).
class UnknownPiggybackPtr {
public:
    UnknownPiggybackPtr(ILocomotion *other) : Pointer(0)
    {
        HRESULT result = Query(other);
        if (FAILED(result) && result != E_NOINTERFACE) {
            _com_issue_error(result);
        }
    }
    ~UnknownPiggybackPtr()
    {
        if (Pointer != 0) {
            Pointer->Release();
        }
    }
    HRESULT Query(ILocomotion *other)
    {
        HRESULT result;
        if (other != 0) {
            IPiggyback *pointer;
            result = other->QueryInterface(unknown_uuid_IPiggyback_7cfc30, (void **)&pointer);
            Attach(SUCCEEDED(result) ? pointer : 0);
        } else {
            result = E_NOINTERFACE;
        }
        return result;
    }
    void Attach(IPiggyback *pointer)
    {
        if (Pointer != 0) {
            Pointer->Release();
        }
        Pointer = pointer;
    }
    operator IPiggyback *() const { return Pointer; }
    IPiggyback *operator->() const { return Pointer; }
    IPiggyback *Pointer;
};

// A random entry of a sound list.
inline int Random_Sound(TypeList<int> &list)
{
    unsigned index = unknown_random_839218();
    return list[index % list.Count()];
}

void FootClass::AI()
{
    TechnoClass::AI();
    if (!unknown_7d) {
        return;
    }
    unknown_59d = false;
    if (Frame % Rules->unknown_144c == 0 && !unknown_slot32()->ImmuneToRadiation && !unknown_slot21()) {
        Cell cell = Coord_Cell(Center_Coord());
        int amount = Map_Cell_At(cell)->Unknown_0047CE70();
        if (amount > 0) {
            int damage = (int)(amount * Rules->unknown_1460);
            unknown_slot86(&damage, 0, Rules->unknown_147c, 0, false, 1);
            if (!unknown_7d) {
                return;
            }
        }
    }
    if (!unknown_32d && unknown_slot32()->BalloonHover
        && Map.Unknown_0055A740((CellClass *)unknown_slot105(), 1)) {
        unknown_32d = true;
    }
    if (Locomotor.Checked()->Is_Moving_Now() && unknown_slot21() && House->Is_Ally(unknown_player_a35db4)
        && unknown_54c.Value() == 0) {
        unknown_slot263(0, 0, 0, 0);
        unknown_slot262(0, 0, 0, 0);
        if (unknown_1f8 != unknown_slot108()) {
            Map.Unknown_0054A550(CoordStruct(Coord), 0, unknown_1f4 + 3, 0);
        } else {
            Map.Unknown_0054A550(CoordStruct(Coord), unknown_1f4 - 3, unknown_1f4 + 3, 0);
        }
        unknown_1f8 = unknown_slot108();
        unknown_54c = CDTimerClass<FrameTimerClass>(15);
    }

    int frame = unknown_430;
    if (Locomotor != 0 && !unknown_325 && !unknown_7a) {
        Locomotor.Checked()->Process();
        if (!unknown_7d) {
            return;
        }
        if (((Locomotor.Checked()->Is_Moving_Now() && !unknown_slot112())
                || (unknown_228 != 0 && unknown_slot32()->HoverAttack))
            && Frame % unknown_slot32()->WalkRate == 0 && !unknown_slot111() && !unknown_slot112()
            || unknown_slot32()->IdleRate != 0 && !Locomotor.Checked()->Is_Moving_Now()
            && Frame % unknown_slot32()->IdleRate == 0 && !unknown_slot111() && !unknown_slot112()) {
            unknown_430++;
        }
    }
    if ((frame != unknown_430 || Locomotor.Checked()->Is_Moving_Now()) && !unknown_7a && !unknown_37d) {
        if (!unknown_434 && unknown_slot32()->MoveSound.Count() > 0) {
            unknown_43c.Unknown_00405D50();
            Unknown_00713E60(Random_Sound(unknown_slot32()->MoveSound), CoordStruct(Coord), (int)&unknown_43c);
            unknown_434 = true;
        }
        unknown_438 = 3;
    } else if (unknown_434) {
        if (unknown_438 != 0 && !unknown_7a && !unknown_37d) {
            unknown_438--;
        } else {
            unknown_43c.Unknown_00406070();
            unknown_434 = false;
            unknown_438 = 0;
        }
    }

    if (unknown_7a != unknown_7b) {
        if (unknown_7a && unknown_slot32()->VoiceFalling != -1 && unknown_7c) {
            Unknown_00713E60(unknown_slot32()->VoiceFalling, CoordStruct(Coord), 0);
        }
        unknown_7b = unknown_7a;
    }
    if (unknown_325 != unknown_326) {
        if (unknown_325) {
            if (unknown_slot32()->VoiceSinking != -1) {
                Unknown_00713E60(unknown_slot32()->VoiceSinking, CoordStruct(Coord), 0);
            }
            if (unknown_slot32()->SinkingSound != -1) {
                Unknown_00713E60(unknown_slot32()->SinkingSound, CoordStruct(Coord), (int)&unknown_43c);
            } else if (Rules->unknown_200 != -1) {
                Unknown_00713E60(Rules->unknown_200, CoordStruct(Coord), (int)&unknown_43c);
            }
        } else if (!unknown_434) {
            unknown_43c.Unknown_00406070();
        }
        unknown_326 = unknown_325;
    }
    if (unknown_37d != unknown_37e) {
        if (unknown_37d) {
            unknown_43c.Unknown_00406070();
            if (unknown_slot32()->VoiceCrashing != -1 && House->Unknown_004F52B0()) {
                Unknown_00713E60(unknown_slot32()->VoiceCrashing, CoordStruct(Coord), 0);
            }
            if (unknown_slot32()->CrashingSound != -1) {
                Unknown_00713E60(unknown_slot32()->CrashingSound, CoordStruct(Coord), (int)&unknown_43c);
            }
        } else if (!unknown_434) {
            unknown_43c.Unknown_00406070();
        }
        unknown_37e = unknown_37d;
    }
    Unknown_007141B0(CoordStruct(Coord), &unknown_43c);

    if ((Frame & 0x3F) == 0x3F && unknown_494 == 0 && !unknown_79
        && !((UnknownCellClass *)unknown_slot105())->unknown_11c && (unsigned char)unknown_slot164() && unknown_slot108() == 0) {
        unknown_slot87(CoordStruct(0, 0, 0), 1 != 0, 0 != 0);
    }

    UnknownPiggybackPtr piggyback(Locomotor);
    if (piggyback != 0 && piggyback->Is_Ok_To_End()) {
        Locomotor.Attach(0);
        piggyback->End_Piggyback(&Locomotor.Pointer);
    }
    unknown_59e = false;
    unknown_6d7f70();
    if (unknown_580 != 0) {
        unknown_580->unknown_588->AI();
    }
}

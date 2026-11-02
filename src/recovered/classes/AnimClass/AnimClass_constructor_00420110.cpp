// AnimClass::AnimClass(AnimTypeClass const *type, CoordStruct const &coord, int loop_delay, int loops, int flags, int zadjust) (0x00420110)
// Starts an animation of a type at a coordinate: takes the type's defaults
// (sort and z adjust, the frame count when the type has none, a random rate
// when the type asks for one), places it (a bouncing or meteor animation
// first picks a random launch velocity and start position above the
// coordinate), lights the map when it is the type that reveals ground, sets
// the loop count and, with no loop delay, starts it (0x004226D0).
#include "shared/anim.hpp"
#include "shared/rules.hpp"
#include "shared/shape_file.hpp"
#include "shared/random.hpp"
#include "shared/map_view.hpp"
#include "shared/options.hpp"
#include "shared/id_source.hpp"
// The existing Anim layout splits the contiguous 0x50-byte BounceClass at +0x108
// into its leading state and two quaternions. Calls use that evidenced full view.
// @ref ??0ObjectClass@@QAE@XZ=005d22e0
// @ref ??0UnknownQuaternion@@QAE@MMMM@Z=00622160
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?Init@UnknownAudioController@@QAEXXZ=00405bf0
// @ref ?Frame@@3HA=00a40d2c
// @ref ?Anims@@3V?$DynamicVectorClass@PAVAnimClass@@@@A=00a40960
// @ref _unknown_geometry_l=0084c6d0
// @ref ??_7AnimClass@@6BIPersistStream@@@=0079c084
// @ref ??_7AnimClass@@6BIRTTITypeInfo@@@=0079c068
// @ref ??_7AnimClass@@6BINoticeSink@@@=0079c060
// @ref ??_7AnimClass@@6BINoticeSource@@@=0079c058
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_slot39@ObjectTypeClass@@UBEPAXXZ=00426550
// @ref ?Unknown_005D9760@UnknownSpeedA40B18@@QAEHH@Z=005d9760
// @ref ?unknown_speed_a40b18@@3VUnknownSpeedA40B18@@A=00a40b18
// @ref ?unknown_func_5d4920@ObjectClass@@QAEXH@Z=005d4920
// @ref ?unknown_slot109@ObjectClass@@UAEXH@Z=005d4860
// @ref ?unknown_slot53@ObjectClass@@UAE_NPBUCoordStruct@@H@Z=005d3890
// @ref ?Center_Coord@ObjectClass@@UBE?AUCoordStruct@@XZ=005d4e40
// @ref __ftol=0077f110
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_func_4226d0@AnimClass@@QAEXXZ=004226d0

AnimClass::AnimClass(AnimTypeClass const *type, CoordStruct const &coord, int loop_delay, int loops, int flags, int zadjust) :
    Class((AnimTypeClass *)type),
    unknown_b4(0),
    unknown_b8(-1),
    unknown_bc(0),
    unknown_c0(-1),
    unknown_e4(1000),
    ZAdjust(0),
    YSortAdjust(0),
    unknown_f0(unknown_geometry_l),
    unknown_fc(0),
    unknown_100(false),
    unknown_101(false),
    unknown_102(false),
    unknown_103(false),
    unknown_104(0),
    unknown_138(0.0f, 0.0f, 0.0f, 1.0f),
    unknown_148(0.0f, 0.0f, 0.0f, 1.0f),
    unknown_158(false),
    unknown_159(false),
    unknown_15c(0),
    LoopDelay(loop_delay),
    unknown_168(1.0),
    unknown_170(flags),
    unknown_174(false),
    Loops(1),
    unknown_176(false),
    unknown_177(false),
    unknown_178(false),
    unknown_179(false),
    unknown_17a(false),
    unknown_17b(false),
    unknown_17c(true),
    unknown_17d(false),
    unknown_17e(false)
{
    Palette.Buffer[0] = 0;
    AbstractClass::Create_ID();
    unknown_180.Init();
    unknown_194.Init();
    Anims.Add(this);
    unknown_7d = true;
    YSortAdjust = Class->YSortAdjust;
    if (Class->End == -1) {
        Class->End = ((ShapeFileStruct *)Class->unknown_slot39())->FrameCount;
        if (Class->Shadow) {
            Class->End = Class->End / 2;
        }
    }
    if (Class->LoopEnd == -1) {
        Class->LoopEnd = Class->End;
    }
    if (zadjust != 0) {
        ZAdjust = zadjust;
    } else {
        ZAdjust = Class->ZAdjust;
    }
    int rate = Class->Rate;
    if ((Class->RandomRateMin != 0 || Class->RandomRateMax != 0) && Class->RandomRateMin <= Class->RandomRateMax) {
        rate = unknown_id_source_a3d290->Random()(Class->RandomRateMin, Class->RandomRateMax);
    }
    if (Class->Normalized) {
        rate = Options.Normalize_Delay(rate);
        Set_Rate(rate);
    } else {
        Set_Rate(rate);
    }
    Stage = 0;
    if (Class->Layer == 3 || Class->Layer == 4) {
        unknown_func_5d4920(Rules->unknown_6dc);
    } else {
        ObjectClass::unknown_slot109(0);
    }
    if (Class->Reverse) {
        Set_Stage(Class->LoopEnd);
        Set_Step(-Fetch_Step());
    }
    if (!Class->Bouncer && !Class->IsMeteor) {
        ObjectClass::unknown_slot53(&coord, 0);
    } else {
        unknown_174 = true;
        if (Class->IsMeteor) {
            int rand_y = unknown_id_source_a3d290->Random()();
            int rand_x = unknown_id_source_a3d290->Random()();
            Vector3 velocity(
                abs(rand_x) % (int)(Class->MaxXYVel * 2) - Class->MaxXYVel,
                abs(rand_y) % (int)(Class->MaxXYVel * 2) - Class->MaxXYVel,
                Class->MinZVel);
            if (velocity.X < -velocity.Y) {
                velocity.X = -velocity.X;
                velocity.Y = -velocity.Y;
            }
            int height = 70 - abs(unknown_id_source_a3d290->Random()() % 20);
            CoordStruct start((int)(coord.X - height * velocity.X), (int)(coord.Y - height * velocity.Y), (int)(coord.Z - height * velocity.Z));
            ObjectClass::unknown_slot53(&start, 0);
            ((BounceClass *)&unknown_108)->Init(Center_Coord(), Class->Elasticity, 1.4f, 0, velocity, 0);
        } else {
            ObjectClass::unknown_slot53(&coord, 0);
            CoordStruct position;
            position = Center_Coord() + CoordStruct(0, 0, 10);
            int rand_z = unknown_id_source_a3d290->Random()();
            int rand_y = unknown_id_source_a3d290->Random()();
            int rand_x = unknown_id_source_a3d290->Random()();
            float vy = abs(rand_y) % (int)(Class->MaxXYVel * 2) - Class->MaxXYVel;
            Vector3 velocity(
                abs(rand_x) % (int)(Class->MaxXYVel * 2) - Class->MaxXYVel,
                vy,
                abs(rand_z) % (int)(Class->unknown_2e0 - Class->MinZVel + 1.0) + Class->MinZVel);
            ((BounceClass *)&unknown_108)->Init(position, Class->Elasticity, 1.4f, 0, velocity, 0);
        }
    }
    if (Class == Rules->DropZoneAnim) {
        Map.Sight_From(coord, Rules->DropZoneRadius / 256, unknown_player_a35db4, false, 0, 0, true, 0);
        Map.Sight_From(coord, Rules->DropZoneRadius / 256, unknown_player_a35db4, false, 0, 0, true, 1);
    }
    if (loops <= 1) {
        loops = 1;
    }
    Loops = Class->LoopCount * loops;
    Loops = (Loops > 1) ? Loops : 1;
    if (LoopDelay == 0) {
        unknown_func_4226d0();
    }
}
// @ref __real@8@3fff8000000000000000=0079a708

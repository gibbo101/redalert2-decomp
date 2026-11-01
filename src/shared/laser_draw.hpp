// LaserDrawClass: a laser line drawn for a time (0x58 bytes; name from the
// RTTI of VectorClass<LaserDrawClass *> 0x007A5434; every live laser is in
// LaserDrawList::Array, shared/laser_draw_list.hpp).
// LaserDraw.cpp: constructor 0x00533110, destructor 0x00533260, Clear_All
// 0x005332B0, Update 0x00533330, Update_All 0x005333F0. Layout from the
// constructor; the constructor argument names are hypotheses (public YR
// references); TechnoClass 0x006C9DF0 and BuildingClass 0x00446820 create lasers.
#ifndef RA2_SHARED_LASER_DRAW_HPP
#define RA2_SHARED_LASER_DRAW_HPP

#include "shared/coord.hpp"
#include "shared/rgb_class.hpp"
#include "shared/stage.hpp"

class LaserDrawClass {
public:
    LaserDrawClass(CoordStruct source, CoordStruct target, int z_adjust, bool unknown, RGBClass inner, RGBClass outer,
                   RGBClass outer_spread, int duration, bool blinks, bool fades, float start_intensity,
                   float end_intensity);       // 0x00533110
    ~LaserDrawClass();                         // 0x00533260 (leaves LaserDrawList::Array)

    // Deletes every laser.
    static void Clear_All();                   // 0x005332B0
    // Steps the progress, toggles a blinking laser and deletes it when its
    // duration is over.
    void Update();                             // 0x00533330
    // Updates every laser, last first.
    static void Update_All();                  // 0x005333F0
    // Draws the laser (nothing once its duration is not positive; the
    // house-colour lasers through Draw_House_Color).
    void Draw_It();                            // 0x005334F0
    // Draws every laser, last first.
    static void Draw_All();                    // 0x005334D0

    StageClass Progress;                       // +0x00 (stage 0, rate 1)
    int unknown_18;                            // +0x18 (1; 0x4468DD stores 3)
    bool IsHouseColor;                         // +0x1C (drawn in the owner's colour)
    bool unknown_1d;                           // +0x1D
    CoordStruct Source;                        // +0x20
    CoordStruct Target;                        // +0x2C
    int ZAdjust;                               // +0x38
    bool unknown_3c;                           // +0x3C
    RGBClass InnerColor;                       // +0x3D
    RGBClass OuterColor;                       // +0x40
    RGBClass OuterSpread;                      // +0x43
    int Duration;                              // +0x48 progress at which the laser ends
    bool Blinks;                               // +0x4C
    bool BlinkState;                           // +0x4D
    bool Fades;                                // +0x4E
    float StartIntensity;                      // +0x50
    float EndIntensity;                        // +0x54
};

#endif

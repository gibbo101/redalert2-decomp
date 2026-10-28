// LineTrail: the fading line behind a moving object (LineTrail.cpp, unit
// 0x00539170: 0x005393E0-0x0053986F; the RTTI of DynamicVectorClass<LineTrail *>
// names it). ObjectClass +0x94 owns one: Place (0x005D3890) makes it for a type
// with a line trail and sets its colour, decrement and owner. Layout from the
// constructor 0x005393E0; member names follow public YR references (hypotheses).
#ifndef RA2_SHARED_LINE_TRAIL_HPP
#define RA2_SHARED_LINE_TRAIL_HPP

#include "shared/coord.hpp"
#include "shared/rgb_class.hpp"
#include "shared/vector_class_decl.hpp"

class ObjectClass;

// One point of the trail and its remaining intensity (0x10 bytes).
struct LineTrailNode {
    CoordStruct Position;       // +0x00
    int Value;                  // +0x0C
};

class LineTrail {
public:
    LineTrail();                            // 0x005393E0 (grey, decrement 16; listed)
    ~LineTrail();                           // 0x00539490 (released by the owner; unlisted)
    // Detaches the trail from its owner (the owner's +0x94 and Owner cleared).
    void Clear_Owner();                     // 0x005394F0
    // Intensity lost per frame; doubled unless 0x00A40B2C is set.
    void Set_Decrement(int decrement);      // 0x00539510
    // Adds the owner's position when it moved and fades every point.
    void AI();                              // 0x00539530
    // Draws the segments between the live points.
    void Draw();                            // 0x005395C0
    // True when the trail has no owner and its newest point has faded.
    int Is_Dead() const;                    // 0x005396E0
    // Updates every trail, deleting the dead ones and drawing the others.
    static void Update_All();               // 0x00539700
    // Deletes every trail and clears the list.
    static void Delete_All();               // 0x005397B0

    RGBClass Color;                         // +0x00 (128, 128, 128)
    ObjectClass *Owner;                     // +0x04
    int Decrement;                          // +0x08 (16)
    int ActiveSlot;                         // +0x0C newest point
    LineTrailNode Trails[32];               // +0x10 ring of points
};
typedef char LineTrail_size_210[(sizeof(LineTrail) == 0x210) ? 1 : -1];

// Every trail (0x00A6E970; defined with the unit's header statics; name hypothesis).
extern DynamicVectorClass<LineTrail *> unknown_LineTrail_list_00a6e970;

#endif

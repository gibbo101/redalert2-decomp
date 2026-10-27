// UnknownOverlayType: the overlay type fields the object units read, and the
// overlay type list (shared by shared/techno.hpp and shared/anim.hpp).
#ifndef RA2_SHARED_OVERLAY_VIEW_HPP
#define RA2_SHARED_OVERLAY_VIEW_HPP

#include "shared/vector_class.hpp"

// An overlay type (stand-in for OverlayTypeClass: the fields TechnoClass,
// InfantryClass and AnimClass read).
class UnknownOverlayType {
public:
    char unknown_000[0x9C];
    int unknown_9c;                         // +0x09C (TechnoClass slot 27: 6 allows a Parasite warhead's attack; hypothesis)
    char unknown_0a0[0x201 - 0xA0];
    bool unknown_201;                       // +0x201 (TechnoClass slot 27: attackable)
    char unknown_202[0x270 - 0x202];
    int unknown_270;                        // +0x270 (a house index; InfantryClass slot 101: compared with the cell's +0x11E >> 4)
    char unknown_274[0x278 - 0x274];
    bool unknown_278;                       // +0x278 (InfantryClass slot 101: a wall)
    char unknown_279;
    bool unknown_27a;                       // +0x27A (InfantryClass slot 101)
    char unknown_27b[0x285 - 0x27B];
    bool unknown_285;                       // +0x285
};
extern DynamicVectorClass<UnknownOverlayType *> unknown_overlay_types_a35de8;   // 0x00A35DE8 (OverlayTypes)

#endif

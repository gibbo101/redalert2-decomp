// LogicClass (Logic.CPP, unit 0x0053D630-0x0053E3CF; RTTI vtable 0x0079A8EC): the layer of every
// object that runs its AI each frame (Westwood's LOGIC.CPP; TibSun logic.cpp names).
#ifndef RA2_SHARED_LOGIC_HPP
#define RA2_SHARED_LOGIC_HPP

#include "shared/layer.hpp"

class AbstractClass;

class LogicClass : public LayerClass {
public:
    void AI();                                              // 0x0053D890
    void Environment_AI();                                  // 0x0053DFB0
    void Detach(AbstractClass const *target, bool all);    // 0x0053E110
    void Remove(ObjectClass *object);                       // 0x0053E370
};
extern LogicClass Logic;                                    // 0x00832470

// The frame-rate threshold for the light and particle detail level, with hysteresis: the
// lower threshold (0x007DFB34) until the frame rate falls under it, then the threshold plus
// the buffer zone (0x007DFB38) until the rate climbs back over that (0x0053D840).
unsigned int Unknown_0053D840();
// Runs the AI of every submitted object in the object lists, last first (0x0053E180).
void AI_Submitted_Objects();

#endif

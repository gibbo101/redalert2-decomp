// SpotLightClass (SpotLight.cpp, unit 0x005DD320: 0x005DD590-0x005DDD..;
// not polymorphic; RTTI name from the unit's list): a light at a coordinate
// that registers itself in unknown_SpotLightClass_list_00a731c0 and grows
// for ten frames. The layout is from the constructor 0x005DD590 (hypotheses).
#ifndef RA2_SHARED_SPOT_LIGHT_HPP
#define RA2_SHARED_SPOT_LIGHT_HPP

#include "shared/coord.hpp"
#include "shared/vector_class_decl.hpp"

class SpotLightClass {
public:
    SpotLightClass(CoordStruct coord, int size);    // 0x005DD590
    ~SpotLightClass();                              // 0x005DD610
    // Grows by 8; deleted once it reaches 80.
    void AI();                                      // 0x005DD660
    // Runs AI for every light, last first.
    static void Update_All();                       // 0x005DD6D0
    void unknown_func_5ddb90();                     // 0x005DDB90
    // Runs unknown_func_5ddb90 (the drawing) for every light, last first.
    static void Draw_All();                         // 0x005DE2E0

    CoordStruct Coord;                              // +0x00
    int unknown_0c;                                 // +0x0C (0; +8 per frame, deleted at 80)
    int unknown_10;                                 // +0x10 the size argument
    int unknown_14;                                 // +0x14 (0)
};

// Every spot light (0x00A731C0; defined with the unit's header statics; name hypothesis).
extern DynamicVectorClass<SpotLightClass *> unknown_SpotLightClass_list_00a731c0;

// Frees the block 0x00A73378 and deletes every object of the 74-entry table 0x00A731E0 (0x005DDB40; convention
// unevidenced: __cdecl and __fastcall compile alike, and no caller is recovered).
void Unknown_005DDB40();

#endif

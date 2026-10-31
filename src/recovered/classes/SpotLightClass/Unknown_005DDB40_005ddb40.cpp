// @ref ?Free_Memory_00781d3b@@YAXPAX@Z=00781d3b
// @ref ?unknown_block_a73378@@3PAXA=00a73378
// @ref ?unknown_objects_a731e0@@3PAPAVUnknownSpotLightObject_a731e0@@A=00a731e0
#include "shared/spot_light.hpp"
// The CRT free (lobby.hpp and main_opt.hpp declare it too; neither belongs in this unit).
void Free_Memory_00781d3b(void *block);

// A polymorphic object the SpotLight unit keeps in a 74-entry table (0x00A731E0; type not recovered).
class UnknownSpotLightObject_a731e0 {
public:
    virtual ~UnknownSpotLightObject_a731e0();
};
extern UnknownSpotLightObject_a731e0 *unknown_objects_a731e0[74];
// A block freed by Unknown_005DDB40 (0x00A73378).
extern void *unknown_block_a73378;

void Unknown_005DDB40()
{
    if (unknown_block_a73378 != 0) {
        Free_Memory_00781d3b(unknown_block_a73378);
        unknown_block_a73378 = 0;
    }
    for (int i = 0; i < 74; i++) {
        delete unknown_objects_a731e0[i];
        unknown_objects_a731e0[i] = 0;
    }
}

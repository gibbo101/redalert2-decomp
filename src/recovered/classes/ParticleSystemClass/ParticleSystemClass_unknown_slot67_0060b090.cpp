// void ParticleSystemClass::unknown_slot67(int arg1, int arg2) (0x0060B090, slot 67)
// A one-frame light type flashes a spot light sized by how full the system
// is (the particle count over ParticleCap, between 0.4 and 1).
#include "shared/particle_system.hpp"
#include "shared/spot_light.hpp"
// @ref __real@4@3fff8000000000000000=0079b7f8
// @ref __real@8@3ffdccccccccccccd000=0079c268
// @ref __ftol=0077f110
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??0SpotLightClass@@QAE@UCoordStruct@@H@Z=005dd590
// @ref ??1SpotLightClass@@QAE@XZ=005dd610
// @ref ?unknown_func_5ddb90@SpotLightClass@@QAEXXZ=005ddb90

void ParticleSystemClass::unknown_slot67(int arg1, int arg2)
{
    if (Class->OneFrameLight && Class->LightSize > 0 && Particles.Count() > 0) {
        // Westwood's Max(0.4, Min(1.0f, fill)) macros: each operand is
        // evaluated again where it is chosen.
        float ratio = (0.4 > ((1.0f < (float)Particles.Count() / Class->ParticleCap) ? 1.0f : (float)Particles.Count() / Class->ParticleCap))
            ? 0.4
            : ((1.0f < (float)Particles.Count() / Class->ParticleCap) ? 1.0f : (float)Particles.Count() / Class->ParticleCap);
        int size = ratio * Class->LightSize;
        SpotLightClass *light = new SpotLightClass(Coord, size);
        light->unknown_0c = unknown_e0;
        light->unknown_func_5ddb90();
        delete light;
    }
}

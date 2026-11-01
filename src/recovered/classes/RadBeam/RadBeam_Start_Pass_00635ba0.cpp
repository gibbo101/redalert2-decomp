// void RadBeam::Start_Pass() (0x00635BA0)
// Steps, the per-step delta, the first step, the wave value and the colour for a new pass (no
// caller: unknown_6358d0 0x006358D0 writes the same code out).
#include "shared/rad_beam_list.hpp"

void RadBeam::Start_Pass()
{
    Steps = (int)(Length / StepLength);
    int x = Delta.X;
    int y = Delta.Y;
    int z = Delta.Z;
    if (Steps != 0) {
        x /= Steps;
        y /= Steps;
        z /= Steps;
    }
    StepDelta = CoordStruct(x, y, z);
    Current = Source;
    double phase = unknown_6c;
    phase /= Period;
    unknown_70 = phase * Amplitude;
    CurrentColor = Color;
}


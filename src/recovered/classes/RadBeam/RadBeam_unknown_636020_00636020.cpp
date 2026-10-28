// void RadBeam::unknown_636020() (0x00636020)
#include "shared/rad_beam_list.hpp"
#include "shared/unknown_geometry.hpp"

void RadBeam::unknown_636020()
{
    int period = Period;
    double phase;
    if (unknown_6c < period / 2) {
        phase = unknown_6c * 2;
    } else {
        phase = period - unknown_6c * 2 % period;
    }
    unknown_70 = phase / period * Amplitude;
    int offset = (int)(unknown_48 * unknown_6c * unknown_40);
    Delta = Delta + CoordStruct(unknown_60.X * offset, unknown_60.Y * offset, unknown_60.Z * offset);
    Length = unknown_sqrt_4ba410(Delta.X * Delta.X + Delta.Y * Delta.Y + Delta.Z * Delta.Z);
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
}

// void RadBeam::unknown_635f80() (0x00635F80)
#include "shared/rad_beam_list.hpp"
#include "shared/unknown_geometry.hpp"

void RadBeam::unknown_635f80()
{
    Delta = Target - Source;
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
    unknown_60 = CoordStruct(x, y, z);
}

// void RadBeam::Compute_Delta() (0x00635B30)
#include "shared/rad_beam_list.hpp"
#include "shared/unknown_geometry.hpp"

void RadBeam::Compute_Delta()
{
    Delta = Target - Source;
    Length = unknown_sqrt_4ba410(Delta.X * Delta.X + Delta.Y * Delta.Y + Delta.Z * Delta.Z);
}

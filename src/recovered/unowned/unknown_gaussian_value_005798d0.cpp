// double __stdcall unknown_gaussian_value(double mean, double deviation) -- 0x005798D0
// Purpose: a normally distributed value: the shared normal-variate
// generator at 0x00A6FD50 (0x00579830, Box-Muller with a cached spare)
// scaled by `deviation` and offset by `mean`. Random map generator area
// (after MapSeedClass); names are hypotheses.
// @ref ?Next@UnknownGaussianSource_005798d0@@QAENXZ=00579830
// @ref ?unknown_gaussian_a6fd50@@3VUnknownGaussianSource_005798d0@@A=00a6fd50

class UnknownGaussianSource_005798d0 {
public:
    double Next();

    bool HasSpare;       // +0x00
    double Spare;        // +0x08
};

extern UnknownGaussianSource_005798d0 unknown_gaussian_a6fd50;

double __stdcall unknown_gaussian_value_005798d0(double mean, double deviation)
{
    return unknown_gaussian_a6fd50.Next() * deviation + mean;
}

// Gains value / (cost * VeteranRatio) experience, capped at VeteranCap (0x00713360; TS Made_A_Kill).
// The original loads the cap as an FP rvalue (fld, then fld again for the store), which a
// double-returning inline accessor reproduces; reading the member directly copies it as two dwords.
#define MIN(a,b) (((a)<(b))?(a):(b))
inline double Veteran_Cap() { return Rules->VeteranCap; }
void UnknownTechnoPair::Unknown_00713360(int cost, int value)
{
    Experience += value / (cost * Rules->VeteranRatio);
    Experience = MIN(Experience, Veteran_Cap());
}

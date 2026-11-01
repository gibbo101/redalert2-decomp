// float Vector3::Length() const (0x00437710): Westwood's (float)sqrt(Length2()); the out-of-line
// copy BounceClass::AI 0x004370E0 calls.
double __cdecl unknown_sqrt_4ba410(double value);     // 0x004BA410

float Vector3::Length() const
{
    return (float)unknown_sqrt_4ba410(X * X + Y * Y + Z * Z);
}
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410

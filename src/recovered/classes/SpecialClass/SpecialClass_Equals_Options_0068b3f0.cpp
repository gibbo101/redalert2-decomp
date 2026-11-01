// bool SpecialClass::Equals_Options(SpecialClass const &other) const (0x0068B3F0)
// Whether bits 0-18 (every option) are equal; the original tests the XOR's low
// byte and then bits 8-18. The if/return form returns the bool in al.
#include "shared/special.hpp"
bool SpecialClass::Equals_Options(SpecialClass const &other) const
{
    if (unknown_bits_0 == other.unknown_bits_0
        && IsFromInstall == other.IsFromInstall
        && EscapeMovies == other.EscapeMovies
        && unknown_bit_4 == other.unknown_bit_4
        && Inert == other.Inert
        && TiberiumGrows == other.TiberiumGrows
        && TiberiumSpreads == other.TiberiumSpreads
        && MCVDeploy == other.MCVDeploy
        && InitialVeteran == other.InitialVeteran
        && FixedAlliance == other.FixedAlliance
        && HarvesterImmune == other.HarvesterImmune
        && FogOfWar == other.FogOfWar
        && unknown_bit_13 == other.unknown_bit_13
        && TiberiumExplosive == other.TiberiumExplosive
        && DestroyableBridges == other.DestroyableBridges
        && Meteorites == other.Meteorites
        && IonStorms == other.IonStorms
        && Visceroids == other.Visceroids) {
        return true;
    }
    return false;
}

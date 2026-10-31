// bool SuperClass::unknown_69e990() const (0x0069E990)
// Whether the super weapon is still charging, or a charge-drain weapon (hypothesis).

bool SuperClass::unknown_69e990() const
{
    if (Type->UseChargeDrain) {
        return true;
    }
    return !unknown_0x57;
}

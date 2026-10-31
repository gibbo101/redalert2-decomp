// bool SuperClass::Unknown_0069D820() (0x0069D820)
// Whether the super weapon can be fired now (TS SuperClass::Can_Place).

bool SuperClass::Unknown_0069D820()
{
    if (!unknown_0x58) {
        if (Type->UseChargeDrain) {
            return unknown_0x60 != 0 ? true : false;
        }
        return unknown_0x57;
    }
    return false;
}

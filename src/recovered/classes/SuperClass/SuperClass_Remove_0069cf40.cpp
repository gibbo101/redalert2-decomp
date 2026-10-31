// bool SuperClass::Remove() (0x0069CF40)
// Takes the super weapon away from its house.

bool SuperClass::Remove()
{
    if (unknown_0x55) {
        unknown_0x57 = false;
        unknown_0x55 = false;
        unknown_supers_a35db8.Delete(this);
        return true;
    }
    return false;
}

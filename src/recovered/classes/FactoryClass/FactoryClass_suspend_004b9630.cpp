bool FactoryClass::Suspend_004B9630(bool value)
{
    if (!unknown_6c) {
        unknown_6d = value;
        unknown_6c = true;
        Set_Rate(0);
        return true;
    }
    return false;
}

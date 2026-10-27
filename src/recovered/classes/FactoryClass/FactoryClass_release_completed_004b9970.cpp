bool FactoryClass::Release_Completed_004B9970()
{
    if (Object && Stage == 54) {
        Object = 0;
        unknown_6c = true;
        unknown_59 = true;
        Stage = 0;
        Set_Rate(0);
        return true;
    }
    if (unknown_64 && Stage == 54) {
        unknown_64 = -1;
        unknown_6c = true;
        unknown_59 = true;
        Stage = 0;
        Set_Rate(0);
        return true;
    }
    return false;
}

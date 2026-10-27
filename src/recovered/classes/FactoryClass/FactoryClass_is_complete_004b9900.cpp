bool FactoryClass::Is_Complete_004B9900() const
{
    if (Object && Stage == 54) return true;
    if (unknown_64 != -1 && Stage == 54) return true;
    return false;
}

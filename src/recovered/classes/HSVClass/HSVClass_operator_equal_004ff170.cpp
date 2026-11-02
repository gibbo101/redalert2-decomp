bool HSVClass::operator==(HSVClass const &that) const
{
    return Hue == that.Hue && Saturation == that.Saturation && Value == that.Value;
}

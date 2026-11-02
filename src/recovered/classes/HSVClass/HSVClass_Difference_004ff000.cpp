// The squared distance between two colours, channel by channel (0x004FF000).
int HSVClass::Difference(HSVClass const &hsv) const
{
    int hue = (int)Hue - (int)hsv.Hue;
    if (hue < 0) hue = -hue;

    int saturation = (int)Saturation - (int)hsv.Saturation;
    if (saturation < 0) saturation = -saturation;

    int value = (int)Value - (int)hsv.Value;
    if (value < 0) value = -value;

    return hue * hue + saturation * saturation + value * value;
}

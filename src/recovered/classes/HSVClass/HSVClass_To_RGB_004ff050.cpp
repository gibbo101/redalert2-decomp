// The colour as red, green and blue (0x004FF050; Tiberian Sun's operator RGBClass).
RGBClass HSVClass::To_RGB() const
{
    unsigned int i;
    unsigned int f;
    unsigned int tmp;
    unsigned int values[7];

    int hue = Hue;
    int saturation = Saturation;
    int value = Value;
    int red, green, blue;

    hue *= 6;
    f = hue % 255;

    values[1] =
    values[2] = value;

    tmp = (saturation * f) / 255;
    values[3] = (value * (255 - tmp)) / 255;

    values[4] =
    values[5] = (value * (255 - saturation)) / 255;

    tmp = 255 - (saturation * (255 - f)) / 255;
    values[6] = (value * tmp) / 255;

    i = hue / 255;
    i += (i > 4) ? -4 : 2;
    red = values[i];
    i += (i > 4) ? -4 : 2;
    blue = values[i];
    i += (i > 4) ? -4 : 2;
    green = values[i];

    RGBClass rgb((unsigned char)red, (unsigned char)green, (unsigned char)blue);
    return rgb;
}

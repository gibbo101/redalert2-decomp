// Scales the value (HSV) of every palette entry by percentage, clamped to 0..255 (0x0051EA50).
void __fastcall Increase_Palette_Luminance(PaletteClass &palette, double percentage)
{
    for (int i = 0; i < 256; i++) {
        HSVClass hsv = palette[i];

        int value = (int)(hsv.Value * percentage);
        value = value < 255 ? value : 255;
        value = value > 0 ? value : 0;
        hsv.Value = (unsigned char)value;
        RGBClass rgb = hsv.To_RGB();
        palette[i] = rgb;
    }
}

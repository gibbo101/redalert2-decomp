// Unknown_00486010 (0x00486010; TibSun ConvertClass::Reinitialize_Hicolor_Tables):
// after a display format change every 16-bit converter's colour table is
// unpacked with the old format's shifts and repacked for the new format; the
// masks and blitters are rebuilt.
void __fastcall Unknown_00486010(int red_right, int red_left, int green_right, int green_left, int blue_right, int blue_left);

void __fastcall Unknown_00486010(int red_right, int red_left, int green_right, int green_left, int blue_right, int blue_left)
{
    for (int i = 0; i < ConvertClass::Drawers.Count(); i++) {
        ConvertClass *converter = ConvertClass::Drawers[i];
        if (converter->BytesPerPixel == 2) {
            unsigned short *table = (unsigned short *)converter->AlphaPalette;
            for (int index = 0; index < 256; index++) {
                unsigned short color = table[index];

                RGBClass rgb;
                rgb.Red = (unsigned char)((color >> red_left) << red_right);
                rgb.Green = (unsigned char)((color >> green_left) << green_right);
                rgb.Blue = (unsigned char)((color >> blue_left) << blue_right);

                // Repacked green first (not shared/hicolor.hpp's Build_Hicolor_Pixel order).
                table[index] = (unsigned short)(((rgb.Green >> unknown_shift_852fcc) << unknown_shift_852fc8)
                                              | ((rgb.Red >> unknown_shift_852fbc) << unknown_shift_852fb8)
                                              | ((rgb.Blue >> unknown_shift_852fc4) << unknown_shift_852fc0));
            }

            converter->HalfMask = unknown_half_mask_852fd0;
            converter->QuarterMask = unknown_quarter_mask_852fd2;

            converter->Delete_Blitters_004853A0();
            converter->Initialize_Blitters_00483B00();
        }
    }
}

// Tiberian Sun interpal.cpp (continued).
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ?Is_Available@CCFileClass@@UAE_NH@Z=004691a0
// @ref ?Open@CCFileClass@@UAEHH@Z=00469220
// @ref ?Read@CCFileClass@@UAEJPAXJ@Z=00469060
// @ref ?Write@CCFileClass@@UAEJPBXJ@Z=00469030
// @ref ?Close@CCFileClass@@UAEXXZ=004691f0
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
int CopyType = 0;

// Copies source to dest at twice the size with one of the assembly routines; the blend
// table is read from palette_file_name or rebuilt first when the palette changed, then
// written back (0x0051EB00).
void __fastcall Interpolate_2X_Scale(Surface *source, Surface *dest, char const *palette_file_name)
{
    unsigned char *src_ptr;
    unsigned char *dest_ptr;
    int src_width;
    int dest_width;
    bool source_locked = false;
    bool dest_locked = false;

    if (InterpolationPaletteChanged) {
        if (palette_file_name) {
            Read_Interpolation_Palette(palette_file_name);
        }
        if (InterpolationPaletteChanged) {
            Create_Palette_Interpolation_Table();
        }
    }

    if (palette_file_name) {
        Write_Interpolation_Palette(palette_file_name);
    }

    Wait_For_Surface_Blit_004961d0();

    src_ptr = (unsigned char *)source->Lock();
    if (src_ptr != 0) {
        source_locked = true;
    }

    dest_ptr = (unsigned char *)dest->Lock();
    if (dest_ptr != 0) {
        dest_locked = true;
    }

    if (dest_locked && source_locked) {
        src_width = source->Get_Width();
        dest_width = 2 * dest->Stride();

        switch (CopyType) {
            case 0:
                Asm_Interpolate(src_ptr, dest_ptr, source->Get_Height(), src_width, dest_width);
                break;

            case 1:
                Asm_Interpolate_Line_Double(src_ptr, dest_ptr, source->Get_Height(), src_width, dest_width);
                break;

            case 2:
                Asm_Interpolate_Line_Interpolate(src_ptr, dest_ptr, source->Get_Height(), src_width, dest_width);
                break;
        }
    }

    if (source_locked) {
        source->Unlock();
    }
    if (dest_locked) {
        dest->Unlock();
    }
}

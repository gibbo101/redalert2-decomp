// Writes the blend table to palette_file_name unless that file exists (0x0051E8A0).
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
void __fastcall Write_Interpolation_Palette(char const *palette_file_name)
{
    CCFileClass palette_file(palette_file_name);

    if (!palette_file.Is_Available()) {
        palette_file.Open(FILE_RIGHTS_WRITE);
        palette_file.Write(&PaletteInterpolationTable[0][0], 256 * 256);
        palette_file.Close();
    }
}

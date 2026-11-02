bool UnknownPreview_0061D430::Load_0061E170(char const *filename)
{
    CCFileClass file(filename);

    if (file.Is_Available()) {
        if (unknown_00 != 0) {
            delete unknown_00;
            unknown_00 = 0;
        }
        Surface *surf = unknown_load_pcx_60d110(&file, 0, 0, 0);

        if (surf != 0 && surf->Get_Width() && surf->Get_Height()) {
            unknown_00 = new DSurface(surf->Get_Width(), surf->Get_Height(), true);
            unknown_00->Fill(0);
            unknown_00->Copy_From(*surf, false, true);
            delete surf;
            return true;
        }
    }

    return false;
}
// @ref ?File_Name@RawFileClass@@UBEPBDXZ=00401940
// @ref ??_GCDFileClass@@UAEPAXI@Z=00401950
// @ref ??_GCCFileClass@@UAEPAXI@Z=004019a0
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ??0DSurface@@QAE@HH_N@Z=004aa4a0
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
// @ref ??2@YAPAXI@Z=00782017
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ?Is_Available@CCFileClass@@UAE_NH@Z=004691a0
// @ref ?unknown_load_pcx_60d110@@YIPAVSurface@@PAVFileClass@@PAVPaletteClass@@HH@Z=0060d110

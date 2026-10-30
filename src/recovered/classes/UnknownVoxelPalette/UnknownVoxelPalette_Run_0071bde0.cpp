int UnknownVoxelPalette::Run(FileClass *file)
{
    int failed = 0;
    UnknownVoxelPaletteHeader header;
    if (!file->Open(1)) {
        failed = 1;
    } else if (file->Read(&header, sizeof(header)) != sizeof(header)) {
        failed = 1;
    } else {
        Header.unknown_00 = header.unknown_00;
        Header.unknown_04 = header.unknown_04;
        Header.unknown_08 = header.unknown_08;
        Header.unknown_0c = header.unknown_0c;
        if (file->Read(Palette, 0x300) != 0x300) {
            failed = 1;
        } else if (file->Read(unknown_14, Header.unknown_08 << 8) != Header.unknown_08 << 8) {
            failed = 1;
        }
    }
    file->Close();
    return failed;
}

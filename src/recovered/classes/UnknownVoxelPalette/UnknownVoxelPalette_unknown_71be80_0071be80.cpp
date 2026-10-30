int UnknownVoxelPalette::unknown_71be80(FileClass *file)
{
    int failed = 0;
    UnknownVoxelPaletteHeader header;
    if (!file->Open(2)) {
        failed = 1;
    } else {
        header.unknown_00 = Header.unknown_00;
            header.unknown_04 = Header.unknown_04;
            header.unknown_08 = Header.unknown_08;
            header.unknown_0c = Header.unknown_0c;
        if (file->Write(&header, sizeof(header)) != sizeof(header)) {
            failed = 1;
        } else if (file->Write(Palette, 0x300) != 0x300) {
            failed = 1;
        } else if (file->Write(unknown_14, Header.unknown_08 << 8) != Header.unknown_08 << 8) {
            failed = 1;
        }
    }
    file->Close();
    return failed;
}

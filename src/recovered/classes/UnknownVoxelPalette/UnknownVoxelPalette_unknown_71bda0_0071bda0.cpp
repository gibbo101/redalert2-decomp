int UnknownVoxelPalette::unknown_71bda0(FileClass *file)
{
    int failed = 0;
    file->Open(1);
    if (file->Read(Palette, 0x300) != 0x300) {
        failed = 1;
    }
    file->Close();
    return failed;
}

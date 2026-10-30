UnknownVoxelPalette::~UnknownVoxelPalette()
{
    if (unknown_18) {
        operator delete(Palette);
    }
    if (unknown_1c) {
        operator delete(unknown_14);
    }
}

// ConvertClass::~ConvertClass (0x00485310; TibSun convert.cpp): frees the
// blitters and tables and takes the converter off Drawers. The deleting
// destructor (vtable 0x0079DF70 slot 0, 0x00486120) expands it inline.
ConvertClass::~ConvertClass()
{
    Delete_Blitters_004853A0();

    delete [] (unsigned char *)AlphaPalette;
    AlphaPalette = 0;

    delete [] (unsigned char *)Remap;
    Remap = 0;

    Drawers.Delete(this);
}

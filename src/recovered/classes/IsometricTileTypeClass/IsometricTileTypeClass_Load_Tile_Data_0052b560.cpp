// int IsometricTileTypeClass::unknown_func_52b560() (0x0052B560): reads the image file, turns its
// cell offsets into pointers and rebuilds the preview colours; returns the file's size
// (TibSun Load_Tile_Data).
#include "shared/isometric_tile_type.hpp"
#include "shared/cc_file_class.hpp"
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ?unknown_func_52b560@IsometricTileTypeClass@@QAEHXZ=0052b560

int IsometricTileTypeClass::unknown_func_52b560()
{
    CCFileClass file(Filename);
    int size = file.Size();
    if (unknown_a4 != 0) {
        delete [] (unsigned char *)unknown_a4;
    }
    unsigned char *data = new unsigned char[size];
    unknown_a4 = data;
    file.Read(data, size);
    unknown_a8 = true;

    IsoTileImageStruct *image = (IsoTileImageStruct *)unknown_a4;
    unknown_2b4 = (unsigned char)image->unknown_00[0];
    unknown_2b8 = (unsigned char)image->unknown_00[1];

    for (int i = 0; i < unknown_2b4 * unknown_2b8; i++) {
        if (image->Tiles[i] != 0) {
            unsigned char *ptr = (unsigned char *)unknown_a4;
            if ((unsigned char *)image->Tiles[i] < ptr) {
                image->Tiles[i] = (int)(ptr + image->Tiles[i]);
            }
        }
    }
    unknown_func_52e3d0();
    return size;
}
// @ref ?Open@CCFileClass@@UAEHPBDH@Z=00401980
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??_GCCFileClass@@UAEPAXI@Z=004019a0
// @ref ??_GCDFileClass@@UAEPAXI@Z=00401950
// @ref ?File_Name@RawFileClass@@UBEPBDXZ=00401940

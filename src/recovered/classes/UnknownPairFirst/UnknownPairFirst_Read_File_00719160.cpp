// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
#include "shared/unknown_pair_first.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/unknown_voxel_palette.hpp"
#include "shared/matrix3d.hpp"
// @ref ?VoxelRGBColors@@3PAUVxlRGB@@A=00ae3008
// @ref ?VoxelPaletteTranslateTable@@3PAEA=00af4608
struct VxlRGB { unsigned char Red,Green,Blue; };
extern VxlRGB VoxelRGBColors[256];
extern unsigned char VoxelPaletteTranslateTable[];
struct VxlFileHeader { char Name[16]; unsigned PaletteCount; int LayerCount, LayerInfoCount, DataSize; };
struct VxlLayerHeader { char Name[16]; int InfoIndex, Unused1; unsigned char Unused2; };
struct VxlLayerInfo { int StartOffset, EndOffset, DataOffset; float Scale; float Transform[12]; float MinBounds[3], MaxBounds[3]; unsigned char XSize,YSize,ZSize,NormalType; };
struct VxlMatrixData { float Data[12]; };
int UnknownPairFirst::unknown_719160(FileClass *file, int load_palette)
{
    unsigned i = 0;
    unknown_719110();
    if (!file->Open(1)) return 0;
    VxlLayerInfo layer_info;
    VxlFileHeader header;
    VxlLayerHeader layer_header;
    file->Read(&header, sizeof(header));
    unknown_04 = header.LayerCount;
    unknown_08 = header.LayerInfoCount;
    unknown_0c = header.DataSize;
    unknown_10 = new UnknownVoxelSection[unknown_04];
    unknown_14 = new UnknownVoxelTailer[unknown_08];
    unknown_18 = new unsigned char[unknown_0c];
    if (!unknown_10 || !unknown_14 || !unknown_18) {
        unknown_719110(); file->Close(); return 0;
    }
    if (load_palette) {
        UnknownVoxelPalette palette((unsigned char *)VoxelRGBColors,VoxelPaletteTranslateTable);
        unsigned char first, last;
        if (file->Read(&first,1)!=1) { file->Close(); unknown_719110(); return 0; }
        if (file->Read(&last,1)!=1) { file->Close(); unknown_719110(); return 0; }
        palette.Header.unknown_00=first;
        palette.Header.unknown_04=last;
        for (unsigned char *green=&VoxelRGBColors[0].Green;green<&VoxelRGBColors[256].Green;green+=3) {
            unsigned channel=0;
            file->Read(green+channel++-1,1); file->Read(green+channel++-1,1); file->Read(green+channel-1,1);
        }
        if (header.PaletteCount>1) file->Seek(768*header.PaletteCount-768,1);
        palette.unknown_71bf20(0,0);
    } else file->Seek(770*header.PaletteCount,1);
    for (i=0;i<(unsigned)unknown_04;++i) {

        if (file->Read(&layer_header,sizeof(layer_header))!=sizeof(layer_header)) { unknown_719110(); file->Close(); return 0; }
        unknown_10[i].unknown_00=layer_header.InfoIndex;
        unknown_10[i].unknown_04=layer_header.Unused1;
        *(unsigned char *)&unknown_10[i].unknown_08=layer_header.Unused2;
    }
    if (file->Read(unknown_18,unknown_0c)!=unknown_0c) { unknown_719110(); file->Close(); return 0; }
    for (i=0;i<unknown_08;++i) {

        if (file->Read(&layer_info,sizeof(layer_info))!=sizeof(layer_info)) { unknown_719110(); file->Close(); return 0; }
        unknown_14[i].unknown_a0=layer_info.XSize;
        unknown_14[i].unknown_a1=layer_info.YSize;
        unknown_14[i].unknown_a2=layer_info.ZSize;
        unknown_14[i].unknown_a3=layer_info.NormalType;
        unknown_14[i].unknown_0c=layer_info.Scale;
        *(VxlMatrixData *)unknown_14[i].unknown_10 = (VxlMatrixData &)Matrix3D(layer_info.Transform);
        Vector3 min; min.X=layer_info.MinBounds[0]; min.Y=layer_info.MinBounds[1]; min.Z=layer_info.MinBounds[2];
        Vector3 max; max=*(Vector3 const *)layer_info.MaxBounds;
        unknown_14[i].unknown_40[0]=Vector3(max.X,max.Y,min.Z);
        unknown_14[i].unknown_40[1]=Vector3(max.X,min.Y,min.Z);
        unknown_14[i].unknown_40[2]=Vector3(min.X,min.Y,min.Z);
        unknown_14[i].unknown_40[3]=Vector3(min.X,max.Y,min.Z);
        unknown_14[i].unknown_40[4]=Vector3(max.X,max.Y,max.Z);
        unknown_14[i].unknown_40[5]=Vector3(max.X,min.Y,max.Z);
        unknown_14[i].unknown_40[6]=Vector3(min.X,min.Y,max.Z);
        unknown_14[i].unknown_40[7]=Vector3(min.X,max.Y,max.Z);
        unknown_14[i].unknown_00=(int *)((unsigned char *)unknown_18+layer_info.StartOffset);
        unknown_14[i].unknown_04=(int *)((unsigned char *)unknown_18+layer_info.EndOffset);
        unknown_14[i].unknown_08=(unsigned char *)unknown_18+layer_info.DataOffset;
    }
    file->Close(); return 1;
}

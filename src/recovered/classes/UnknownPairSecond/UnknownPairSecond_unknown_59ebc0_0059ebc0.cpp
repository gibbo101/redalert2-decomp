// int UnknownPairSecond::unknown_59ebc0(FileClass *file) (0x0059EBC0)
// Reads a .HVA motion library: the header (a 16-character name, the frame and section counts),
// skips the section names and reads one 3 x 4 transform per section per frame. 1 on success;
// 0 when the file does not open or ends early (the transforms are freed).
#include "shared/unknown_pair_second.hpp"
#include "shared/matrix3d.hpp"
#include "shared/raw_file_class.hpp"
// @ref ??0Matrix3D@@QAE@PBM@Z=0058fde0

int UnknownPairSecond::unknown_59ebc0(FileClass *file)
{
    if (unknown_transforms != 0) {
        delete [] unknown_transforms;
    }
    unknown_transforms = 0;

    if (!file->Open()) {
        return 0;
    }

    struct {
        char Name[16];
        unsigned FrameCount;
        unsigned SectionCount;
    } header;
    file->Read(&header, sizeof(header));
    unknown_section_count = header.SectionCount;
    unknown_frame_count = header.FrameCount;

    if (unknown_transforms != 0) {
        delete [] unknown_transforms;
    }
    unknown_transforms = new Matrix3D[unknown_frame_count * unknown_section_count];
    if (unknown_transforms == 0) {
        unknown_transforms = 0;
        file->Close();
        return 0;
    }

    file->Seek(unknown_section_count * 16, 1);
    for (unsigned frame = 0; frame < unknown_frame_count; frame++) {
        for (unsigned section = 0; section < unknown_section_count; section++) {
            float matrix[12];
            if (file->Read(matrix, sizeof(matrix)) != sizeof(matrix)) {
                file->Close();
                if (unknown_transforms != 0) {
                    delete [] unknown_transforms;
                }
                unknown_transforms = 0;
                return 0;
            }
            unknown_transforms[frame * unknown_section_count + section] = Matrix3D(matrix);
        }
    }
    file->Close();
    return 1;
}

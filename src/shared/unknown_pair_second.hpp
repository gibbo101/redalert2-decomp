// UnknownPairSecond: a .HVA motion library of the voxel loader (hypothesis;
// constructor 0x0059EB70, scale 0x0059ED30; owned by ObjectTypeClass's
// UnknownObjectPair). Split out of shared/object_type.hpp so the units of its
// members include no ObjectTypeClass header statics.
#ifndef RA2_SHARED_UNKNOWN_PAIR_SECOND_HPP
#define RA2_SHARED_UNKNOWN_PAIR_SECOND_HPP

class FileClass;
class Matrix3D;

class UnknownPairSecond {
public:
#ifdef RA2_UNKNOWN_PAIR_SECOND_UNIT
    UnknownPairSecond();                // 0x0059EB60 (empty library; unreferenced; declared for its unit only)
#endif
    UnknownPairSecond(FileClass *file);  // 0x0059EB70 (a .HVA motion library; hypothesis)
    ~UnknownPairSecond();               // 0x0059EBA0
    int unknown_59ebc0(FileClass *file);    // 0x0059EBC0 (reads the library; 0 on success)
    void unknown_59ed30(float scale);   // 0x0059ED30
    bool unknown_00;                    // +0x00 load failed (hypothesis)
    char unknown_01[3];
    unsigned unknown_section_count; // +04,463A5B
    unsigned unknown_frame_count;   // +08,463A51
    class Matrix3D *unknown_transforms; // +0C, frame/section48-byte matrix array
};

#endif

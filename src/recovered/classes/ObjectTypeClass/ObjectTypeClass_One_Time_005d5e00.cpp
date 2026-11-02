// void ObjectTypeClass::One_Time() (0x005D5E00)
// Loads the shared pip and talk-bubble shapes once: from a loose file when
// one exists (then owned), else from the mixfiles.
#include "shared/object_type.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/anim_type.hpp"
// @ref ??0RawFileClass@@QAE@PBD@Z=00638b40
// @ref ??1RawFileClass@@UAE@XZ=00638ac0
// @ref ?Load_Alloc_Data@@YIPAXAAVFileClass@@@Z=00495230
// @ref ?Retrieve@MixFileClass@@SIPBXPBD@Z=005956c0
// @ref ??_C@_0L@LBLF@PIPBRD?4SHP?$AA@=007e80d0
// @ref ??_C@_08LBPN@PIPS?4SHP?$AA@=007e80c4
// @ref ??_C@_09CMJO@PIPS2?4SHP?$AA@=007e80b8
// @ref ??_C@_0N@LLOK@TALKBUBL?4SHP?$AA@=007e80a8
// @ref ?unknown_pipbrd_shapes_a72fe0@@3PBXB=00a72fe0
// @ref ?unknown_pips_shapes_a72fe4@@3PBXB=00a72fe4
// @ref ?unknown_pips2_shapes_a72fe8@@3PBXB=00a72fe8
// @ref ?unknown_talkbubl_shapes_a72fec@@3PBXB=00a72fec
// @ref ?unknown_pipbrd_owned_a72ff0@@3_NA=00a72ff0
// @ref ?unknown_pips_owned_a72ff1@@3_NA=00a72ff1
// @ref ?unknown_pips2_owned_a72ff2@@3_NA=00a72ff2
// @ref ?unknown_talkbubl_owned_a72ff3@@3_NA=00a72ff3

extern void const *unknown_pipbrd_shapes_a72fe0;
extern void const *unknown_pips_shapes_a72fe4;
extern void const *unknown_pips2_shapes_a72fe8;
extern void const *unknown_talkbubl_shapes_a72fec;
extern bool unknown_pipbrd_owned_a72ff0;
extern bool unknown_pips_owned_a72ff1;
extern bool unknown_pips2_owned_a72ff2;
extern bool unknown_talkbubl_owned_a72ff3;

void ObjectTypeClass::One_Time()
{
    if (unknown_pipbrd_shapes_a72fe0 == 0) {
        RawFileClass file("PIPBRD.SHP");
        unknown_pipbrd_shapes_a72fe0 = Load_Alloc_Data(file);
        unknown_pipbrd_owned_a72ff0 = unknown_pipbrd_shapes_a72fe0 != 0;
        if (unknown_pipbrd_shapes_a72fe0 == 0) {
            unknown_pipbrd_shapes_a72fe0 = MixFileClass::Retrieve("PIPBRD.SHP");
        }
    }
    if (unknown_pips_shapes_a72fe4 == 0) {
        RawFileClass file("PIPS.SHP");
        unknown_pips_shapes_a72fe4 = Load_Alloc_Data(file);
        unknown_pips_owned_a72ff1 = unknown_pips_shapes_a72fe4 != 0;
        if (unknown_pips_shapes_a72fe4 == 0) {
            unknown_pips_shapes_a72fe4 = MixFileClass::Retrieve("PIPS.SHP");
        }
    }
    if (unknown_pips2_shapes_a72fe8 == 0) {
        RawFileClass file("PIPS2.SHP");
        unknown_pips2_shapes_a72fe8 = Load_Alloc_Data(file);
        unknown_pips2_owned_a72ff2 = unknown_pips2_shapes_a72fe8 != 0;
        if (unknown_pips2_shapes_a72fe8 == 0) {
            unknown_pips2_shapes_a72fe8 = MixFileClass::Retrieve("PIPS2.SHP");
        }
    }
    if (unknown_talkbubl_shapes_a72fec == 0) {
        RawFileClass file("TALKBUBL.SHP");
        unknown_talkbubl_shapes_a72fec = Load_Alloc_Data(file);
        unknown_talkbubl_owned_a72ff3 = unknown_talkbubl_shapes_a72fec != 0;
        if (unknown_talkbubl_shapes_a72fec == 0) {
            unknown_talkbubl_shapes_a72fec = MixFileClass::Retrieve("TALKBUBL.SHP");
        }
    }
}

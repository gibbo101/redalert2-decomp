// Original initializer body: 0x00483B00..0x00485301; independently traced full CFG.
#include "shared/convert.hpp"
#include "shared/basic_depth_blitters.hpp"
#include "shared/basic_depth_warp_blitters.hpp"
#include "shared/basic_depth_write_blitters.hpp"
#include "shared/basic_lucent_blitters.hpp"
#include "shared/basic_rle_depth_blitters.hpp"
#include "shared/basic_rle_lucent_blitters.hpp"
#include "shared/basic_xlat_blitters.hpp"
#include "shared/byte_rle_blitters.hpp"
#include "shared/conditional_alpha_blitters.hpp"
#include "shared/destination_blitters.hpp"
#include "shared/translucent_write_alpha_blitter.hpp"
#include "shared/plain_xlat_alpha_blitter.hpp"
#include "shared/rle_active_alpha_depth.hpp"
#include "shared/rle_alpha_blend_depth.hpp"
#include "shared/rle_alpha_depth.hpp"
#include "shared/rle_blitter.hpp"
#include "shared/rle_byte_remaining.hpp"
#include "shared/rle_darken_depth.hpp"
#include "shared/rle_lucent_depth.hpp"
#include "shared/rle_remaining_writers.hpp"
#include "shared/rle_remap_depth.hpp"
#include "shared/trans_lucent_alpha_blitter.hpp"
#include "shared/trans_lucent_alpha_depth_blitter.hpp"
#include "shared/trans_lucent_alpha_warp_blitter.hpp"
#include "shared/trans_remap_xlat_alpha_blitter.hpp"
#include "shared/trans_remap_xlat_alpha_depth_blitter.hpp"
#include "shared/trans_xlat_alpha_blitter.hpp"
#include "shared/trans_xlat_alpha_depth_blitter.hpp"
#include "shared/trans_xlat_alpha_read_blitter.hpp"
#include "shared/xlat_alpha_blitter.hpp"
void ConvertClass::Initialize_Blitters_00483B00()
{
    if (BytesPerPixel == 1) {
        Blitters[0] = new BlitPlainXlat<unsigned char>((unsigned char const *)Table);
        Blitters[1] = new BlitTransXlat<unsigned char>((unsigned char const *)Table);
        Blitters[3] = new BlitTransZRemapXlat<unsigned char>((unsigned char const *const *)&ActiveRemap, (unsigned char const *)Table);
        Blitters[2] = new BlitTransRemapDest<unsigned char>((unsigned char const *)Remap);
        Blitters[4] = new BlitTransRemapXlat<unsigned char>((unsigned char const *)Remap, (unsigned char const *)Table);
        Blitters[5] = new BlitTransRemapXlat<unsigned char>((unsigned char const *)Remap, (unsigned char const *)Table);
        Blitters[6] = new BlitTransRemapXlat<unsigned char>((unsigned char const *)Remap, (unsigned char const *)Table);
        RLEBlitters[0] = new RLEBlitTransXlat<unsigned char>((unsigned char const *)Table);
        RLEBlitters[2] = new RLEBlitTransZRemapXlat<unsigned char>((unsigned char const *const *)&ActiveRemap, (unsigned char const *)Table);
        RLEBlitters[1] = new RLEBlitTransRemapDest<unsigned char>((unsigned char const *)Remap);
        RLEBlitters[3] = new RLEBlitTransRemapXlat<unsigned char>((unsigned char const *)Remap, (unsigned char const *)Table);
        RLEBlitters[4] = new RLEBlitTransRemapXlat<unsigned char>((unsigned char const *)Remap, (unsigned char const *)Table);
        RLEBlitters[5] = new RLEBlitTransRemapXlat<unsigned char>((unsigned char const *)Remap, (unsigned char const *)Table);
        RLEBlitters[6] = new RLEBlitTransXlatZRead<unsigned char>((unsigned char const *)Table);
        RLEBlitters[7] = new RLEBlitTransZRemapXlatZRead<unsigned char>((unsigned char const *const *)&ActiveRemap, (unsigned char const *)Table);
        RLEBlitters[8] = new RLEBlitTransRemapDestZRead<unsigned char>((unsigned char const *)Remap);
        RLEBlitters[9] = new RLEBlitTransRemapXlatZRead<unsigned char>((unsigned char const *)Remap, (unsigned char const *)Table);
        RLEBlitters[10] = new RLEBlitTransRemapXlatZRead<unsigned char>((unsigned char const *)Remap, (unsigned char const *)Table);
        RLEBlitters[11] = new RLEBlitTransRemapXlatZRead<unsigned char>((unsigned char const *)Remap, (unsigned char const *)Table);
        RLEBlitters[15] = new RLEBlitTransXlatZReadWrite<unsigned char>((unsigned char const *)Table);
        RLEBlitters[16] = new RLEBlitTransZRemapXlatZReadWrite<unsigned char>((unsigned char const *const *)&ActiveRemap, (unsigned char const *)Table);
        RLEBlitters[17] = new RLEBlitTransRemapDestZReadWrite<unsigned char>((unsigned char const *)Remap);
        RLEBlitters[18] = new RLEBlitTransRemapXlatZReadWrite<unsigned char>((unsigned char const *)Remap, (unsigned char const *)Table);
        RLEBlitters[19] = new RLEBlitTransRemapXlatZReadWrite<unsigned char>((unsigned char const *)Remap, (unsigned char const *)Table);
        RLEBlitters[20] = new RLEBlitTransRemapXlatZReadWrite<unsigned char>((unsigned char const *)Remap, (unsigned char const *)Table);
    } else {
        Blitters[0] = new BlitPlainXlat<unsigned short>((unsigned short const *)Table);
        Blitters[1] = new BlitTransXlat<unsigned short>((unsigned short const *)Table);
        Blitters[3] = new BlitTransZRemapXlat<unsigned short>((unsigned char const *const *)&ActiveRemap, (unsigned short const *)Table);
        Blitters[2] = new BlitTransDarken<unsigned short>(HalfMask);
        Blitters[4] = new BlitTransLucent75<unsigned short>((unsigned short const *)Table, QuarterMask);
        Blitters[5] = new BlitTransLucent50<unsigned short>((unsigned short const *)Table, HalfMask);
        Blitters[6] = new BlitTransLucent25<unsigned short>((unsigned short const *)Table, QuarterMask);
        Blitters[7] = new BlitPlainXlatZRead<unsigned short>((unsigned short const *)Table);
        Blitters[8] = new BlitTransXlatZRead<unsigned short>((unsigned short const *)Table);
        Blitters[10] = new BlitTransZRemapXlatZRead<unsigned short>((unsigned char const *const *)&ActiveRemap, (unsigned short const *)Table);
        Blitters[9] = new BlitTransDarkenZRead<unsigned short>(HalfMask);
        Blitters[11] = new BlitTransLucent75ZRead<unsigned short>((unsigned short const *)Table, QuarterMask);
        Blitters[12] = new BlitTransLucent50ZRead<unsigned short>((unsigned short const *)Table, HalfMask);
        Blitters[13] = new BlitTransLucent25ZRead<unsigned short>((unsigned short const *)Table, QuarterMask);
        Blitters[14] = new BlitTransLucent75ZReadWarp<unsigned short>((unsigned short const *)Table, QuarterMask);
        Blitters[15] = new BlitTransLucent50ZReadWarp<unsigned short>((unsigned short const *)Table, HalfMask);
        Blitters[16] = new BlitTransLucent25ZReadWarp<unsigned short>((unsigned short const *)Table, QuarterMask);
        Blitters[17] = new BlitPlainXlatZReadWrite<unsigned short>((unsigned short const *)Table);
        Blitters[18] = new BlitTransXlatZReadWrite<unsigned short>((unsigned short const *)Table);
        Blitters[20] = new BlitTransZRemapXlatZReadWrite<unsigned short>((unsigned char const *const *)&ActiveRemap, (unsigned short const *)Table);
        Blitters[19] = new BlitTransDarkenZReadWrite<unsigned short>(HalfMask);
        Blitters[21] = new BlitTransLucent75ZReadWrite<unsigned short>((unsigned short const *)Table, QuarterMask);
        Blitters[22] = new BlitTransLucent50ZReadWrite<unsigned short>((unsigned short const *)Table, HalfMask);
        Blitters[23] = new BlitTransLucent25ZReadWrite<unsigned short>((unsigned short const *)Table, QuarterMask);
        Blitters[24] = new BlitPlainXlatAlpha<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count);
        Blitters[25] = new BlitTransXlatAlpha<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count);
        Blitters[26] = new BlitTransZRemapXlatAlpha<unsigned short>((unsigned char const *const *)&ActiveRemap, (unsigned short const *)AlphaPalette, unknown_shadow_count);
        Blitters[27] = new BlitTransLucent75Alpha<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, QuarterMask);
        Blitters[28] = new BlitTransLucent50Alpha<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, HalfMask);
        Blitters[29] = new BlitTransLucent25Alpha<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, QuarterMask);
        Blitters[30] = new BlitTransXlatWriteAlpha<unsigned short>();
        Blitters[31] = new BlitTransXlatMultWriteAlpha<unsigned short>();
        Blitters[32] = new BlitTranslucentWriteAlpha<unsigned short>((unsigned short const *)AlphaPalette);
        Blitters[33] = new BlitTranslucent50NonzeroAlpha<unsigned short>((unsigned short const *)Table, HalfMask);
        Blitters[34] = new BlitTranslucent50ZeroAlpha<unsigned short>((unsigned short const *)Table, HalfMask);
        Blitters[35] = new BlitPlainXlatAlpha<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count);
        Blitters[36] = new BlitTransXlatAlphaZRead<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count);
        Blitters[37] = new BlitTransZRemapXlatAlphaZRead<unsigned short>((unsigned char const *const *)&ActiveRemap, (unsigned short const *)AlphaPalette, unknown_shadow_count);
        Blitters[38] = new BlitTransLucent75AlphaZRead<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, QuarterMask);
        Blitters[39] = new BlitTransLucent50AlphaZRead<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, HalfMask);
        Blitters[40] = new BlitTransLucent25AlphaZRead<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, QuarterMask);
        Blitters[41] = new BlitTransLucent75AlphaZReadWarp<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, QuarterMask);
        Blitters[42] = new BlitTransLucent50AlphaZReadWarp<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, HalfMask);
        Blitters[43] = new BlitTransLucent25AlphaZReadWarp<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, QuarterMask);
        Blitters[44] = new BlitPlainXlatAlpha<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count);
        Blitters[45] = new BlitTransXlatAlphaZReadWrite<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count);
        Blitters[46] = new BlitTransZRemapXlatAlphaZReadWrite<unsigned short>((unsigned char const *const *)&ActiveRemap, (unsigned short const *)AlphaPalette, unknown_shadow_count);
        Blitters[47] = new BlitTransLucent75AlphaZReadWrite<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, QuarterMask);
        Blitters[48] = new BlitTransLucent50AlphaZReadWrite<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, HalfMask);
        Blitters[49] = new BlitTransLucent25AlphaZReadWrite<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, QuarterMask);
        RLEBlitters[0] = new RLEBlitTransXlat<unsigned short>((unsigned short const *)Table);
        RLEBlitters[2] = new RLEBlitTransZRemapXlat<unsigned short>((unsigned char const *const *)&ActiveRemap, (unsigned short const *)Table);
        RLEBlitters[1] = new RLEBlitTransDarken<unsigned short>(HalfMask);
        RLEBlitters[3] = new RLEBlitTransLucent75<unsigned short>((unsigned short const *)Table, QuarterMask);
        RLEBlitters[4] = new RLEBlitTransLucent50<unsigned short>((unsigned short const *)Table, HalfMask);
        RLEBlitters[5] = new RLEBlitTransLucent25<unsigned short>((unsigned short const *)Table, QuarterMask);
        RLEBlitters[6] = new RLEBlitTransXlatZRead<unsigned short>((unsigned short const *)Table);
        RLEBlitters[7] = new RLEBlitTransZRemapXlatZRead<unsigned short>((unsigned char const *const *)&ActiveRemap, (unsigned short const *)Table);
        RLEBlitters[8] = new RLEBlitTransDarkenZRead<unsigned short>(HalfMask);
        RLEBlitters[9] = new RLEBlitTransLucent75ZRead<unsigned short>((unsigned short const *)Table, QuarterMask);
        RLEBlitters[10] = new RLEBlitTransLucent50ZRead<unsigned short>((unsigned short const *)Table, HalfMask);
        RLEBlitters[11] = new RLEBlitTransLucent25ZRead<unsigned short>((unsigned short const *)Table, QuarterMask);
        RLEBlitters[12] = new RLEBlitTransLucent75ZReadWarp<unsigned short>((unsigned short const *)Table, QuarterMask);
        RLEBlitters[13] = new RLEBlitTransLucent50ZReadWarp<unsigned short>((unsigned short const *)Table, HalfMask);
        RLEBlitters[14] = new RLEBlitTransLucent25ZReadWarp<unsigned short>((unsigned short const *)Table, QuarterMask);
        RLEBlitters[15] = new RLEBlitTransXlatZReadWrite<unsigned short>((unsigned short const *)Table);
        RLEBlitters[16] = new RLEBlitTransZRemapXlatZReadWrite<unsigned short>((unsigned char const *const *)&ActiveRemap, (unsigned short const *)Table);
        RLEBlitters[17] = new RLEBlitTransDarkenZReadWrite<unsigned short>(HalfMask);
        RLEBlitters[18] = new RLEBlitTransLucent75ZReadWrite<unsigned short>((unsigned short const *)Table, QuarterMask);
        RLEBlitters[19] = new RLEBlitTransLucent50ZReadWrite<unsigned short>((unsigned short const *)Table, HalfMask);
        RLEBlitters[20] = new RLEBlitTransLucent25ZReadWrite<unsigned short>((unsigned short const *)Table, QuarterMask);
        RLEBlitters[21] = new RLEBlitTransXlatAlpha<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count);
        RLEBlitters[22] = new RLEBlitTransZRemapXlatAlpha<unsigned short>((unsigned char const *const *)&ActiveRemap, (unsigned short const *)AlphaPalette, unknown_shadow_count);
        RLEBlitters[23] = new RLEBlitTransLucent75Alpha<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, QuarterMask);
        RLEBlitters[24] = new RLEBlitTransLucent50Alpha<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, HalfMask);
        RLEBlitters[25] = new RLEBlitTransLucent25Alpha<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, QuarterMask);
        RLEBlitters[26] = new RLEBlitTransXlatAlphaZRead<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count);
        RLEBlitters[27] = new RLEBlitTransZRemapXlatAlphaZRead<unsigned short>((unsigned char const *const *)&ActiveRemap, (unsigned short const *)AlphaPalette, unknown_shadow_count);
        RLEBlitters[28] = new RLEBlitTransLucent75AlphaZRead<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, QuarterMask);
        RLEBlitters[29] = new RLEBlitTransLucent50AlphaZRead<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, HalfMask);
        RLEBlitters[30] = new RLEBlitTransLucent25AlphaZRead<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, QuarterMask);
        RLEBlitters[31] = new RLEBlitTransLucent75AlphaZReadWarp<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, QuarterMask);
        RLEBlitters[32] = new RLEBlitTransLucent50AlphaZReadWarp<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, HalfMask);
        RLEBlitters[33] = new RLEBlitTransLucent25AlphaZReadWarp<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, QuarterMask);
        RLEBlitters[34] = new RLEBlitTransXlatAlphaZReadWrite<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count);
        RLEBlitters[35] = new RLEBlitTransZRemapXlatAlphaZReadWrite<unsigned short>((unsigned char const *const *)&ActiveRemap, (unsigned short const *)AlphaPalette, unknown_shadow_count);
        RLEBlitters[36] = new RLEBlitTransLucent75AlphaZReadWrite<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, QuarterMask);
        RLEBlitters[37] = new RLEBlitTransLucent50AlphaZReadWrite<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, HalfMask);
        RLEBlitters[38] = new RLEBlitTransLucent25AlphaZReadWrite<unsigned short>((unsigned short const *)AlphaPalette, unknown_shadow_count, QuarterMask);
    }
}

// void RadarClass::Unknown_006324A0() (0x006324A0)
// TibSun's Render_Tracked_Objects: clears the pixel flags, then plots each
// tracked object once per pixel in its house's bright colour (slot 48 objects
// in the colour of the slot 51 house, LightGrey without one).
#include "shared/radar.hpp"
#include "shared/techno.hpp"
#include "shared/house.hpp"
#include "shared/color_scheme.hpp"
#include "shared/convert.hpp"
#include "shared/progress_screen.hpp"
#include "shared/crt_string.hpp"
// @ref ??_C@_09LBMK@LightGrey?$AA@=007ebfc4

void RadarClass::Unknown_006324A0()
{
    memset(unknown_1270, 0, unknown_1218->Get_Width() * unknown_1218->Get_Height() / 8 + 1);
    for (int b = 0; b < 256; b++) {
        DynamicVectorClass<HashObject<RadarTrackingStruct, TechnoClass *> > &bucket = unknown_1254->Buckets[b];
        int count = bucket.Count();
        HashObject<RadarTrackingStruct, TechnoClass *> *ptr = &bucket[0];
        for (int t = 0; t < count; t++) {
            RadarTrackingStruct *track = &ptr[t].Key;
            TechnoClass *tech = track->unknown_00;
            int id = track->unknown_04.X + track->unknown_04.Y * unknown_1218->Get_Width();
            int i = id >> 3;
            int bit = 1 << (id & 7);
            if ((unknown_1270[i] & bit) == 0) {
                unknown_1270[i] |= bit;
                ColorScheme *scheme = ColorSchemes[tech->House->ColorSchemeIndex];
                if (tech->unknown_slot48()) {
                    if (tech->unknown_slot51(false) != 0) {
                        scheme = ColorSchemes[tech->unknown_slot51(false)->ColorSchemeIndex];
                    } else {
                        scheme = unknown_color_scheme_663d30("LightGrey", 1);
                    }
                }
                int color = scheme->Converter->Convert(scheme->unknown_color_0x330);
                unknown_1218->Put_Pixel(track->unknown_04, color);
            }
        }
    }
}

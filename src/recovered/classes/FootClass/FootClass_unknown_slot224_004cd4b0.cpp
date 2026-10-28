// bool FootClass::unknown_slot224(int source) (0x004CD4B0)
// The unit is destroyed: with strength left the tag hears events 0x26 and
// 0x29 and slot 55 runs; then mission 3 (slot 149), slot 210, TechnoClass
// 0x006D3040, random spin rates (+0x288, +0x28C) for non-infantry, and the
// object leaves the scenario lists (0x006ECB90). False when slot 108 is 0.
#include "shared/foot.hpp"
#include "shared/tag.hpp"
// @ref ?Spring@TagClass@@QAE_NHPAVObjectClass@@VCell@@_NH@Z=006b3df0
// @ref ?unknown_6d3040@TechnoClass@@QAEXPAV1@@Z=006d3040
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref __real@8@3fe08000000200000000=0079c280
// @ref __real@8@3ffc9999999999999800=007a17f0
// @ref __real@8@3ffbccccccccccccd000=0079c570

bool FootClass::unknown_slot224(int source)
{
    if (unknown_slot108() > 0) {
        if (Strength > 0) {
            if (source != 0 && unknown_34 != 0) {
                unknown_34->Spring(0x26, this, unknown_geometry_k, 0, 0);
            }
            if (unknown_34 != 0 && unknown_7d) {
                unknown_34->Spring(0x29, this, unknown_geometry_k, 0, 0);
            }
            if (unknown_34 != 0 && unknown_7d && source != 0) {
                unknown_34->Spring(0x29, this, unknown_geometry_k, 0, source);
            }
            if (!unknown_7d) {
                return true;
            }
            unknown_slot55((TechnoClass *)source);
            if (!unknown_7d) {
                return true;
            }
            Strength = 0;
        }
        unknown_37d = true;
        unknown_slot149(3);
        unknown_slot210();
        unknown_6d3040((TechnoClass *)source);
        if (Kind_Of() != 15 && unknown_a40774 == 0) {
            double spin = unknown_id_source_a3d290->Random()(0, 0x7FFFFFFE);
            spin *= 1.0 / 2147483646.0;
            spin *= 0.15;
            unknown_288 = (float)(spin + 0.1);
            if (unknown_id_source_a3d290->Random()(0, 1) == 0) {
                unknown_288 = -unknown_288;
            }
            double tilt = unknown_id_source_a3d290->Random()(0, 0x7FFFFFFE);
            tilt *= 1.0 / 2147483646.0;
            unknown_28c = (float)(tilt * 0.1);
        }
        Unknown_006ECB90(this, false);
        return true;
    }
    return false;
}

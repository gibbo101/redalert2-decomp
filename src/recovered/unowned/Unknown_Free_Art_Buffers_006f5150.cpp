// void Unknown_006F5150() (0x006F5150)
// Frees the 16 buffers (0x00AC0FF8, 0x00AC10C4, ...) that the loader
// 0x006F4C90's owners flagged (flags 0x00AC1236..0x00AC1245) and clears
// every pointer. Called from 4 sites.
#include "shared/string_table.hpp"
// @ref ?unknown_owned_ac1236@@3_NA=00ac1236
// @ref ?unknown_buffer_ac0ff8@@3PAXA=00ac0ff8
// @ref ?unknown_owned_ac1237@@3_NA=00ac1237
// @ref ?unknown_buffer_ac10c4@@3PAXA=00ac10c4
// @ref ?unknown_owned_ac1238@@3_NA=00ac1238
// @ref ?unknown_buffer_ac10bc@@3PAXA=00ac10bc
// @ref ?unknown_owned_ac1239@@3_NA=00ac1239
// @ref ?unknown_buffer_ac105c@@3PAXA=00ac105c
// @ref ?unknown_owned_ac123a@@3_NA=00ac123a
// @ref ?unknown_buffer_ac10f8@@3PAXA=00ac10f8
// @ref ?unknown_owned_ac123b@@3_NA=00ac123b
// @ref ?unknown_buffer_ac0ff0@@3PAXA=00ac0ff0
// @ref ?unknown_owned_ac123c@@3_NA=00ac123c
// @ref ?unknown_buffer_ac1070@@3PAXA=00ac1070
// @ref ?unknown_owned_ac123d@@3_NA=00ac123d
// @ref ?unknown_buffer_ac1078@@3PAXA=00ac1078
// @ref ?unknown_owned_ac123e@@3_NA=00ac123e
// @ref ?unknown_buffer_ac10ec@@3PAXA=00ac10ec
// @ref ?unknown_owned_ac123f@@3_NA=00ac123f
// @ref ?unknown_buffer_ac100c@@3PAXA=00ac100c
// @ref ?unknown_owned_ac1240@@3_NA=00ac1240
// @ref ?unknown_buffer_ac1094@@3PAXA=00ac1094
// @ref ?unknown_owned_ac1241@@3_NA=00ac1241
// @ref ?unknown_buffer_ac1058@@3PAXA=00ac1058
// @ref ?unknown_owned_ac1242@@3_NA=00ac1242
// @ref ?unknown_buffer_ac1048@@3PAXA=00ac1048
// @ref ?unknown_owned_ac1243@@3_NA=00ac1243
// @ref ?unknown_buffer_ac1098@@3PAXA=00ac1098
// @ref ?unknown_owned_ac1244@@3_NA=00ac1244
// @ref ?unknown_buffer_ac10a4@@3PAXA=00ac10a4
// @ref ?unknown_owned_ac1245@@3_NA=00ac1245
// @ref ?unknown_buffer_ac10b0@@3PAXA=00ac10b0
// @ref ??3@YAXPAX@Z=00781d3b

extern bool unknown_owned_ac1236;
extern void *unknown_buffer_ac0ff8;
extern bool unknown_owned_ac1237;
extern void *unknown_buffer_ac10c4;
extern bool unknown_owned_ac1238;
extern void *unknown_buffer_ac10bc;
extern bool unknown_owned_ac1239;
extern void *unknown_buffer_ac105c;
extern bool unknown_owned_ac123a;
extern void *unknown_buffer_ac10f8;
extern bool unknown_owned_ac123b;
extern void *unknown_buffer_ac0ff0;
extern bool unknown_owned_ac123c;
extern void *unknown_buffer_ac1070;
extern bool unknown_owned_ac123d;
extern void *unknown_buffer_ac1078;
extern bool unknown_owned_ac123e;
extern void *unknown_buffer_ac10ec;
extern bool unknown_owned_ac123f;
extern void *unknown_buffer_ac100c;
extern bool unknown_owned_ac1240;
extern void *unknown_buffer_ac1094;
extern bool unknown_owned_ac1241;
extern void *unknown_buffer_ac1058;
extern bool unknown_owned_ac1242;
extern void *unknown_buffer_ac1048;
extern bool unknown_owned_ac1243;
extern void *unknown_buffer_ac1098;
extern bool unknown_owned_ac1244;
extern void *unknown_buffer_ac10a4;
extern bool unknown_owned_ac1245;
extern void *unknown_buffer_ac10b0;

void __fastcall Unknown_006F5150()
{
    if (unknown_owned_ac1236) {
        delete unknown_buffer_ac0ff8;
        unknown_owned_ac1236 = false;
    }
    unknown_buffer_ac0ff8 = 0;
    if (unknown_owned_ac1237) {
        delete unknown_buffer_ac10c4;
        unknown_owned_ac1237 = false;
    }
    unknown_buffer_ac10c4 = 0;
    if (unknown_owned_ac1238) {
        delete unknown_buffer_ac10bc;
        unknown_owned_ac1238 = false;
    }
    unknown_buffer_ac10bc = 0;
    if (unknown_owned_ac1239) {
        delete unknown_buffer_ac105c;
        unknown_owned_ac1239 = false;
    }
    unknown_buffer_ac105c = 0;
    if (unknown_owned_ac123a) {
        delete unknown_buffer_ac10f8;
        unknown_owned_ac123a = false;
    }
    unknown_buffer_ac10f8 = 0;
    if (unknown_owned_ac123b) {
        delete unknown_buffer_ac0ff0;
        unknown_owned_ac123b = false;
    }
    unknown_buffer_ac0ff0 = 0;
    if (unknown_owned_ac123c) {
        delete unknown_buffer_ac1070;
        unknown_owned_ac123c = false;
    }
    unknown_buffer_ac1070 = 0;
    if (unknown_owned_ac123d) {
        delete unknown_buffer_ac1078;
        unknown_owned_ac123d = false;
    }
    unknown_buffer_ac1078 = 0;
    if (unknown_owned_ac123e) {
        delete unknown_buffer_ac10ec;
        unknown_owned_ac123e = false;
    }
    unknown_buffer_ac10ec = 0;
    if (unknown_owned_ac123f) {
        delete unknown_buffer_ac100c;
        unknown_owned_ac123f = false;
    }
    unknown_buffer_ac100c = 0;
    if (unknown_owned_ac1240) {
        delete unknown_buffer_ac1094;
        unknown_owned_ac1240 = false;
    }
    unknown_buffer_ac1094 = 0;
    if (unknown_owned_ac1241) {
        delete unknown_buffer_ac1058;
        unknown_owned_ac1241 = false;
    }
    unknown_buffer_ac1058 = 0;
    if (unknown_owned_ac1242) {
        delete unknown_buffer_ac1048;
        unknown_owned_ac1242 = false;
    }
    unknown_buffer_ac1048 = 0;
    if (unknown_owned_ac1243) {
        delete unknown_buffer_ac1098;
        unknown_owned_ac1243 = false;
    }
    unknown_buffer_ac1098 = 0;
    if (unknown_owned_ac1244) {
        delete unknown_buffer_ac10a4;
        unknown_owned_ac1244 = false;
    }
    unknown_buffer_ac10a4 = 0;
    if (unknown_owned_ac1245) {
        delete unknown_buffer_ac10b0;
        unknown_owned_ac1245 = false;
    }
    unknown_buffer_ac10b0 = 0;
}

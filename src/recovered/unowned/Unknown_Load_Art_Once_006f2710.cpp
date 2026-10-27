// void __fastcall Unknown_Load_Art_Once_006F2710(int alternate) -- 0x006F2710
// Once (flag 0x00AC1168): loads the flagged buffers and the art pair, choosing the pair by the argument (hypothesis).
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_load_art_6f1fa0@@YIXPBDPAPAX1@Z=006f1fa0
// @ref ?Unknown_00495270@@YIPAXPBDPA_N@Z=00495270
// @ref ?Unknown_Load_Art_Flagged_006F2840@@YIXH@Z=006f2840
// @ref ?unknown_flag_ac1168@@3_NA=00ac1168
// @ref ?unknown_art_ac1160@@3PAXA=00ac1160
// @ref ?unknown_art_ac1164@@3PAVUnknownArtData_006f2390@@A=00ac1164
// @ref ?unknown_name_7f8708@@3QBDB=007f8708
// @ref ?unknown_name_7f870c@@3QBDB=007f870c

class UnknownArtData_006f2390 {
public:
    virtual ~UnknownArtData_006f2390();
};
void __fastcall unknown_load_art_6f1fa0(char const *name, void **shape, void **data);   // 0x006F1FA0
void *__fastcall Unknown_00495270(char const *name, bool *allocated);
void __fastcall Unknown_Load_Art_Flagged_006F2840(int alternate);
extern bool unknown_flag_ac1168;
extern char const * const unknown_name_7f8708;
extern char const * const unknown_name_7f870c;
extern void *unknown_art_ac1160;
extern UnknownArtData_006f2390 *unknown_art_ac1164;

void __fastcall Unknown_Load_Art_Once_006F2710(int alternate)
{
    if (!unknown_flag_ac1168) {
        Unknown_Load_Art_Flagged_006F2840(alternate);
        char const *name = unknown_name_7f8708;
        if (alternate) {
            name = unknown_name_7f870c;
        }
        unknown_load_art_6f1fa0(name, &unknown_art_ac1160, (void **)&unknown_art_ac1164);
        unknown_flag_ac1168 = true;
    }
}

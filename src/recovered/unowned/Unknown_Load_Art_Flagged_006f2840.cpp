// void __fastcall Unknown_Load_Art_Flagged_006F2840(int alternate) -- 0x006F2840
// Loads three flagged buffers, chosen by the argument and by the screen width (640 selects the first of each pair; hypothesis).
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_load_art_6f1fa0@@YIXUUnknownArtOut@@PBDPAPAX@Z=006f1fa0
// @ref ?Unknown_00495270@@YIPAXPBDPA_N@Z=00495270
// @ref ?Unknown_Load_Art_Flagged_006F2840@@YIXH@Z=006f2840
// @ref ?unknown_value_8523e0@@3HA=008523e0
// @ref ?unknown_flag_ac1214@@3_NA=00ac1214
// @ref ?unknown_flag_ac1215@@3_NA=00ac1215
// @ref ?unknown_flag_ac1216@@3_NA=00ac1216
// @ref ?unknown_art_ac110c@@3PAXA=00ac110c
// @ref ?unknown_art_ac10f0@@3PAXA=00ac10f0
// @ref ?unknown_art_ac1108@@3PAXA=00ac1108
// @ref ?unknown_name_7f8750@@3QBDB=007f8750
// @ref ?unknown_name_7f8754@@3QBDB=007f8754
// @ref ?unknown_name_7f8758@@3QBDB=007f8758
// @ref ?unknown_name_7f875c@@3QBDB=007f875c
// @ref ?unknown_name_7f8760@@3QBDB=007f8760
// @ref ?unknown_name_7f8764@@3QBDB=007f8764
// @ref ?unknown_name_7f8768@@3QBDB=007f8768
// @ref ?unknown_name_7f876c@@3QBDB=007f876c
// @ref ?unknown_name_7f8770@@3QBDB=007f8770
// @ref ?unknown_name_7f8774@@3QBDB=007f8774
// @ref ?unknown_name_7f8778@@3QBDB=007f8778
// @ref ?unknown_name_7f877c@@3QBDB=007f877c

class UnknownArtData_006f2390 {
public:
    virtual ~UnknownArtData_006f2390();
};
struct UnknownArtOut {
    UnknownArtOut(void **pointer) : Pointer(pointer) {}
    void **Pointer;
};
void __fastcall unknown_load_art_6f1fa0(UnknownArtOut data, char const *name, void **shape);
void *__fastcall Unknown_00495270(char const *name, bool *allocated);
extern int unknown_value_8523e0;
extern bool unknown_flag_ac1214;
extern bool unknown_flag_ac1215;
extern bool unknown_flag_ac1216;
extern void *unknown_art_ac110c;
extern void *unknown_art_ac10f0;
extern void *unknown_art_ac1108;
extern char const * const unknown_name_7f8750;
extern char const * const unknown_name_7f8754;
extern char const * const unknown_name_7f8758;
extern char const * const unknown_name_7f875c;
extern char const * const unknown_name_7f8760;
extern char const * const unknown_name_7f8764;
extern char const * const unknown_name_7f8768;
extern char const * const unknown_name_7f876c;
extern char const * const unknown_name_7f8770;
extern char const * const unknown_name_7f8774;
extern char const * const unknown_name_7f8778;
extern char const * const unknown_name_7f877c;

void __fastcall Unknown_Load_Art_Flagged_006F2840(int alternate)
{
    if (!alternate) {
        if (unknown_value_8523e0 == 0x280) {
            unknown_art_ac110c = Unknown_00495270(unknown_name_7f8750, &unknown_flag_ac1214);
            unknown_art_ac10f0 = Unknown_00495270(unknown_name_7f8758, &unknown_flag_ac1215);
            unknown_art_ac1108 = Unknown_00495270(unknown_name_7f8760, &unknown_flag_ac1216);
        } else {
            unknown_art_ac110c = Unknown_00495270(unknown_name_7f8754, &unknown_flag_ac1214);
            unknown_art_ac10f0 = Unknown_00495270(unknown_name_7f875c, &unknown_flag_ac1215);
            unknown_art_ac1108 = Unknown_00495270(unknown_name_7f8764, &unknown_flag_ac1216);
        }
    } else {
        if (unknown_value_8523e0 == 0x280) {
            unknown_art_ac110c = Unknown_00495270(unknown_name_7f8768, &unknown_flag_ac1214);
            unknown_art_ac10f0 = Unknown_00495270(unknown_name_7f8770, &unknown_flag_ac1215);
            unknown_art_ac1108 = Unknown_00495270(unknown_name_7f8778, &unknown_flag_ac1216);
        } else {
            unknown_art_ac110c = Unknown_00495270(unknown_name_7f876c, &unknown_flag_ac1214);
            unknown_art_ac10f0 = Unknown_00495270(unknown_name_7f8774, &unknown_flag_ac1215);
            unknown_art_ac1108 = Unknown_00495270(unknown_name_7f877c, &unknown_flag_ac1216);
        }
    }
}

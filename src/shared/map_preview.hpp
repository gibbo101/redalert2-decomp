// The scenario's map preview (unit 0x0061D240; its header statics start there):
// a pointer-sized object made by 0x0061D430 and freed by 0x0061D440, filled
// from the map by 0x0061D660 and written as the [Preview]/[PreviewPack]
// sections by 0x0061DC80 (Write_Scenario_INI). Names are hypotheses.
#ifndef RA2_SHARED_MAP_PREVIEW_HPP
#define RA2_SHARED_MAP_PREVIEW_HPP

class CCINIClass;
typedef struct HWND__ *HWND;
class UnknownPreview_0061D430 {
public:
    UnknownPreview_0061D430();                      // 0x0061D430 (clears the pointer)
    ~UnknownPreview_0061D430();                     // 0x0061D440 (deletes the object it holds)
    void Unknown_0061D660();                        // 0x0061D660 (renders the preview from the map)
    void Write_INI_0061DC80(CCINIClass &ini);       // 0x0061DC80
    void Draw_0061D460(HWND window);                // 0x0061D460 (paints the preview into the dialog)
    bool Is_Present() const { return unknown_00 != 0; }   // inline (Write_Scenario_INI)

    void *unknown_00;                               // +0x00 the preview surface (hypothesis)
};
// The loaded scenario's preview (0x00A6FEE4).
extern UnknownPreview_0061D430 *unknown_preview_a6fee4;
// The map preview the skirmish and multiplayer setup dialogs draw (0x00A72CE8).
extern UnknownPreview_0061D430 *unknown_dialog_preview_a72ce8;

#endif

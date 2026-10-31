// SidebarClass: the sidebar layer of the screen chain (Sidebar.CPP, from the
// header statics at 0x0067B2C0; RTTI vtable 0x007AB408, 55 slots), derived
// from PowerClass, with its nested gadgets SBGadgetClass (vtable 0x007AB2F4)
// and StripClass::SelectClass (vtable 0x007AB37C).
//
// Evidenced: the unit's static members and their guarded initializers
// (0x0067B4B0-0x0067B6DF), the constructor 0x0067B700 (four 0xE64-byte strips
// at +0x1540, the flags at +0x4ED8..+0x4EE6). Names are TS/RA1 hypotheses
// or unknown_.
#ifndef RA2_SHARED_SIDEBAR_HPP
#define RA2_SHARED_SIDEBAR_HPP
#include "shared/unknown_globals.hpp"
#include "shared/vox_class.hpp"
#ifdef RA2_SHARED_MAP_VIEW_HPP
#error "shared/map_view.hpp declares light screen layers: include the full layer headers before it"
#endif

#include "shared/stage.hpp"
#include "shared/power.hpp"
#include "shared/abstract.hpp"

// Shape file retrieval by name: MixFileClass<CCFileClass>::Retrieve, shared/mix_file_class.hpp.
// Unidentified input flag (0x00A40D44; shared/keyboard.hpp, shared/scroll.hpp).

// More of the sidebar geometry (0x00839628/0x0083962C: width and height;
// 0x00839630/0x00839638: the tactical area's X and width;
// 0x00ABCD48..0x00ABCD74: control X positions).
extern int unknown_int_83962c;
// The sidebar rectangle the origin and height belong to (0x00839620; hypothesis).
extern Rect unknown_rect_839620;
extern int unknown_abcd48;
// The screen size (0x007ADD80 width, 0x007ADD84 height; hypothesis) and the
// rest of the sidebar/tactical rectangles (0x00839628 sidebar width,
// 0x00839634 tactical Y, 0x0083963C tactical height).
extern int unknown_int_7add84;
extern int unknown_int_839628;
extern int unknown_int_83963c;
extern int unknown_abcd78;
extern int unknown_abcd7c;
extern int unknown_abcd80;
extern int unknown_abcd4c;
extern int unknown_abcd50;
extern int unknown_abcd58;
extern int unknown_abcd5c;
// The shape drawer the sidebar buttons draw with (0x008323CC).
extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);   // 0x007820F4
// The current game palette (0x006F45E0 returns the pointer at 0x00AC11A0).
PaletteClass *Unknown_006F45E0();
extern int unknown_abcd54;
extern int unknown_abcd60;
extern int unknown_abcd64;
extern int unknown_abcd74;
// A buildable's kind for type 7 (0x004EB550).
int __fastcall Unknown_004EB550(int type, int id);
// The production column of an object type (0x006818D0; callers in HouseClass and TActionClass; name hypothesis): 2 for
// types 0xF and 0x10, 3 for 1, 2, 3 and 0x28, 1 for 0x1F, 0x20 and 0x39, whether the kind is 5 for 6 and 7, else -1.
int __fastcall Unknown_006818D0(int type, int id, int arg3);

class TechnoClass;
class TechnoTypeClass;
// The player's house as the sidebar uses it (a view of HouseClass).
class UnknownSidebarHouse {
public:
    bool Unknown_004F4F30(TechnoTypeClass *type);       // 0x004F4F30 (can build the type; hypothesis)
};
// A building's type flag at +0x1365 (views of BuildingClass +0x418 Type).
struct UnknownSidebarBuildingType {
    char unknown_0000[0x1365];
    bool unknown_1365;                                  // +0x1365
};
struct UnknownSidebarBuilding {
    char unknown_000[0x418];
    UnknownSidebarBuildingType *Type;                   // +0x418
};

// The sidebar's shapes (0x00ABCD20) and which were allocated (0x00ABCD40).
extern void const *unknown_shapes_abcd20[8];
extern bool unknown_shapes_allocated_abcd40[8];

class ObjectTypeClass;
// A buildable's type by kind and index (0x00482C00).
ObjectTypeClass *__fastcall Unknown_00482C00(int kind, int id);
// Help-text state: tooltips on (0x00A40958), cost-only format (0x008373C0)
// and the text buffer (0x00AB9484).
extern bool unknown_flag_8373c0;
// Prints a cameo caption in the "DarkRed" scheme when captions are on (0x00682140).
void __fastcall Unknown_00682140(wchar_t const *text, Point2D const &point, Rect const &window, int width);
extern wchar_t unknown_text_ab9484[];
extern "C" unsigned int __cdecl wcslen(wchar_t const *string);     // 0x00783605

// The game option bits unknown_flags_a3f600 are in shared/unknown_globals.hpp.
// Unknown_005A09E0 (called when the sidebar is hidden) is in shared/unknown_globals.hpp.

// The shape drawer (0x0049EEA0; shared/palette.hpp's declaration, which
// this unit cannot include).
struct ShapeFileStruct;
// Plays a screen-layer sound at full volume (the play call is 0x00713DB0,
// declared in shared/radar.hpp). Inline: TabClass::AI 0x006A0F30 spends its
// inline budget on it (with a plain call the bar helpers' nested calls 0x006A0600
// and 0x006A0D80 are inlined, as they are not in the original).
inline void Unknown_Play_Sound(int sound)
{
    Voc_Play(sound, 1.0f, 0x2000, 0);
}
void __fastcall CC_Draw_Shape(Surface *surface, ConvertClass *drawer, ShapeFileStruct const *shape, int frame,
                              Point2D const &point, Rect const &window, int flags, int unknown8,
                              int unknown9, int unknown10, int brightness, int unknown12,
                              int unknown13, Point2D offset);
// A window rectangle the sidebar resets (0x008336E8).
extern Rect unknown_rect_8336e8;
// Whether the sidebar is shown on the screen (0x00A40D04; hypothesis).
// Set when a sidebar button repainted (0x00ABCD84).

// The strip icon size factors (0x00ABCD68, 0x00ABCD6C).
extern int unknown_abcd68;
extern int unknown_abcd6c;
// Set once the new-construction speech is suppressed (0x00A40774).
// A redraw request flag (0x008373C3).
// Speech by name: Speech_Play_Name is in shared/vox_class.hpp.
// A factory: its completion (0x004B98F0).
class ObjectClass;
class UnknownFactory {
public:
    void Unknown_004B97C0();                            // 0x004B97C0 (on removal from a strip)
    int Unknown_004B98F0();
    bool Unknown_004B9420();                            // 0x004B9420
    bool Unknown_004B9430();                            // 0x004B9430 (just completed; hypothesis)
    bool Unknown_004B9900();                            // 0x004B9900 (completed; hypothesis)
    char unknown_00[0x34];
    int unknown_34;                                     // +0x34
    char unknown_38[0x6C - 0x38];
    bool unknown_6c;                                    // +0x6C (on hold; hypothesis)
    ObjectClass *Get_Object();                          // 0x004B9930 the object being built (a TechnoClass)
};
// Unknown_006F8A20/Unknown_006F8A00 (building placement): shared/unknown_globals.hpp.
// The placement cell the sidebar passes with a place event (0x00AB9698).
extern Cell unknown_cell_ab9698;

// ControlClass, ShapeButtonClass: shared/gadget.hpp.

// Westwood's tag for the constructors that rebuild an object in place.
class InitClass {
};

// UnknownStage: shared/stage.hpp.

// One build icon entry of a strip (0x30 bytes; constructor 0x00682480,
// empty destructor kept at 0x0040D130).
struct UnknownBuildable30 {
    ~UnknownBuildable30() {}
    int unknown_00;                                     // +0x00 (id)
    int unknown_04;                                     // +0x04
    int unknown_08;                                     // +0x08
    UnknownFactory *Factory;                            // +0x0C its factory while building
    int unknown_10;                                     // +0x10
    UnknownStage Stage;                                 // +0x14
    int unknown_2c;                                     // +0x2C
};

class SidebarClass : public PowerClass {
public:
    // The sidebar's background gadget.
    class SBGadgetClass : public GadgetClass {
    public:
        SBGadgetClass();                                // 0x0067B6E0
        virtual int Action(unsigned flags, unsigned &key); // slot 31 0x006816B0
    };

    // One column of build icons (0xE64 bytes).
    class StripClass {
    public:
        StripClass() {}
        StripClass(InitClass const &init);              // 0x0067E660
        void Unknown_0067E770();                        // 0x0067E770 Init_Clear of a strip

        // A build icon button (0x38 bytes).
        class SelectClass : public ControlClass {
        public:
            SelectClass();                              // 0x006809A0
            virtual void Mouse_Enter();                 // slot 28 0x00681600
            virtual void Mouse_Leave();                 // slot 29 0x00681650
            virtual int Action(unsigned flags, unsigned &key); // slot 31 0x006809F0
            void Set_Owner(StripClass &strip, int index);   // 0x006809D0
            bool Unknown_00681690();                    // 0x00681690 hovered while input is live

            StripClass *Strip;                          // +0x2C
            int Index;                                  // +0x30
            bool unknown_34;                            // +0x34 mouse over
        };

        void Unknown_00682400(int id, int delay);       // 0x00682400
        void One_Time(int id);                          // 0x0067E720 (loads DARKEN.SHP)
        bool Unknown_0067EDF0(int type, int id);        // 0x0067EDF0 adds a buildable (announces it)
        void Unknown_0067ED10(int type, int id);        // 0x0067ED10
        void Flag_To_Redraw();                          // 0x0067F030
        int Unknown_0067F7C0(int index);                // 0x0067F7C0 an icon's progress
        bool Unknown_006802D0();                        // 0x006802D0 (strip AI; true to redraw)
        bool Unknown_00681730();                        // 0x00681730 any buildables
        wchar_t const *Help_Text(int gadget_index);     // 0x0067F580 an icon's name and cost
        void const *Unknown_0067E740(int index);        // 0x0067E740 a super weapon type's sidebar icon, or null
        void Deactivate();                              // 0x0067E9A0 removes the strip's buttons
        void Unknown_0067E8F0();                        // 0x0067E8F0 adds the strip's buttons
        void Unknown_0067E7E0(int id);                  // 0x0067E7E0 (Init_IO: numbers the strip)
        void Activate();                                // 0x0067F680 flags the strip and adds its buttons
        void Unknown_0067F730();                        // 0x0067F730 unflags the strip and removes its buttons
        bool Unknown_006817D0(UnknownFactory *factory); // 0x006817D0
        bool AI(int &input, Point2D const &xy);         // 0x0067F050 the strip's per-frame update; true when it changed
        bool Scroll(bool up, int amount);               // 0x0067EE60
        bool Step(bool up);                             // 0x0067EEF0 scrolls by a row
        bool Page(bool up);                             // 0x0067EF70 scrolls by a page
        bool Unknown_0067EA20(int type, int id, int other_type, int other_id);   // 0x0067EA20 (sort order)
        // Rows of icons that fit (inline). The ternary is the original's: its inlined
        // copies subtract the 18/26 term before unknown_abcd64 (Draw_It 0x0067CF80),
        // unlike the if/else in the out-of-line SidebarClass::Unknown_006820A0.
        static int Max_Visible_Rows()
        {
            return (unknown_int_839624 + unknown_int_83962c - unknown_abcd64
                - (unknown_id_source_a3d290->unknown_2239 ? 26 : 18) - 7) / 50;
        }
        bool Unknown_006816D0(int value, int type, int id);  // 0x006816D0 sets a buildable's +0x0C by type and id

        UnknownStage unknown_00;                        // +0x00
        bool unknown_18;                                // +0x18 (set by Activate)
        int unknown_1c;                                 // +0x1C
        int unknown_20;                                 // +0x20
        void Unknown_0067F800(bool complete);           // 0x0067F800 draws the strip
        Rect unknown_24;                                // +0x24 (copied from unknown_rect_ab9688)
        int unknown_34;                                 // +0x34
        bool unknown_38;                                // +0x38 redraw request
        bool unknown_39;                                // +0x39
        bool unknown_3a;                                // +0x3A
        bool unknown_3b;                                // +0x3B
        int unknown_3c;                                 // +0x3C (-1)
        int unknown_40;                                 // +0x40
        int unknown_44;                                 // +0x44
        int unknown_48;                                 // +0x48
        int unknown_4c;                                 // +0x4C
        int BuildableCount;                             // +0x50
        UnknownBuildable30 Buildables[75];              // +0x54

        static Rect unknown_rect_ab9688;                // 0x00AB9688
    };

    SidebarClass();                                     // 0x0067B700
    SidebarClass(NoInitClass const &noinit);            // 0x0067B7B0

    virtual void One_Time();                            // slot 5  0x0067B890
    virtual void Init_Clear();                          // slot 7  0x0067B8B0
    virtual void Init_IO();                             // slot 8  0x0067BAD0
    virtual void AI(int &input, Point2D const &xy);     // slot 10 0x0067DC90
    virtual void Draw_It(bool complete = false);        // slot 16 0x0067CF80
    int Unknown_00681980();                             // 0x00681980 first strip with buildables, or -1
    bool Unknown_0067C450(int control);                 // 0x0067C450 sets/toggles unknown_4ee6 (-1 toggles); the old state
    bool Unknown_0067C4C0(int control);                 // 0x0067C4C0 the same for unknown_4ee5
    void Unknown_0067DC00(int index);                   // 0x0067DC00 starts a tab button's flash
    void Unknown_0067C100();                            // 0x0067C100 redraws the active strip (soon)
    void Unknown_0067C2D0(int column);                  // 0x0067C2D0 redraws a strip if active
    // The strip of a type kind (0x00681940; TS name; buildings with arg3 5 take strip 1; naval is unused).
    static int __fastcall Which_Column(int kind, int arg3, bool naval);
    void Unknown_0067C310(int column);                  // 0x0067C310 and soon
    void Unknown_0067E1C0();                            // 0x0067E1C0 strip AI
    static void Unknown_0067BA60();                     // 0x0067BA60 places the sidebar and its controls
    void Unknown_0067B910();                            // 0x0067B910
    bool Unknown_0067C370(int value, int type, int id); // 0x0067C370 updates a buildable in its strip
    bool Unknown_00681740(int type, int id, UnknownFactory *factory);   // 0x00681740
    int Unknown_006820A0();                             // 0x006820A0 rows of icons that fit
    int Unknown_006820F0();                             // 0x006820F0 icons that fit, two per row
    bool Unknown_0067C530(int type, int id);            // 0x0067C530 adds a buildable to its strip (hypothesis: Add)
    void Unknown_0067D420(bool complete);               // 0x0067D420
    void Unknown_0067CA50(int index);                   // 0x0067CA50 a tab whose strip emptied
    void Select_Tab(int index);                         // 0x0067D990 switches to another tab
    void Unknown_006822B0(TechnoTypeClass *type, int arg2);   // 0x006822B0 (TActionClass 0x006B3060)
    void Activate_Tab(int index);                       // 0x0067D7E0 selects a tab and shows its strip
    void Unknown_0067C910(int index);                   // 0x0067C910 enables a tab button
    void Unknown_0067C850();                            // 0x0067C850 enables the scroll buttons when the strip overflows
    bool Scroll(bool up, int column);                   // 0x0067CDD0 by one row
    bool Scroll_Page(bool up, int column);              // 0x0067CE90 by a page
    void Unknown_0067C150(ObjectClass *object);         // 0x0067C150 redraws the strip a new object belongs to
    // The strip a buildable type belongs to (inline).
    static int Which_Column(int type, int id)
    {
        if (type == 15 || type == 16) {
            return 2;
        } else if (type == 1 || type == 40 || type == 2 || type == 3) {
            return 3;
        } else if (type == 6 || type == 7) {
            return (Unknown_004EB550(type, id) == 5);
        } else if (type == 57 || type == 32 || type == 31) {
            return 1;
        }
        return -1;
    }
    static int __fastcall Unknown_0067E640(int value);  // 0x0067E640
    static int __fastcall Unknown_0067E650(int value);  // 0x0067E650
    bool Unknown_0067DC70(int index);                   // 0x0067DC70 stops it
    virtual HRESULT unknown_slot30(IStream *stream);                      // slot 30 0x00682290 load
    virtual HRESULT unknown_slot31(IStream *stream);                      // slot 31 0x006822A0 save
    virtual wchar_t const *unknown_slot33(int id);      // slot 33 0x00681ED0
    virtual void unknown_slot34();                      // slot 34 0x006819A0
    virtual void unknown_slot50();                      // slot 50 0x0067BFC0
    virtual void unknown_slot53();                      // slot 53 0x0067BD90
    virtual bool unknown_slot54(int control);           // slot 54 0x0067E210 (new; shows (1), hides (0) or toggles (-1) the sidebar; true when it changed)

    static SBGadgetClass Background;                    // 0x00AB9718
    static ShapeButtonClass unknown_button_ab96b8;      // 0x00AB96B8
    static ShapeButtonClass unknown_button_abcc58;      // 0x00ABCC58
    static ShapeButtonClass unknown_buttons_ab9508[4];  // 0x00AB9508
    static ShapeButtonClass unknown_button_abcbe8;      // 0x00ABCBE8
    static ShapeButtonClass unknown_button_abccc0;      // 0x00ABCCC0
    static StripClass::SelectClass SelectButton[240];   // 0x00AB9740
    static void const *unknown_shape_ab9480;            // 0x00AB9480 (One_Time)

    StripClass Column[4];                               // +0x1540
    int unknown_4ed0;                                   // +0x4ED0
    int unknown_4ed4;                                   // +0x4ED4
    int unknown_4ed8;                                   // +0x4ED8
    int unknown_4edc;                                   // +0x4EDC
    bool unknown_4ee0;                                  // +0x4EE0
    bool unknown_4ee1;                                  // +0x4EE1
    bool unknown_4ee2;                                  // +0x4EE2 true after Init_Clear
    bool unknown_4ee3;                                  // +0x4EE3
    bool unknown_4ee4;                                  // +0x4EE4
    bool unknown_4ee5;                                  // +0x4EE5
    bool unknown_4ee6;                                  // +0x4EE6
};

#endif

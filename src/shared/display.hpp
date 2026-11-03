// DisplayClass: the tactical display layer of the screen chain (Display.CPP,
// from the header statics at 0x00498760; RTTI vtable 0x0079E91C, 50 slots),
// derived from MapClass.
//
// Layout from the constructor 0x00498A50 (members +0x1170..+0x11DF after
// MapClass, all cleared or set to the 0x00852610 cell) and Init_Clear
// 0x00498BE0. Unit statics: the five LayerClass objects at 0x00852578
// (initializer 0x00498950) and the TacticalClass button at 0x00852910
// (initializer 0x00498A00). Member names are unknown_ unless evidenced.
#ifndef RA2_SHARED_DISPLAY_HPP
#define RA2_SHARED_DISPLAY_HPP
#include "shared/unknown_globals.hpp"
#ifdef RA2_SHARED_MAP_VIEW_HPP
#error "shared/map_view.hpp declares light screen layers: include the full layer headers before it"
#endif

#include "shared/map.hpp"
#include "shared/rgb_class.hpp"
#include "shared/string_table.hpp"

class ObjectClass;
class ObjectTypeClass;
class BuildingTypeClass;

// A display layer (LayerClass): shared/layer.hpp.
#include "shared/layer.hpp"

// A three-component offset with an out-of-line constructor (0x0041B630)
// and length (0x0041B780) (hypothesis: a coordinate difference class).
#include "shared/unknown_vector3.hpp"
// The selected objects (0x00A40C60) are unknown_objects_a40c60 (shared/object.hpp).

// The small-cursor flag passed to Set_Default_Mouse (0x0083740C).

// The layer orders Next_Object (0x007D5CDC: 2, 3, 4) and Prev_Object
// (0x007D5CE8: 4, 3, 2) walk.
extern int unknown_layers_7d5cdc[3];
extern int unknown_layers_7d5ce8[3];

// Member-wise sum of two cells: shared/coord.hpp.

// Square root (0x004BA410; as shared/unknown_geometry.hpp).
double __cdecl unknown_sqrt_4ba410(double value);

// The tactical area: X, Y, width, height (0x00839630; as shared/tool_tip.hpp).
extern Rect unknown_rect_839630;
// The cursor position display toggle (0x00A416BC; CursorPositionCommandClass 0x0051D990 flips it).
extern bool unknown_show_cursor_position_a416bc;
// A copy of the view rectangle (0x0085291C; set by slot 42).
extern Rect unknown_rect_85291c;

// The cell offsets of the eight facings (0x00851A70; Westwood's AdjacentCell;
// the same block as shared/infantry.hpp).
#ifndef RA2_ADJACENT_CELL
#define RA2_ADJACENT_CELL
#include "shared/adjacent_cell.hpp"
// The cell next to `cell` toward an 8-way facing (TibSun Adjacent_Cell: the
// cell is the left operand of TPoint2D<short>::operator+; DisplayClass slot 38
// 0x0049A0F0).
inline Cell Adjacent_Cell(Cell const &cell, int facing)
{
    return cell + AdjacentCell[facing & 7];
}
#endif

// The object at 0x0084E8D0 (class not identified; 0x0042D960 and 0x0042D990
// also use it): whether a house may enter the mode +0x11B0 (0x0042E700).

// The cell value DisplayClass starts its cursor cells with (0x00852610).
extern Cell unknown_cell_852610;

class DisplayClass : public MapClass {
public:
    DisplayClass();                                                             // 0x00498A50
    // Restore-in-place form (the copy the linker kept is 0x006824F0, Sidebar.CPP).
    DisplayClass(NoInitClass const &noinit)
        : MapClass(noinit), WaypointColor(0, 0, 0)
    {
    }

    virtual void One_Time();                                                    // slot 5 0x00498B70
    virtual void Init_Clear();                                                  // slot 7 0x00498BE0
    virtual void Init_IO();                                                     // slot 8 0x00498C50
    virtual void AI(int &input, Point2D const &xy);                             // slot 10 0x00499A20
    // Puts an object into the layer it belongs to (0x00499A40) after taking
    // it out of its old one (0x00499A90).
    void Submit(ObjectClass *object);
    void Remove(ObjectClass *object);
    // Mode switches (-1 toggles, 0 off, 1 on) (hypotheses: Sell_Mode_Control
    // 0x0049C7C0 with +0x11AD, Repair_Mode_Control 0x0049CA20 with +0x11AC).
    void Unknown_0049C7C0(int control);
    void Unknown_0049CA20(int control);
    CoordStruct Unknown_0049CB70(CoordStruct const &coord, bool any);   // 0x0049CB70
    bool Unknown_0049CBF0(CoordStruct const &coord, bool alt);   // 0x0049CBF0
    // Unmaps a cell for layer 0: clears its visible and fully-shrouded bits
    // and refreshes it and its neighbours (0x0049CF00).
    void Unknown_0049CF00(Cell const &cell);
    // Re-maps every mapped cell (0x0049CD20): marks them (+0x140 bit 6), lets
    // 0x0049E110 run, then maps the marked ones again through 0x0049CDB0.
    void Unknown_0049CD20();
    // Unmaps a cell for layer 1 and spreads to the neighbours the view still
    // shows (0x0049CDB0).
    void Unknown_0049CDB0(Cell const &cell);
    // Unmaps every cell no longer seen (0x0049CC20): marks the visible cells
    // that are not fully shrouded (+0x140 bit 5), unmaps them through
    // 0x0049CF00, then runs 0x0049E110 (false, 0) and redraws.
    void Unknown_0049CC20();
    void Unknown_0049E110(bool skip_buildings, bool arg2);   // 0x0049E110 (slot 70 over the technos of layer 2)
    void Unknown_0049E000(bool skip_buildings, bool arg2);    // 0x0049E000 (slots 263/236 over every techno)
#ifdef RA2_DISPLAY_START_POS
    void Unknown_0049C670(); // original start position; matches the existing light interface
#endif
    void Unknown_0049DE00(bool skip_buildings, bool arg2);    // 0x0049DE00 (over every techno; MapClass 0x00559F10)
    void Constrained_Look(CoordStruct const &center, int distance);   // 0x0049E1D0 (TibSun Constrained_Look)
    // Whether a building type may be placed for the player at a cell: false
    // only when one of its foundation cells (by Width and Foundation_Height)
    // is a 0x00568140 cell and the type's +0xBF0 is clear (0x00499390).
    bool Unknown_00499390(BuildingTypeClass *type, int house, int arg3, Cell const *cell);
    // Packs the map's description (theater, map sizes, set waypoints, the cells' terrain) into a
    // buffer and returns its size (0x0049DB60); unpacks it again (0x0049DCD0).
    int Unknown_0049DB60(void *buffer, int arg2);
    void Unknown_0049DCD0(void *buffer);
    void Unknown_0049E570();                            // 0x0049E570 resets every cell (0x004790F0) and redraws
    // The width and height of a cell list ending with (0x7FFF, 0x7FFF), at
    // least 1 x 1; 0 x 0 for no list (0x00499810).
    Cell Unknown_00499810(Cell const *list);
    // Sets the placement cursor's cell list (0x00499070; RA Set_Cursor_Shape): unmarks the old
    // one, copies the list into a function static and centres it on the zone cell.
    void Set_Cursor_Shape(Cell const *list);
    // Sets or clears flag 2 (0x004998C0) or 4 (0x00499970) of the cells of
    // the list at +0x1178 / +0x1188 placed at a cell.
    void Unknown_004998C0(Cell const &cell, bool set);
    void Unknown_00499970(Cell const &cell, bool set);
    // Runs 0x004798F0 on every cell of the map (0x0049E5E0; a member: Ion.cpp's 0x00520B00 calls it on Map).
    void Unknown_0049E5E0();
    // Loads eight house colours (color % 12, or the first eight for -1) into
    // entries 1-8 of the drawer 0x008323C8's surface value table (0x0049EB40).
    void Unknown_0049EB40(int color);
    // Whether a move between two cells is open: always for speed 4, else both
    // cells enterable and empty (0x0049AD90).
    bool Unknown_0049AD90(Cell const &from, Cell const &to, int speed, int arg4, int arg5);
    // Centres the tactical view on the selected objects, leaving out the one
    // farthest from their centre when there are more than two (0x0049E3B0).
    void Unknown_0049E3B0();
    // The selectable object after (0x0049A5D0) or before (0x0049A670) one,
    // over layers 2, 3 and 4; the first one found when there is none.
    ObjectClass *Next_Object(ObjectClass *object);
    Cell Unknown_0049A700(int edge, Cell const &cell1, Cell const &cell2, int arg4, bool zonecheck, int arg6);   // 0x0049A700 (a cell on map edge `edge` near two cells; AircraftClass slot 134 passes 4, 1, 0)
    bool Passes_Proximity_Check_004991D0(ObjectTypeClass const *, int, Cell const *, Cell const &) const;
    ObjectClass *Unknown_0049EC40();                    // 0x0049EC40
    void Unknown_0049EC60(ObjectClass *object);         // 0x0049EC60
    // Moves the cursor cell (+0x1170) to a cell and returns the old one (0x004994D0).
    Cell Unknown_004994D0(Cell const &cell);
    ObjectClass *Prev_Object(ObjectClass *object);                     // 0x0049E5E0 runs 0x004798F0 on every cell
    void Unknown_0049C980(int control);
    void Unknown_0049CAC0(int control);                 // 0x0049CAC0 the mode switch for +0x11B0
    void Unknown_00498F10(Cell const *list);            // 0x00498F10 (the placement cursor's cell list; 0 clears it)
    void Unknown_0049C860(int control, bool keep);     // 0x0049C860 the same for +0x11AF (the player's waypoint mode)                 // 0x0049C980 the same for the mode at +0x11AE
    // The mouse shape over a cell with one of the player's waypoints (0x0049EAD0).
    int Unknown_0049EAD0(int mouse, Cell const &cell);
    // The screen's load and save (0x0049E810, 0x0049E840).
    virtual HRESULT unknown_slot30(IStream *stream);                  // slot 30
    virtual HRESULT unknown_slot31(IStream *stream);                  // slot 31
    // The map's sections of a scenario INI (0x0049D910; TibSun Write_INI).
    void Write_INI_0049D910(CCINIClass &ini);
#ifdef RA2_DISPLAY_READ_INI
    // Slot 32 (unknown_slot32 below) as map_view.hpp's direct-call alias; only the Display unit declares it
    // here (a new DisplayClass declaration moves one load in Print_CRCs 0x0062A360).
    void Read_INI_0049CFD0(CCINIClass &ini);                // 0x0049CFD0
#endif
    virtual void unknown_slot32();                                    // slot 32
    // Help text of a button id (RadarClass 0x00634AA0, PowerClass 0x0061D1C0 for id 999).
    virtual wchar_t const *unknown_slot33(int id);                   // slot 33
    virtual void unknown_slot34();                                    // slot 34 0x0049E7D0 places the controls
    virtual void unknown_slot35();                                    // slot 35
    // Cell tests (0x00499BB0, 0x00499FC0; meaning not recovered).
    virtual bool unknown_slot36(Cell const &cell, HouseClass *house);    // slot 36
    virtual bool unknown_slot37(Cell const &cell, HouseClass *house, bool arg3);  // slot 37 0x00499FC0 (maps a cell; arg3 counts a viewer in or out)
    virtual bool unknown_slot38(Cell const &cell, HouseClass *house);    // slot 38 0x0049A0F0 (maps a cell for layer 1 and spreads to the neighbours)
    virtual bool unknown_slot39(Cell const &cell, HouseClass *house);    // slot 39 0x0049A370 (the layer-0 form of slot 38)
    virtual int unknown_slot40() = 0;                                 // slot 40 (pure; MouseClass 0x0040D150 returns its shape)
    virtual bool unknown_slot41(int arg1, int *arg2, bool arg3);       // slot 41 0x00499B60
    // Slot 42 (0x00498C80): One_Time passes it the tactical view rectangle.
    virtual void unknown_slot42(Rect const &rect);
    virtual void unknown_slot43();                                    // slot 43 0x0040D120
    void Active_Click_0049E870(ObjectClass *, Cell, int);
    virtual void unknown_slot44(Point2D const &point);               // slot 44 0x0049AF80
    virtual void unknown_slot45(Point2D const &xy);                   // slot 45 0x0049C490 (the left button went down at xy: anchors a selection band)
    // Slot 46 (0x0049B0F0): the left button released over a cell (Westwood's
    // Mouse_Left_Up: cell, shadowed, object, action, small mouse; hypothesis).
    virtual void unknown_slot46(Cell const &cell, bool shadow, ObjectClass *object, int action, bool small_mouse);
    virtual void unknown_slot47(Point2D const &xy);                   // slot 47 0x0049C500 (the mouse held at xy: drags a selection band)
    // Slot 48 (0x0049BB20): the left button released after a drag (Westwood's
    // Mouse_Left_Release: coordinate, cell, object, action, small mouse; hypothesis).
    virtual void unknown_slot48(CoordStruct const &coord, Cell const &cell, ObjectClass *object, int action, bool small_mouse);
    virtual void unknown_slot49(Point2D const &xy);                    // slot 49 0x0049AF90 (ScrollClass 0x0066A7A0 passes Point2D(-1, -1))

    // The tactical area's gadget (0x00852910; RTTI DisplayClass::TacticalClass).
    // Constructor: GadgetClass(0, 0, 0, 0, 0x7F, true) inlined (0x00498A00).
    class TacticalClass : public GadgetClass {
    public:
        TacticalClass() : GadgetClass(0, 0, 0, 0, 0x7F, true) {}
        virtual int Action(unsigned flags, unsigned &key);  // slot 31 0x0049AE70
    };
    static TacticalClass TacButton;

    static LayerClass Layer[5];                     // 0x00852578
    static void const *TransIconset;                // 0x00852614 "PLACE.SHP" (name from TS/RA1, hypothesis)
    static void const *ShadowShapes;                // 0x00852934 "SHADOW.SHP"
    static int unknown_852630;                      // 0x00852630

    Cell unknown_1170;        // +0x1170
    Cell unknown_1174;        // +0x1174
    Cell const *unknown_1178; // +0x1178 a cell list (offsets ending with 0x7FFF, 0x7FFF) marked with flag 2
    bool unknown_117c;              // +0x117C
    bool unknown_117d;              // +0x117D
    Cell unknown_117e;        // +0x117E
    Cell unknown_1182;        // +0x1182
    Cell const *unknown_1188; // +0x1188 a cell list marked with flag 4
    int unknown_118c;               // +0x118C
    int unknown_1190;               // +0x1190
    int unknown_1194;               // +0x1194 -1
    bool unknown_1198;              // +0x1198
    void *unknown_119c;             // +0x119C (a pointer: the load swizzles it)
    ObjectClass *unknown_11a0;   // +0x11A0 an object waiting for placement (cancelled by slot 49)
    ObjectTypeClass const *unknown_11a4;             // +0x11A4 (a pointer: the load swizzles it)
    int unknown_11a8;               // +0x11A8 -1
    bool unknown_11ac;              // +0x11AC
    bool unknown_11ad;              // +0x11AD
    bool unknown_11ae;              // +0x11AE
    bool unknown_11af;              // +0x11AF
    bool unknown_11b0;              // +0x11B0
    int unknown_11b4;               // +0x11B4 -1
    CoordStruct *unknown_11b8;      // +0x11B8 where 0x0049C860 puts back the coordinate at +0x11BC
    int unknown_11bc;               // +0x11BC
    int unknown_11c0;               // +0x11C0
    int unknown_11c4;               // +0x11C4
    RGBClass WaypointColor;        // +0x11C8 original three-byte mouse waypoint color
    bool unknown_11cb;              // +0x11CB
    bool unknown_11cc;              // +0x11CC
    bool unknown_11cd;              // +0x11CD
    Point2D unknown_11d0;           // +0x11D0 where a drag select started (slot 47)
    Point2D unknown_11d8;           // +0x11D8 the drag select's last point (slot 47)
};

// The tactical view rectangle (0x006F1F30, returned through ECX).
Rect __fastcall Unknown_006F1F30();

#endif

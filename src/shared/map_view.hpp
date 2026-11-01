// The game's map/screen object and the screen layer classes as the units
// below the screen layer see them.
//
// The object at 0x008324E0 is a MouseClass (the top of the screen chain:
// its initializer 0x0040D060 calls MouseClass::MouseClass 0x0059F020, which
// stores vtable 0x0079A954) and is declared here once, as Westwood named it:
//
//     extern MouseClass Map;          // ?Map@@3VMouseClass@@A, 0x008324E0
//
// Data members: the light classes declare only the data other units read,
// at the full layout's offsets (GScreenClass's 0x10 bytes, then MapClass's
// +0x120..+0x12C); static members never.
//
// Why the screen layers are declared twice. Every static data member
// declaration takes one value of the compiler's per-unit counter (the
// numbers in the _$E initializer and $S guard names). Measured with the
// Bullet unit (population-1061) and the class headers included first:
//   gadget.hpp +4, gscreen.hpp +1, map.hpp +0, display.hpp +5,
//   radar.hpp +10, power.hpp +2 (sidebar.hpp, tab.hpp, scroll.hpp and
//   mouse_class.hpp add 9, 6, 1 and 3 more after their own includes),
// so Bullet's first header-static initializer becomes _$E24 instead of the
// original's _$E2, and its slot 64 guard and exit thunk shift even when the
// chain comes after the header statics. Moving the members to namespace
// scope does not help: the owner units need them (with RadarClass's ten
// static members as externs the Radar unit's initializers renumber from
// _$E61.._$E80 to _$E51.._$E69). So:
//   - units of the screen layers (GScreen, Map, Display, Radar, Power,
//     Sidebar, Tab, Scroll, Mouse) and the gadgets include the full class
//     headers, which keep their static members;
//   - every other unit sees only this header: the same class names, bases
//     and member function declarations (so the same decorated names), no
//     data members and no static members.
// A light class is declared only when its full header has not been
// included, so a unit may include some full layers and then this header;
// the full headers refuse to follow it. Members called through Map must be
// declared both here and in the full header of their class, with the same
// signature.
#ifndef RA2_SHARED_MAP_VIEW_HPP
#define RA2_SHARED_MAP_VIEW_HPP

#include "shared/coord.hpp"
#include "shared/rect.hpp"
#include "shared/vector_class.hpp"

class AbstractClass;
class CellClass;
class ObjectClass;
class ObjectTypeClass;
class TechnoClass;
class HouseClass;
class BuildingTypeClass;
class TechnoTypeClass;
class CCINIClass;

#ifndef RA2_SHARED_GSCREEN_HPP
class GScreenClass {
public:
    virtual void Flag_To_Redraw(int complete = false);                          // slot 14 0x004E09A0
    virtual void Render();                                                      // slot 15 0x004E0B30

    // The data the light layers place after it (shared/gscreen.hpp's layout).
    int ShakeX;                                 // +0x04
    int ShakeY;                                 // +0x08
    int IsToRedraw;                             // +0x0C
};
#endif

#ifndef RA2_SHARED_MAP_HPP
class MapClass : public GScreenClass {
public:
    virtual long __stdcall Is_Visible(Cell cell);                         // slot 3 0x00547FA0
    CoordStruct Unknown_00569FB0(CoordStruct const &from, CoordStruct const &to, HouseClass *house); // owner0200Z, observed hidden-result thiscall
    CellClass &operator[](CoordStruct const &coord);                            // 0x00548000
    CellClass &operator[](Cell const &cell);                              // 0x00548070
    void Sight_From(CoordStruct const &coord, int sight, HouseClass *house, bool arg4, bool arg5, int arg6, bool arg7, int arg8);   // 0x0054A110
    void Unknown_0054A720(CoordStruct const &coord, int radius);           // 0x0054A720 (TActionClass 0x006B1050: the rules RevealTriggerRadius around a waypoint)
    void Unknown_0055A300();                                              // 0x0055A300
    Cell Unknown_005689D0(Cell const &cell, int arg2);                    // 0x005689D0 (TActionClass 0x006B2860 launches from the cell it returns)
    void Unknown_0055AA50();                                                    // 0x0055AA50 (starts the walk of 0x0055A910)
    CellClass *Unknown_0055A910();                                              // 0x0055A910 (the next cell of the local-map walk, or null)
    void Unknown_00549C50(CoordStruct const &coord, int sight, HouseClass *house, bool arg4, bool arg5, bool arg6, bool arg7, bool arg8);   // 0x00549C50 (reveals around coord; TechnoClass slot 70)
    unsigned int Unknown_0055BD70(CellClass *cell); // physical full-EAX mask/RET4; Map receiver/source intent hypotheses
    unsigned char Unknown_0055C2C0(int first, int second); // physical AL-only/RET8; signedness/source intent hypotheses
    void Unknown_00559F10();                                              // 0x00559F10
    void Unknown_0055A120();                                              // 0x0055A120 (shared/map.hpp)
    void Unknown_0055A1F0();                                              // 0x0055A1F0 (shared/map.hpp)
    int Unknown_0056A8A0();                                               // 0x0056A8A0 (the lowest cell level, +0x144; TechnoClass 0x006CD6F0)
    bool Unknown_0054AAB0(Cell const &cell);                              // 0x0054AAB0
    bool Unknown_0054AB00(CoordStruct const &coord);                            // 0x0054AB00
    void Unknown_0054AB70(Cell const &cell, ObjectClass *object);         // 0x0054AB70
    void Unknown_0054AF70(Cell const &cell, ObjectClass *object);         // 0x0054AF70
    bool Unknown_0054F7C0(Cell const &from, Cell const &to, int zone, bool arg4, bool bridge, bool arg6);   // 0x0054F7C0
    int Zone(Cell const &cell, int zone_type, bool alt);                  // 0x0054F8F0
    void Unknown_0054FB20(Cell const &cell);                              // 0x0054FB20
    int Unknown_0055A280(CoordStruct const &coord);                             // 0x0055A280
    CellClass *Unknown_0055A490();
    bool Unknown_0054E580(Cell cell, int arg2);                             // 0x0054E580
    void Unknown_00559FD0();                                              // 0x00559FD0                                              // 0x0055A490
    int Unknown_0054B2E0();                                                     // 0x0054B2E0 (TibSun Overpass)
    void Unknown_005685F0();                                                    // 0x005685F0
    bool Unknown_00569090(Cell *cell);                                          // 0x00569090
    void Unknown_00563D40();                                                    // 0x00563D40
    void Unknown_0054EBD0();                                                    // 0x0054EBD0
    void Unknown_005688A0(DynamicVectorClass<Cell> &cells);                    // 0x005688A0 (as shared/map.hpp)
    void Unknown_0055A550();                                                    // 0x0055A550
    void Unknown_0054FDA0();                                                    // 0x0054FDA0 (shared/map.hpp)
    void Unknown_00568B00();                                                    // 0x00568B00
    bool Unknown_0054E410();                                                    // 0x0054E410 (places a crate on a random cell)
    void Unknown_0055D990(Cell const &cell);                              // 0x0055D990
    void Unknown_00562F50(CellClass *cell); // 00562F50: observed thiscall/RET4; unused return hypothesis
    CellClass *Unknown_005629D0(AbstractClass *object);                         // 0x005629D0 (the cell under an object; hypothesis)
    int Unknown_0054E3A0(Cell const &cell, HouseClass *house);                 // 0x0054E3A0
    bool Unknown_0055A660(Cell const &cell, bool flag);                   // 0x0055A660
    bool Unknown_0055A740(CellClass *cell, bool flag);                          // 0x0055A740
    bool Unknown_0055A7F0(CoordStruct const &coord);                            // 0x0055A7F0
    void Unknown_0055ACC0();                                                    // 0x0055ACC0
    bool Unknown_0055ACD0(ObjectClass *object, Cell const &cell);             // 0x0055ACD0 (whether the object may enter the cell: false when another object there blocks it)
    void Unknown_0054FC60(Cell const &cell);      // 0x0054FC60
    void Unknown_00566340(Cell const &cell);                              // 0x00566340
    bool Unknown_005683C0(CoordStruct const &coord);                            // 0x005683C0 (Tunnel.cpp)
    bool Unknown_00568140(CoordStruct const &coord);                            // 0x00568140
    void Unknown_0054A550(CoordStruct const &coord, int arg2, int arg3, int arg4);   // 0x0054A550
    int Unknown_0054E370(Cell const &cell);                               // 0x0054E370
    Cell Unknown_005502E0(Cell const &cell, int speed, int zone_index, int zone, bool bridge, Point2D size, bool arg8, bool arg9, bool arg10, bool arg11, Cell const &arg12, int arg13);   // 0x005502E0 (size: width and height, by value)
    void Unknown_00552570(Cell const &cell);                              // 0x00552570
    void Unknown_00555A60(Cell const &cell);                              // 0x00555A60
    Cell Unknown_00568ED0(Cell const &cell, Cell const &from);   // 0x00568ED0
    bool Unknown_00569320(Cell const &cell);                              // 0x00569320
    Cell Unknown_00564F70(CellClass *cell, bool bridge);                  // 0x00564F70 (the zone connection cell of a cell, its bridge deck when bridge; TS Get_Bridge_Zone_Connection_Cell)
    int Unknown_005500D0(Cell const &cell, int distance, int start);      // 0x005500D0 (shared/map.hpp)
    Cell Unknown_00565610(Cell const &cell, int layer, unsigned int subzone); // 0x00565610 (a bridge end cell in the subzone, or (0,0); TS Find_Bridge_End_Cell_For_Subzone)
    int Unknown_0054FAB0(Cell const &cell);                               // 0x0054FAB0 (shared/map.hpp)
    // Lists the layer subzones around the cell's (hypothesis); true sends the caller to 0x0042A840 (0x00565EB0).
    bool Unknown_00565EB0(CellClass &cell, int layer, DynamicVectorClass<unsigned short> *list, int arg4);

    // The map's data the other units read, at its shared/map.hpp offsets
    // (the light class has no other members, so the gap is padding).
    char unknown_010[0x6C - 0x10];
    char *unknown_6c;                           // +0x6C (shared/map.hpp; 10 bytes per cell: the subzone of each path estimator layer, a short each)
    int unknown_70[3];                          // +0x70 (shared/map.hpp)
#ifdef RA2_SHARED_SUBZONE_TRACKING_HPP
    // Only units that include shared/subzone_tracking.hpp first see the vectors (the element's list
    // member makes every VectorClass instantiation that sees it emit the list's own members).
    char unknown_07c[0x88 - 0x7C];
    DynamicVectorClass<SubzoneTrackingStruct> SubzoneTracking[3];   // +0x88 (shared/map.hpp)
    char unknown_0d0[0xE8 - 0xD0];
#else
    char unknown_07c[0xE8 - 0x7C];
#endif
    Rect MapSize;                               // +0xE8 (shared/map.hpp)
    Rect MapLocalSize;                          // +0xF8 (shared/map.hpp)
    char unknown_108[0x120 - 0x108];
    int unknown_120;                            // +0x120 the map's first cell X (hypothesis: MapCellX)
    int unknown_124;                            // +0x124 the first cell Y
    int unknown_128;                            // +0x128 the width in cells
    int unknown_12c;                            // +0x12C the height in cells
};
#endif

#ifndef RA2_SHARED_DISPLAY_HPP
class DisplayClass : public MapClass {
public:
    void Submit(ObjectClass *object);                                           // 0x00499A40
    void Remove(ObjectClass *object);                                           // 0x00499A90
    CoordStruct Unknown_0049CB70(CoordStruct const &coord, bool any);           // 0x0049CB70
    Cell Unknown_0049A700(int edge, Cell const &cell1, Cell const &cell2, int arg4, int arg5, int arg6);   // 0x0049A700
    void Unknown_0049E5E0();                                                    // 0x0049E5E0 (every cell runs 0x004798F0)
    ObjectClass *Unknown_0049EC40();                                            // 0x0049EC40
    void Unknown_0049EC60(ObjectClass *object);                                 // 0x0049EC60
    Cell Unknown_004994D0(Cell const &cell);                                    // 0x004994D0
    void Unknown_0049C7C0(int control);                                         // 0x0049C7C0
    void Unknown_0049C860(int control, bool keep);                              // 0x0049C860
    void Unknown_0049C980(int control);                                         // 0x0049C980
    void Unknown_0049CA20(int control);                                         // 0x0049CA20
    void Unknown_0049CAC0(int control);                                         // 0x0049CAC0
    void Unknown_0049CC20();                                                    // 0x0049CC20
    void Unknown_0049E110(bool skip_buildings, bool arg2);                      // 0x0049E110
    void Unknown_0049E000(bool skip_buildings, bool arg2);                      // 0x0049E000
    void Unknown_0049DE00(bool skip_buildings, bool arg2);                      // 0x0049DE00
    void Unknown_0049C670();                                                    // 0x0049C670 (multiplayer setup 0x0065E8C0)
    void Write_INI_0049D910(CCINIClass &ini);                                   // 0x0049D910 (Theater, Size, LocalSize; Write_Scenario_INI)
    void Read_INI_0049CFD0(CCINIClass &ini);                                    // 0x0049CFD0 (the map's sections of a scenario; Read_Scenario_INI)
    virtual bool unknown_slot39(Cell const &cell, HouseClass *house);                    // slot 39 0x0049A370
#ifdef MAP_VIEW_DECLARE_SLOT41
    // Slot 41 (0x00499B60, virtual in shared/display.hpp): scrolls the view; Main_Loop calls it directly.
    // Behind a guard (shared/main_loop.hpp defines it): a new declaration here renumbers
    // Refresh_Wonline_Players 0x0073FEE0's $L labels.
    bool unknown_slot41(int arg1, int *arg2, bool arg3);
#endif
    // Slot 38 (0x0049A0F0, virtual in shared/display.hpp), declared non-virtual so the light vtable keeps its layout;
    // Map calls it directly (MapClass 0x00549C50).
    bool unknown_slot38(Cell const &cell, HouseClass *house);
    void Set_Cursor_Shape(Cell const *list);
    void Unknown_00498F10(Cell const *list);                                    // 0x00498F10 (the placement cursor's cell list)
    // The pending placement (as shared/display.hpp; HouseClass::Manual_Place sets them).
#ifdef RA2_SHARED_MAP_HPP
    Cell unknown_1170;
    Cell unknown_1174;
    Cell const *unknown_1178;
    bool unknown_117c;
    bool unknown_117d;
    Cell unknown_117e;
    Cell unknown_1182;
    Cell const *unknown_1188;
    ObjectClass *unknown_118c;
    ObjectTypeClass *unknown_1190;
    int unknown_1194;
    bool unknown_1198;
    void *unknown_119c;
#else
    char unknown_130[0x11A0 - 0x130];
#endif
    ObjectClass *unknown_11a0;      // +0x11A0 the object waiting for placement
    void *unknown_11a4;             // +0x11A4 its type
    int unknown_11a8;               // +0x11A8 its house (-1)
    bool unknown_11ac;              // +0x11AC
    bool unknown_11ad;              // +0x11AD
    bool unknown_11ae;              // +0x11AE
    bool unknown_11af;              // +0x11AF
    bool unknown_11b0;              // +0x11B0
    int unknown_11b4;               // +0x11B4 -1
};
#endif

#ifndef RA2_SHARED_RADAR_HPP
class RadarClass : public DisplayClass {
public:
    virtual bool unknown_slot36(Cell const &cell, HouseClass *house);              // slot 36 0x0062FC80
    virtual void unknown_slot52(CoordStruct const &coord);                       // slot 52 0x00630320 (centres the tactical view on a coordinate)
    // Slot 37 (0x0062FCA0, virtual in shared/radar.hpp), declared non-virtual as slot 38 above.
    bool unknown_slot37(Cell const &cell, HouseClass *house, bool arg3);
    void Unknown_00631570(Cell const &cell);                              // 0x00631570
    void Unknown_00631910(TechnoClass *techno, Point2D point);                  // 0x00631910
    void Unknown_00631AF0(TechnoClass *techno, Point2D point);                  // 0x00631AF0
    Point2D Unknown_00631BA0(CoordStruct const &coord, bool clip);              // 0x00631BA0 (the radar point of a coordinate; RadarClass declares it with a Point2D; TechnoClass slot 53)
    void Unknown_00632620(Point2D const &point);                                // 0x00632620
    void Unknown_006328F0(Cell const &cell);                                    // 0x006328F0 marks the radar pixels of a cell for redraw (as shared/radar.hpp)
    DynamicVectorClass<Point2D> *Unknown_006328D0(BuildingTypeClass *type);     // 0x006328D0
    bool Unknown_006331A0();                                                    // 0x006331A0
    bool Unknown_00633130();                                                    // 0x00633130 (+0x14D4: the radar is on; as shared/radar.hpp)
    void Unknown_00633140(bool on);                                             // 0x00633140 (turns the radar on or off; as shared/radar.hpp)
    void Unknown_00634970(int arg1); // as shared/radar.hpp
    void Unknown_006331E0(bool flag);                                           // 0x006331E0
    void Unknown_00631D40();                                                    // 0x00631D40 (as shared/radar.hpp)
    void Unknown_00634030();                                                    // 0x00634030
    void Unknown_00630A00();                                                    // 0x00630A00
    void Unknown_00631ED0();                                                    // 0x00631ED0 builds the radar's table and surfaces (load path)

    // The radar's data the other units read, at shared/radar.hpp's offset.
    CoordStruct *unknown_11b8;                                                  // +0x11B8 the coordinate of the waypoint being dragged (as shared/display.hpp; FootClass slot 93)
    CoordStruct unknown_11bc;                                                   // +0x11BC where it is dragged to (FootClass slot 93 takes its cell)
    char unknown_11c8[0x1220 - 0x11C8];
    DynamicVectorClass<Cell> unknown_1220;                                      // +0x1220 the cells to redraw

    // Forgets the cells waiting for a radar redraw (inline in Read_Scenario_INI;
    // as shared/radar.hpp).
    void Clear_Redraw_Cells() { unknown_1220.Clear(); }
};
#endif

#ifndef RA2_SHARED_POWER_HPP
class PowerClass : public RadarClass {
};
#endif

#ifndef RA2_SHARED_SIDEBAR_HPP
// The production column of an object type (as shared/sidebar.hpp; 0x006818D0).
int __fastcall Unknown_006818D0(int type, int id, int arg3);

class SidebarClass : public PowerClass {
public:
    void Unknown_0067C150(ObjectClass *object);                                 // 0x0067C150 (as shared/sidebar.hpp)
    virtual void unknown_slot34();                                              // slot 34 0x006819A0
#ifdef RA2_HOUSE_SCREEN_AI
    void Unknown_0067E1C0(); // as shared/sidebar.hpp
#endif
    void Unknown_0067C2D0(int column);                                          // 0x0067C2D0 redraws a strip if active
    bool Unknown_0067C370(int value,int type,int id); // 0067C370, as shared/sidebar.hpp; House production link
    bool Unknown_00681740(int type, int id, class FactoryClass *factory);             // 0x00681740 (as shared/sidebar.hpp; production abandoned)
    static int __fastcall Which_Column(int kind, int arg3, bool naval);           // 0x00681940 (as shared/sidebar.hpp)
    void Unknown_0067B880(bool cameo_text);                                     // 0x0067B880 (empty; OptionsClass SidebarCameoText)
    void Select_Tab(int index);                                                 // 0x0067D990 (as shared/sidebar.hpp)
    bool Unknown_0067C530(int type, int id);                                    // 0x0067C530 (as shared/sidebar.hpp; adds a buildable to its strip)
    void Unknown_006822B0(TechnoTypeClass *type, int arg2);                     // 0x006822B0 (as shared/sidebar.hpp)

    // A production strip, as far as the other units read it (shared/sidebar.hpp's StripClass, 0xE64 bytes).
    class StripClass {
    public:
        bool Unknown_00681730();                                                // 0x00681730 any buildables
        char unknown_0[0xE64];
    };

    // The sidebar's data the other units read, at shared/sidebar.hpp's offset.
    char unknown_1238[0x1540 - 0x1238];
    StripClass Column[4];                                                       // +0x1540
};
#endif

#ifndef RA2_SHARED_TAB_HPP
#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif
class TabClass : public SidebarClass {
public:
    virtual void Init_IO();                                     // slot 8  0x006A0C50
    virtual wchar_t const *unknown_slot33(int id);              // slot 33 0x006A20B0 (the tooltip text; called directly)
    virtual bool unknown_slot54(int control);                   // slot 54 0x006A0DA0 (the sidebar shown or hidden)
#ifdef RA2_HOUSE_SCREEN_AI
    void Unknown_006A1770(); // as shared/tab.hpp
#endif
    void Unknown_006A17B0();                                    // 0x006A17B0 (sets +0x4F15 and flags a redraw)
    void Unknown_006A1EC0(); // as shared/tab.hpp
    void Unknown_006A1F10(); // as shared/tab.hpp
};
#endif

#ifndef RA2_SHARED_SCROLL_HPP
class ScrollClass : public TabClass {
public:
    virtual void unknown_slot35();                              // slot 35 0x0066AC20 (aborts a drag select)
    bool Unknown_00669650(Point2D const &xy, Cell &cell, CoordStruct &coord, ObjectClass *&object, bool &arg5, bool &arg6);   // 0x00669650
};
#endif

#ifndef RA2_SHARED_MOUSE_CLASS_HPP
class MouseClass : public ScrollClass {
public:
    // The overrides of the pure virtuals above (Map is a complete object).
    virtual void Set_Default_Mouse(int mouse, bool wsmall = false);      // slot 18 0x0059F060
    virtual bool Override_Mouse_Shape(int mouse, bool wsmall = false);   // slot 19 0x0059F250
    virtual void Revert_Mouse_Shape();                          // slot 20 0x0059F080
    virtual void Mouse_Small(bool wsmall);                      // slot 21 0x0059F090
    virtual int unknown_slot40();                               // slot 40 0x0040D150
#ifdef MAP_VIEW_DECLARE_SAVELOAD
    // The save/load unit's (0x00654A50) direct calls on Map; guarded because a new member
    // hides DisplayClass::unknown_slot42 elsewhere and shifts type-count victims (0x00428370).
    // Slot 31 (0x0059FC80, virtual in shared/mouse_class.hpp): the map's save, which
    // Put_All 0x006558B0 calls directly on Map.
    long unknown_slot31(struct IStream *stream);
    // Slot 30 (0x0059F530): the map's load (Get_All 0x00656B80).
    long unknown_slot30(struct IStream *stream);
    // DisplayClass slot 42 (0x00498C80): sets the tactical view rectangle (TS Set_View_Dimensions).
    void unknown_slot42(Rect const &rect);
#endif
};
#endif

extern MouseClass Map;                          // 0x008324E0

#endif

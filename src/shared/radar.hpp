// RadarClass: the radar layer of the screen chain (Radar.CPP, from the header
// statics at 0x0062EB00; RTTI vtable 0x007A871C, 54 slots), derived from
// DisplayClass.
//
// Stand-in for now: its own members (+0x11E0..+0x1507, constructor
// 0x0062EDE0) are not recovered; the size is fixed by PowerClass's first
// member at +0x1508. Slots 50..53 are RadarClass's own. Needs the
// display.hpp of build/class-work/Screen/next (slot 33 signature, slots
// 43..49).
#ifndef RA2_SHARED_RADAR_HPP
#define RA2_SHARED_RADAR_HPP
#include "shared/unknown_globals.hpp"
#ifdef RA2_SHARED_MAP_VIEW_HPP
#error "shared/map_view.hpp declares light screen layers: include the full layer headers before it"
#endif

#include "shared/display.hpp"
#include "shared/gadget.hpp"
#include "shared/system_timer.hpp"
#include "shared/string_table.hpp"
#include "shared/sound_play.hpp"

// The radar's own gadget (RTTI RadarClass::RTacticalClass, vtable
// 0x007A8694; GadgetClass constructor 0x004CEFE0 inlined with flags 0x9F).
class RTacticalClass : public GadgetClass {
public:
    RTacticalClass() : GadgetClass(0, 0, 0, 0, 0x9F, true) {}
    virtual int Action(unsigned flags, unsigned &key);  // slot 31 0x0062FE30
    int unknown_24;                                     // +0x24
    void *unknown_28;                                   // +0x28 its shape (Init_For_House: the art buffer 0x00AC1070; Draw_It draws frame 0..32)
};

// ShapeButtonClass: shared/gadget.hpp.

// A 16-byte list header at RadarClass +0x14BC: the constructor body calls
// 0x00405BF0 (clears it, +0x0C = 0x00830FAC), the destructor 0x00405C10.
struct AudioEventType;
struct UnknownList14BC {
    void Unknown_00405BF0();
    void Unknown_00405C10();
    void Unknown_00406070();                            // 0x00406070 (clears it)
    void __fastcall Unknown_00406100(AudioEvent *event, AudioEventType *type);   // 0x00406100 (keeps a playing event and its type; hypothesis)
    int unknown_00;
    int unknown_04;
    int unknown_08;
    void *unknown_0c;
};

// The key of the radar's tracking table (12 bytes, cleared by its
// constructor; compared member-wise by the bucket vectors' ID 0x00634DD0).
class TechnoClass;
class HouseClass;
struct RadarTrackingStruct {
    RadarTrackingStruct() : unknown_00(0), unknown_04(0, 0) {}
    TechnoClass *unknown_00;                            // +0x00 the object tracked
    Point2D unknown_04;                                 // +0x04 its radar point
};
inline bool operator==(RadarTrackingStruct const &a, RadarTrackingStruct const &b)
{
    return a.unknown_00 == b.unknown_00 && a.unknown_04 == b.unknown_04;
}
inline bool operator!=(RadarTrackingStruct const &a, RadarTrackingStruct const &b) { return !(a == b); }
class TechnoClass;
// The bucket vectors compare keys only.
inline bool operator==(HashObject<RadarTrackingStruct, TechnoClass *> const &a, HashObject<RadarTrackingStruct, TechnoClass *> const &b)
{
    return a.Key == b.Key;
}
// Hash of a radar point (0x00631C40) and of a tracking key, by its point
// (0x00631C60): x + y * 251.
unsigned __fastcall Unknown_00631C40(Point2D const &point);
unsigned __fastcall Unknown_00631C60(RadarTrackingStruct const &key);

// The radar's background art (0x00AC0FF0; a shell art buffer, as the art
// loaders name it), drawn by Draw_It at the radar origin.
extern void *unknown_buffer_ac0ff0;
// The frame art of the multiplayer player list (0x00AB64A0; frame 32 drawn by 0x00630350).
extern void *unknown_shape_ab64a0;
// Updates every radar event (RadarEvent.cpp 0x0063B910; name hypothesis).
void RadarEventClass_unknown_all_63b910();

// Positions of the two radar shape buttons (set by slot 53, used by Init_IO).
class ConvertClass;
extern int unknown_int_ab6470;      // 0x00AB6470 width of the 0xF2 shape
extern int unknown_int_ab6474;      // 0x00AB6474 its height
extern int unknown_int_ab6340;      // 0x00AB6340 width of the 0xF3 shape
extern int unknown_int_ab6344;      // 0x00AB6344 its height
// Names of the two button shapes (0x007EE064 "DIPLOBTN.SHP", 0x007EE068 "OPTBTN.SHP").
extern char const *unknown_name_7ee064;
extern char const *unknown_name_7ee068;
// The screen width (0x007ADD80; shared/sidebar.hpp).
// The radar's colour and a value for the radar button (0x00AC1028, 0x00AC1070;
// rules or scenario data; hypothesis).
class RGBClass;
extern RGBClass unknown_color_ac1028;
extern int unknown_int_ac1070;
// Loads a shape file, noting whether it was allocated (0x00495270; shared/power.hpp).
void const *__fastcall Unknown_Load_Shape_00495270(char const *filename, bool &allocated);
extern int unknown_int_ab6468;      // 0x00AB6468 button 0xF2 X
extern int unknown_int_ab646c;      // 0x00AB646C button 0xF2 Y
extern int unknown_int_ab6338;      // 0x00AB6338 button 0xF3 X
extern int unknown_int_ab633c;      // 0x00AB633C button 0xF3 Y
// The two radar buttons' rectangles as one value each (0x00AB6468 and
// 0x00AB6338; the ints around them are their fields).
extern Rect unknown_rect_ab6468;
extern Rect unknown_rect_ab6338;

// CoordStruct !=: shared/coord.hpp.

// The session (0x00A3D29C) whose slots 1 and 2 the radar's diplomacy button
// asks before choosing its mode (meaning not recovered).
class CCINIClass;
extern int unknown_int_af8fe8;                          // 0x00AF8FE8
// Runs after the radar's update unless it is in mode 4 (0x00716950).
void Unknown_00716950();
// The radar's transmission sequence (mode 4) helpers (meanings not recovered).
// Speech_Clear 0x007157B0 and Speech_Play 0x007158C0: shared/vox_class.hpp.
#include "shared/vox_class.hpp"
void Unknown_00716940();                                // 0x00716940
bool __fastcall Unknown_00716690(int voice);            // 0x00716690
void Unknown_004082B0();                                // 0x004082B0
int Unknown_00408330();                                 // 0x00408330
void Unknown_005A0B10();                                // 0x005A0B10
void Unknown_005A0AC0();                                // 0x005A0AC0 (radar mode 3: after the last movie)
// Unknown_0065C1F0 (0x0065C1F0): shared/unknown_globals.hpp.
void Unknown_0065C310();                                // 0x0065C310
bool Speech_Is_Playing();                               // 0x00715E20 (as shared/wdt_voices.hpp)
// The movies queued for the radar (0x00AF8FD8; mode 3 plays the first; shared/movie.hpp).
#include "shared/movie_queue.hpp"

// Values at RadarClass +0x1238 (a buffer and two values) and +0x1244 (four), cleared by their
// constructors (meaning not recovered).
struct UnknownRadar1238 {
    UnknownRadar1238() : unknown_00(0), unknown_04(0), unknown_08(0) {}
    UnknownRadar1238(NoInitClass const &noinit) {}
    unsigned char *unknown_00;                          // a buffer (deleted by 0x00631E40)
    int unknown_04;
    int unknown_08;
};
struct UnknownRadar1244 {
    UnknownRadar1244() : unknown_00(0), unknown_04(0), unknown_08(0), unknown_0c(0) {}
    UnknownRadar1244(NoInitClass const &noinit) {}
    int unknown_00;
    int unknown_04;
    int unknown_08;
    int unknown_0c;
};

// unknown_int_a3d548 (0x00A3D548): shared/unknown_globals.hpp.

// The objects of the list at 0x00A40C20 whose +0x37B flag the radar clears
// when it is rebuilt (view; type not identified).
struct UnknownRadarObject37B {
    char unknown_00[0x37B];
    bool unknown_37b;                                   // +0x37B
};
extern DynamicVectorClass<UnknownRadarObject37B *> unknown_vector_a40c20;    // 0x00A40C20

// A new tracking table (inline; Radar.cpp writes the creation as this
// helper, which keeps the bucket vector constructor 0x00635110 out of line).
inline HashTableClass<RadarTrackingStruct, TechnoClass *> *New_Tracking_Table(int count, int growth)
{
    HashTableClass<RadarTrackingStruct, TechnoClass *> *table = new HashTableClass<RadarTrackingStruct, TechnoClass *>(Unknown_00631C60, count, growth);
    return table;
}

// The radar dot sizes in cells, width and height per shape (0x007CFC70,
// 0x007CFCC8; 22 entries).
extern int unknown_widths_7cfc70[22];
extern int unknown_heights_7cfcc8[22];

// Index of a voice (EVA) entry by name (0x00716640, __fastcall; One_Time
// passes "EVA_IncomingTransmission").
int __fastcall Unknown_00716640(char const *name);

class BuildingTypeClass;
class RadarClass : public DisplayClass {
public:
    RadarClass();                                       // 0x0062EDE0
    // Restore-in-place form: the display restored, the radar's lists rebuilt
    // empty (inlined into SidebarClass(NoInitClass const &) 0x0067B7B0).
    RadarClass(NoInitClass const &noinit) : DisplayClass(noinit), unknown_1238(noinit), unknown_1244(noinit), unknown_14fc(0)
    {
        unknown_14bc.Unknown_00405BF0();
    }
    virtual ~RadarClass();                              // 0x0062F080 (??_G 0x00634AD0)

    virtual void One_Time();                            // slot 5  0x0062F170
    virtual void Init_Clear();                          // slot 7  0x0062F260
    virtual void Init_IO();                             // slot 8  0x0062F490
    virtual void AI(int &input, Point2D const &xy);     // slot 10 0x0062FCC0
    virtual void Draw_It(bool complete = false);        // slot 16 0x0062F580
    // Slot 33 returns the help text of a button id (PowerClass answers 999).
    virtual wchar_t const *unknown_slot33(int id);      // slot 33 0x00634AA0
    virtual void unknown_slot34();                      // slot 34 0x006306D0
    virtual void unknown_slot28(Rect const *rect, bool arg2, bool arg3, bool arg4);   // slot 28 0x00630300 (thunk passing the four arguments on to MapClass's)
    virtual void unknown_slot29(Rect const &rect);              // slot 29 0x00630840 (MapClass's slot) fits the radar to the map
    virtual HRESULT unknown_slot30(IStream *stream);    // slot 30 0x00632BF0 load
    virtual HRESULT unknown_slot31(IStream *stream);    // slot 31 0x00632E10 save
    virtual bool unknown_slot36(Cell const &cell, HouseClass *house);              // slot 36 0x0062FC80
    virtual bool unknown_slot37(Cell const &cell, HouseClass *house, bool arg3);   // slot 37 0x0062FCA0

    virtual void unknown_slot50();                      // slot 50 0x0062F210 (frees shapes)
    virtual Cell unknown_slot51(Point2D const &xy);   // slot 51 0x0062FBD0 the cell under a screen point
    virtual void unknown_slot52(Point2D const &point);  // slot 52 0x00630320 moves the tactical view
    virtual void unknown_slot53();                      // slot 53 0x0062F310 Init_For_House (loads shapes)

    // Adds (true) or removes the two radar shape buttons (0x0062F2D0).
    void Unknown_0062F2D0(bool add);
    // Sets +0x14A8 to 4 and +0x14F8 to 25 (0x0062F150; no direct callers).
    void Unknown_0062F150();
    // Empties the radar's tracking table at +0x1254 (0x00631E40).
    void Unknown_00631E40();
    bool Unknown_00630340(Cell const &cell);      // 0x00630340
    // The radar pixels of a cell (0x00631400) and the same scaled by the
    // zoom at +0x1484 (0x00631470).
    Rect Unknown_00631400(Cell const &cell);
    Rect Unknown_00631470(Cell const &cell);
    Cell Unknown_00631500(Point2D const &point);  // 0x00631500 the cell under a radar pixel
    void Unknown_00631570(Cell const &cell);      // 0x00631570 adds a cell to redraw (+0x1220) once
    void Unknown_00631910(TechnoClass *techno, Point2D point);   // 0x00631910 starts tracking an object (Techno/Building slot 264)
    void Unknown_00631AF0(TechnoClass *techno, Point2D point);   // 0x00631AF0 stops tracking an object
    DynamicVectorClass<Point2D> *Unknown_006328D0(BuildingTypeClass *type);    // 0x006328D0 (the type's foundation offsets; BuildingClass slots 264-266)
    void Unknown_00632620(Point2D const &point);        // 0x00632620
    // The radar pixel of a lepton position (256 per cell), optionally kept
    // inside the radar rectangle (0x00631BA0).
    Point2D Unknown_00631BA0(Point2D const &position, bool clip);
    void Unknown_00632000(Point2D const &point);        // 0x00632000 draws one radar point
    void Unknown_006324A0();                            // 0x006324A0
    void Unknown_00634030();                            // 0x00634030 redraws the whole radar
    void Unknown_00631ED0();                            // 0x00631ED0 builds the radar's table and surfaces (load path)
    void Unknown_00631D40();                            // 0x00631D40 rebuilds the tracking table and refits the radar
    void Unknown_00630A00();                            // 0x00630A00 rebuilds the radar surfaces
    Rect Unknown_00630B70(Rect const &area, Rect const &clip, bool flag);   // 0x00630B70 builds the radar image (+0x121C)
    void Unknown_006328F0(Cell const &cell);      // 0x006328F0 marks the radar pixels of a cell for redraw
    void Unknown_00632700();                            // 0x00632700 builds the 22 dot shapes (+0x1274)
    // The cell under a radar pixel, or under the object tracked at that pixel
    // (also returned through found) (0x00632AA0).
    Cell Unknown_00632AA0(Point2D const &pixel, TechnoClass **found);
    void Unknown_00631C80();
    bool Unknown_006331A0();                            // 0x006331A0 (TechnoClass slot 55: the radar is up)
    bool Unknown_00633130();                            // 0x00633130 returns +0x14D4 (the radar is on)
    void Unknown_00633140(bool on);                     // 0x00633140 turns the radar on or off (+0x14D4; HouseClass 0x004F2E50)
    void Unknown_006331E0(bool flag);                   // 0x006331E0 asks for a radar redraw (+0x14D6 complete)
    void Unknown_00632F30(bool on, bool sound);         // 0x00632F30 activates (3) or deactivates (2) the radar
    void Unknown_00634670(int arg1, int index, HouseClass *house);  // 0x00634670
    void Unknown_00634970(int arg1);                    // 0x00634970 runs 0x00634670 for each house                            // 0x00631C80 builds a new tracking table
    void Unknown_00633000(int mode, bool sound);        // 0x00633000 switches the radar mode (+0x14AC)
    void Unknown_00633C40();                            // 0x00633C40 the mode-4 (transmission) update
    void Unknown_00633210();                            // 0x00633210 (Draw_It, every frame)
    void Unknown_00630350();                            // 0x00630350 (Draw_It, mode 2)
    void Unknown_00633D30();                            // 0x00633D30 (Draw_It, mode 3)

    // Statics of Radar.CPP (guarded atexit destructors: static members).
    static RTacticalClass RadarButton;                  // 0x00AB6478
    static ShapeButtonClass unknown_button_ab63e8;      // 0x00AB63E8
    static ShapeButtonClass unknown_button_ab6380;      // 0x00AB6380
    static void const *unknown_shape_ab6350;            // 0x00AB6350 freed by slot 50 when
    static bool unknown_shape_ab6350_allocated;         // 0x00AB6369 allocated
    static void const *unknown_shape_ab6318;            // 0x00AB6318
    static bool unknown_shape_ab6318_allocated;         // 0x00AB6368
    static Rect unknown_rect_ab6320;                    // 0x00AB6320 copied into three rectangles
    // Statics with empty constructors (their do-nothing initializers are
    // 0x0062ED40 and 0x0062ED90): slot 51's cached cell and coordinate.
    static Cell unknown_cell_ab6330;              // 0x00AB6330
    static CoordStruct unknown_coord_ab6370;            // 0x00AB6370

    int unknown_11e0;                                   // +0x11E0 (One_Time: 0)
    int unknown_11e4;                                   // +0x11E4 (One_Time: 16)
    int unknown_11e8;                                   // +0x11E8 (One_Time: 48)
    int unknown_11ec;                                   // +0x11EC
    int unknown_11f0;                                   // +0x11F0 (One_Time: 49; radar button Y)
    int unknown_11f4;                                   // +0x11F4 (One_Time: 140)
    int unknown_11f8;                                   // +0x11F8 (One_Time: 108)
    int unknown_11fc;                                   // +0x11FC (One_Time: 140; radar button width)
    int unknown_1200;                                   // +0x1200 (One_Time: 108; radar button height)
    int unknown_1204;                                   // +0x1204
    Rect unknown_1208;                                  // +0x1208
    Surface *unknown_1218;                              // +0x1218 (deleted by 0x00631E40; a surface: hypothesis)
    Surface *unknown_121c;                              // +0x121C
    DynamicVectorClass<Cell> unknown_1220;        // +0x1220
    // Forgets the cells waiting for a radar redraw (inline in Read_Scenario_INI).
    void Clear_Redraw_Cells() { unknown_1220.Clear(); }
    UnknownRadar1238 unknown_1238;                      // +0x1238 (three values)
    UnknownRadar1244 unknown_1244;                      // +0x1244 (four values)
    HashTableClass<RadarTrackingStruct, TechnoClass *> *unknown_1254;  // +0x1254 tracking table
    DynamicVectorClass<Point2D> unknown_1258;           // +0x1258 (growth step 500)
    unsigned char *unknown_1270;                        // +0x1270 a buffer (deleted by 0x00631E40)
    DynamicVectorClass<Point2D> unknown_1274[22];       // +0x1274
    float unknown_1484;                                 // +0x1484 zoom (pixels per cell)
    int unknown_1488;                                   // +0x1488 1
    int unknown_148c;                                   // +0x148C
    int unknown_1490;                                   // +0x1490
    int unknown_1494;                                   // +0x1494
    Rect unknown_1498;                                  // +0x1498
    int unknown_14a8;                                   // +0x14A8
    int unknown_14ac;                                   // +0x14AC
    int unknown_14b0;                                   // +0x14B0
    int unknown_14b4;                                   // +0x14B4
    bool unknown_14b8;                                  // +0x14B8
    bool unknown_14b9;                                  // +0x14B9
    UnknownList14BC unknown_14bc;                       // +0x14BC
    int unknown_14cc;                                   // +0x14CC
    int unknown_14d0;                                   // +0x14D0 -1; One_Time stores 0x00716640's result
    bool unknown_14d4;                                  // +0x14D4
    bool unknown_14d5;                                  // +0x14D5
    bool unknown_14d6;                                  // +0x14D6
    Rect unknown_14d8;                                  // +0x14D8
    int unknown_14e8[4];                                // +0x14E8
    int unknown_14f8;                                   // +0x14F8
    CDTimerClass<SystemTimerClass> unknown_14fc;        // +0x14FC
};

#endif

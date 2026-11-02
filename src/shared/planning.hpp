// Waypoint planning mode (Planning.cpp, unit 0x006101B0-0x0061C25F): the
// planned orders of selected units, drawn as nodes and lines on the map and
// released together. Class names follow the RTTI names of their vector
// instances (DynamicVectorClass<PlanningNodeClass *> 0x007A821C, ...<
// PlanningTokenClass *> 0x007A825C, ...<PlanningBranchClass *> 0x007A829C,
// ...<PlanningMemberClass *> 0x007A82BC); the classes themselves have no
// RTTI. Layouts come from the constructors; field names are hypotheses
// unless stated.
//
// TechnoClass +0x408 (shared/techno.hpp's UnknownTechno408, reached through
// TechnoClass::unknown_6d1430/unknown_6d1420) is the techno's
// PlanningTokenClass; renaming it there needs the TechnoClass population
// (892) re-planned, so the planning code casts.
#ifndef RA2_SHARED_PLANNING_HPP
#define RA2_SHARED_PLANNING_HPP

#include "shared/unknown_globals.hpp"
#include "shared/event.hpp"
#include "shared/techno.hpp"
#include "shared/house.hpp"
#include "shared/planning_mouse.hpp"

// Two lists Planning.cpp defines (0x00A76648 the planned events, 0x00A76700 the
// technos with a planning token). They are static members here rather than of
// EventClass/TechnoClass: in VC6 a static data member of class type takes a
// static-initializer counter value in every unit that sees its class, so
// declaring them in event.hpp/techno.hpp would renumber every unit including
// those headers.
struct PlanningLists {
    static DynamicVectorClass<EventClass *> unknown_list_00a76648;     // 0x00A76648
    static DynamicVectorClass<TechnoClass *> unknown_list_00a76700;    // 0x00A76700
};
#include "shared/gscreen.hpp"
#include "shared/rgb_class.hpp"
#include "shared/string_table.hpp"

#include "shared/debug_printf.hpp"

// The tactical area origin (shared/sidebar.hpp).

class PlanningNodeClass;
class PlanningBranchClass;
class PlanningTokenClass;

// One techno's part in a node (0x10 bytes, constructor 0x006107E0).
//   +0x00 TechnoClass *Owner, +0x04 EventClass *Event (its own copy),
//   +0x08 int BranchIndex (-1, or the node branch it counts in),
//   +0x0C bool (counted in the node's own branch)
class PlanningMemberClass {
public:
    PlanningMemberClass();                      // 0x006107E0

    void Set_Owner(TechnoClass *owner);         // 0x00610800
    void Set_Event(EventClass *event);          // 0x00610810
    void Set_BranchIndex(int index);            // 0x00610820
    void Set_unknown_0c(bool value);            // 0x00610830
    TechnoClass *Get_Owner() const;             // 0x00610840
    EventClass *Get_Event() const;              // 0x00610850
    int Get_BranchIndex() const;                // 0x00610860
    bool Get_unknown_0c() const;                // 0x00610870

    TechnoClass *Owner;                         // +0x00
    EventClass *Event;                          // +0x04
    int BranchIndex;                            // +0x08
    bool unknown_0c;                            // +0x0C
};

// A planned order of a node (0x78 bytes, constructor 0x00610880): the event
// shared by Count members and an int. Every node has its own at +0x38 and
// a list of further branches; the vector instances name the class.
class PlanningBranchClass {
public:
    PlanningBranchClass();                                     // 0x00610880

    void Set_Event(EventClass const &event);                  // 0x006108A0
    void Set_Count(int value);                                // 0x006108C0
    void Set_unknown_74(int value);                           // 0x006108D0
    void Clear_Count();                                       // 0x006108E0
    int Increment_Count();                                   // 0x006108F0
    int Decrement_Count();                                   // 0x00610900
    EventClass Get_Event() const;                             // 0x00610910
    int Get_Count() const;                                    // 0x00610930
    int Get_unknown_74() const;                               // 0x00610940
    CoordStruct Coord() const;                                // 0x00610950
    Point2D Pixel() const;                                    // 0x00610A20

    EventClass Event;                                         // +0x00
    char unknown_6f;
    int Count;                                                // +0x70
    int unknown_74;                                           // +0x74
};

// The payload of a type-4 (mission) event as the planning code reads it:
// three object references (hypothesis; compare shared/techno.hpp's
// UnknownSlot268Arg view of the same record).
#pragma pack(push, 1)
struct PlanningEventTargets {
    AbstractClass *First_Target_Object() const;   // 0x00617DF0
    int unknown_61a2d0() const;                   // 0x0061A2D0
    int Unknown_006F6750() const;                 // 0x006F6750
    int Unknown_006F6760() const;                 // 0x006F6760
    unsigned char Type;                 // +0x00
    char unknown_01;
    signed char House;                  // +0x02 the issuing house
    int unknown_03;                     // +0x03 an id (-1: any)
    char unknown_07[0x0C - 0x07];
    unsigned char unknown_0c;           // +0x0C (2 -> 0x1D in 0x00611440)
    char unknown_0d;
    TargetClass Target_0e;              // +0x0E
    TargetClass Target_13;              // +0x13
    TargetClass Target_18;              // +0x18
    unsigned char unknown_1d;           // +0x1D (set to 1 when planned, 0x00614B70)
};
#pragma pack(pop)

// The view pixel of a coordinate: the tactical view's pixel plus the
// tactical area's origin (0x006107A0).
Point2D __fastcall Planning_Coord_Pixel(CoordStruct const &coord);
// The tactical view rectangle (0x006F1F30, shared/display.hpp).
Rect __fastcall Unknown_006F1F30();
// Grows a rectangle by amount on every side (shrinks it for a negative one;
// a rectangle that would vanish becomes empty) (0x00612570).
void __fastcall Planning_Inflate(Rect &rect, int amount);
// The colours the planning markers fade toward (0x00AB6841, 0x00AB6849).
extern RGBClass unknown_rgb_ab6841;
extern RGBClass unknown_rgb_ab6849;

// The colour of the house a techno's planning is drawn for (the player's
// house on a human-controlled side).
inline RGBClass Planning_House_Color(TechnoClass *techno)
{
    int house = techno->House->ArrayIndex;
    if (techno->House->Unknown_004F52B0() && unknown_player_a35db4) {
        house = unknown_player_a35db4->ArrayIndex;
    }
    return Houses[house]->unknown_55e9;
}

// The screen pixel of a colour moved ratio/256 of the way toward target (0x00619E00).
class RGBClass;
int __fastcall Planning_Adjusted_Pixel(RGBClass const &color, RGBClass const &target, int ratio);
// Lowers a house's counter, never below 0 (0x00616D20).
void __fastcall Planning_Uncount(int house);
extern int unknown_counts_a76684[8];            // 0x00A76684
extern bool unknown_flag_a767a5;                // 0x00A767A5 (the planning lists are being torn down)
extern bool unknown_flag_a767a4;                // 0x00A767A4
extern bool unknown_flag_a767a6;                // 0x00A767A6 (a re-entry guard)
// The screen point the mouse button went down at ((-1, -1): none) (0x00A76728).
extern Point2D unknown_point_a76728;
extern bool unknown_flag_a76770;                // 0x00A76770
// An object the planning mode notifies (0x00A76680; hypothesis: its slot 0 takes a message and an argument).
struct UnknownPlanningSink {
    virtual void Unknown_Slot0(int message, int argument);
};
extern UnknownPlanningSink *unknown_sink_a76680;
// Planning mode starts / ends (0x00614760, 0x006147B0).
void Planning_Begin();
void Planning_End();
// Takes a node out of the three planning lists (0x006143E0).
void __fastcall Planning_Unlist_Node(PlanningNodeClass *node);
// Makes a techno's planning token, lists it and hands it to the techno (0x00615820).
PlanningTokenClass *__fastcall Planning_New_Token(TechnoClass *techno);
// Sends a planned mission event (0x00614B70; the event is passed by value).
void __stdcall Planning_Send_Event(EventClass event);
// Displays a message (0x006F58E0; hypothesis: text and a priority).
void __fastcall Unknown_006F58E0(wchar_t const *text, int priority);
// Shows a planning-mode help message (0x00616FB0).
void __fastcall Planning_Message(char const *label);
// Once per session: shows a refusal message and plays the refused-action sound (0x00616FD0).
void __fastcall Planning_Refuse(char const *label);
void __fastcall Planning_Refuse_No_Guard_Area();         // 0x00616E70
extern bool unknown_flag_a766c8;                // 0x00A766C8 (a refusal was shown)
extern int unknown_counts_a766b4[];             // 0x00A766B4 (help messages shown, per kind)
// Shows a planning-mode help message the first time it is wanted (0x00616F50).
void __fastcall Planning_Help(int kind);
// Shows a planning-mode introduction message (0x00616EC0).
void __fastcall Planning_Intro(bool forced, bool first);
// Whether a house number indexes the counters.
inline bool Planning_Valid_House(int house)
{
    return house >= 0 && house < 8;
}
// A house's counter, 0 out of range (0x00616D50).
int __fastcall Planning_Count(int house);
// Shows the refusal for an order planning mode cannot take (0x00616D70).
void __fastcall Planning_Refuse_Event(EventClass const *event);
// The remembered node when the screen point is inside its grown marker (0x00615D30).
PlanningNodeClass *__stdcall Planning_Node_At(int x, int y);
// Whether the selected technos without a path still fit the planning limit (0x00615ED0).
bool __fastcall Planning_Can_Add();
// The node at a coordinate with a given id and house (-1: any) (0x00615FB0).
PlanningNodeClass *__fastcall Planning_Find_Node(int house, int id, CoordStruct coord);
// The drawn node at a coordinate (0x00616210).
PlanningNodeClass *__stdcall Planning_Find_Drawn(CoordStruct coord);
// The drawn / listed node whose grown marker contains a screen point (0x00616140, 0x00616070).
PlanningNodeClass *__stdcall Planning_Pick_Drawn(int x, int y);
PlanningNodeClass *__stdcall Planning_Pick_Node(int x, int y);
// Classifies the selection for planning mode (0x00616B40).
int Planning_Selection_Kind();
// Marks a node queued and appends it to the queue list (0x00614650).
void __fastcall Planning_Queue_Node(PlanningNodeClass *node);
// The coordinate an event points at, or the object's (0x00619810).
CoordStruct __fastcall Planning_Event_Or_Object_Coord(EventClass const &event, AbstractClass *object);
// A techno's house colour faded (0x00619CA0 by 0x50, 0x00619D50 by 100).
int __fastcall Planning_Dim_Color(TechnoClass *techno);
int __fastcall Planning_Bright_Color(TechnoClass *techno);
// A square outline / fill centred on a screen point (0x0061A190, 0x0061A210).
void __fastcall Planning_Draw_Dot(int color, int unused, int x, int y);
void __fastcall Planning_Fill_Dot(int color, int unused, int x, int y);
// The screen pixel of a palette colour (0x0061A860).
int __fastcall Planning_Pixel(RGBClass const *color);
// Shows the refusal for a selection planning mode cannot take (0x00617100).
void __fastcall Planning_Refuse_Selection(int kind);
void __fastcall Planning_Refuse_Command(int kind);   // 0x00617250
// What planning mode does with an order (0x006171E0).
int __fastcall Planning_Event_Result(PlanningTokenClass *token, PlanningEventTargets const *event);
double __cdecl unknown_sqrt_4ba410(double value);   // 0x004BA410 (shared/building.hpp)
// Outlines a square on the midpoint of two far-apart screen points (0x0061A2F0).
void __fastcall Planning_Draw_Midpoint(int color, int unused, Point2D start, Point2D end);
// Draws the planning mode (0x00617EF0); its drawing helpers (0x00619870, 0x00618C00).
void Planning_Draw_All();
void __fastcall Planning_Draw_Techno(TechnoClass *techno);
void __fastcall Planning_Draw_Node_619870(PlanningNodeClass *node);       // 0x00619870
void __fastcall Planning_Draw_Techno_618c00(TechnoClass *techno);       // 0x00618C00
extern DynamicVectorClass<TechnoClass *> unknown_list_a40c20;      // 0x00A40C20
int __fastcall Planning_Techno_Color(TechnoClass *techno);                     // 0x00619E80
Point2D __fastcall Planning_Event_Pixel(EventClass const *event, AbstractClass *object);   // 0x00619FA0
// Draws a clipped line shifted sideways (0x0061A5A0).
void __fastcall Planning_Draw_Line(int offset, int color, Point2D start, Point2D end, bool dashed);
void __fastcall Planning_Draw_Thick_Line(int thickness, int color, Point2D start, Point2D end);          // 0x0061A6A0
void __fastcall Planning_Draw_Dashed_Thick_Line(int thickness, int color, Point2D start, Point2D end);   // 0x0061A6F0
// Whether the techno's mission lets planning mode take over (0x00615A10).
bool __fastcall Planning_Mission_Allows(TechnoClass *techno);
// Whether a mission 11 order keeps the techno where it is (0x00615910).
bool __fastcall Planning_Order_Stays_Put(TechnoClass *techno, int mission, TargetClass target);
// Lists a copy of an event among the planned events (0x00614350).
void __fastcall Planning_Store_Event(EventClass const &event);
// Makes the techno's path loop back to one of its nodes (0x006164E0).
void __fastcall Planning_Close_Loop(TechnoClass *techno, PlanningNodeClass *node);
void __fastcall Planning_Unknown_616a50(TechnoClass *techno);   // 0x00616A50
extern bool unknown_flag_a76788;                // 0x00A76788 (a loop was closed once)
// Empties the list of nodes drawn on screen (0x00615BC0).
void Planning_Clear_Drawn();
// Settles every queued node and empties the queue (0x006146C0).
void Planning_Process_Queue();
// Clears the planning mode's flags and remembered nodes (0x00613E10).
void Planning_Reset();
// A size x size rectangle centred on (x, y) (0x006112D0).
Rect __fastcall Planning_Centered_Rect(int size, Point2D center);

// The coordinate an event points at ((-1, -1, -1) without one; 0x00610980).
CoordStruct __fastcall Planning_Event_Coord(EventClass const &event);

// A planned waypoint (0xB8 bytes, constructor 0x00610A80, destructor
// 0x00610AF0).
//   +0x00 DynamicVectorClass<PlanningMemberClass *> Members
//   +0x18 int (the event's +0x03 when made from an event)
//   +0x1C bool IsQueued (in unknown_list_00a76758)
//   +0x20 DynamicVectorClass<PlanningBranchClass *> Branches
//   +0x38 PlanningBranchClass Action
//   +0xB0, +0xB4 int (-1)
class PlanningNodeClass {
public:
    PlanningNodeClass(int unknown_18);                        // 0x00610A80
    ~PlanningNodeClass();                                     // 0x00610AF0
    PlanningNodeClass *Release(unsigned int flags);           // 0x0061A750
    void operator delete(void *pointer) { ::operator delete(pointer); }

    int Index_For(TechnoClass *techno);                       // 0x00610C30
    PlanningNodeClass *Previous(TechnoClass *techno);         // 0x00610C60
    PlanningNodeClass *Next(TechnoClass *techno);             // 0x00610CE0
    void Add_Member(TechnoClass *techno, EventClass const &event);   // 0x00610D60
    void Remove_Member(TechnoClass *techno);                  // 0x00610E70
    int Member_Index(TechnoClass *techno) const;              // 0x00611050
    TechnoClass *Member_Owner(int index) const;               // 0x00611090
    EventClass Member_Event(int index) const;                 // 0x006110A0
    EventClass Event_For(TechnoClass *techno) const;          // 0x006110D0
    bool Has_Member(TechnoClass *techno) const;               // 0x00611120
    HouseClass *House() const;                                // 0x00611170
    CoordStruct Coord() const;                                // 0x00611180
    Point2D Pixel() const;                                    // 0x006111C0
    int Is_At_Pixel(Point2D point) const;                      // 0x00611230
    int Is_At(CoordStruct coord) const;                        // 0x00611310
    ::Rect Rect() const;                                      // 0x00611360
    int Is_In_Loop();                                        // 0x006113F0
    void unknown_611440();                                    // 0x00611440
    PlanningMemberClass *Member_For(TechnoClass *techno) const;   // 0x00611470
    int Branch_Count() const;                                 // 0x006114C0
    bool Has_Branch_Members() const;                          // 0x006114D0
    int unknown_6114e0() const;                              // 0x006114E0
    TechnoClass *Branch_Owner(int index) const;               // 0x00611500
    TechnoClass *First_Counted_Owner() const;                 // 0x00611530
    PlanningBranchClass *Branch_At(int index) const;          // 0x00611560
    PlanningBranchClass *Branch_For(TechnoClass *techno) const;   // 0x00611570
    PlanningBranchClass *Own_Branch();                        // 0x006115C0
    CoordStruct Branch_Coord(int index) const;                // 0x006115D0
    CoordStruct Own_Branch_Coord() const;                     // 0x00611610
    Point2D Branch_Pixel(int index) const;                    // 0x00611640
    Point2D Own_Branch_Pixel() const;                         // 0x006116B0
    void Set_Queued();                                        // 0x00611710
    bool Is_Queued() const;                                   // 0x00611720
    void unknown_611730();                                    // 0x00611730
    void unknown_611770();                                    // 0x00611770
    int unknown_611a80(TechnoClass *techno);                  // 0x00611A80
    void Dump() const;                                        // 0x006118E0
    void unknown_611bd0(PlanningMemberClass *member);         // 0x00611BD0
    void unknown_611e20(PlanningMemberClass *member);         // 0x00611E20
    void unknown_611ee0();                                    // 0x00611EE0
    bool Is_Loop_Start(TechnoClass *techno);                  // 0x00611F60
    void unknown_611fa0(PlanningMemberClass *member);         // 0x00611FA0
    void unknown_611fd0();                                    // 0x00611FD0
    void unknown_612090();                                    // 0x00612090
    void unknown_6120c0();                                    // 0x006120C0
    void Draw_Marker(int color);                              // 0x006120F0
    // Outlines the grown marker three times, shrinking it by a pixel each time.
    void Draw_Outer_Outline(int color);                       // 0x00612300
    void Fill_Marker(int color);                              // 0x00612230
    void Draw_Marker_Outline(int color);                      // 0x00612420
    ::Rect Outer_Rect() const;                                // 0x00612B90
    ::Rect Outer_Rect2() const;                               // 0x00612C30
    int Color();                                              // 0x006125D0
    void unknown_619420();                                    // 0x00619420
    void unknown_619870();                                    // 0x00619870
    void Fill_Marker_Colored();                               // 0x00619BD0
    int Highlight_Color();                                    // 0x0061A060
    int Branch_Color(int index);                              // 0x006127E0
    int Loop_Color();                                         // 0x006129B0
    void unknown_612b50(bool all);                             // 0x00612B50
    void unknown_614aa0();                                    // 0x00614AA0

    // Clears the loop marks: +0xB4 and every branch's +0x74 (expanded inline
    // by PlanningTokenClass::unknown_613a80).
    void Clear_Loop_Marks()
    {
        unknown_b4 = -1;
        int count = Branches.Count();
        for (int i = 0; i < count; i++) {
            Branches[i]->unknown_74 = -1;
        }
        Branch.unknown_74 = -1;
    }

    DynamicVectorClass<PlanningMemberClass *> Members;        // +0x00
    int unknown_18;                                           // +0x18
    bool IsQueued;                                            // +0x1C
    DynamicVectorClass<PlanningBranchClass *> Branches;       // +0x20
    PlanningBranchClass Branch;                               // +0x38
    int unknown_b0;                                           // +0xB0
    int unknown_b4;                                           // +0xB4

    static DynamicVectorClass<PlanningNodeClass *> unknown_list_00a76758;   // 0x00A76758 (queued)
    static DynamicVectorClass<PlanningNodeClass *> unknown_list_00a76628;   // 0x00A76628
    static DynamicVectorClass<PlanningNodeClass *> unknown_list_00a766d8;   // 0x00A766D8
};

// A techno's planning token (0x9C bytes, constructor 0x00612CC0; the
// techno's +0x408, shared/techno.hpp's UnknownTechno408): its path of nodes,
// which may close into a loop of LoopLength nodes from LoopStart.
//   +0x00 TechnoClass *Owner, +0x04 DynamicVectorClass<PlanningNodeClass *>
//   Nodes, +0x1C bool, +0x1D EventClass, +0x8C int (the first node's index,
//   -1), +0x90 int LoopLength, +0x94 int LoopStart (-1), +0x98/+0x99 bool
class PlanningTokenClass {
public:
    PlanningTokenClass(TechnoClass *owner);                   // 0x00612CC0
    ~PlanningTokenClass();                                    // 0x00612D20
    void unknown_6144f0();                                    // 0x006144F0
    bool Reached(int slot) const;                             // 0x00613B40
    void unknown_612ec0();                                    // 0x00612EC0
    void Add_Node(PlanningNodeClass *node);                   // 0x00613BA0
    EventClass unknown_613330();                              // 0x00613330
    void unknown_613a80();                                    // 0x00613A80
    bool Has_Node(PlanningNodeClass *node);                   // 0x00613C60
    void unknown_613c80(PlanningNodeClass *node);             // 0x00613C80
    EventClass Event_At(int index);                           // 0x00613CA0
    EventClass Get_Event() const;                             // 0x00613D00
    int unknown_613d80() const;                               // 0x00613D80
    void unknown_613de0();                                    // 0x00613DE0

    // The node at index, wrapping into the loop past the end; 0 outside.
    PlanningNodeClass *Node_At(int index) const;             // 0x00613C00

    // The index of a node in the path, or -1 (expanded inline by
    // 0x00617A10 and 0x006164E0).
    int Node_Index(PlanningNodeClass *node) { return Nodes.ID(node); }

    // The last node of the path, or 0 (expanded inline by its callers).
    PlanningNodeClass *Last_Node() const
    {
        int index = Nodes.Count() - 1;
        if (index < 0) {
            return 0;
        }
        return Nodes[index];
    }

    TechnoClass *Owner;                                       // +0x00
    DynamicVectorClass<PlanningNodeClass *> Nodes;            // +0x04
    bool unknown_1c;                                          // +0x1C
    EventClass Event;                                         // +0x1D
    int unknown_8c;                                           // +0x8C
    int LoopLength;                                           // +0x90
    int LoopStart;                                            // +0x94
    bool unknown_98;                                          // +0x98
    bool unknown_99;                                          // +0x99

    static DynamicVectorClass<PlanningTokenClass *> unknown_list_00a76738;   // 0x00A76738
};

// The planning token of a techno (TechnoClass +0x408).
inline PlanningTokenClass *Planning_Token(TechnoClass *techno)
{
    return (PlanningTokenClass *)techno->unknown_6d1430();
}

// Nodes the planning mode remembers (0x00A7678C, 0x00A766F8, 0x00A766B0;
// cleared when that node is destroyed). Names are hypotheses.
extern PlanningNodeClass *unknown_node_a7678c;
extern PlanningNodeClass *unknown_node_a766f8;
extern PlanningNodeClass *unknown_node_a766b0;

// Adds every member of from to node, each with a copy of the event aimed at
// that member's techno (0x006167F0; PlanningNodeClass::Add_Member's body).
void __fastcall Planning_Copy_Members(PlanningNodeClass *node, PlanningNodeClass *from, EventClass event);

#endif

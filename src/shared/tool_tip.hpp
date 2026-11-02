// ToolTipManager and CCToolTip (ToolTip.cpp, unit 0x006EB2C0-0x006EC350;
// RTTI vtables 0x007AD934 ToolTipManager (6 slots), 0x007AF51C CCToolTip).
//
// The manager shows the text of a registered screen region once the mouse
// rests over it (a window timer, TIMER id 'TTIP' = 0x54544950). The regions
// (ToolTip, 0x1C bytes) are kept in a vector and in an ID index. The game
// owns one CCToolTip, the object at 0x008399B0.
//
// Layout (names are hypotheses):
//   +0x04  ToolTip *Current   (region under the mouse; 0 when none shows)
//   +0x08  HWND Window, +0x0C bool Enabled
//   +0x10  POINT Cursor (client coordinates of the last timer/mouse event)
//   +0x18  ToolTipRecord Record (the shown tip: area and text)
//   +0x228 int Delay (1000), +0x22C int SavedDelay, +0x230 int Duration (10000)
//   +0x234 DynamicVectorClass<ToolTip *> Tips (growth 10)
//   +0x24C IndexClass<int, ToolTip *> Index (keyed by ToolTip::ID)
//   size 0x260 (CCToolTip adds a flag at +0x260)
#ifndef RA2_SHARED_TOOL_TIP_HPP
#define RA2_SHARED_TOOL_TIP_HPP

#include "shared/unknown_globals.hpp"
#include "shared/win32_api.hpp"
#include "shared/rect.hpp"
#include "shared/vector_class.hpp"
#include "shared/ini_class.hpp"
#include "shared/string_table.hpp"
#include "shared/tag_rect.hpp"

// TOOL_TIP_UNIT (defined by the ToolTip.cpp unit before this header) declares the unit's own
// out-of-line members; other users keep the original declarations unchanged.




class ToolTip;

// The ID index of the tooltip manager: the last-hit check (0x006EC280) and
// the lazy-sort search (0x006EC2A0) are out-of-line members that the
// original keeps after their callers; the binary search is 0x006EC350.
struct ToolTipIndexNode {
    ToolTipIndexNode();                     // 0x006EC270 (empty; out of line)
#ifdef TOOL_TIP_UNIT
    bool operator==(ToolTipIndexNode const &other) const { return ID == other.ID; }
    bool operator<(ToolTipIndexNode const &other) const { return ID < other.ID; }
#endif
    unsigned int ID;
    ToolTip *Data;
};

class ToolTipIndex {
public:
    ToolTipIndex() : IndexTable(0), IndexCount(0), IndexSize(0), IsSorted(false), Archive(0) {}
    ~ToolTipIndex() { Clear(); }
    void Clear()
    {
        delete[] IndexTable;
        IndexTable = 0;
        IndexCount = 0;
        IndexSize = 0;
        IsSorted = false;
        Archive = 0;
    }
    bool Increase_Table_Size(int amount)
    {
        if (amount >= 0) {
            ToolTipIndexNode *table = new ToolTipIndexNode[IndexSize + amount];
            if (table != 0) {
                for (int index = 0; index < IndexCount; index++) {
                    table[index] = IndexTable[index];
                }
                delete[] IndexTable;
                IndexTable = table;
                IndexSize += amount;
                Archive = 0;
                return true;
            }
        }
        return false;
    }
    bool Add_Index(unsigned int const &id, ToolTip *const &data)
    {
        if (IndexCount + 1 > IndexSize) {
            if (!Increase_Table_Size(IndexSize == 0 ? 10 : IndexSize)) {
                return false;
            }
        }
        IndexTable[IndexCount].ID = id;
        IndexTable[IndexCount].Data = data;
        IndexCount++;
        IsSorted = false;
        return true;
    }
    bool Is_Present(unsigned int const &id) const
    {
        if (IndexCount == 0) {
            return false;
        }
        if (Is_Archive_Same(id)) {
            return true;
        }
        ToolTipIndexNode const *node = Search_For_Node(id);
        if (node != 0) {
            ((ToolTipIndex *)this)->Archive = node;
            return true;
        }
        return false;
    }
    ToolTip *const &operator[](unsigned int const &id) const
    {
        static ToolTip *x;
        if (Is_Present(id)) {
            return ((ToolTipIndexNode *)Archive)->Data;
        }
        return x;
    }
#ifdef TOOL_TIP_UNIT
    // Drops the node of id, moving the later nodes down (inline in
    // ToolTipManager::Remove 0x006EBA10; Tiberian Sun's IndexClass::Remove_Index).
    bool Remove_Index(unsigned int const &id)
    {
        ToolTipIndexNode const *node = Search_For_Node(id);
        if (node == 0) {
            return false;
        }
        int found = node - IndexTable;
        if (found != -1) {
            for (int index = found + 1; index < IndexCount; index++) {
                IndexTable[index - 1] = IndexTable[index];
            }
            IndexCount--;
            ToolTipIndexNode fake;
            fake.ID = 0;
            fake.Data = 0;
            IndexTable[IndexCount] = fake;
            Archive = 0;
            return true;
        }
        return false;
    }
#endif
    bool Is_Archive_Same(unsigned int const &id) const;                         // 0x006EC280
    ToolTipIndexNode const *Search_For_Node(unsigned int const &id) const;      // 0x006EC2A0
    static int __cdecl search_compfunc(void const *left, void const *right);    // 0x006EC320

    ToolTipIndexNode *IndexTable;       // +0x00
    int IndexCount;                     // +0x04
    int IndexSize;                      // +0x08
    bool IsSorted;                      // +0x0C
    ToolTipIndexNode const *Archive;    // +0x10
};

ToolTipIndexNode *__fastcall Binary_Search(ToolTipIndexNode *table, int count, ToolTipIndexNode const &target);   // 0x006EC350

// A registered help-text region (0x1C bytes).
class ToolTip {
public:
    ToolTip() : ID(0), Region(0, 0, 0, 0), Label(0), unknown_18(false) {}
    ~ToolTip() {}
    ToolTip(ToolTip const &other) : ID(other.ID), Region(other.Region), Label(other.Label), unknown_18(other.unknown_18) {}
#ifdef TOOL_TIP_UNIT
    unsigned int ID;                // +0x00 (unsigned as Tiberian Sun's ToolTip)
#else
    int ID;                         // +0x00
#endif
    Rect Region;                    // +0x04 screen area
    char const *Label;              // +0x14 string table label; 0 asks Get_Text(ID)
    bool unknown_18;                // +0x18
};

// The tip being shown: its area (4 words) and text.
struct ToolTipRecord {
    int unknown_00;
    int unknown_04;
    int unknown_08;
    int unknown_0c;
    wchar_t Text[256];              // +0x10
};

class ToolTipManager {
public:
    ToolTipManager(HWND window);                                        // 0x006EB2E0
    virtual ~ToolTipManager();                                          // slot 0 (0x006EBEF0 scalar deleting; body 0x006EB390)

    virtual bool Show(ToolTipRecord *record);                           // slot 1 (0x006EBD80; true)
    virtual void Hide(ToolTipRecord *record);                           // slot 2 (0x006EBD90; clears it)
    virtual void Refresh(bool update);                                  // slot 3 (0x006EBE60)
    virtual void Debug_Print(ToolTipRecord *record);                    // slot 4 (0x006EBE90)
    virtual wchar_t const *Get_Text(int id);                            // slot 5 (0x006EBEB0; none)

    void Enable(bool enable);                                           // 0x006EB480
    void Process_Message(MSG *message);                                 // 0x006EB4E0
    int Get_Delay() const;                                              // 0x006EB7F0
    void Set_Delay(int delay);                                          // 0x006EB800
    void Save_Delay();                                                  // 0x006EB810
    void Restore_Delay();                                               // 0x006EB820
    int Get_Duration() const;                                           // 0x006EB830
    void Set_Duration(int duration);                                    // 0x006EB840
    int Count() const;                                                  // 0x006EB850
    bool Add(ToolTip const &tip);                                       // 0x006EB860
    void Remove(unsigned int id);                                             // 0x006EBA10
    bool Update();                                                      // 0x006EBDB0
#ifdef TOOL_TIP_UNIT
    // The registered tip whose area contains the point, or 0 (0x006EBD10;
    // expanded in Process_Message).
    ToolTip *Find(POINT const *point);
    // The tip registered under id, copied to tooltip when that is not 0
    // (0x006EBBA0; expanded in Add; Tiberian Sun's Find).
    bool Find(unsigned int id, ToolTip *tooltip);
#else
    // The registered tip whose area contains the point, or 0 (an inline
    // member: expanded in Process_Message, out-of-line copy 0x006EBD10).
    ToolTip *Find(POINT const *point)
    {
        for (int index = 0; index < Tips.Count(); index++) {
            Rect const *region = &Tips[index]->Region;
            if (point->x >= region->X && point->x <= region->X + region->Width
                && point->y >= region->Y && point->y <= region->Y + region->Height) {
                return Tips[index];
            }
        }
        return 0;
    }
#endif
    void Hide_Current();                                                // 0x006EBEC0
    bool Is_Active() const;                                             // 0x006EBEE0

    ToolTip *Current;                       // +0x04
    HWND Window;                            // +0x08
    bool Enabled;                           // +0x0C
    POINT Cursor;                           // +0x10
    ToolTipRecord Record;                   // +0x18
    int Delay;                              // +0x228
    int SavedDelay;                         // +0x22C
    int Duration;                           // +0x230
    DynamicVectorClass<ToolTip *> Tips;     // +0x234
    ToolTipIndex Index;                     // +0x24C
};


// The screen layout the tip placement reads (the sidebar rectangle, the
// tactical rectangle and the layout flags; shared/sidebar.hpp declares the
// same objects field by field but drags in the radar headers).
extern Rect unknown_rect_839620;        // 0x00839620 sidebar X, Y, width, height
extern Rect unknown_rect_839630;        // 0x00839630 tactical X, Y, width, height
extern bool unknown_flag_8373c2;        // 0x008373C2

class CCToolTip : public ToolTipManager {
public:
#ifdef TOOL_TIP_DECLARE_CREATE
    CCToolTip(HWND window) : ToolTipManager(window), unknown_264(7) {}
#endif
#ifdef TOOL_TIP_DECLARE_CREATE
    virtual ~CCToolTip() {}
#else
    virtual ~CCToolTip();                                               // scalar deleting 0x00738420
#endif
    virtual bool Show(ToolTipRecord *record);                           // slot 1 (0x0046DFC0; places the tip)
    virtual void Hide(ToolTipRecord *record);                           // slot 2 (0x0046E1D0)
    virtual void Refresh(bool update);                                  // slot 3 (0x0046E230; sets +0x260)
    virtual void Debug_Print(ToolTipRecord *record);                    // slot 4 (0x0046E250; draws the tip)
    virtual wchar_t const *Get_Text(int id);                            // slot 5 (0x0046E470)

    bool unknown_260;                       // +0x260 (set by Refresh: the tip follows the sidebar)
#ifdef TOOL_TIP_DECLARE_CREATE
    int unknown_264;                        // +0x264 (constructor sets 7)
#endif
};

#endif

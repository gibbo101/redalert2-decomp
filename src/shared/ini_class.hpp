// INIClass: Westwood's INI-file database (sections of key=value entries).
//
// Names come from the executable's RTTI: INIClass (vtable 0x007A2B34, one
// slot, the scalar deleting destructor 0x004DEEF0), INIClass::INIEntry
// (vtable 0x007A3B9C), INIClass::INISection (0x007A3BA4),
// List<INIClass::INIEntry *> (0x007A3BAC), List<INIClass::INISection *>
// (0x0079AAEC), Node<INIClass::INISection *> (0x007A3BB4), GenericList
// (0x0079AAF4) and GenericNode (0x0079AAFC). Method names follow Westwood's
// INI vocabulary; each was checked against the behavior of the original code.
//
// Layout (all offsets observed in the original code):
//
//   INIClass (0x38 bytes)
//     +0x00 vtable
//     +0x04 SectionList   List<INISection *>, sections in file order
//     +0x20 SectionIndex  IndexClass<int, INISection *>, keyed by name CRC
//     +0x34 LineComments  comment lines that precede the first section
//
//   INISection (0x44 bytes)            INIEntry (0x28 bytes)
//     +0x00 Node (vtable, next, prev)    +0x00 Node (vtable, next, prev)
//     +0x0C Name                         +0x0C Key
//     +0x10 EntryList                    +0x10 Value
//     +0x2C EntryIndex                   +0x14 Comments (lines above the entry)
//     +0x40 Comments                     +0x18 CommentString (after ';')
//                                        +0x1C EqualsColumn
//                                        +0x20 ValueColumn
//                                        +0x24 CommentColumn
//
// The three columns record where the loaded line had its '=', its value and
// its ';' (tabs advance to the next multiple of 8; scanner 0x005106B0), so a
// save can reproduce the original alignment.
//
// Strings owned by sections, entries and comments are heap blocks from
// _strdup and are released with free().
//
// Names are looked up by CRCEngine (0x00493FC0) over the raw name bytes, so
// lookups are case sensitive. Both indexes are sorted lazily with qsort and
// searched with Binary_Search; the last hit is cached in Archive.
#ifndef RA2_SHARED_INI_CLASS_HPP
#define RA2_SHARED_INI_CLASS_HPP

#include "shared/crt_string.hpp"
#include "shared/crc_memory.hpp"
#include "shared/rect.hpp"
#include "shared/coord.hpp"

extern "C" unsigned int __cdecl strlen(char const *string);
extern "C" char *__cdecl strchr(char const *string, int character);
extern "C" char *__cdecl strncpy(char *destination, char const *source, unsigned int count);
extern "C" char *__cdecl _strdup(char const *string);
extern "C" void __cdecl free(void *block);
extern "C" void __cdecl qsort(void *base, unsigned int count, unsigned int width,
                              int(__cdecl *compare)(void const *, void const *));
extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);
extern "C" int __cdecl sscanf(char const *buffer, char const *format, ...);
extern "C" int __cdecl atoi(char const *string);
extern "C" int __cdecl tolower(int character);
extern "C" int __cdecl toupper(int character);
extern "C" void *__cdecl memset(void *destination, int value, unsigned int count);
#pragma intrinsic(strlen, memset)

#include "shared/wstring.hpp"

struct GUID;

void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *block);

// Removes leading and trailing whitespace (bytes <= ' ') in place (0x006EEF10).
char *__fastcall strtrim(char *buffer);

// CRC-32 accumulator (0x00493FC0 is operator()). The staging buffer collects
// a partial 32-bit word between calls.
class CRCEngine {
public:
    CRCEngine(long initial = 0) : CRC(initial), Index(0)
    {
        StagingBuffer.Composite = 0;
    }
    long operator()(void const *buffer, int length);
    void operator()(char value);
    void operator()(bool value);
    // Original Value writes Buffer[4] when called from a full-word append.
    // This transient +0x0C write is preserved; no larger storage extent claimed.
    // The value operation in CRC push/pull streams00494240/004942D0.
    // Pads only the partial word; CRC/Index remain unchanged.
    unsigned long Value()
    {
        if(Index!=0) {
        StagingBuffer.Buffer[Index]=(char)Index;
        for(unsigned int i=(unsigned int)Index+1;i<4;++i)
            StagingBuffer.Buffer[i]=StagingBuffer.Buffer[0];
        unsigned long word=StagingBuffer.Composite;
        return CRC_Memory_00494190(&word,4,CRC);
        }
        return CRC;
    }



    // This operation consumes a byte of an already partial word.
    void Append_Partial_Byte(char value)
    {
        StagingBuffer.Buffer[Index++]=value;
        if(Index==4) { CRC=Value(); Index=0; }
    }

    void const *Consume_Whole_Words(void const *cursor,unsigned int words,int &remaining)
    {
        while(words--) {
            CRC=CRC_Memory_00494190(cursor,4,CRC);
            cursor=(char const *)cursor+4;
            remaining-=4;
        }
        return cursor;
    }

private:
    long CRC;               // +0x00
    int Index;              // +0x04
    union {
        long Composite;
        char Buffer[4];
    } StagingBuffer;        // +0x08
};

// Doubly linked node with sentinel-terminated lists. A node is valid (part of
// a list) only when both links are set; the list's sentinels have one null
// link each.
class GenericNode {
public:
    GenericNode() : NextNode(0), PrevNode(0) {}
    virtual ~GenericNode() { Unlink(); }

    void Unlink()
    {
        if (Is_Valid()) {
            PrevNode->NextNode = NextNode;
            NextNode->PrevNode = PrevNode;
            PrevNode = 0;
            NextNode = 0;
        }
    }
    // Inserts node directly after this one.
    void Link(GenericNode *node)
    {
        node->Unlink();
        node->NextNode = NextNode;
        node->PrevNode = this;
        if (NextNode) {
            NextNode->PrevNode = node;
        }
        NextNode = node;
    }
    GenericNode *Next() const { return NextNode; }
    GenericNode *Prev() const { return PrevNode; }
    bool Is_Valid() const { return this != 0 && NextNode != 0 && PrevNode != 0; }

protected:
    GenericNode *NextNode;  // +0x04
    GenericNode *PrevNode;  // +0x08
};

class GenericList {
public:
#ifdef GENERIC_LIST_IMPLEMENT_CONSTRUCTOR
    GenericList(); // Kept out-of-line copy at 0x00490E80.
#else
    GenericList() { FirstNode.Link(&LastNode); }
#endif
    virtual ~GenericList()
    {
        while (FirstNode.Next()->Is_Valid()) {
            FirstNode.Next()->Unlink();
        }
    }
    GenericNode *First() const { return FirstNode.Next(); }
    GenericNode *Last() const { return LastNode.Prev(); }
    void Add_Tail(GenericNode *node) { LastNode.Prev()->Link(node); }

protected:
    GenericNode FirstNode;  // +0x04 head sentinel
    GenericNode LastNode;   // +0x10 tail sentinel
};

template<class T>
class Node : public GenericNode {
public:
    T Next() const { return (T)GenericNode::Next(); }
    T Prev() const { return (T)GenericNode::Prev(); }
    bool Is_Valid() const { return GenericNode::Is_Valid(); }
};

template<class T>
class List : public GenericList {
public:
#ifdef LIST_DECLARE_CONSTRUCTOR
    List();
#else
    List() {}
#endif
    T First() const { return (T)GenericList::First(); }
    T Last() const { return (T)GenericList::Last(); }
    // Deletes every member (each member's destructor unlinks it).
    void Delete()
    {
        while (First()->Is_Valid()) {
            delete First();
        }
    }
};

// Binary search of a sorted array of index records (explicit fastcall: array
// and count in registers).
template<class T>
T *__fastcall Binary_Search(T *array, int count, T const &target)
{
    int stride = count;
    while (stride > 0) {
        int half = stride / 2;
        T *middle = &array[half];
        if (target.ID < middle->ID) {
            stride = half;
        } else if (middle->ID == target.ID) {
            return middle;
        } else {
            array = middle + 1;
            stride = stride - half - 1;
        }
    }
    return 0;
}

// Sorted (ID, value) table with a one-entry lookup cache. Records are 8
// bytes: a 32-bit ID and a 32-bit value. The table is re-sorted lazily before
// the first lookup after an insertion.
template<class INDEX, class T>
class IndexClass {
public:
    IndexClass();
    ~IndexClass() { Clear(); }

    bool Add_Index(INDEX const &id, T const &data);
    bool Remove_Index(INDEX const &id);
    bool Is_Present(INDEX const &id) const;
    int Count() const { return IndexCount; }
    T const &operator[](INDEX const &id) const;
    void Clear()
    {
        delete[] IndexTable;
        IndexTable = 0;
        IndexCount = 0;
        IndexSize = 0;
        IsSorted = false;
        Archive = 0;
    }
    bool Increase_Table_Size(int amount);

    struct NodeElement {
        NodeElement() {}
        INDEX ID;
        T Data;
    };

private:
    NodeElement *IndexTable;        // +0x00
    int IndexCount;                 // +0x04
    int IndexSize;                  // +0x08
    bool IsSorted;                  // +0x0C
    NodeElement const *Archive;     // +0x10 last record found

    bool Is_Archive_Same(INDEX const &id) const;
    void Invalidate_Archive() { Archive = 0; }
    void Set_Archive(NodeElement const *node) { Archive = node; }
    NodeElement const *Search_For_Node(INDEX const &id) const;
    static int __cdecl search_compfunc(void const *left, void const *right);
};

#ifndef INDEX_DECLARE_CONSTRUCTOR
template<class INDEX, class T>
IndexClass<INDEX, T>::IndexClass() :
    IndexTable(0), IndexCount(0), IndexSize(0), IsSorted(false), Archive(0)
{
}

#endif

// Grows the table by amount records, copying the existing ones.
template<class INDEX, class T>
bool IndexClass<INDEX, T>::Increase_Table_Size(int amount)
{
    if (amount >= 0) {
        NodeElement *table = new NodeElement[IndexSize + amount];
        if (table != 0) {
            for (int index = 0; index < IndexCount; index++) {
                table[index] = IndexTable[index];
            }
            delete[] IndexTable;
            IndexTable = table;
            IndexSize += amount;
            Invalidate_Archive();
            return true;
        }
    }
    return false;
}

// Appends a record (growing by the current size, or 10 when empty) and marks
// the table unsorted. Duplicate IDs are not checked.
template<class INDEX, class T>
bool IndexClass<INDEX, T>::Add_Index(INDEX const &id, T const &data)
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

// Removes the record with this ID, closing the gap.
template<class INDEX, class T>
bool IndexClass<INDEX, T>::Remove_Index(INDEX const &id)
{
    int found_index = -1;
    NodeElement const *node = Search_For_Node(id);
    if (node != 0) {
        found_index = node - IndexTable;
    }
    if (found_index != -1) {
        for (int index = found_index + 1; index < IndexCount; index++) {
            IndexTable[index - 1] = IndexTable[index];
        }
        IndexCount--;
        NodeElement empty;
        empty.ID = 0;
        empty.Data = 0;
        IndexTable[IndexCount] = empty;
        Invalidate_Archive();
        return true;
    }
    return false;
}

// True when a record with this ID exists; a hit becomes the cached record.
template<class INDEX, class T>
bool IndexClass<INDEX, T>::Is_Present(INDEX const &id) const
{
    if (IndexCount == 0) {
        return false;
    }
    if (Is_Archive_Same(id)) {
        return true;
    }
    NodeElement const *node = Search_For_Node(id);
    if (node != 0) {
        ((IndexClass<INDEX, T> *)this)->Set_Archive(node);
        return true;
    }
    return false;
}

// Value stored for this ID, or a shared default (zero) value when missing.
template<class INDEX, class T>
T const &IndexClass<INDEX, T>::operator[](INDEX const &id) const
{
    static T x;
    if (Is_Present(id)) {
        return Archive->Data;
    }
    return x;
}

template<class INDEX, class T>
bool IndexClass<INDEX, T>::Is_Archive_Same(INDEX const &id) const
{
    if (Archive != 0 && Archive->ID == id) {
        return true;
    }
    return false;
}

// Sorts the table if needed, then binary searches it for the ID.
template<class INDEX, class T>
typename IndexClass<INDEX, T>::NodeElement const *IndexClass<INDEX, T>::Search_For_Node(INDEX const &id) const
{
    if (IndexCount == 0) {
        return 0;
    }
    if (!IsSorted) {
        qsort(&IndexTable[0], IndexCount, sizeof(IndexTable[0]), search_compfunc);
        ((IndexClass<INDEX, T> *)this)->Invalidate_Archive();
        ((IndexClass<INDEX, T> *)this)->IsSorted = true;
    }
    NodeElement node;
    node.ID = id;
    return Binary_Search(IndexTable, IndexCount, node);
}

// qsort comparator: orders records by ID (signed).
template<class INDEX, class T>
int __cdecl IndexClass<INDEX, T>::search_compfunc(void const *left, void const *right)
{
    if (*(INDEX const *)left == *(INDEX const *)right) {
        return 0;
    }
    if (*(INDEX const *)left < *(INDEX const *)right) {
        return -1;
    }
    return 1;
}

#include "shared/file_straw.hpp"
#include "shared/file_pipe.hpp"
#include "shared/cache_straw.hpp"

// Reads one line (through LF, CR dropped, at most length - 1 bytes kept) and
// sets eof when the source is exhausted; returns the kept length (0x00639670).
int __fastcall Read_Line(Straw &file, char *buffer, int length, bool &eof);

// Value types read and written by the INIClass typed accessors. Field names
// are hypotheses; only the layouts (consecutive 32-bit members) are observed.

struct INIRect {
    int X;          // +0x00
    int Y;          // +0x04
    int Width;      // +0x08
    int Height;     // +0x0C
};

struct INIPoint2D {
    int X;          // +0x00
    int Y;          // +0x04
};

// Every caller of Get_Point 0x0050F670 loads both returned members before
// storing either: the returned point is converted into the game's Point2D.
// BuildingTypeClass::Read_INI converts 0x0050FA40's result the same way into
// its CoordStruct offsets (TargetCoordOffset=, ExitCoord=).
inline Point2D::Point2D(INIPoint2D const &point) : X(point.X), Y(point.Y) {}

struct INIPoint3D {
    int X;          // +0x00
    int Y;          // +0x04
    int Z;          // +0x08
};

inline CoordStruct::CoordStruct(INIPoint3D const &point) : X(point.X), Y(point.Y), Z(point.Z) {}

// Value initialization and serialized-state restoration of the particle-system direction.
class NoInitClass;
struct INIVector3 {
    INIVector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
    INIVector3(NoInitClass const &) {} // preserve the vector loaded from a stream
    float X;        // +0x00
    float Y;        // +0x04
    float Z;        // +0x08
};

class INIClass {
public:
    // Comment line kept for re-saving: a heap string and the next line.
    struct INIComment {
        INIComment() : Value(0), Next(0) {}
        char *Value;
        INIComment *Next;
    };

    struct INIEntry : public Node<INIEntry *> {
        INIEntry(char *key, char *value, INIComment *comments, char *comment_string,
                 int comment_column, int equals_column, int value_column);
        virtual ~INIEntry();

        // Index key: CRC of the key text.
        int Index_ID() const { return CRCEngine()(Key, strlen(Key)); }

        char *Key;                  // +0x0C
        char *Value;                // +0x10
        INIComment *Comments;       // +0x14
        char *CommentString;        // +0x18
        int EqualsColumn;           // +0x1C
        int ValueColumn;            // +0x20
        int CommentColumn;          // +0x24
    };

    struct INISection : public Node<INISection *> {
        INISection(char *name, INIComment *comments = 0) : Name(name), Comments(comments) {}
        virtual ~INISection();

        // Index key: CRC of the section name.
        int Index_ID() const { return CRCEngine()(Name, strlen(Name)); }

        // Entry with this key, or null (also for a null key). The CRC is
        // held as an int here (one temporary for both lookups), unlike
        // INIClass::Find_Section's long; both forms are needed for exact code.
        INIEntry *Find_Entry(char const *entry) const
        {
            if (entry != 0) {
                int crc = CRCEngine()(entry, strlen(entry));
                if (EntryIndex.Is_Present(crc)) {
                    return EntryIndex[crc];
                }
            }
            return 0;
        }

        char *Name;                                 // +0x0C
        List<INIEntry *> EntryList;                 // +0x10
        IndexClass<int, INIEntry *> EntryIndex;     // +0x2C
        INIComment *Comments;                       // +0x40
    };

    // Inline (MapSelect::Load 0x005B0030 constructs a local INIClass: the
    // list constructor 0x00490E80 is called, LineComments cleared).
    INIClass() : LineComments(0) {}
    virtual ~INIClass();

    // Load(Straw &) 0x0050BC30 and Save(Pipe &) 0x0050C620 are not recovered
    // yet; their return types are inferred from the FileClass wrappers.
    bool Clear(char const *section = 0, char const *entry = 0);
    int Load(FileClass &file, bool keep_comments);
    int Load(Straw &file, bool keep_comments);
    int Save(FileClass &file) const;
    int Save(Pipe &pipe) const;

    INISection *Find_Section(char const *section) const;
    // Inline Wstring form (PlayerProfile::Load_Default 0x00738670 spends one more inline site here).
    INISection *Find_Section(Wstring const &section) const { return Find_Section(section.Peek_Buffer()); }
    int Section_Count() const;
    int Entry_Count(char const *section) const;
    INIEntry *Find_Entry(char const *section, char const *entry) const;
    // Westwood's Is_Present: the section (or the entry in it) exists.
    bool Is_Present(char const *section, char const *entry = 0) const
    {
        if (entry == 0) {
            return Find_Section(section) != 0;
        }
        return Find_Entry(section, entry) != 0;
    }
    int Entry_Count(Wstring const &section) const;
    char const *Get_Entry(char const *section, int index) const;
    Wstring Get_Entry(Wstring const &section, int index) const;

    bool Put_Int(char const *section, char const *entry, int number, int format = 0);
    bool Put_Int(Wstring const &section, Wstring const &entry, int number, int format = 0);
    int Get_Int(char const *section, char const *entry, int defvalue = 0) const;
    int Get_Int(Wstring const &section, Wstring const &entry, int defvalue = 0) const;

    bool Put_String(char const *section, char const *entry, char const *string);
    bool Put_String(Wstring const &section, Wstring const &entry, Wstring const &string);
    bool Put_Rect(char const *section, char const *entry, INIRect const &value);
    bool Put_Rect(Wstring const &section, Wstring const &entry, INIRect const &value);
    bool Put_Hex(char const *section, char const *entry, int number);
    bool Put_Hex(Wstring const &section, Wstring const &entry, int number);
    bool Put_Double(char const *section, char const *entry, double number);
    bool Put_Double(Wstring const &section, Wstring const &entry, double number);
    bool Put_Bool(char const *section, char const *entry, bool value);
    bool Put_Bool(Wstring const &section, Wstring const &entry, bool value);
    bool Put_Point(char const *section, char const *entry, INIPoint2D const &value);
    bool Put_Point(Wstring const &section, Wstring const &entry, INIPoint2D const &value);
    bool Put_Point(char const *section, char const *entry, INIPoint3D const &value);
    bool Put_Point(Wstring const &section, Wstring const &entry, INIPoint3D const &value);
    bool Put_Vector(char const *section, char const *entry, INIVector3 const &value);
    bool Put_Vector(Wstring const &section, Wstring const &entry, INIVector3 const &value);
    bool Put_Time(char const *section, char const *entry, int ticks);
    int Get_Hex(char const *section, char const *entry, int defvalue = 0) const;
    double Get_Double(char const *section, char const *entry, double defvalue = 0.0) const;
    // A class ID written as text (0x0050DA00).
    GUID Get_UUID(char const *section, char const *entry, GUID defvalue) const;
    bool Get_Bool(char const *section, char const *entry, bool defvalue = false) const;
    INIRect Get_Rect(char const *section, char const *entry, INIRect const &defvalue) const;
    INIRect Get_Rect(Wstring const &section, Wstring const &entry, INIRect const &defvalue) const;
    // 0x0050F670: returns a Point2D (through a hidden pointer: Point2D has
    // constructors).
    INIPoint2D Get_Point(char const *section, char const *entry, Point2D const &defvalue) const;
    INIPoint2D Get_Point(Wstring const &section, Wstring const &entry, Point2D const &defvalue) const;  // 0x0050F800 (default a Point2D like the char overload: Create_Anim_Item 0x004DF350)
    INIPoint3D Get_Point(char const *section, char const *entry, INIPoint3D const &defvalue) const;
    INIPoint3D Get_Point(Wstring const &section, Wstring const &entry, INIPoint3D const &defvalue) const;
    INIVector3 Get_Vector(char const *section, char const *entry, INIVector3 const &defvalue) const;
    INIVector3 Get_Vector(Wstring const &section, Wstring const &entry, INIVector3 const &defvalue) const;
    int Get_String(char const *section, char const *entry, char const *defvalue, char *buffer, int size) const;
    int Get_String(Wstring const &section, Wstring const &entry, Wstring const &defvalue, Wstring &result) const;
    // A wide string with a wide default (0x0050EDF0; name hypothesis).
    int Get_Unicode(char const *section, char const *entry, unsigned short const *defvalue, unsigned short *buffer, int size) const;
    bool Put_Unicode(char const *section, char const *entry, unsigned short const *string);   // 0x0050ECF0 (name hypothesis)
    // A binary block stored uuencoded across the entries of a section;
    // returns the decoded length (0x0050D0F0 / 0x0050CFC0).
    int Get_UUBlock(char const *section, void *block, int length) const;
    bool Put_UUBlock(char const *section, void const *block, int length);

    // Line helpers used by Load (explicit fastcall, like the rest of the
    // game's non-member code).
    static char *__fastcall Locate_Line_Comment(char *line, int &equals_column, int &value_column,
                                                int &comment_column);
    static void __fastcall Strip_Comments(char *buffer);
    static bool __fastcall Is_Section_Header(char const *line);

private:
    List<INISection *> SectionList;             // +0x04
    IndexClass<int, INISection *> SectionIndex; // +0x20
    INIComment *LineComments;                   // +0x34
};

#endif

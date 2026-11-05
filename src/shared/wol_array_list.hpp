// Real 12-byte WOL list template; source operations remain exact-target derived.
#ifndef RA2_WOL_ARRAY_LIST_HPP
#define RA2_WOL_ARRAY_LIST_HPP
#include "shared/wstring.hpp"
#include "shared/crt_memory.hpp"
void *__cdecl operator new(unsigned int,void *);
template<class T> class WolArrayList {
public:
    WolArrayList() : Count(0), Capacity(0), Items(0) {}
    ~WolArrayList() {
        for (int i = 0; i < Count; ++i) (Items+i)->~T();
        Count = 0;
        operator delete(Items);
    }
    void Clear() {
        for(int i=0;i<Count;++i) (Items+i)->~T();
        Count=0;
    }
    int Count;
    int Capacity;
    T *Items;
    // Copies and removes the last string (the published ArrayList operation).
    char Remove_Tail(T &text) {
        int index=Count-1;
        char found=Get(text,index);
        if(found==0) return 0;
        return Remove(index);
    }
#ifdef RA2_WOL_ARRAY_LIST_REMOVE_HEAD
    // Copies and removes the first string (the published ArrayList operation; Service_Buddy_Find_Queue 0x00756610).
    char Remove_Head(T &text) {
        int index=0;
        char found=Get(text,index);
        if(found==0) return 0;
        return Remove(index);
    }
#endif
    bool Grow_00768320();
    // wlib growVector/shrinkVector kept out of line for other element types (explicit specializations; ownrdraw.cpp's
    // lists 0x00602360, 0x00602940, 0x006029D0 and 0x006023F0, 0x00602480).
    bool Grow_Vector();
    bool Shrink_Vector();
    // wlib clear() kept out of line (explicit specializations; ownrdraw.cpp's 0x00601490).
    void Clear_Vector();
#ifdef RA2_WOL_ARRAY_LIST_COPY
    // wlib ArrayList(ArrayList &other) and operator= with the out-of-line get and add (wonline.cpp's by-value sound lists,
    // 0x00743720; guarded like RA2_WOL_ARRAY_LIST_ASSIGN).
    WolArrayList(WolArrayList &other) : Count(0), Capacity(0), Items(0) { *this = other; }
    WolArrayList &operator=(WolArrayList &other) {
        T node;
        Clear();
        for (int i = 0; i < other.Count; ++i) {
            other.Get_007662c0(node, i);
            Insert(node, Count);
        }
        return *this;
    }
#endif
#ifdef RA2_WOL_ARRAY_LIST_ASSIGN
    // wlib ArrayList(ArrayList &other) and operator= (ownrdraw.cpp's 0x006025A0 expands both; guarded: only the
    // ownrdraw.cpp population, whose header-statics source defines the macro, declares them).
    // wlib ArrayList::add(item, index) with the out-of-line growVector.
    char Add_Vector(T const &item, int index) {
        if (index > Count) index = Count;
        if (index >= Capacity) Grow_Vector();
        if (Count >= Capacity) Grow_Vector();
        if (index < Count) memmove(Items + index + 1, Items + index, (Count - index) * sizeof(T));
        new (Items + index) T(item);
        ++Count;
        return 1;
    }
    WolArrayList(WolArrayList const &other) : Count(0), Capacity(0), Items(0) { *this = other; }
    WolArrayList &operator=(WolArrayList const &other) {
        T node;
        Clear();
        for (int i = 0; i < other.Count; ++i) {
            if (i >= 0 && i < other.Count) node = other.Items[i];
            Add_Vector(node, Count);
        }
        return *this;
    }
#endif
    bool Grow() {
        if (Count < Capacity) return false;
        int capacity = Count * 2;
        if (capacity < 10) capacity = 10;
        T *items = (T *)operator new(capacity * sizeof(T));
        memset(items, 0, capacity * sizeof(T));
        if (Items) memcpy(items, Items, Count * sizeof(T));
        operator delete(Items);
        Items = items;
        Capacity = capacity;
        return true;
    }
    bool Shrink_00767b20();
    bool Remove_007661f0(int index);
    bool Remove(int index) {
        if(Count==0) return false;
        if(index<0) index=0;
        if(index>=Count) index=Count-1;
        (Items+index)->~T();
        memmove(Items+index,Items+index+1,(Count-index-1)*sizeof(T));
        --Count;
        if(Count*3<=Capacity) Shrink();
        return true;
    }

    bool Remove_Inline(int index) {
        if(Count==0) return false;
        if(index<0) index=0;
        if(index>=Count) index=Count-1;
        (Items+index)->~T();
        memmove(Items+index,Items+index+1,(Count-index-1)*sizeof(T));
        --Count;
        if(Count*3<=Capacity) Shrink_00767b20();
        return true;
    }
    bool Shrink() {
        if (Count * 3 > Capacity) return false;
        int capacity = Capacity / 2;
        if (capacity < 10) capacity = 10;
        if (capacity >= Capacity) return false;
        T *items = (T *)operator new(capacity * sizeof(T));
        if (Items) memcpy(items, Items, Count * sizeof(T));
        operator delete(Items);
        Items = items;
        Capacity = capacity;
        return true;
    }
    bool Get(T &text, int index) {
        if (index >= 0 && index < Count) { text = Items[index]; return true; }
        return false;
    }
#ifdef RA2_WOL_ARRAY_LIST_HEAD_INSERT
    char Add_Head(T &text) { return Add_At(text,0); }
#endif
    bool Insert(T const &text, int index); // original complete method 0x007679c0
    bool Get_007662c0(T &text, int index); // out of line in wonline.cpp (accepted unowned 0x007662C0)
    void Add(T const &text) {
        int index = Count;
        if (index > Count) index = Count;
        if (index >= Capacity) Grow_00768320();
        if (Count >= Capacity) Grow_00768320();
        if (index < Count) memmove(Items + index + 1, Items + index, (Count - index) * sizeof(T));
        new (Items + index) T(text);
        ++Count;
    }
    // Published ArrayList::add and addTail operations, with the actual element reference.
    char Add_At(T &text,int index) {
        if(index>Count) index=Count;
        if(index>=Capacity) Grow();
        if(Count>=Capacity) Grow();
        if(index<Count) memmove(Items+index+1,Items+index,(Count-index)*sizeof(T));
        new(Items+index) T(text);
        ++Count;
        return 1;
    }
    int Length() const { return Count; }
    char Add_Tail(T &text) { return Add_At(text,Length()); }
    void Prepend(T const &text) {
        int index = 0;
        if (index > Count) index = Count;
        if (index >= Capacity) Grow_00768320();
        if (Count >= Capacity) Grow_00768320();
        if (index < Count) memmove(Items + index + 1, Items + index, (Count - index) * sizeof(T));
        new (Items + index) T(text);
        ++Count;
    }

};
typedef WolArrayList<Wstring> WolStringArray;
#endif

// ReferenceCounted and rc_ptr<T>: the intrusive reference counting the
// World Domination Tour classes use (RTTI ReferenceCounted, vtable
// 0x007A8D14; rc_ptr has no RTTI record, its vtables are per T, e.g.
// 0x007AF1A4 rc_ptr<WDTState>).
//
// ReferenceCounted layout: +0x00 vptr, +0x04 int RefCount (0 when built).
// Slot 0 the scalar deleting destructor (0x00639750), slot 1 0x00639740
// (returns false; meaning unknown), slot 2 Release (0x00639720: deletes
// the object when the count drops to 0).
//
// rc_ptr_base (vtable 0x007A8D0C) holds the pointer at +0x04; its
// constructors (0x006394E0 empty, 0x006394F0 from a pointer, taking a
// reference), destructor (0x00639510, releases) and assignment
// (0x00639530) are out of line; rc_ptr<T> adds only the typed access and
// its own vtable (the destructor is expanded inline).
//
// Names: ReferenceCounted and rc_ptr come from the RTTI names
// (VectorClass<rc_ptr<...>>); rc_ptr_base, Set, Release and the slot 1
// name are hypotheses.
#ifndef RA2_SHARED_REFERENCE_COUNTED_HPP
#define RA2_SHARED_REFERENCE_COUNTED_HPP

class ReferenceCounted {
public:
    ReferenceCounted() : RefCount(0) {}
    virtual ~ReferenceCounted();                    // 0x00639710
    virtual bool unknown_slot1(int arg);            // 0x00639740
    virtual void Release();                         // 0x00639720

    int RefCount;                                   // +0x04
};

class rc_ptr_base {
public:
    rc_ptr_base();                                  // 0x006394E0
    rc_ptr_base(ReferenceCounted *pointer);         // 0x006394F0
    virtual ~rc_ptr_base();                         // 0x00639510
    void Set(ReferenceCounted *pointer);            // 0x00639530

    ReferenceCounted *Pointer;                      // +0x04
};

template<class T>
class rc_ptr : public rc_ptr_base {
public:
    rc_ptr() {}
    rc_ptr(T *pointer) { Set(pointer); }
    rc_ptr(rc_ptr<T> const &other) { Set(other.Pointer); }
    // From an rc_ptr of another type (a derived class: rc_ptr<GameOption> from
    // rc_ptr<FlagGameOption>; out of line at 0x00728300). Not explicit: the last Add of
    // Conflict::Init_Options 0x00727480 converts implicitly (lea of the temporary).
    rc_ptr(rc_ptr_base const &other) { Set(other.Pointer); }
    virtual ~rc_ptr() {}

    rc_ptr<T> &operator=(rc_ptr<T> const &other)
    {
        Set(other.Pointer);
        return *this;
    }
    bool operator==(rc_ptr<T> const &other) const { return Pointer == other.Pointer; }
    bool operator!=(rc_ptr<T> const &other) const { return Pointer != other.Pointer; }

    T *Get() const { return (T *)Pointer; }
    T *operator->() const { return (T *)Pointer; }
};

#endif

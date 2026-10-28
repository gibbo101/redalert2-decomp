// EventClass and the outgoing event queue (proposal from the Sidebar unit).
// An event is 0x6F packed bytes: +0x00 type, +0x02 house index, +0x03 frame,
// then the payload (+0x07, +0x0B, +0x0F, +0x13 cell). OutList (0x00A32338)
// is a 128-entry queue: Count, Head, Tail, the events (0x00A32344) and their
// timeGetTime() stamps (0x00A35AC4).
#ifndef RA2_SHARED_EVENT_HPP
#define RA2_SHARED_EVENT_HPP

#include "shared/coord.hpp"
#include "shared/vector_class.hpp"
#include "shared/target.hpp"
#include "shared/cd_timer.hpp"
#include "shared/debug_printf.hpp"

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

#pragma pack(push, 1)
class EventClass {
public:
    // An empty event (type 0): the outgoing queue's 128 entries (0x004D46D0)
    // and the planning copies (Planning.cpp) are built this way.
    EventClass() { Type = 0; }
    // An event with only a house and a type (0x004B5FD0; Planning.cpp).
    EventClass(int house, int type);
    // A production event (type 0x10 from the strips; payload kind, id, naval).
    EventClass(int house, int type, int rtti, int id, int naval);                         // 0x004B6280
    // The same with a cell (type 0x0B: place).
    EventClass(int house, int type, int rtti, int id, int naval, Cell const &cell);  // 0x004B63F0

    unsigned char Type;         // +0x00
    unsigned char unknown_01;   // +0x01
    unsigned char House;        // +0x02 (0xFF: none)
    unsigned long Frame;        // +0x03 the frame it was queued
    // +0x07 the payload; each constructor fills its own shape. The
    // three-long-and-cell shape of 0x004B6370 and 0x004B63F0 is written
    // through these members (writing it through LongAt schedules the stores
    // differently).
    union {
        unsigned char Bytes[0x6F - 0x07];
        struct {
            long Long1;             // +0x07
            long Long2;             // +0x0B
            long Long3;             // +0x0F
            struct { short X, Y; } Location;   // +0x13 a cell (Cell has constructors: not a union member)
        } LongsCell;
    } Data;

    // The payload field at a packed offset of the event (offsets as in the
    // constructors: 0x07 and up).
    TargetClass &TargetAt(int offset) { return *(TargetClass *)&Data.Bytes[offset - 0x07]; }
    unsigned char &ByteAt(int offset) { return Data.Bytes[offset - 0x07]; }
    short &ShortAt(int offset) { return *(short *)&Data.Bytes[offset - 0x07]; }
    long &LongAt(int offset) { return *(long *)&Data.Bytes[offset - 0x07]; }
    Cell &CellAt(int offset) { return *(Cell *)&Data.Bytes[offset - 0x07]; }

    // An event about an object (0x004B5EF0; BuildingClass slot 77 queues
    // type 0x16 for itself).
    EventClass(int house, int type, TargetClass target);
    // An event about two objects (0x004B6090; BuildingClass slot 78 queues
    // type 0x1E for itself and the target).
    EventClass(int house, int type, TargetClass target1, TargetClass target2);
    // An event with a long and a cell (0x004B62F0; fills +0x0B with -1 and +0x0F with 0).
    EventClass(int house, int type, long a, Cell const &cell);
    // Type 5 (0x004B61F0): like type 4 with two more longs.
    EventClass(int house, TargetClass whom, unsigned char mission, TargetClass target, TargetClass destination, long a, long b);
    // Type 0x18 (0x004B5EB0): one long.
    EventClass(int house, long a);
    // Type 4 (0x004B6170): a target, a mission byte and three more targets.
    EventClass(int house, TargetClass whom, unsigned char mission, TargetClass target, TargetClass destination, TargetClass follow);
    // The same with two longs (0x004B6370; +0x0F is 0).
    EventClass(int house, int type, int a, int b, Cell const &cell);
};
#pragma pack(pop)

// Event type names (0x007D65CC; used by the "Adding event %s" trace).
extern char const *EventNames[];

// The event sequence number within the current frame (0x004B5E80; 0 on the first call of a frame).
unsigned char Event_Sequence();

template <class T, int size>
class QueueClass {
public:
    bool Add(T const &q)
    {
        if (Count < size) {
            Array[Tail] = q;
            Timings[Tail] = timeGetTime();
            Tail = (Tail + 1) & (size - 1);
            Count++;
            return true;
        }
        return false;
    }

    int Count;
    int Head;
    int Tail;
    T Array[size];
    int Timings[size];
};

extern QueueClass<EventClass, 128> OutList;     // 0x00A32338

#endif

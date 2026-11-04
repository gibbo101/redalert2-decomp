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

class SpecialClass;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
class IPXAddressClass;

#pragma pack(push, 1)
class EventClass {
public:
    // An empty event (type 0): the outgoing queue's 128 entries (0x004D46D0)
    // and the planning copies (Planning.cpp) are built this way.
    EventClass() { Type = 0; }
    // An event with only a house and a type (0x004B5FD0; Planning.cpp; the
    // type is a byte: Queue_Exit pushes a byte local).
    EventClass(int house, unsigned char type);
    // A production event (type 0x10 from the strips; payload kind, id, naval).
    EventClass(int house, int type, int rtti, int id, int naval);                         // 0x004B6280
    // The same with a cell (type 0x0B: place).
    EventClass(int house, int type, int rtti, int id, int naval, Cell const &cell);  // 0x004B63F0

    unsigned char Type;         // +0x00
    unsigned char IsExecuted : 1;   // +0x01 bit 0: executed (Red Alert's IsExecuted)
    unsigned char unknown_01 : 7;
    char House;                 // +0x02 (0xFF: none)
    long Frame;                 // +0x03 the frame it was queued or executes (signed: Clean_DoList compares with jle)
    // +0x07 the payload; each constructor fills its own shape. The
    // three-long-and-cell shape of 0x004B6370 and 0x004B63F0 is written
    // through these members (writing it through LongAt schedules the stores
    // differently).
    union {
        unsigned char Bytes[0x6F - 0x07];
        struct {
            xTargetClass Whom;       // +0x07
            unsigned char Mission;        // +0x0C
            xTargetClass Target;     // +0x0D
            xTargetClass Destination;// +0x12
            long Speed;                   // +0x17
            long MaxSpeed;                // +0x1B
        } MegaMissionF;
        struct {
            long Long1;             // +0x07
            long Long2;             // +0x0B
            long Long3;             // +0x0F
            struct { short X, Y; } Location;   // +0x13 a cell (Cell has constructors: not a union member)
        } LongsCell;
        // TIMING (type 0x20): the new timing values (Red Alert's TimingEventType).
        struct {
            unsigned short DesiredFrameRate;    // +0x07
            unsigned short MaxAhead;            // +0x09
            unsigned char FrameSendRate;        // +0x0B
        } Timing;
        // PROCESS_TIME (type 0x21): the sender's average frame time.
        struct {
            unsigned short AverageTicks;        // +0x07
        } ProcessTime;
    } Data;

    // The payload field at a packed offset of the event (offsets as in the
    // constructors: 0x07 and up).
    TargetClass &TargetAt(int offset) { return *(TargetClass *)&Data.Bytes[offset - 0x07]; }
    unsigned char &ByteAt(int offset) { return Data.Bytes[offset - 0x07]; }
    short &ShortAt(int offset) { return *(short *)&Data.Bytes[offset - 0x07]; }
    long &LongAt(int offset) { return *(long *)&Data.Bytes[offset - 0x07]; }
    Cell &CellAt(int offset) { return *(Cell *)&Data.Bytes[offset - 0x07]; }
    SpecialClass &SpecialAt(int offset) { return *(SpecialClass *)&Data.Bytes[offset - 0x07]; }

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
    // Type 0x18 (SPECIAL, 0x004B5EB0): the game options word (Red Alert's
    // EventClass(SpecialClass)).
    EventClass(int house, SpecialClass data);
    // Type and a four-byte payload (0x004B6030; the type is a byte).
    EventClass(int house, int type, unsigned long a);
    // Type 4 (0x004B6170): a target, a mission byte and three more targets.
    EventClass(int house, TargetClass whom, unsigned char mission, TargetClass target, TargetClass destination, TargetClass follow);
    // ADDRESSCHANGE (type 0x29, 0x004B6560): the first four node bytes of an address
    // (the IP of a UDP address) at +0x08 and a byte at +0x07.
    EventClass(int house, IPXAddressClass *address, unsigned char unknown);
    // The same with two longs (0x004B6370; +0x0F is 0).
    EventClass(int house, int type, int a, int b, Cell const &cell);
    // The cell at +0x07 (0x004B5F60; TibSun's SellCell shape).
    EventClass(int house, unsigned char type, Cell const &cell);
    // A long at +0x07 and the cell at +0x0B (0x004B6470).
    EventClass(int house, unsigned char type, int id, Cell const &cell);
    // Two longs at +0x07 and +0x0B (0x004B64F0).
    EventClass(int house, unsigned char type, int rtti, int id);
    // ANIMATION (type 0x14, 0x004B6110): anim type, owner and the coordinate's X and Y.
    EventClass(int house, int anim, int owner, CoordStruct const &coord);

    // Carries out the event (0x004B65C0; Red Alert's Execute).
    void Execute();
};
#pragma pack(pop)

// Event type names (0x007D65CC; used by the "Adding event %s" trace).
extern char const *EventNames[];

// The event sequence number within the current frame (0x004B5E80; 0 on the first call of a frame).
unsigned char Event_Sequence();

template <class T, int size>
class QueueClass {
public:
    // Empty queue (Red Alert's QUEUE.H: the constructor calls Init); the globals unit at
    // 0x004D2BA0 builds OutList, DoList and the 256-entry queue 0x00A35F30 this way.
    QueueClass() { Init(); }
    void Init()
    {
        Count = 0;
        Head = 0;
        Tail = 0;
    }
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
#ifdef RA2_QUEUE_STATICS
    // Appends q with a given time stamp (Add_Compressed_Events 0x00627B60 moves an OutList event
    // into DoList with its OutList stamp). Declared only for Queue.CPP (RA2_QUEUE_STATICS).
    bool Add(T const &q, int timing)
    {
        if (Count < size) {
            Array[Tail] = q;
            Timings[Tail] = timing;
            Tail = (Tail + 1) & (size - 1);
            Count++;
            return true;
        }
        return false;
    }
#endif
    // Drops the head entry (Red Alert's QueueClass::Next).
    int Next()
    {
        if (Count) {
            Head = (Head + 1) & (size - 1);
            Count--;
        }
        return Count;
    }
    T &operator[](int index) { return Array[(Head + index) & (size - 1)]; }
    T &First() { return Array[Head]; }

    int Count;
    int Head;
    int Tail;
    T Array[size];
    int Timings[size];
};

extern QueueClass<EventClass, 128> OutList;     // 0x00A32338
// Stamps the event with the current frame and adds it to OutList; false when
// the queue is full (0x0062E670, the Queue unit; the event is passed by value;
// moved from shared/planning.hpp).
bool __stdcall Unknown_0062E670(EventClass event);
// The events the game executes (0x00866270, Red Alert's DoList): 0x4000 entries
// (Clean_DoList 0x00629E80 and Queue_Record 0x00629ED0 wrap the head with
// 0x3FFF; the array starts at 0x0086627C).
extern QueueClass<EventClass, 0x4000> DoList;
// A third event queue of 256 entries (0x00A35F30; the array starts at 0x00A35F3C; use not recovered).
extern QueueClass<EventClass, 256> unknown_event_queue_a35f30;

#endif

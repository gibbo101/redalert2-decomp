// A polymorphic base whose assignment is the shared helper at 0x00539000
// (copies itself from another instance by virtual slots 9 and 3 unless it is
// the same object; name and role unknown). Two derived records (assigned by
// 0x004A5690 and 0x004A5730) extend it from offset 0x0C.
#ifndef RA2_SHARED_UNKNOWN_BASE_539000_HPP
#define RA2_SHARED_UNKNOWN_BASE_539000_HPP

class UnknownBase539000 {
public:
    UnknownBase539000 &operator=(UnknownBase539000 const &other);   // 0x00539000
    virtual void unknown_slot0();
    virtual void unknown_slot1();
    virtual void unknown_slot2();
    virtual void unknown_slot3(UnknownBase539000 const &other);     // copies the payload (+0x0C in vtable terms)
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual void unknown_slot8();
    virtual void unknown_slot9();                                   // clears
    int unknown_04;
    int unknown_08;
};

#endif

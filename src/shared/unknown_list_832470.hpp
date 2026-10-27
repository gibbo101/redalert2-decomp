#ifndef RA2_SHARED_UNKNOWN_LIST_832470_HPP
#define RA2_SHARED_UNKNOWN_LIST_832470_HPP

class ObjectClass;

// The object list at 0x00832470 (a DynamicVectorClass<ObjectClass *> with
// its own members; hypothesis: the logic/layer list). ObjectClass +0x84
// records membership.
class UnknownList832470 {
public:
    bool Submit(ObjectClass *object, bool arg2);    // 0x0053E330 (name hypothesis)
    void Remove(ObjectClass *object);               // 0x0053E370 (name hypothesis)
};
extern UnknownList832470 unknown_list_832470;

#endif

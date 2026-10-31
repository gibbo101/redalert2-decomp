#ifndef RA2_SHARED_UNKNOWN_LIST_832470_HPP
#define RA2_SHARED_UNKNOWN_LIST_832470_HPP

#include "shared/vector_class.hpp"
class ObjectClass;

// The object list at 0x00832470 (hypothesis: Red Alert's Logic, a LogicClass:
// RTTI LogicClass vtable 0x0079A8EC derives from LayerClass, which derives
// from DynamicVectorClass<ObjectClass *>; the LayerClass base is left out so
// Submit stays non-virtual here). ObjectClass +0x84 records membership;
// Compute_Game_CRC 0x00629FA0 reads its Vector (+0x04) and ActiveCount (+0x10).
class UnknownList832470 : public DynamicVectorClass<ObjectClass *> {
public:
    bool Submit(ObjectClass *object, bool arg2);    // 0x0053E330 (name hypothesis)
    void Remove(ObjectClass *object);               // 0x0053E370 (name hypothesis)
    // Once per frame from Main_Loop (0x0053D890; Westwood's LogicClass::AI, hypothesis).
    void Unknown_0053D890();
};
extern UnknownList832470 unknown_list_832470;

#endif

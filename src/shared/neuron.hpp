// NeuronClass (RTTI vtable 0x0079CAF0, AbstractClass base; unit 0x00437740)
// and BrainClass (RTTI vtable 0x0079CB74, no base), which owns a capped
// list of neurons. Layouts from the constructor 0x00437910, Load 0x00437B00
// and the BrainClass members 0x00437BC0-0x00437F5C. Nothing in the
// executable calls the BrainClass members; field purposes are unknown.
#ifndef RA2_SHARED_NEURON_HPP
#define RA2_SHARED_NEURON_HPP
#include "shared/abstract.hpp"
#include "shared/vector_class_decl.hpp"

class BrainClass;

extern "C" GUID const CLSID_NeuronClass;           // 0x007A1EC0

class NeuronClass : public AbstractClass {
public:
    NeuronClass();                                              // 0x00437910
    NeuronClass(NoInitClass const &noinit) : AbstractClass(noinit) {}
    virtual ~NeuronClass();                                     // 0x00437A00 (deleting 0x00437F80)
    virtual HRESULT __stdcall GetClassID(GUID *clsid);          // slot 3 0x00437AC0
    virtual HRESULT __stdcall Load(IStream *stream);            // slot 5 0x00437B00
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);   // slot 6 0x00437B70
    virtual int Kind_Of() const { return 0x3C; }                // slot 11 0x00437F60
    virtual int Size_Of() const { return sizeof(NeuronClass); } // slot 12 0x00437F70
    virtual void Compute_CRC(WWCRCEngine &crc) const;           // slot 13 0x00437B90

    AbstractClass *unknown_24;  // +0x24 (swizzled)
    AbstractClass *unknown_28;  // +0x28 (swizzled)
    BrainClass *Brain;          // +0x2C set by BrainClass::Add
    int CreationFrame;          // +0x30 Frame when constructed
    int unknown_34;             // +0x34 (not constructed)
};
typedef char NeuronClass_size_38[(sizeof(NeuronClass) == 0x38) ? 1 : -1];

class BrainClass {
public:
    virtual ~BrainClass();                                      // 0x00437BC0 (deleting 0x00438050)
    void Clear();                                               // 0x00437C30
    void Init(int value, int max_neurons);                      // 0x00437C70
    bool Add(NeuronClass *neuron);                              // 0x00437CC0
    HRESULT Save(IStream *stream, BOOL clear_dirty);            // 0x00437D30
    HRESULT Load(IStream *stream);                              // 0x00437DA0

    DynamicVectorClass<NeuronClass *> Neurons;  // +0x04
    int unknown_1c;                             // +0x1C
    int MaxNeurons;                             // +0x20
};
typedef char BrainClass_size_24[(sizeof(BrainClass) == 0x24) ? 1 : -1];

#endif

// TargetClass (proposal: moved here from shared/ccini_extra.hpp so units that
// cannot include ccini_extra.hpp's padded HouseClass view can use it;
// ccini_extra.hpp would include this header instead of defining it).
#ifndef RA2_SHARED_TARGET_HPP
#define RA2_SHARED_TARGET_HPP

class AbstractClass;
class AbstractTypeClass;

// A reference to a game object: its ID and its kind (Kind_Of, slot 11);
// kind 0 means none. Five bytes, byte-packed: copies move a dword and a
// byte. Names are hypotheses.
#pragma pack(push, 1)
class TargetClass {
public:
    TargetClass() : Kind(0) {}
    TargetClass(AbstractClass *object);                     // 0x006B54A0
    // Unpacks As_Target's form.
    TargetClass(int target)
    {
        Kind = target >> 24;
        ID = target & 0x00FFFFFF;
    }

    // The referenced type object, or null.
    AbstractTypeClass *As_Type() const;                     // 0x006B5D20

    bool Is_Valid() const { return Kind != 0; }
    // The packed form: kind in the top byte, the low 24 bits of the ID.
    int As_Target() const { return (Kind << 24) | (ID & 0x00FFFFFF); }

    int ID;                 // +0x00
    unsigned char Kind;     // +0x04
};
#pragma pack(pop)

#endif

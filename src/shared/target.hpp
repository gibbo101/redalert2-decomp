// TargetClass (Target.cpp, 0x006B54A0-0x006B6654; proposal: moved here from
// shared/ccini_extra.hpp so units that cannot include ccini_extra.hpp's padded
// HouseClass view can use it; ccini_extra.hpp would include this header
// instead of defining it).
#ifndef RA2_SHARED_TARGET_HPP
#define RA2_SHARED_TARGET_HPP

class AbstractClass;
class AbstractTypeClass;
class AircraftClass;
class AnimClass;
class BuildingClass;
class BulletClass;
class Cell;
class CellClass;
class FootClass;
class HouseClass;
class InfantryClass;
class ObjectClass;
class TagClass;
class TagTypeClass;
class TeamClass;
class TeamTypeClass;
class TechnoClass;
class TechnoTypeClass;
class TerrainClass;
class TriggerClass;
class TriggerTypeClass;
class UnitClass;
struct CoordStruct;

// A reference to a game object: its ID and its kind (Kind_Of, slot 11);
// kind 0 means none, 11 a cell (ID = X + Y * 1000), 0x34 an object in the
// object index (ID = Fetch_ID; shared/object_index.hpp). Five bytes,
// byte-packed: copies move a dword and a byte. Names are hypotheses.
#pragma pack(push, 1)
class TargetClass {
public:
    TargetClass() : Kind(0) {}
    TargetClass(AbstractClass *object);                     // 0x006B54A0
    TargetClass(Cell const &cell);                          // 0x006B5510
    TargetClass(CoordStruct const &coord);                  // 0x006B5560
    // Unpacks As_Target's form.
    TargetClass(int target)
    {
        Kind = target >> 24;
        ID = target & 0x00FFFFFF;
    }

    // The referenced object as each class (a dynamic_cast of the indexed
    // object), or null.
    AbstractTypeClass *As_AbstractType() const;             // 0x006B55A0
    TagClass *As_Tag() const;                               // 0x006B5670
    TagTypeClass *As_TagType() const;                       // 0x006B5740
    AbstractClass *As_Abstract() const;                     // 0x006B5810 (a cell too)
    TechnoClass *As_Techno() const;                         // 0x006B5910
    ObjectClass *As_Object() const;                         // 0x006B59E0
    FootClass *As_Foot() const;                             // 0x006B5AB0
    TriggerClass *As_Trigger() const;                       // 0x006B5B80
    HouseClass *As_House() const;                           // 0x006B5C50
    TechnoTypeClass *As_TechnoType() const;                 // 0x006B5D20
    TriggerTypeClass *As_TriggerType() const;               // 0x006B5DF0
    TeamTypeClass *As_TeamType() const;                     // 0x006B5EC0
    TerrainClass *As_Terrain() const;                       // 0x006B5F90
    BulletClass *As_Bullet() const;                         // 0x006B6060
    AnimClass *As_Anim() const;                             // 0x006B6130
    TeamClass *As_Team() const;                             // 0x006B6200
    InfantryClass *As_Infantry() const;                     // 0x006B62D0
    UnitClass *As_Unit() const;                             // 0x006B63A0
    BuildingClass *As_Building() const;                     // 0x006B6470
    AircraftClass *As_Aircraft() const;                     // 0x006B6540
    CellClass *As_Cell() const;                             // 0x006B6610

    bool Is_Valid() const { return Kind != 0; }
    // The packed form: kind in the top byte, the low 24 bits of the ID.
    int As_Target() const { return (Kind << 24) | (ID & 0x00FFFFFF); }

    long ID;                // +0x00
    unsigned char Kind;     // +0x04
};
#pragma pack(pop)

#endif

// TagClass: a live scenario tag (Tag.cpp, unit 0x006B3600; RTTI vtables
// 0x007AC700 primary, 0x007AC6E4 IRTTITypeInfo at +4, 0x007AC6DC
// INoticeSink, 0x007AC6D4 INoticeSource). Replaces the stand-in in
// object.hpp (ObjectClass keeps the count of objects carrying the tag in
// unknown_2c).
//
// Layout (from the constructor 0x006B3870 and the destructor 0x006B39F0;
// names are hypotheses):
//   +0x00  AbstractClass (0x24)
//   +0x24  TagTypeClass *Class
//   +0x28  TriggerClass *AttachedTrigger   (one per trigger type, chained)
//   +0x2C  int unknown_2c                  (objects carrying the tag)
//   +0x30  Cell unknown_30
//   +0x34  bool unknown_34                 (queued for removal)
//   +0x35  bool unknown_35                 (springing; blocks reentry)
//   size 0x38
// Every tag is added to Tags (0x00ABFE48) and the abstract lists 0x00AC0CB0
// and 0x00AC0D48.
#ifndef RA2_SHARED_TAG_HPP
#define RA2_SHARED_TAG_HPP

#include "shared/tag_type.hpp"
#include "shared/trigger.hpp"

class ObjectClass;

extern "C" GUID const CLSID_TagClass;           // 0x007A1D30

class TagClass : public AbstractClass {
public:
    TagClass(TagTypeClass *type);                                       // 0x006B3870
    TagClass(NoInitClass const &noinit) : AbstractClass(noinit) {}
    virtual ~TagClass();                                                // 0x006B39F0

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x006B40D0 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x006B4160 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x006B41D0 slot 6
    virtual void Detach(AbstractClass *target, bool all = true);        // 0x006B4040 slot 10
    virtual int Kind_Of() const;                                        // 0x006B42D0 slot 11
    virtual int Size_Of() const;                                        // 0x006B42C0 slot 12
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x006B4110 slot 13

    void unknown_func_6b3cc0();                                         // 0x006B3CC0 (queue for removal)
    bool unknown_func_6b3d20() const;                                   // 0x006B3D20
    Cell Get_Cell() const;                                        // 0x006B3D80
    bool unknown_func_6b3d90() const;                                   // 0x006B3D90 (Class->unknown_func_6b4c90)
    bool unknown_func_6b3da0() const;                                   // 0x006B3DA0 (Class->unknown_func_6b4c60)
    bool unknown_func_6b3db0() const;                                   // 0x006B3DB0 (Class->unknown_func_6b4cc0)
    bool unknown_func_6b3dc0() const;                                   // 0x006B3DC0 (Class->unknown_func_6b4c30)
    bool Is_Trigger_Attached(TriggerClass *trigger) const;              // 0x006B3DD0
    // 0x006B3DF0 (spring an event; hypothesis). Returns a bool in al.
    bool Unknown_006B3DF0(int event, ObjectClass *object, Cell cell, int arg4, int arg5);
    void Set_Cell(Cell cell);                                     // 0x006B3F90
    void unknown_func_6b3fd0(int value);                                // 0x006B3FD0
    bool unknown_func_6b41f0() const;                                   // 0x006B41F0
    bool unknown_func_6b4280() const;                                   // 0x006B4280 (no other tag of this type)

    static TagClass *__fastcall Find_Or_Make(TagTypeClass *type);       // 0x006B3D30
    static void Clear_All();                                            // 0x006B3FA0
    static void __fastcall unknown_func_6b4220(int value);              // 0x006B4220
    static void __fastcall unknown_func_6b4250(int value);              // 0x006B4250

    TagTypeClass *Class;                    // +0x24
    TriggerClass *AttachedTrigger;          // +0x28
    int unknown_2c;                         // +0x2C
    Cell unknown_30;                  // +0x30
    bool unknown_34;                        // +0x34
    bool unknown_35;                        // +0x35
};

// Every tag (0x00ABFE48; defined in this unit).
extern DynamicVectorClass<TagClass *> unknown_TagClass_list_00abfe48;

#endif

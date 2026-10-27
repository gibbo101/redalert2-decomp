// BulletTypeClass: a projectile type (BulletType.cpp, 0x004642F0-0x00465275;
// RTTI vtables 0x0079D5C0 primary (40 slots), 0x0079D5A4 IRTTITypeInfo at
// +4, 0x0079D59C INoticeSink, 0x0079D594 INoticeSource).
//
// Layout (from the constructor 0x004644E0; member names follow the INI keys
// Read_INI 0x00464800 reads, the others are unknown):
//   +0x000  ObjectTypeClass (0x264)
//   +0x264..+0x279  bools (+0x26A, +0x271, +0x275 true)
//   +0x27C  int (1), +0x280..+0x28C ints, +0x290 bool
//   +0x298  double (0.75), +0x2A0 int (3), +0x2A4 int
//   +0x2A8  AnimTypeClass *unknown_2a8 (Detach clears it)
//   +0x2AC  int, +0x2B0 int, +0x2B4 int (3), +0x2B8 int (0x00465150 sets it)
//   +0x2BC  bool, +0x2C0 int, +0x2C4..+0x2C7 bools
//   size 0x2C8 (slot 12)
// Every type is added to BulletTypes (0x00A35CF0) and the abstract list
// 0x00AC0CB0.
#ifndef RA2_SHARED_BULLET_TYPE_HPP
#define RA2_SHARED_BULLET_TYPE_HPP

#include "shared/object_type.hpp"

class AnimTypeClass;
class WeaponTypeClass;

extern "C" GUID const CLSID_BulletTypeClass;    // 0x007A1B40

class BulletTypeClass : public ObjectTypeClass {
public:
    BulletTypeClass(char const *ini_name);                              // 0x004644E0
    BulletTypeClass(NoInitClass const &noinit);                         // 0x00464700
    virtual ~BulletTypeClass();                                         // 0x00464730

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x00465060 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x00464FB0 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x00465040 slot 6
    virtual void Detach(AbstractClass *target, bool all = true);        // 0x00465130 slot 10
    virtual int Kind_Of() const;                                        // 0x00465160 slot 11
    virtual int Size_Of() const;                                        // 0x00465170 slot 12
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x00464E70 slot 13
    virtual bool Read_INI(CCINIClass &ini);                             // 0x00464800 slot 25
    virtual CoordStruct unknown_slot27(CoordStruct const &coord) const; // 0x00464E00
    virtual bool unknown_slot32(Cell const &cell, HouseClass *house) const;   // 0x00465180 (false)
    virtual ObjectClass *unknown_slot35(HouseClass *house) const;       // 0x00465190 (0)

    void Set_unknown_2b8(int value);                                    // 0x00465150
    static BulletTypeClass *__fastcall Find_Or_Make(char const *name);  // 0x004650A0
    static int __fastcall Index_Or_Make(char const *name);              // 0x00464D50 (-1 for "<none>")
    static char const *__fastcall Name_From(int index);                 // 0x00464DE0 (0 when out of range)

    bool Airburst;                          // +0x264
    bool Floater;                           // +0x265
    bool SubjectToCliffs;                   // +0x266
    bool SubjectToElevation;                // +0x267
    bool SubjectToWalls;                    // +0x268
    bool VeryHigh;                          // +0x269
    bool Shadow;                            // +0x26A
    bool Arcing;                            // +0x26B
    bool Dropping;                          // +0x26C
    bool Level;                             // +0x26D
    bool Inviso;                            // +0x26E
    bool Proximity;                         // +0x26F
    bool Ranged;                            // +0x270
    bool Rotates;                           // +0x271
    bool Inaccurate;                        // +0x272
    bool FlakScatter;                       // +0x273
    bool AA;                                // +0x274
    bool AG;                                // +0x275
    bool Degenerates;                       // +0x276
    bool Bouncy;                            // +0x277
    bool AnimPalette;                       // +0x278
    bool FirersPalette;                     // +0x279
    int Cluster;                            // +0x27C
    WeaponTypeClass *AirburstWeapon;        // +0x280
    WeaponTypeClass *ShrapnelWeapon;        // +0x284
    int ShrapnelCount;                      // +0x288
    int DetonationAltitude;                 // +0x28C
    bool Vertical;                          // +0x290
    int unknown_294;                        // +0x294 (not set by the constructor)
    double Elasticity;                      // +0x298
    int Acceleration;                       // +0x2A0
    int Color;                              // +0x2A4
    AnimTypeClass *Trailer;                 // +0x2A8
    int ROT;                                // +0x2AC
    int CourseLockDuration;                 // +0x2B0
    int SpawnDelay;                         // +0x2B4
    int unknown_2b8;                        // +0x2B8
    bool Scalable;                          // +0x2BC
    int Arm;                                // +0x2C0
    unsigned char AnimLow;                  // +0x2C4
    unsigned char AnimHigh;                 // +0x2C5
    unsigned char AnimRate;                 // +0x2C6
    bool Flat;                              // +0x2C7
};

// Every bullet type (0x00A35CF0; defined in the globals unit).
extern DynamicVectorClass<BulletTypeClass *> BulletTypes;

#endif

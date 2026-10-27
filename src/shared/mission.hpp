// MissionClass: ObjectClass with the mission state (Mission.cpp,
// 0x00594310-0x00595166; RTTI vtables 0x007A6200 primary (149 slots),
// 0x007A61E4/0x007A61DC/0x007A61D4) and MissionControlClass (the mission
// table at 0x00A403B0, 0x20 bytes per mission).
//
// Layout (constructor 0x00594500): +0x98 Mission, +0x9C SuspendedMission,
// +0xA0 MissionQueue (all -1), +0xA4 bool, +0xA8 int, +0xAC int (frame of
// the last change), +0xB0 CDTimerClass<FrameTimerClass> Timer; 0xBC bytes.
// Names follow Westwood's TS vocabulary where the behaviour agrees.
#ifndef RA2_SHARED_MISSION_HPP
#define RA2_SHARED_MISSION_HPP

#include "shared/object.hpp"
#include "shared/cd_timer.hpp"

class MissionControlClass {
public:
    MissionControlClass();                                      // 0x00594DD0
    char const *Name() const;                                   // 0x00594E10
    // Reads the mission's own section (its name; NoThreat=, Zombie=, Recruitable=,
    // Paralyzed=, Retaliate=, Scatter=, Rate=, AARate=).
    bool Read_INI(CCINIClass &ini);                             // 0x00594E30

    int Mission;                // +0x00 (-1)
    bool unknown_04;            // +0x04
    bool unknown_05;            // +0x05
    bool unknown_06;            // +0x06 true
    bool unknown_07;            // +0x07
    bool unknown_08;            // +0x08 true
    bool unknown_09;            // +0x09 true
    int unknown_0c;             // +0x0C
    double unknown_10;          // +0x10 0.016
    double unknown_18;          // +0x18 0.016
};
extern MissionControlClass MissionControl[];                    // 0x00A403B0
extern char const *MissionNames[30];                            // 0x007CD774

class MissionClass : public ObjectClass {
public:
    MissionClass();                                             // 0x00594500
    MissionClass(NoInitClass const &noinit) : ObjectClass(noinit), Timer(noinit) {}
    virtual ~MissionClass() {}

    virtual void Compute_CRC(WWCRCEngine &crc) const;           // slot 13 0x00595040
    virtual void AI();                                          // slot 23 0x00594790
    virtual int unknown_slot91();                               // slot 91 0x00594770 current mission

    virtual void unknown_slot116(int mission, bool commence);   // slot 116 0x00594CB0 queue
    virtual bool unknown_slot117();                             // slot 117 0x00594C50 commence the queued mission
    virtual void unknown_slot118(int mission);                  // slot 118 0x00594710 set
    virtual void unknown_slot119(int mission, int unknown2, int unknown3);  // slot 119 0x00594D20 override
    virtual bool unknown_slot120();                             // slot 120 0x00594D80 restore the suspended mission
    virtual bool unknown_slot121() const;                       // slot 121 0x005950E0 has a suspended mission
    virtual bool unknown_slot122() { return true; }             // slot 122 kept copy 0x004CDDE0
    virtual int unknown_slot123();              // slot 123 (+0x1EC) 0x00594570 returns 450
    virtual int unknown_slot124();              // slot 124 (+0x1F0) 0x00594580 returns 450
    virtual int unknown_slot125();              // slot 125 (+0x1F4) 0x00594590 returns 450
    virtual int unknown_slot126();              // slot 126 (+0x1F8) 0x005945A0 returns 450
    virtual int unknown_slot127();              // slot 127 (+0x1FC) 0x005945B0 returns 450
    virtual int unknown_slot128();              // slot 128 (+0x200) 0x005945C0 returns 450
    virtual int unknown_slot129();              // slot 129 (+0x204) 0x005945D0 returns 450
    virtual int unknown_slot130();              // slot 130 (+0x208) 0x005945E0 returns 450
    virtual int unknown_slot131();              // slot 131 (+0x20C) 0x005945F0 returns 450
    virtual int unknown_slot132();              // slot 132 (+0x210) 0x00594600 returns 450
    virtual int unknown_slot133();              // slot 133 (+0x214) 0x00594610 returns 450
    virtual int unknown_slot134();              // slot 134 (+0x218) 0x00594620 returns 450
    virtual int unknown_slot135();              // slot 135 (+0x21C) 0x00594630 returns 450
    virtual int unknown_slot136();              // slot 136 (+0x220) 0x00594640 returns 450
    virtual int unknown_slot137();              // slot 137 (+0x224) 0x00594650 returns 450
    virtual int unknown_slot138();              // slot 138 (+0x228) 0x00594660 returns 450
    virtual int unknown_slot139();              // slot 139 (+0x22C) 0x00594670 returns 450
    virtual int unknown_slot140();              // slot 140 (+0x230) 0x00594680 returns 450
    virtual int unknown_slot141();              // slot 141 (+0x234) 0x00594690 returns 450
    virtual int unknown_slot142();              // slot 142 (+0x238) 0x005946A0 returns 450
    virtual int unknown_slot143();              // slot 143 (+0x23C) 0x005946B0 returns 450
    virtual int unknown_slot144();              // slot 144 (+0x240) 0x005946C0 returns 450
    virtual int unknown_slot145();              // slot 145 (+0x244) 0x005946D0 returns 450
    virtual int unknown_slot146();              // slot 146 (+0x248) 0x005946E0 returns 450
    virtual int unknown_slot147();              // slot 147 (+0x24C) 0x005946F0 returns 450
    virtual int unknown_slot148();              // slot 148 (+0x250) 0x00594700 returns 450

    MissionControlClass *Control() const;                       // 0x005950D0
    int Timer_Value() const;                                    // 0x005950F0

    static int __fastcall Mission_From_Name(char const *name);  // 0x00594FE0 (-1: none)
    static char const *__fastcall Name_From_Mission(int mission);   // 0x00595020
    static bool __fastcall unknown_594db0(int mission);         // 0x00594DB0 (true for -1)

    int Mission;                            // +0x98
    int SuspendedMission;                   // +0x9C
    int MissionQueue;                       // +0xA0
    bool unknown_a4;                        // +0xA4
    int unknown_a8;                         // +0xA8
    int unknown_ac;                         // +0xAC
    CDTimerClass<FrameTimerClass> Timer;    // +0xB0
};

#endif

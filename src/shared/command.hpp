// Keyboard commands (RTTI CommandClass and its 56 subclasses; vtables
// 0x007A3C44-0x007A4504), defined in Init.cpp (their strings carry
// "D:\Ra2\Init.CPP"; the registration function is 0x005173C0). Slot order
// from the vtables; slot names follow the public YR headers (hypotheses).
// Subclasses declare only the slots they override (from the vtables).
#ifndef RA2_SHARED_COMMAND_HPP
#define RA2_SHARED_COMMAND_HPP

#include "shared/string_table.hpp"

// The shared text buffers the name slots format into.
extern char unknown_command_name_a4149c[];       // 0x00A4149C (Get_Name)
extern wchar_t unknown_command_text_a4153c[];    // 0x00A4153C (Get_UI_Name, Get_Description)

class CommandClass {
public:
    virtual ~CommandClass() {}                                   // slot 0 (scalar deleting 0x0051AFA0)
    virtual char const *Get_Name() const = 0;                    // slot 1
    virtual wchar_t const *Get_UI_Name() const;                  // slot 2 (0x0051AF90)
    virtual wchar_t const *Get_Category() const = 0;             // slot 3
    virtual wchar_t const *Get_Description() const = 0;          // slot 4
    virtual bool unknown_slot5(int key) const;                   // slot 5 (0x0051AE70)
    virtual bool unknown_slot6(int key) const;                   // slot 6 (0x0051AE80)
    virtual bool unknown_slot7(int key) const;                   // slot 7 (0x0051AE90)
    virtual void Execute(int key) const = 0;                     // slot 8
};

// vtable 0x007A3C44 (scalar deleting destructor 0x0051E020)
class ScreenCaptureCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051D500
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051D530
    virtual wchar_t const *Get_Category() const;                // 0x0051D510
    virtual wchar_t const *Get_Description() const;             // 0x0051D550
    virtual void Execute(int key) const;                        // 0x0051D570
};

// vtable 0x007A3C6C (scalar deleting destructor 0x0051AF70)
class CreateTeamCommandClass : public CommandClass {
public:
    CreateTeamCommandClass(int number);
    virtual char const *Get_Name() const;                       // 0x0051AEC0
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051AEE0
    virtual wchar_t const *Get_Category() const;                // 0x0051AF10
    virtual wchar_t const *Get_Description() const;             // 0x0051AF30
    virtual void Execute(int key) const;                        // 0x0051AF60

    int TeamNumber;                                           // +0x04
};

// vtable 0x007A3C94 (scalar deleting destructor 0x0051E000)
class SetInfantryTabCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051B140
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051B150
    virtual wchar_t const *Get_Category() const;                // 0x0051B170
    virtual wchar_t const *Get_Description() const;             // 0x0051B190
    virtual void Execute(int key) const;                        // 0x0051B1B0
};

// vtable 0x007A3CBC (scalar deleting destructor 0x0051DFE0)
class SetUnitTabCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051B1D0
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051B1E0
    virtual wchar_t const *Get_Category() const;                // 0x0051B200
    virtual wchar_t const *Get_Description() const;             // 0x0051B220
    virtual void Execute(int key) const;                        // 0x0051B240
};

// vtable 0x007A3CE4 (scalar deleting destructor 0x0051DFC0)
class SetDefenseTabCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051B080
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051B090
    virtual wchar_t const *Get_Category() const;                // 0x0051B0B0
    virtual wchar_t const *Get_Description() const;             // 0x0051B0D0
    virtual void Execute(int key) const;                        // 0x0051B0F0
};

// vtable 0x007A3D0C (scalar deleting destructor 0x0051DFA0)
class SetStructureTabCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051AFC0
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051AFD0
    virtual wchar_t const *Get_Category() const;                // 0x0051AFF0
    virtual wchar_t const *Get_Description() const;             // 0x0051B010
    virtual void Execute(int key) const;                        // 0x0051B030
};

// vtable 0x007A3D34 (scalar deleting destructor 0x0051DF80)
class VeterancyNavCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051BC10
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051BC20
    virtual wchar_t const *Get_Category() const;                // 0x0051BC40
    virtual wchar_t const *Get_Description() const;             // 0x0051BC60
    virtual bool unknown_slot5(int key) const;                  // 0x0051BC80
    virtual void Execute(int key) const;                        // 0x0051BC90
};

// vtable 0x007A3D5C (scalar deleting destructor 0x0051DF60)
class HealthNavCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051BB70
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051BB80
    virtual wchar_t const *Get_Category() const;                // 0x0051BBA0
    virtual wchar_t const *Get_Description() const;             // 0x0051BBC0
    virtual bool unknown_slot5(int key) const;                  // 0x0051BBE0
    virtual void Execute(int key) const;                        // 0x0051BBF0
};

// vtable 0x007A3D84 (scalar deleting destructor 0x0051DF40)
class TypeSelectCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051BAB0
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051BAC0
    virtual wchar_t const *Get_Category() const;                // 0x0051BAE0
    virtual wchar_t const *Get_Description() const;             // 0x0051BB00
    virtual bool unknown_slot5(int key) const;                  // 0x0051BB20
    virtual bool unknown_slot6(int key) const;                  // 0x0051BB30
    virtual bool unknown_slot7(int key) const;                  // 0x0051BB40
    virtual void Execute(int key) const;                        // 0x0051BB50
};

// vtable 0x007A3DAC (scalar deleting destructor 0x0051DF20)
class CombatantSelectCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051BA10
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051BA20
    virtual wchar_t const *Get_Category() const;                // 0x0051BA40
    virtual wchar_t const *Get_Description() const;             // 0x0051BA60
    virtual bool unknown_slot5(int key) const;                  // 0x0051BA80
    virtual void Execute(int key) const;                        // 0x0051BA90
};

// vtable 0x007A3DD4 (scalar deleting destructor 0x0051DF00)
class PlanningModeCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051B940
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051B950
    virtual wchar_t const *Get_Category() const;                // 0x0051B970
    virtual wchar_t const *Get_Description() const;             // 0x0051B990
    virtual bool unknown_slot5(int key) const;                  // 0x0051B9B0
    virtual bool unknown_slot6(int key) const;                  // 0x0051B9D0
    virtual bool unknown_slot7(int key) const;                  // 0x0051B9E0
    virtual void Execute(int key) const;                        // 0x0051B9F0
};

// vtable 0x007A3DFC (scalar deleting destructor 0x0051DEE0)
class NextObjectCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051B840
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051B850
    virtual wchar_t const *Get_Category() const;                // 0x0051B870
    virtual wchar_t const *Get_Description() const;             // 0x0051B890
    virtual void Execute(int key) const;                        // 0x0051B8B0
};

// vtable 0x007A3E24 (scalar deleting destructor 0x0051DEC0)
class PrevObjectCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051BCB0
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051BCC0
    virtual wchar_t const *Get_Category() const;                // 0x0051BCE0
    virtual wchar_t const *Get_Description() const;             // 0x0051BD00
    virtual void Execute(int key) const;                        // 0x0051BD20
};

// vtable 0x007A3E4C (scalar deleting destructor 0x0051DEA0)
class DeployCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051BEB0
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051BEC0
    virtual wchar_t const *Get_Category() const;                // 0x0051BEE0
    virtual wchar_t const *Get_Description() const;             // 0x0051BF00
    virtual void Execute(int key) const;                        // 0x0051BF20
};

// vtable 0x007A3E74 (scalar deleting destructor 0x0051DE80)
class AllToCheerCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051BE30
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051BE40
    virtual wchar_t const *Get_Category() const;                // 0x0051BE60
    virtual wchar_t const *Get_Description() const;             // 0x0051BE80
    virtual void Execute(int key) const;                        // 0x0051BEA0
};

// vtable 0x007A3E9C (scalar deleting destructor 0x0051DE60)
class StopCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051BDB0
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051BDC0
    virtual wchar_t const *Get_Category() const;                // 0x0051BDE0
    virtual wchar_t const *Get_Description() const;             // 0x0051BE00
    virtual void Execute(int key) const;                        // 0x0051BE20
};

// vtable 0x007A3EC4 (scalar deleting destructor 0x0051DE40)
class GuardCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051BF30
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051BF40
    virtual wchar_t const *Get_Category() const;                // 0x0051BF60
    virtual wchar_t const *Get_Description() const;             // 0x0051BF80
    virtual void Execute(int key) const;                        // 0x0051BFA0
};

// vtable 0x007A3EEC (scalar deleting destructor 0x0051DE20)
class ScatterCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051BFB0
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051BFC0
    virtual wchar_t const *Get_Category() const;                // 0x0051BFE0
    virtual wchar_t const *Get_Description() const;             // 0x0051C000
    virtual void Execute(int key) const;                        // 0x0051C020
};

// vtable 0x007A3F14 (scalar deleting destructor 0x0051DE00)
class CenterViewCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051C030
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051C040
    virtual wchar_t const *Get_Category() const;                // 0x0051C060
    virtual wchar_t const *Get_Description() const;             // 0x0051C080
    virtual void Execute(int key) const;                        // 0x0051C0A0
};

// vtable 0x007A3F3C (scalar deleting destructor 0x0051DDE0)
class CenterBaseCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051C0D0
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051C0E0
    virtual wchar_t const *Get_Category() const;                // 0x0051C100
    virtual wchar_t const *Get_Description() const;             // 0x0051C120
    virtual void Execute(int key) const;                        // 0x0051C140
};

// vtable 0x007A3F64 (scalar deleting destructor 0x0051DDC0)
class AllianceCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051C3C0
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051C3D0
    virtual wchar_t const *Get_Category() const;                // 0x0051C3F0
    virtual wchar_t const *Get_Description() const;             // 0x0051C410
    virtual void Execute(int key) const;                        // 0x0051C430
};

// vtable 0x007A3F8C (scalar deleting destructor 0x0051DDA0)
class ToggleRepairCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051C440
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051C450
    virtual wchar_t const *Get_Category() const;                // 0x0051C470
    virtual wchar_t const *Get_Description() const;             // 0x0051C490
    virtual void Execute(int key) const;                        // 0x0051C4B0
};

// vtable 0x007A3FB4 (scalar deleting destructor 0x0051DD80)
class ToggleSellCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051C4C0
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051C4D0
    virtual wchar_t const *Get_Category() const;                // 0x0051C4F0
    virtual wchar_t const *Get_Description() const;             // 0x0051C510
    virtual void Execute(int key) const;                        // 0x0051C530
};

// vtable 0x007A3FDC (scalar deleting destructor 0x0051DD60)
class BeaconPlacementCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051C540
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051C550
    virtual wchar_t const *Get_Category() const;                // 0x0051C570
    virtual wchar_t const *Get_Description() const;             // 0x0051C590
    virtual void Execute(int key) const;                        // 0x0051C5B0
};

// vtable 0x007A4004 (scalar deleting destructor 0x0051DD40)
class CenterREventCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051C5D0
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051C5E0
    virtual wchar_t const *Get_Category() const;                // 0x0051C600
    virtual wchar_t const *Get_Description() const;             // 0x0051C620
    virtual void Execute(int key) const;                        // 0x0051C640
};

// vtable 0x007A402C (scalar deleting destructor 0x0051DD20)
class RSidebarPageDownCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051CC80
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051CC90
    virtual wchar_t const *Get_Category() const;                // 0x0051CCB0
    virtual wchar_t const *Get_Description() const;             // 0x0051CCD0
    virtual void Execute(int key) const;                        // 0x0051CCF0
};

// vtable 0x007A4054 (scalar deleting destructor 0x0051DD00)
class LSidebarPageDownCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051CBF0
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051CC00
    virtual wchar_t const *Get_Category() const;                // 0x0051CC20
    virtual wchar_t const *Get_Description() const;             // 0x0051CC40
    virtual void Execute(int key) const;                        // 0x0051CC60
};

// vtable 0x007A407C (scalar deleting destructor 0x0051DCE0)
class SidebarPageDownCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051CB60
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051CB70
    virtual wchar_t const *Get_Category() const;                // 0x0051CB90
    virtual wchar_t const *Get_Description() const;             // 0x0051CBB0
    virtual void Execute(int key) const;                        // 0x0051CBD0
};

// vtable 0x007A40A4 (scalar deleting destructor 0x0051DCC0)
class RSidebarPageUpCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051C920
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051C930
    virtual wchar_t const *Get_Category() const;                // 0x0051C950
    virtual wchar_t const *Get_Description() const;             // 0x0051C970
    virtual void Execute(int key) const;                        // 0x0051C990
};

// vtable 0x007A40CC (scalar deleting destructor 0x0051DCA0)
class LSidebarPageUpCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051C890
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051C8A0
    virtual wchar_t const *Get_Category() const;                // 0x0051C8C0
    virtual wchar_t const *Get_Description() const;             // 0x0051C8E0
    virtual void Execute(int key) const;                        // 0x0051C900
};

// vtable 0x007A40F4 (scalar deleting destructor 0x0051DC80)
class SidebarPageUpCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051C800
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051C810
    virtual wchar_t const *Get_Category() const;                // 0x0051C830
    virtual wchar_t const *Get_Description() const;             // 0x0051C850
    virtual void Execute(int key) const;                        // 0x0051C870
};

// vtable 0x007A411C (scalar deleting destructor 0x0051DC60)
class RSidebarDownCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051CAD0
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051CAE0
    virtual wchar_t const *Get_Category() const;                // 0x0051CB00
    virtual wchar_t const *Get_Description() const;             // 0x0051CB20
    virtual void Execute(int key) const;                        // 0x0051CB40
};

// vtable 0x007A4144 (scalar deleting destructor 0x0051DC40)
class LSidebarDownCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051CA40
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051CA50
    virtual wchar_t const *Get_Category() const;                // 0x0051CA70
    virtual wchar_t const *Get_Description() const;             // 0x0051CA90
    virtual void Execute(int key) const;                        // 0x0051CAB0
};

// vtable 0x007A416C (scalar deleting destructor 0x0051DC20)
class SidebarDownCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051C9B0
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051C9C0
    virtual wchar_t const *Get_Category() const;                // 0x0051C9E0
    virtual wchar_t const *Get_Description() const;             // 0x0051CA00
    virtual void Execute(int key) const;                        // 0x0051CA20
};

// vtable 0x007A4194 (scalar deleting destructor 0x0051DC00)
class RSidebarUpCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051C770
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051C780
    virtual wchar_t const *Get_Category() const;                // 0x0051C7A0
    virtual wchar_t const *Get_Description() const;             // 0x0051C7C0
    virtual void Execute(int key) const;                        // 0x0051C7E0
};

// vtable 0x007A41BC (scalar deleting destructor 0x0051DBE0)
class LSidebarUpCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051C6E0
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051C6F0
    virtual wchar_t const *Get_Category() const;                // 0x0051C710
    virtual wchar_t const *Get_Description() const;             // 0x0051C730
    virtual void Execute(int key) const;                        // 0x0051C750
};

// vtable 0x007A41E4 (scalar deleting destructor 0x0051DBC0)
class SidebarUpCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051C650
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051C660
    virtual wchar_t const *Get_Category() const;                // 0x0051C680
    virtual wchar_t const *Get_Description() const;             // 0x0051C6A0
    virtual void Execute(int key) const;                        // 0x0051C6C0
};

// vtable 0x007A420C (scalar deleting destructor 0x0051DBA0)
class OptionsCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051CD10
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051CD20
    virtual wchar_t const *Get_Category() const;                // 0x0051CD40
    virtual wchar_t const *Get_Description() const;             // 0x0051CD60
    virtual void Execute(int key) const;                        // 0x0051CD80
};

// vtable 0x007A4234 (scalar deleting destructor 0x0051DB80)
class SetView4CommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051D390
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051D3A0
    virtual wchar_t const *Get_Category() const;                // 0x0051D3C0
    virtual wchar_t const *Get_Description() const;             // 0x0051D3E0
    virtual void Execute(int key) const;                        // 0x0051D400
};

// vtable 0x007A425C (scalar deleting destructor 0x0051DB60)
class SetView3CommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051D2D0
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051D2E0
    virtual wchar_t const *Get_Category() const;                // 0x0051D300
    virtual wchar_t const *Get_Description() const;             // 0x0051D320
    virtual void Execute(int key) const;                        // 0x0051D340
};

// vtable 0x007A4284 (scalar deleting destructor 0x0051DB40)
class SetView2CommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051D210
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051D220
    virtual wchar_t const *Get_Category() const;                // 0x0051D240
    virtual wchar_t const *Get_Description() const;             // 0x0051D260
    virtual void Execute(int key) const;                        // 0x0051D280
};

// vtable 0x007A42AC (scalar deleting destructor 0x0051DB20)
class SetView1CommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051D150
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051D160
    virtual wchar_t const *Get_Category() const;                // 0x0051D180
    virtual wchar_t const *Get_Description() const;             // 0x0051D1A0
    virtual void Execute(int key) const;                        // 0x0051D1C0
};

// vtable 0x007A42D4 (scalar deleting destructor 0x0051DB00)
class View4CommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051D060
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051D070
    virtual wchar_t const *Get_Category() const;                // 0x0051D090
    virtual wchar_t const *Get_Description() const;             // 0x0051D0B0
    virtual void Execute(int key) const;                        // 0x0051D0D0
};

// vtable 0x007A42FC (scalar deleting destructor 0x0051DAE0)
class View3CommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051CF70
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051CF80
    virtual wchar_t const *Get_Category() const;                // 0x0051CFA0
    virtual wchar_t const *Get_Description() const;             // 0x0051CFC0
    virtual void Execute(int key) const;                        // 0x0051CFE0
};

// vtable 0x007A4324 (scalar deleting destructor 0x0051DAC0)
class View2CommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051CE80
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051CE90
    virtual wchar_t const *Get_Category() const;                // 0x0051CEB0
    virtual wchar_t const *Get_Description() const;             // 0x0051CED0
    virtual void Execute(int key) const;                        // 0x0051CEF0
};

// vtable 0x007A434C (scalar deleting destructor 0x0051DAA0)
class View1CommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051CD90
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051CDA0
    virtual wchar_t const *Get_Category() const;                // 0x0051CDC0
    virtual wchar_t const *Get_Description() const;             // 0x0051CDE0
    virtual void Execute(int key) const;                        // 0x0051CE00
};

// vtable 0x007A4374 (scalar deleting destructor 0x0051DA80)
class FollowCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051D450
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051D460
    virtual wchar_t const *Get_Category() const;                // 0x0051D480
    virtual wchar_t const *Get_Description() const;             // 0x0051D4A0
    virtual void Execute(int key) const;                        // 0x0051D4C0
};

// vtable 0x007A439C (scalar deleting destructor 0x0051DA60)
class MultiplayerSyncCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051D7E0
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051D800
    virtual wchar_t const *Get_Category() const;                // 0x0051D7F0
    virtual wchar_t const *Get_Description() const;             // 0x0051D810
    virtual void Execute(int key) const;                        // 0x0051D820
};

// vtable 0x007A43C4 (scalar deleting destructor 0x0051DA40)
class MultiplayerDebugCommandClass : public CommandClass {
public:
    virtual char const *Get_Name() const;                       // 0x0051D780
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051D7A0
    virtual wchar_t const *Get_Category() const;                // 0x0051D790
    virtual wchar_t const *Get_Description() const;             // 0x0051D7B0
    virtual void Execute(int key) const;                        // 0x0051D7C0
};

// vtable 0x007A4414 (scalar deleting destructor 0x0051B330)
class SelectTeamCommandClass : public CommandClass {
public:
    SelectTeamCommandClass(int number);
    virtual char const *Get_Name() const;                       // 0x0051B280
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051B2A0
    virtual wchar_t const *Get_Category() const;                // 0x0051B2D0
    virtual wchar_t const *Get_Description() const;             // 0x0051B2F0
    virtual void Execute(int key) const;                        // 0x0051B320

    int TeamNumber;                                           // +0x04
};

// vtable 0x007A443C (scalar deleting destructor 0x0051B420)
class AddTeamCommandClass : public CommandClass {
public:
    AddTeamCommandClass(int number);
    virtual char const *Get_Name() const;                       // 0x0051B370
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051B390
    virtual wchar_t const *Get_Category() const;                // 0x0051B3C0
    virtual wchar_t const *Get_Description() const;             // 0x0051B3E0
    virtual void Execute(int key) const;                        // 0x0051B410

    int TeamNumber;                                           // +0x04
};

// vtable 0x007A4464 (scalar deleting destructor 0x0051B510)
class CenterTeamCommandClass : public CommandClass {
public:
    CenterTeamCommandClass(int number);
    virtual char const *Get_Name() const;                       // 0x0051B460
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051B480
    virtual wchar_t const *Get_Category() const;                // 0x0051B4B0
    virtual wchar_t const *Get_Description() const;             // 0x0051B4D0
    virtual void Execute(int key) const;                        // 0x0051B500

    int TeamNumber;                                           // +0x04
};

// vtable 0x007A448C (scalar deleting destructor 0x0051B820)
class TauntCommandClass : public CommandClass {
public:
    TauntCommandClass(int number);
    virtual char const *Get_Name() const;                       // 0x0051B550
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051B570
    virtual wchar_t const *Get_Category() const;                // 0x0051B5A0
    virtual wchar_t const *Get_Description() const;             // 0x0051B5C0
    virtual void Execute(int key) const;                        // 0x0051B5F0

    int TauntNumber;                                          // +0x04
};

// vtable 0x007A44B4 (scalar deleting destructor 0x0051E040)
class PageUserCommandClass : public CommandClass {
public:
    PageUserCommandClass();
    virtual char const *Get_Name() const;                       // 0x0051D880
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051D890
    virtual wchar_t const *Get_Category() const;                // 0x0051D8B0
    virtual wchar_t const *Get_Description() const;             // 0x0051D8D0
    virtual void Execute(int key) const;                        // 0x0051D8F0
};

// vtable 0x007A44DC (scalar deleting destructor 0x0051E060)
class CursorPositionCommandClass : public CommandClass {
public:
    CursorPositionCommandClass();
    virtual char const *Get_Name() const;                       // 0x0051D920
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051D930
    virtual wchar_t const *Get_Category() const;                // 0x0051D950
    virtual wchar_t const *Get_Description() const;             // 0x0051D970
    virtual void Execute(int key) const;                        // 0x0051D990
};

// vtable 0x007A4504 (scalar deleting destructor 0x0051E080)
class DeleteCommandClass : public CommandClass {
public:
    DeleteCommandClass();
    virtual char const *Get_Name() const;                       // 0x0051D9C0
    virtual wchar_t const *Get_UI_Name() const;                 // 0x0051D9D0
    virtual wchar_t const *Get_Category() const;                // 0x0051D9F0
    virtual wchar_t const *Get_Description() const;             // 0x0051DA10
    virtual void Execute(int key) const;                        // 0x0051DA30
};

// The registered commands (0x00832358) and the default hotkeys (0x00832380:
// key code to command). Names are hypotheses.
#include "shared/vector_class.hpp"
#include "shared/ini_class.hpp"
extern DynamicVectorClass<CommandClass const *> unknown_commands_832358;
extern IndexClass<int, CommandClass *> unknown_hotkeys_832380;

// Creates and registers every command (0x005173C0).
void unknown_init_commands_5173c0();

#endif

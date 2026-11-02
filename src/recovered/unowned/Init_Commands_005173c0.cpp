// void unknown_init_commands_5173c0() -- 0x005173C0
// Body 0x005173C0-0x0051923F (7807 bytes, linear sweep to the ret, padding to 0x00519240; no jump tables).
// The 46 first Adds expand inline; the rest call DynamicVectorClass<CommandClass const *>::Add
// (0x0051E360) on the inline budget, which also leaves CreateTeamCommandClass(1) and the implicit
// constructors of SetInfantryTab and ScreenCapture inline (Westwood's int operator[] and
// `(*this)[ActiveCount++] = object` Add are what reproduce that budget).
// @ref ?Add@?$DynamicVectorClass@PBVCommandClass@@@@QAE_NABQBVCommandClass@@@Z=0051e360
// @ref ?Add_Index@?$IndexClass@HPAVCommandClass@@@@QAE_NABHABQAVCommandClass@@@Z=0051e3b0
// @ref ?Is_Present@?$IndexClass@HPAVCommandClass@@@@QBE_NABH@Z=0051e560
// @ref ?Remove_Index@?$IndexClass@HPAVCommandClass@@@@QAE_NABH@Z=0051e480
// @ref ??_7ScreenCaptureCommandClass@@6B@=007a3c44
// @ref ??_7CreateTeamCommandClass@@6B@=007a3c6c
// @ref ??_7SetInfantryTabCommandClass@@6B@=007a3c94
// @ref ??_7SetUnitTabCommandClass@@6B@=007a3cbc
// @ref ??_7SetDefenseTabCommandClass@@6B@=007a3ce4
// @ref ??_7SetStructureTabCommandClass@@6B@=007a3d0c
// @ref ??_7VeterancyNavCommandClass@@6B@=007a3d34
// @ref ??_7HealthNavCommandClass@@6B@=007a3d5c
// @ref ??_7TypeSelectCommandClass@@6B@=007a3d84
// @ref ??_7CombatantSelectCommandClass@@6B@=007a3dac
// @ref ??_7PlanningModeCommandClass@@6B@=007a3dd4
// @ref ??_7NextObjectCommandClass@@6B@=007a3dfc
// @ref ??_7PrevObjectCommandClass@@6B@=007a3e24
// @ref ??_7DeployCommandClass@@6B@=007a3e4c
// @ref ??_7AllToCheerCommandClass@@6B@=007a3e74
// @ref ??_7StopCommandClass@@6B@=007a3e9c
// @ref ??_7GuardCommandClass@@6B@=007a3ec4
// @ref ??_7ScatterCommandClass@@6B@=007a3eec
// @ref ??_7CenterViewCommandClass@@6B@=007a3f14
// @ref ??_7CenterBaseCommandClass@@6B@=007a3f3c
// @ref ??_7AllianceCommandClass@@6B@=007a3f64
// @ref ??_7ToggleRepairCommandClass@@6B@=007a3f8c
// @ref ??_7ToggleSellCommandClass@@6B@=007a3fb4
// @ref ??_7BeaconPlacementCommandClass@@6B@=007a3fdc
// @ref ??_7CenterREventCommandClass@@6B@=007a4004
// @ref ??_7RSidebarPageDownCommandClass@@6B@=007a402c
// @ref ??_7LSidebarPageDownCommandClass@@6B@=007a4054
// @ref ??_7SidebarPageDownCommandClass@@6B@=007a407c
// @ref ??_7RSidebarPageUpCommandClass@@6B@=007a40a4
// @ref ??_7LSidebarPageUpCommandClass@@6B@=007a40cc
// @ref ??_7SidebarPageUpCommandClass@@6B@=007a40f4
// @ref ??_7RSidebarDownCommandClass@@6B@=007a411c
// @ref ??_7LSidebarDownCommandClass@@6B@=007a4144
// @ref ??_7SidebarDownCommandClass@@6B@=007a416c
// @ref ??_7RSidebarUpCommandClass@@6B@=007a4194
// @ref ??_7LSidebarUpCommandClass@@6B@=007a41bc
// @ref ??_7SidebarUpCommandClass@@6B@=007a41e4
// @ref ??_7OptionsCommandClass@@6B@=007a420c
// @ref ??_7SetView4CommandClass@@6B@=007a4234
// @ref ??_7SetView3CommandClass@@6B@=007a425c
// @ref ??_7SetView2CommandClass@@6B@=007a4284
// @ref ??_7SetView1CommandClass@@6B@=007a42ac
// @ref ??_7View4CommandClass@@6B@=007a42d4
// @ref ??_7View3CommandClass@@6B@=007a42fc
// @ref ??_7View2CommandClass@@6B@=007a4324
// @ref ??_7View1CommandClass@@6B@=007a434c
// @ref ??_7FollowCommandClass@@6B@=007a4374
// @ref ??_7MultiplayerSyncCommandClass@@6B@=007a439c
// @ref ??_7MultiplayerDebugCommandClass@@6B@=007a43c4
// @ref ??_7SelectTeamCommandClass@@6B@=007a4414
// @ref ??_7AddTeamCommandClass@@6B@=007a443c
// @ref ??_7CenterTeamCommandClass@@6B@=007a4464
// @ref ??_7TauntCommandClass@@6B@=007a448c
// @ref ??_7PageUserCommandClass@@6B@=007a44b4
// @ref ??_7CursorPositionCommandClass@@6B@=007a44dc
// @ref ??_7DeleteCommandClass@@6B@=007a4504
#include "shared/command.hpp"
#include "shared/gscreen.hpp"

// Reads KEYBOARD.INI's hotkeys (0x00519240; defined later in this unit).
bool __fastcall Load_Keyboard_Hotkeys();

// Creates and registers every keyboard command (the two multiplayer debug commands only with
// unknown_flag_a3d8c4), loads KEYBOARD.INI and then binds Delete, Escape and Space to the
// Delete, Options and Center-on-event commands.
void unknown_init_commands_5173c0()
{
    if (unknown_flag_a3d8c4) {
        unknown_commands_832358.Add(new MultiplayerDebugCommandClass);
        unknown_commands_832358.Add(new MultiplayerSyncCommandClass);
    }
    unknown_commands_832358.Add(new FollowCommandClass);
    unknown_commands_832358.Add(new View1CommandClass);
    unknown_commands_832358.Add(new View2CommandClass);
    unknown_commands_832358.Add(new View3CommandClass);
    unknown_commands_832358.Add(new View4CommandClass);
    unknown_commands_832358.Add(new SetView1CommandClass);
    unknown_commands_832358.Add(new SetView2CommandClass);
    unknown_commands_832358.Add(new SetView3CommandClass);
    unknown_commands_832358.Add(new SetView4CommandClass);
    CommandClass *options = new OptionsCommandClass;
    unknown_commands_832358.Add(options);
    unknown_commands_832358.Add(new SidebarUpCommandClass);
    unknown_commands_832358.Add(new LSidebarUpCommandClass);
    unknown_commands_832358.Add(new RSidebarUpCommandClass);
    unknown_commands_832358.Add(new SidebarDownCommandClass);
    unknown_commands_832358.Add(new LSidebarDownCommandClass);
    unknown_commands_832358.Add(new RSidebarDownCommandClass);
    unknown_commands_832358.Add(new SidebarPageUpCommandClass);
    unknown_commands_832358.Add(new LSidebarPageUpCommandClass);
    unknown_commands_832358.Add(new RSidebarPageUpCommandClass);
    unknown_commands_832358.Add(new SidebarPageDownCommandClass);
    unknown_commands_832358.Add(new LSidebarPageDownCommandClass);
    unknown_commands_832358.Add(new RSidebarPageDownCommandClass);
    CommandClass *center_event = new CenterREventCommandClass;
    unknown_commands_832358.Add(center_event);
    unknown_commands_832358.Add(new BeaconPlacementCommandClass);
    unknown_commands_832358.Add(new ToggleSellCommandClass);
    unknown_commands_832358.Add(new ToggleRepairCommandClass);
    unknown_commands_832358.Add(new AllianceCommandClass);
    unknown_commands_832358.Add(new CenterBaseCommandClass);
    unknown_commands_832358.Add(new CenterViewCommandClass);
    unknown_commands_832358.Add(new ScatterCommandClass);
    unknown_commands_832358.Add(new GuardCommandClass);
    unknown_commands_832358.Add(new StopCommandClass);
    unknown_commands_832358.Add(new AllToCheerCommandClass);
    unknown_commands_832358.Add(new DeployCommandClass);
    unknown_commands_832358.Add(new PrevObjectCommandClass);
    unknown_commands_832358.Add(new NextObjectCommandClass);
    unknown_commands_832358.Add(new PlanningModeCommandClass);
    unknown_commands_832358.Add(new CombatantSelectCommandClass);
    unknown_commands_832358.Add(new TypeSelectCommandClass);
    unknown_commands_832358.Add(new HealthNavCommandClass);
    unknown_commands_832358.Add(new VeterancyNavCommandClass);
    unknown_commands_832358.Add(new SetStructureTabCommandClass);
    unknown_commands_832358.Add(new SetDefenseTabCommandClass);
    unknown_commands_832358.Add(new SetUnitTabCommandClass);
    unknown_commands_832358.Add(new SetInfantryTabCommandClass);
    int team_number_1 = 1;
    unknown_commands_832358.Add(new CreateTeamCommandClass(team_number_1));
    int team_number_2 = 2;
    unknown_commands_832358.Add(new CreateTeamCommandClass(team_number_2));
    int team_number_3 = 3;
    unknown_commands_832358.Add(new CreateTeamCommandClass(team_number_3));
    int team_number_4 = 4;
    unknown_commands_832358.Add(new CreateTeamCommandClass(team_number_4));
    int team_number_5 = 5;
    unknown_commands_832358.Add(new CreateTeamCommandClass(team_number_5));
    unknown_commands_832358.Add(new CreateTeamCommandClass(6));
    unknown_commands_832358.Add(new CreateTeamCommandClass(7));
    unknown_commands_832358.Add(new CreateTeamCommandClass(8));
    unknown_commands_832358.Add(new CreateTeamCommandClass(9));
    unknown_commands_832358.Add(new CreateTeamCommandClass(10));
    unknown_commands_832358.Add(new SelectTeamCommandClass(1));
    unknown_commands_832358.Add(new SelectTeamCommandClass(2));
    unknown_commands_832358.Add(new SelectTeamCommandClass(3));
    unknown_commands_832358.Add(new SelectTeamCommandClass(4));
    unknown_commands_832358.Add(new SelectTeamCommandClass(5));
    unknown_commands_832358.Add(new SelectTeamCommandClass(6));
    unknown_commands_832358.Add(new SelectTeamCommandClass(7));
    unknown_commands_832358.Add(new SelectTeamCommandClass(8));
    unknown_commands_832358.Add(new SelectTeamCommandClass(9));
    unknown_commands_832358.Add(new SelectTeamCommandClass(10));
    unknown_commands_832358.Add(new AddTeamCommandClass(1));
    unknown_commands_832358.Add(new AddTeamCommandClass(2));
    unknown_commands_832358.Add(new AddTeamCommandClass(3));
    unknown_commands_832358.Add(new AddTeamCommandClass(4));
    unknown_commands_832358.Add(new AddTeamCommandClass(5));
    unknown_commands_832358.Add(new AddTeamCommandClass(6));
    unknown_commands_832358.Add(new AddTeamCommandClass(7));
    unknown_commands_832358.Add(new AddTeamCommandClass(8));
    unknown_commands_832358.Add(new AddTeamCommandClass(9));
    unknown_commands_832358.Add(new AddTeamCommandClass(10));
    unknown_commands_832358.Add(new CenterTeamCommandClass(1));
    unknown_commands_832358.Add(new CenterTeamCommandClass(2));
    unknown_commands_832358.Add(new CenterTeamCommandClass(3));
    unknown_commands_832358.Add(new CenterTeamCommandClass(4));
    unknown_commands_832358.Add(new CenterTeamCommandClass(5));
    unknown_commands_832358.Add(new CenterTeamCommandClass(6));
    unknown_commands_832358.Add(new CenterTeamCommandClass(7));
    unknown_commands_832358.Add(new CenterTeamCommandClass(8));
    unknown_commands_832358.Add(new CenterTeamCommandClass(9));
    unknown_commands_832358.Add(new CenterTeamCommandClass(10));
    unknown_commands_832358.Add(new TauntCommandClass(1));
    unknown_commands_832358.Add(new TauntCommandClass(2));
    unknown_commands_832358.Add(new TauntCommandClass(3));
    unknown_commands_832358.Add(new TauntCommandClass(4));
    unknown_commands_832358.Add(new TauntCommandClass(5));
    unknown_commands_832358.Add(new TauntCommandClass(6));
    unknown_commands_832358.Add(new TauntCommandClass(7));
    unknown_commands_832358.Add(new TauntCommandClass(8));
    unknown_commands_832358.Add(new ScreenCaptureCommandClass);
    unknown_commands_832358.Add(new PageUserCommandClass);
    unknown_commands_832358.Add(new CursorPositionCommandClass);
    CommandClass *del = new DeleteCommandClass;
    unknown_commands_832358.Add(del);
    Load_Keyboard_Hotkeys();
    if (unknown_hotkeys_832380.Is_Present(0x2E)) {
        unknown_hotkeys_832380.Remove_Index(0x2E);
    }
    unknown_hotkeys_832380.Add_Index(0x2E, del);
    if (unknown_hotkeys_832380.Is_Present(0x1B)) {
        unknown_hotkeys_832380.Remove_Index(0x1B);
    }
    unknown_hotkeys_832380.Add_Index(0x1B, options);
    if (unknown_hotkeys_832380.Is_Present(0x20)) {
        unknown_hotkeys_832380.Remove_Index(0x20);
    }
    unknown_hotkeys_832380.Add_Index(0x20, center_event);
}

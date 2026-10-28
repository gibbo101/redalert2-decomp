// The multiplayer game modes (RTTI MultiplayerGameMode, vtable 0x007A71B8,
// 45 slots; subclasses MultiplayerBattle, MultiplayerManBattle,
// MultiplayerSiege, FreeForAll, Megawealth, UnholyAlliance, MPCooperative)
// and their teams (RTTI MultiplayerTeam, vtable 0x007A7314, and subclasses).
// Base code is in 0x005B6CD0-0x005B9C40; each mode has its own unit.
//
// Slots are numbered from the vtables; names are unknown_slotN except where
// the bodies say more. The base class's inline virtuals are emitted (and
// kept) in the MultiplayerBattle unit (0x005A2380-0x005A24F0): their bodies
// and stack sizes come from there. Out-of-line slots are declared with no
// parameters until their bodies are recovered (their manglings are bound
// by address only).
#ifndef RA2_SHARED_MULTIPLAYER_GAME_MODE_HPP
#define RA2_SHARED_MULTIPLAYER_GAME_MODE_HPP

#include "shared/vector_class.hpp"
#include "shared/wide_string.hpp"
#include "shared/win32_api.hpp"
#include "shared/wstring.hpp"

class CCINIClass;
class MultiMission;

#include "shared/unknown_player_entry.hpp"

// A team of a game mode: a vptr, the team name and its number.
class MultiplayerTeam {
public:
    MultiplayerTeam(WideString const &name, int number);     // 0x005B9B20
    virtual ~MultiplayerTeam();                               // 0x005B9B50 (scalar deleting 0x005B9C20)
    // Slot 1: true for a valid player list index.
    virtual bool unknown_slot1(int player);                   // 0x005B9B60
    // Slot 2: puts a valid player on this team.
    virtual bool unknown_slot2(int player);                   // 0x005B9B80
    // The number of players on this team.
    int unknown_count_members_5b9bb0() const;                 // 0x005B9BB0
    // Adds the team name to a combo box with the team number as item data;
    // returns the new item's index.
    int unknown_add_to_combo_5b9be0(HWND combo);              // 0x005B9BE0

    WideString Name;                                          // +0x04
    int Number;                                               // +0x08
};

// A network-session test (0x0073C370; false unless game mode 4).
bool unknown_73c370();

// Empties a combo box (0x006007F0).
void __fastcall unknown_reset_combo_6007f0(HWND combo);

// The team number as wide text (0x007710C0; swprintf "%d").
WideString __fastcall unknown_number_text_7710c0(int number);


class MultiplayerGameMode {
public:
    MultiplayerGameMode(void const *unknown_1, int unknown_2, int unknown_3, int unknown_4, int unknown_5,
                        int unknown_6);                       // 0x005B6CD0
    virtual ~MultiplayerGameMode();                           // 0x005B6E20 (scalar deleting 0x005B8E10)
    virtual bool unknown_slot1() { return false; }               // 1 0x005A2380
    virtual bool unknown_slot2() { return false; }               // 2 0x005A2390
    virtual bool unknown_slot3(int unknown) { return true; }     // 3 0x005A23A0
    virtual bool unknown_slot4();                                  // 4 0x005B7350
    virtual bool unknown_slot5(WideString *message);                                // 5 0x005B73A0
    virtual bool unknown_slot6();                                  // 6 0x005B73D0
    virtual bool unknown_slot7(int unknown);                       // 7 0x005B7830 (true)
    virtual void unknown_slot8() {}                              // 8 0x005A23B0
    virtual void unknown_slot9() {}                              // 9 0x005A23C0
    virtual int unknown_slot10();                                  // 10 0x005B6EB0 (-2)
    virtual bool unknown_slot11();                                 // 11 0x005B73E0 (unknown_34)
    virtual bool unknown_slot12();                                 // 12 0x005B73F0
    // Slot 13: the index of the first multiplayer map this mode can play
    // (unknown_5b7470), or -1.
    virtual int unknown_slot13();                                  // 13 0x005B7400
    virtual void unknown_slot14(HWND combo, DynamicVectorClass<int> const *items, int selected);                               // 14 0x005B74E0
    virtual void unknown_slot15(HWND list, DynamicVectorClass<int> const *items, int selected);                               // 15 0x005B7550
    virtual void unknown_slot16(HWND combo, int team);                                // 16 0x005B75D0
    virtual bool unknown_slot17(int unknown_1, VectorClass<int> unknown_list, int unknown_2, int unknown_3) { return false; } // 17 0x005A23F0
    virtual bool unknown_slot18(int unknown_1, VectorClass<int> unknown_list, int unknown_2, int unknown_3, int unknown_4, int unknown_5) { return false; } // 18 0x005A23D0
    virtual bool unknown_slot19(int unknown_1, int unknown_2, int unknown_3) { return true; } // 19 0x005A2410
    virtual bool unknown_slot20();                                 // 20 0x005B73B0 (true)
    virtual bool unknown_slot21();                                 // 21 0x005B73C0 (true)
    virtual bool unknown_slot22() { return true; }               // 22 0x005A2420
    virtual void unknown_slot23();                                 // 23 0x005B74C0 (the session's 0x00672940)
    virtual void unknown_slot24();                                 // 24 0x005B74D0 (slot 23)
    virtual void unknown_slot25(int unknown_1, int unknown_2) {} // 25 0x005A2430
    virtual bool unknown_slot26();                                 // 26 0x005B7820
    virtual void unknown_slot27();                                 // 27 0x005B7C00
    virtual bool unknown_slot28();                                 // 28 0x005B8420 (true)
    virtual bool unknown_slot29();                                 // 29 0x005B8470 (true)
    virtual void unknown_slot30() {}                             // 30 0x005A2440
    virtual void unknown_slot31() {}                             // 31 0x005A2450
    virtual int unknown_slot32() { return -1; }                  // 32 0x005A2460
    virtual void unknown_slot33() {}                             // 33 0x005A2470
    virtual void unknown_slot34(int unknown) {}                  // 34 0x005A2480
    virtual void unknown_slot35(int unknown) {}                  // 35 0x005A2490
    virtual bool unknown_slot36() { return false; }              // 36 0x005A24A0
    virtual void unknown_slot37() {}                             // 37 0x005A24B0
    virtual void unknown_slot38() {}                             // 38 0x005A24C0
    virtual bool unknown_slot39(VectorClass<int> unknown_list, int unknown_1, int unknown_2, int unknown_3) { return false; } // 39 0x005A24D0
    virtual bool unknown_slot40() { return true; }               // 40 0x005A24F0
    virtual void unknown_slot41(DynamicVectorClass<MultiplayerTeam *> *teams);                               // 41 0x005B7720
    virtual void unknown_slot42();                                 // 42 0x005B7920
    virtual void unknown_slot43();                                 // 43 0x005B7F90
    virtual void unknown_slot44();                                 // 44 0x005B8060

    MultiplayerTeam *unknown_find_team_5b76b0(int number);   // 0x005B76B0
    void unknown_clear_teams_5b77e0();                       // 0x005B77E0
    int unknown_team_of_5b8430(int id);                      // 0x005B8430
    // Whether this mode can play the multiplayer map (0x005B7470).
    bool unknown_5b7470(MultiMission *map);
    // The registered game modes (a function-local static, 0x005B6C30).
    static DynamicVectorClass<MultiplayerGameMode *> &unknown_modes_5b6c30();
    // The first registered mode, or none (0x005B6EC0).
    static MultiplayerGameMode *unknown_first_mode_5b6ec0();
    // The number of registered modes (0x005B6F80).
    static int unknown_mode_count_5b6f80();
    // The registered mode whose unknown_28 is the id, or none (0x005B6FE0).
    static MultiplayerGameMode *__fastcall unknown_find_mode_5b6fe0(int id);
    // Fills a combo box (reset by 0x006007F0) with the modes' names, each
    // mode as item data, and selects the mode with the id; in game mode 5 only
    // modes whose slot 12 agrees are listed (0x005B70B0).
    static void __fastcall unknown_fill_combo_5b70b0(HWND combo, int id);

    // Creates a game mode of one class (RTTI MultiplayerGameMode::
    // InitializerBase, vtable 0x007A72B0, and Initializer<T>).
    class InitializerBase {
    public:
        virtual ~InitializerBase() {}                                     // scalar deleting 0x005B8EC0
        virtual MultiplayerGameMode *Create(void const *unknown_1, int unknown_2, int unknown_3, int unknown_4,
                                            int unknown_5, int unknown_6) = 0;
    };
    template <class T>
    class Initializer : public InitializerBase {
    public:
        virtual MultiplayerGameMode *Create(void const *unknown_1, int unknown_2, int unknown_3, int unknown_4,
                                            int unknown_5, int unknown_6)
        {
            return new T(unknown_1, unknown_2, unknown_3, unknown_4, unknown_5, unknown_6);
        }
    };
    // Registers a mode by name (0x005B8490; reads its settings).
    static void __fastcall unknown_register_5b8490(Wstring const &name, InitializerBase const &initializer);
    // Recreates the mode list: deletes the old modes and registers the six
    // modes (0x005B8BD0).
    static void unknown_init_modes_5b8bd0();
    // Deletes the registered modes (0x005B8D40).
    static void unknown_delete_modes_5b8d40();

    bool unknown_04;                                        // +0x04
    DynamicVectorClass<MultiplayerTeam *> Teams;            // +0x08
    WideString unknown_name_20;                             // +0x20
    WideString unknown_name_24;                             // +0x24
    int unknown_28;                                         // +0x28
    Wstring unknown_2c;                                     // +0x2C
    Wstring unknown_30;                                     // +0x30
    bool unknown_34;                                        // +0x34 (slot 11 returns it)
    CCINIClass *unknown_ini_38;                             // +0x38 (made by the constructor)
    int unknown_3c;                                         // +0x3C (1, or read from the INI)
};

// vtable 0x007A66B4 (scalar deleting destructor 0x005A2500)
class MultiplayerBattle : public MultiplayerGameMode {
public:
    MultiplayerBattle(void const *unknown_1, int unknown_2, int unknown_3, int unknown_4, int unknown_5, int unknown_6);
    virtual ~MultiplayerBattle();
    virtual bool unknown_slot12();                                 // 12 0x005A2370
};

// vtable 0x007A69DC (scalar deleting destructor 0x005A7500)
class MultiplayerManBattle : public MultiplayerGameMode {
public:
    MultiplayerManBattle(void const *unknown_1, int unknown_2, int unknown_3, int unknown_4, int unknown_5, int unknown_6);
    virtual ~MultiplayerManBattle();
};

// vtable 0x007A6B8C (scalar deleting destructor 0x005ABBA0)
class MultiplayerSiege : public MultiplayerGameMode {
public:
    MultiplayerSiege(void const *unknown_1, int unknown_2, int unknown_3, int unknown_4, int unknown_5, int unknown_6);
    virtual ~MultiplayerSiege();
    virtual bool unknown_slot4();                                  // 4 0x005AB5F0
    virtual bool unknown_slot5(WideString *message);                                // 5 0x005AB640
    virtual bool unknown_slot6();                                  // 6 0x005AB740
    virtual bool unknown_slot11();                                 // 11 0x005AB750 (false)
    virtual bool unknown_slot26();                                 // 26 0x005AB760
    virtual void unknown_slot27();                                 // 27 0x005AB770
    virtual void unknown_slot41(DynamicVectorClass<MultiplayerTeam *> *teams);                               // 41 0x005AB970
    virtual void unknown_slot43();                                 // 43 0x005ABA80
};

// vtable 0x007A6914 (scalar deleting destructor 0x005A71C0)
class FreeForAll : public MultiplayerGameMode {
public:
    FreeForAll(void const *unknown_1, int unknown_2, int unknown_3, int unknown_4, int unknown_5, int unknown_6);
    virtual ~FreeForAll();
    virtual bool unknown_slot4();                                  // 4 0x005A70B0
    virtual bool unknown_slot5(WideString *message);                                // 5 0x005A70C0
    virtual bool unknown_slot6();                                  // 6 0x005A7110
    virtual bool unknown_slot12();                                 // 12 0x005A71B0
    virtual void unknown_slot16(HWND combo, int team);                                // 16 0x005A7150
};

// vtable 0x007A6AA4 (scalar deleting destructor 0x005AA780)
class Megawealth : public MultiplayerGameMode {
public:
    Megawealth(void const *unknown_1, int unknown_2, int unknown_3, int unknown_4, int unknown_5, int unknown_6);
    virtual ~Megawealth();
    virtual bool unknown_slot29();                                 // 29 0x005AA770
};

// vtable 0x007A6C84 (scalar deleting destructor 0x005AC510)
class UnholyAlliance : public MultiplayerGameMode {
public:
    UnholyAlliance(void const *unknown_1, int unknown_2, int unknown_3, int unknown_4, int unknown_5, int unknown_6);
    virtual ~UnholyAlliance();
    virtual bool unknown_slot4();                                  // 4 0x005AC380
    virtual bool unknown_slot5(WideString *message);                                // 5 0x005AC390
    virtual bool unknown_slot6();                                  // 6 0x005AC3C0
    virtual void unknown_slot43();                                 // 43 0x005AC3D0
};

// vtable 0x007A678C (scalar deleting destructor 0x005A62B0)
class MPCooperative : public MultiplayerGameMode {
public:
    MPCooperative(void const *unknown_1, int unknown_2, int unknown_3, int unknown_4, int unknown_5, int unknown_6);
    virtual ~MPCooperative();
    virtual bool unknown_slot1();                                  // 1 0x005A6280
    virtual bool unknown_slot2();                                  // 2 0x005A6290
    virtual bool unknown_slot4();                                  // 4 0x005A2D70
    virtual bool unknown_slot5(WideString *message);                                // 5 0x005A32E0
    virtual bool unknown_slot6();                                  // 6 0x005A3320
    virtual bool unknown_slot7(int unknown);                       // 7 0x005A2CD0
    virtual void unknown_slot8();                                  // 8 0x005A2EF0
    virtual void unknown_slot9();                                  // 9 0x005A31F0
    virtual int unknown_slot10();                                  // 10 0x005A34B0
    virtual bool unknown_slot11();                                 // 11 0x005A46B0
    virtual int unknown_slot13();                                  // 13 0x005A3200
    virtual void unknown_slot15(HWND list, DynamicVectorClass<int> const *items, int selected);                               // 15 0x005A4B70
    virtual void unknown_slot16(HWND combo, int team);                                // 16 0x005A3F70
    virtual bool unknown_slot18(int unknown_1, VectorClass<int> unknown_list, int unknown_2, int unknown_3, int unknown_4, int unknown_5); // 18 0x005A3500
    virtual bool unknown_slot19(int unknown_1, int unknown_2, int unknown_3); // 19 0x005A35D0
    virtual bool unknown_slot20();                                 // 20 0x005A38D0
    virtual bool unknown_slot21();                                 // 21 0x005A3960
    virtual bool unknown_slot22();                                 // 22 0x005A4250
    virtual void unknown_slot23();                                 // 23 0x005A4540
    virtual void unknown_slot24();                                 // 24 0x005A45F0
    virtual void unknown_slot25(int unknown_1, int unknown_2);     // 25 0x005A3CA0
    virtual bool unknown_slot26();                                 // 26 0x005A3EE0
    virtual void unknown_slot27();                                 // 27 0x005A4170
    virtual bool unknown_slot28();                                 // 28 0x005A43C0
    virtual bool unknown_slot29();                                 // 29 0x005A46A0
    virtual void unknown_slot30();                                 // 30 0x005A5000
    virtual void unknown_slot31();                                 // 31 0x005A5190
    virtual int unknown_slot32();                                  // 32 0x005A5340
    virtual void unknown_slot33();                                 // 33 0x005A4F90
    virtual void unknown_slot34(int unknown);                      // 34 0x005A46C0
    virtual void unknown_slot35(int unknown);                      // 35 0x005A5570
    virtual bool unknown_slot36();                                 // 36 0x005A5350
    virtual void unknown_slot37();                                 // 37 0x005A5720
    virtual void unknown_slot38();                                 // 38 0x005A6040
    virtual bool unknown_slot39(VectorClass<int> unknown_list, int unknown_1, int unknown_2, int unknown_3); // 39 0x005A6230
    virtual bool unknown_slot40();                                 // 40 0x005A62A0
    virtual void unknown_slot42();                                 // 42 0x005A3F90
};

// vtable 0x007A676C (scalar deleting destructor 0x005A25F0)
class MultiplayerBattleTeam : public MultiplayerTeam {
public:
    MultiplayerBattleTeam(WideString const &name, int number);   // 0x005A2530
    virtual bool unknown_slot1(int unknown);                  // 0x005A25B0
    virtual bool unknown_slot2(int unknown);                  // 0x005A25D0
};

// vtable 0x007A6B5C (scalar deleting destructor 0x005AA810)
class MultiplayerObserverTeam : public MultiplayerTeam {
public:
    MultiplayerObserverTeam();
    virtual bool unknown_slot1(int unknown);                  // 0x005AA800
};

// vtable 0x007A6C54 (scalar deleting destructor 0x005ABEC0)
class MultiplayerSiegeDefenderTeam : public MultiplayerTeam {
public:
    MultiplayerSiegeDefenderTeam();
    virtual bool unknown_slot1(int unknown);                  // 0x005ABE20
};

// vtable 0x007A6C64 (scalar deleting destructor 0x005ABEF0)
class MultiplayerSiegeAttackerTeam : public MultiplayerTeam {
public:
    MultiplayerSiegeAttackerTeam();
};

#endif

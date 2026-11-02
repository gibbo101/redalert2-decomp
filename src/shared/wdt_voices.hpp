// WorldDominationTour::Voices (WDTVoices, unit 0x007312D0-0x00732CAF): the
// campaign map's spoken commentary. Six voice groups (OldCycle, History,
// Status, Territory, Game, Evacuate) each hold Win/Lose/Draw line numbers
// (plain and Emphasis) per faction section of an INI; two more lists
// (Startup, TerritorySelect) hang off the Voices object. Picked lines become
// speech names "WWD_Allied<NN>" / "WWD-Soviet<NN>" (faction 3) and are queued,
// then played one by one by Update (driven by a Voices::Anim added to the
// map's MSEngine). RTTI names: WorldDominationTour::Voices::Anim (vtable
// 0x007AF40C, base MSAnim); the rest are hypotheses.
#ifndef RA2_SHARED_WDT_VOICES_HPP
#define RA2_SHARED_WDT_VOICES_HPP

#include "shared/world_domination_tour.hpp"
#include "shared/random.hpp"
#include "shared/vox_class.hpp"

struct AudioDevice;
struct AudioStreamPlayer;
AudioDevice *Audio_Get_Device();                                    // 0x00406F40
void __fastcall Audio_Stream_Destroy(AudioStreamPlayer *stream);    // 0x004079C0
int __fastcall Unknown_00716640(char const *name);                 // 0x00716640 (voice index by name)
extern Random2Class unknown_random_839218;                          // 0x00839218
// The faction name of a faction number (0x007685A0; function statics, the
// counterpart of Faction_Code 0x007686D0). Name is a hypothesis.
Wstring const &__fastcall Faction_Name(int faction);

namespace WorldDominationTour {

class Voices {
public:
    // One voice group: its INI key prefix and the lines per result.
    struct Group {
        Group();                                                    // 0x00732060

        void Load(INIClass &ini, Wstring const &section, int faction);                          // 0x007320C0
        void Load(INIClass &ini, Wstring const &section, int faction, int kind, Wstring const &key);   // 0x00732300
        bool Pick(int faction, int kind, Wstring &name) const;                                  // 0x00732160
        bool Pick_Emphasis(int faction, int kind, Wstring &name) const;                         // 0x00732230
#ifdef WDT_VOICES_DECLARE_SET_NAME
        // Inline in the Voices constructor (0x007314C0), which names the groups.
        void Set_Name(Wstring const &name) { Name = name; }
#endif

        Wstring Name;                                               // +0x00
        // The line numbers per result (Win, Lose, Draw): plain at
        // [kind * 2], Emphasis at [kind * 2 + 1].
        DynamicVectorClass<unsigned> Lines[6];                      // +0x04
    };

    // Plays the queue as the engine draws it (RTTI vtable 0x007AF40C). The
    // members are defined in the Voices unit after Create_Anim, which
    // expands the constructor.
    //   +0x1C Voices *Owner   size 0x20
    class Anim : public MSAnim {
    public:
        Anim(Voices *owner);                                        // 0x00732AA0
        virtual ~Anim();                                            // 0x00732AE0
        virtual void Set_Unknown_0C(bool value);                    // 0x00732AF0 (false stops the voices)
        virtual void Pause();                                       // 0x00732B50
        virtual void Resume();                                      // 0x00732BA0
        virtual bool Unknown_Slot4(Surface *surface, Rect *dirty);  // 0x00732BC0
        virtual void Draw(Surface *surface, Rect const *clip);      // 0x00732BD0
        virtual Rect Get_Rect();                                    // 0x00732BE0 (an unset rectangle)
        virtual bool Unknown_Slot7();                               // 0x00732C10 (true once nothing is said)
        virtual void Unknown_Slot8(int unknown1);                   // 0x00732C20

        Voices *Owner;                                              // +0x1C
    };

    Voices(int faction);                                            // 0x007314C0
    ~Voices();                                                      // 0x00731680

    void Load(INIClass &ini, Wstring const &section);               // 0x007317A0
    void Load_List(INIClass &ini, Wstring const &section, int index, Wstring const &key);   // 0x00731AA0
    bool Pick(int group, int kind, Wstring &name) const;            // 0x00731BC0
    bool Pick_Emphasis(int group, int kind, Wstring &name) const;   // 0x00731CA0
    bool Pick_List(int index, Wstring &name) const;                 // 0x00731D80
    static bool __fastcall Pick(int faction, DynamicVectorClass<unsigned> const &lines, Wstring &name);   // 0x00731E60
    static bool __fastcall Make_Name(int faction, int line, Wstring &name);   // 0x00731F30
    static void __fastcall Parse_List(Wstring const &text, DynamicVectorClass<unsigned> &lines);   // 0x00731FC0
    void Say(int group, int kind, bool emphasis, bool counted, int delay);   // 0x00732510
    void Say_List(int index, bool counted, int delay);              // 0x00732700
    void Update();                                                  // 0x00732870
    void Trim();                                                    // 0x00732960
    void Stop();                                                    // 0x007329F0
    bool Is_Speaking();                                             // 0x00732A40
    Anim *Create_Anim();                                            // 0x00732A50

    int Faction;                                                    // +0x000
    Group Groups[6];                                                // +0x004
    DynamicVectorClass<unsigned> Lists[2];                          // +0x37C Startup, TerritorySelect
    CDTimerClass<SystemTimerClass> Timer;                           // +0x3AC
    bool Idle;                                                      // +0x3B8 nothing being said
    int Pending;                                                    // +0x3BC queued lines kept by Trim
    DynamicVectorClass<Wstring> Queue;                              // +0x3C0 speech names
    AudioStreamPlayer *Stream;                                      // +0x3D8
};

}

#endif

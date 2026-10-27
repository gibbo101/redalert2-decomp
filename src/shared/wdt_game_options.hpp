// The World Domination Tour game options (WDTGameOptions.cpp, unit
// 0x00728480-0x00728C5F; ValueGameOption<T> from wdtgameoptions.h) and the
// option list of Conflict.cpp, separate from shared/world_domination_tour.hpp
// so that the other units do not instantiate DynamicVectorClass<rc_ptr<GameOption>>.
#ifndef RA2_SHARED_WDT_GAME_OPTIONS_HPP
#define RA2_SHARED_WDT_GAME_OPTIONS_HPP

#include "shared/world_domination_tour.hpp"

namespace WorldDominationTour {

// RTTI vtable 0x007AF118; WDTGameOptions.cpp (unit 0x00728480-0x00728C5F)
// with the template ValueGameOption<T> in wdtgameoptions.h. One battle
// option of a conflict: Flag is its bit in the description's used mask.
// Slot 3 gives the option's value for a territory (2: forced), slot 4 its
// description (both pure here: __purecall).
//   +0x08 int Flag   size 0x0C (MapSizeGameOption adds nothing)
class GameOption : public ReferenceCounted {
public:
    GameOption(int flag) :
        Flag(flag)
    {
    }
    virtual ~GameOption();                                          // 0x00728670
    virtual int Get_Value(rc_ptr<WDTTerritory> const &territory) const = 0;                       // slot 3
    virtual WideString Describe(rc_ptr<WDTTerritory> const &territory, WideString const &prefix) const = 0;   // slot 4

    bool Is_Forced(rc_ptr<WDTTerritory> const &territory) const;   // 0x00728680 (false)

    int Flag;                                                       // +0x08
};

// An option read from the territory through Getter (RTTI
// ValueGameOption<unsigned char>, vtable 0x007AF100; members expanded in
// Conflict.cpp). Describe formats the getter's value with Name's CSF text.
//   +0x0C int Value (default), +0x10 Getter, +0x14 Wstring Name   size 0x18
template <class T>
class ValueGameOption : public GameOption {
public:
    typedef int (__fastcall *GetterType)(WDTTerritory const *territory);

    ValueGameOption(int flag, GetterType getter, Wstring name, int value) :
        GameOption(flag),
        Value(value),
        Getter(getter),
        Name(name)
    {
    }

    static rc_ptr<ValueGameOption<T> > __fastcall Create(int flag, GetterType getter, Wstring name, int value)
    {
        return rc_ptr<ValueGameOption<T> >(new ValueGameOption<T>(flag, getter, name, value));
    }

    virtual int Get_Value(rc_ptr<WDTTerritory> const &territory) const
    {
        if (Is_Forced(territory)) {
            return 2;
        }
        return Value;
    }

    virtual WideString Describe(rc_ptr<WDTTerritory> const &territory, WideString const &prefix) const
    {
        Wstring number = Wstring_From_Integer(Getter(territory.Get()));
        WideString format(StringTable::Load_String(Name, 0, "D:\\Ra2\\wdtgameoptions.h", 161));
        wchar_t buffer[64];
        swprintf(buffer, format.Get(), number);
        if (prefix.Length()) {
            WideString separator(L", ");
            prefix + separator + buffer;
        }
        return WideString(buffer);
    }

    int Value;                                                      // +0x0C
    GetterType Getter;                                              // +0x10
    Wstring Name;                                                   // +0x14
};

// RTTI vtable 0x007AF154 (WDTGameOptions.cpp): an on/off option from Flag's
// bit in the territory's OptionFlags.
//   +0x0C int OffValue, +0x10 int OnValue, +0x14 Wstring OnLabel,
//   +0x18 Wstring OffLabel   size 0x1C
class FlagGameOption : public GameOption {
public:
    FlagGameOption(int flag, Wstring off_label, int off_value, Wstring on_label, int on_value) :
        GameOption(flag),
        OffValue(off_value),
        OnValue(on_value),
        OnLabel(on_label),
        OffLabel(off_label)
    {
    }   // 0x00728B90 (out of line)

    static rc_ptr<FlagGameOption> __fastcall Create(int flag, Wstring off_label, int off_value, Wstring on_label,
                                                    int on_value);   // 0x007287D0
    virtual int Get_Value(rc_ptr<WDTTerritory> const &territory) const;                         // 0x00728850
    virtual WideString Describe(rc_ptr<WDTTerritory> const &territory, WideString const &prefix) const;   // 0x00728870

    int OffValue;                                                   // +0x0C
    int OnValue;                                                    // +0x10
    Wstring OnLabel;                                                // +0x14
    Wstring OffLabel;                                               // +0x18
};

// RTTI vtable 0x007AF16C (WDTGameOptions.cpp): the map size option, from
// the territory's +0x12/+0x13 bytes (labels WDT:SmallMap..WDT:VeryLargeMap).
//   size 0x0C
class MapSizeGameOption : public GameOption {
public:
    MapSizeGameOption(int flag) :
        GameOption(flag)
    {
    }

    static rc_ptr<MapSizeGameOption> __fastcall Create(int flag);   // 0x00728A60
    virtual int Get_Value(rc_ptr<WDTTerritory> const &territory) const;                         // 0x00728B70
    virtual WideString Describe(rc_ptr<WDTTerritory> const &territory, WideString const &prefix) const;   // 0x00728AB0
};

// The map size labels (0x007AF140, four CSF labels) and values (0x007FBB78,
// by the territory's +0x12 and +0x13 bytes). Names are hypotheses.
extern char const *const MapSize_Labels[4];
extern int MapSize_Values[4][4];

}

#endif

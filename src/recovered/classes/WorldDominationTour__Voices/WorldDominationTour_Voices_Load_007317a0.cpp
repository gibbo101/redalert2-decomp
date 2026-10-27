// void WorldDominationTour::Voices::Load(INIClass &ini, Wstring const &section) (0x007317A0)
// Every group's Win/Lose/Draw lines and the Startup and TerritorySelect
// lists of the faction.
// Container members: only the ones this unit expands (the Group line
// arrays' constructor, Add, Delete(int) and the accessors). vector_class.hpp
// is included first, before wdt_voices.hpp pulls in shared/ms_engine.hpp,
// whose VECTOR_IMPLEMENT_ALL would otherwise compile every
// DynamicVectorClass<Wstring> virtual member and emit a ??_EWstring that
// the original unit never had.
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/vector_class.hpp"
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

void Voices::Load(INIClass &ini, Wstring const &section)
{
    for (int group = 0; group < 6; group++) {
        Groups[group].Load(ini, section, Faction);
    }
    {
        Wstring key("Startup");
        Load_List(ini, section, 0, key);
    }
    {
        Wstring key("TerritorySelect");
        Load_List(ini, section, 1, key);
    }
}

}

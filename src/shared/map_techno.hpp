// TechnoClass as the Map unit sees it (stand-in, like shared/map_cell.hpp for
// CellClass): the real shared/techno.hpp brings headers the Map unit has not.
// Only the members MapClass touches; slots 24-103 other than 70 are
// placeholders (slot numbers and offsets as shared/object.hpp / techno.hpp).
// Units that include shared/techno.hpp must not include this stand-in.
#ifndef RA2_SHARED_MAP_TECHNO_HPP
#define RA2_SHARED_MAP_TECHNO_HPP

#include "shared/abstract_class.hpp"
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"

class HouseClass;

class TechnoClass : public AbstractClass {
public:
    virtual void unknown_slot24(); virtual void unknown_slot25(); virtual void unknown_slot26(); virtual void unknown_slot27(); virtual void unknown_slot28(); virtual void unknown_slot29();
    virtual void unknown_slot30(); virtual void unknown_slot31(); virtual void unknown_slot32(); virtual void unknown_slot33(); virtual void unknown_slot34(); virtual void unknown_slot35();
    virtual void unknown_slot36(); virtual void unknown_slot37(); virtual void unknown_slot38(); virtual void unknown_slot39(); virtual void unknown_slot40(); virtual void unknown_slot41();
    virtual void unknown_slot42(); virtual void unknown_slot43(); virtual void unknown_slot44(); virtual void unknown_slot45(); virtual void unknown_slot46(); virtual void unknown_slot47();
    virtual void unknown_slot48(); virtual void unknown_slot49(); virtual void unknown_slot50(); virtual void unknown_slot51(); virtual void unknown_slot52(); virtual void unknown_slot53();
    virtual void unknown_slot54(); virtual void unknown_slot55(); virtual void unknown_slot56(); virtual void unknown_slot57(); virtual void unknown_slot58(); virtual void unknown_slot59();
    virtual void unknown_slot60(); virtual void unknown_slot61(); virtual void unknown_slot62(); virtual void unknown_slot63(); virtual void unknown_slot64(); virtual void unknown_slot65();
    virtual void unknown_slot66(); virtual void unknown_slot67(); virtual void unknown_slot68(); virtual void unknown_slot69();
    virtual void unknown_slot70(bool arg1, bool arg2);              // slot 70 (+0x118; as shared/techno.hpp)
    virtual void unknown_slot71(); virtual void unknown_slot72(); virtual void unknown_slot73(); virtual void unknown_slot74(); virtual void unknown_slot75(); virtual void unknown_slot76();
    virtual void unknown_slot77(); virtual void unknown_slot78(); virtual void unknown_slot79(); virtual void unknown_slot80(); virtual void unknown_slot81(); virtual void unknown_slot82();
    virtual void unknown_slot83(); virtual void unknown_slot84(); virtual void unknown_slot85(); virtual void unknown_slot86(); virtual void unknown_slot87(); virtual void unknown_slot88();
    virtual void unknown_slot89(); virtual void unknown_slot90(); virtual void unknown_slot91(); virtual void unknown_slot92(); virtual void unknown_slot93(); virtual void unknown_slot94();
    virtual void unknown_slot95(); virtual void unknown_slot96(); virtual void unknown_slot97(); virtual void unknown_slot98(); virtual void unknown_slot99(); virtual void unknown_slot100();
    virtual void unknown_slot101(); virtual void unknown_slot102(); virtual void unknown_slot103();
    virtual Cell unknown_slot104() const;                            // slot 104 (+0x1A0) the object's cell (as shared/object.hpp)

    char unknown_24[0x76 - 0x24];
    bool unknown_76;                        // +0x76 (as shared/object.hpp)
    char unknown_77[0x7D - 0x77];
    bool unknown_7d;                        // +0x7D (as shared/object.hpp)
    char unknown_7e[0x1B4 - 0x7E];
    HouseClass *House;                      // +0x1B4 (as shared/techno.hpp)
    char unknown_1b8[0x32D - 0x1B8];
    bool unknown_32d;                       // +0x32D (as shared/techno.hpp)
};

// Every techno (0x00A40C20; as shared/planning.hpp).
extern DynamicVectorClass<TechnoClass *> unknown_list_a40c20;

#endif

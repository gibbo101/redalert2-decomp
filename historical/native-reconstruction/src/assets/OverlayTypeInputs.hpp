// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace ra2 {
// Selected fields only; base ObjectType construction/INI parsing are services.
// Image/animation handles are supplied identities, not original addresses.
struct OverlayTypeInputs {
    std::string id,imageName;
    int index=-1,land=0,damageLevels=1,strength=1,armor=0;
    std::uint32_t cellAnim=0,image=0;
    int imageMaximum=0; // Selected ObjectType field1BC; initial value supplied.
    std::uint8_t alternateArctic=0,arcticInUse=0; // Fields1E1/1E2.
    std::uint8_t newTheater=0; // Selected base ObjectType art field207; construction/INI association separate.
    std::uint8_t theater=0,crushable=0,radarInvisible=0,selectable=0,
        insignificant=0,flag205=0;
    std::uint8_t wall=0,tiberium=0,crate=0,crateTrigger=0,noUseTileLandType=1,
        veinhole=0,veins=0,demandLoad=0,explodes=0,chainReaction=0,
        overrides=0,drawFlat=1,rubble=0,rock=0;
};
struct OverlayTypeRegistry {
    // Capacity slots, including retained unused tail. Storage is native-owned.
    std::vector<OverlayTypeInputs*> slots;
    int count=0,growth=1;
    std::uint8_t owns=1;
};
struct OverlayConstructionServices {
    std::function<void(OverlayTypeInputs&,std::string_view)> base;
    // The service may replace/resize slots on success. No original heap claim.
    std::function<bool(int)> grow;
    std::function<OverlayTypeInputs*()> allocate;
    std::function<bool(std::string_view,std::string_view)> equal;
    // Original selected stores and registry mutations, for ordered comparison.
    std::function<void(OverlayTypeInputs&,unsigned,unsigned,std::uint32_t)> store;
    std::function<void(unsigned,std::uint32_t)> registryStore;
};
void constructOverlayType(OverlayTypeInputs&,std::string_view,OverlayTypeRegistry&,
    const OverlayConstructionServices&);
OverlayTypeInputs* resolveOverlayType(std::string_view,OverlayTypeRegistry&,
    const OverlayConstructionServices&);
// Complete list parent: positive entry count determines success, even if every
// value is empty/none or allocation fails. Key enumeration/parser stay supplied.
bool readOverlayTypeList(int count,const std::function<std::pair<int,std::string>(int)>&,
    OverlayTypeRegistry&,const OverlayConstructionServices&);

struct OverlayIniServices {
    std::function<bool(OverlayTypeInputs&)> base;
    std::function<int(bool,std::string_view,std::string_view,int)> integer;
    std::function<int(bool,std::string_view,std::string_view,std::uint8_t)> boolean;
    std::function<std::pair<int,std::string>(std::string_view)> cellAnimation;
    std::function<std::uint32_t(std::string_view)> resolveAnimation,loadImage;
    std::function<void(unsigned,unsigned,std::uint32_t)> store;
};
bool readOverlayTypeIni(OverlayTypeInputs&,const OverlayIniServices&);
}

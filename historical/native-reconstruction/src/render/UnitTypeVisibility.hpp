// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <optional>
namespace ra2 {
// These decisions select an image/type; they do not implement fog or discovery.
// The clock and fields are supplied by the actor owner, not a wall clock.
bool unitDrawTimerHasRemainder(int start,int duration,int currentFrame);
struct UnitDisguiseState {
    std::uint8_t disguised=0;
    int creationFrame=0,timerStart=0,timerDuration=0;
};
struct UnitDrawingDefaults {
    UnitDisguiseState disguise;
    int timerStart=0,timerDuration=0,alternateType=0,flagHouse=-1;
    std::int8_t screenOffset=0;
    std::uint8_t bridge=0,addFourteen=0;
};
// Scoped constructor fields only: no allocation, type loading or full actor init.
UnitDrawingDefaults initialUnitDrawingFields(int currentFrame);
bool unitOwnerTypeVisible(int mode,std::uint8_t flag134,std::uint8_t flag135,bool isCurrent);
bool unitOwnerAlliedToCurrent(bool currentPresent,bool sameHouse,int ownerIndex,
                             int currentIndex,std::uint32_t alliances);
using UnitTypeTrace=std::function<void(char)>;
// getCell returns the observer's signed sensor count, or no cell. Observer index
// validation and current-cell storage belong to the map adapter. It is queried
// even for an undisguised actor on the non-owner branch, matching original order.
bool originalUnitTypeVisible(const UnitDisguiseState&,int currentFrame,
                            const std::function<bool()>& ownerVisible,
                            const std::function<std::optional<std::int16_t>()>& getCell,
                            const UnitTypeTrace& trace={});
int selectUnitDisplayType(int originalType,int alternateType,int argument,
                         const std::function<bool()>& allied);
}

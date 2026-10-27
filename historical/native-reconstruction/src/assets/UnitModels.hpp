// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <array>
#include <cstdint>
#include <functional>
#include <string>
#include <string_view>

namespace ra2 {
// Tokens identify supplied resources, not guest addresses or owned heap pointers.
using ModelToken=std::uintptr_t;
enum class ModelKind { Voxel, Animation };
enum class ModelField { Voxel, Animation, MaximumDimension, CachePointer,
                        CacheCount, CacheCapacity, CacheFlag, CacheTail };
struct ModelPair { ModelToken voxel=0,animation=0; };
struct ModelCacheRecord {
    ModelToken pointer=0;
    std::uint32_t count=0,capacity=0;
    std::uint8_t flag=0;
    std::uint32_t tail=0;
};
struct OrdinaryUnitModels {
    std::string image;
    std::uint8_t turret=1;
    int turretCount=0;
    std::array<ModelPair,3> parts; // body, ordinary turret, ordinary barrel
    int maximumDimension=0;
    std::array<ModelCacheRecord,4> caches;
};
struct ModelSection {
    std::uint32_t animationAssociation=0;
    std::array<std::uint8_t,3> dimensions{};
};
struct UnitModelServices {
    std::function<ModelToken(std::string_view)> open;
    std::function<std::uint8_t(ModelToken)> available;
    std::function<void(ModelToken)> close;
    std::function<void(ModelKind,ModelToken)> destroy;
    std::function<void(ModelToken)> release;
    std::function<ModelToken(ModelKind)> allocate;
    std::function<void(ModelKind,ModelToken,ModelToken)> construct;
    std::function<std::uint8_t(ModelToken)> errorByte;
    std::function<int(ModelToken)> sectionCount;
    std::function<ModelSection(ModelToken,int)> section;
    std::function<void(ModelToken,std::uint32_t)> associateAnimation;
    // Read-only query/observer boundaries; callbacks must not mutate this record.
    std::function<void()> queryKind,queryMultipleTurrets;
    std::function<void(ModelField,int,ModelToken)> stored;
};
// Recovered ordinary UnitType, nonzero Turret, TurretCount=0 protocol only.
// File, allocation, parsing, construction and ownership services are supplied.
// A false result clears body/turret, retains barrel and leaves caches untouched.
bool loadOrdinaryUnitModels(OrdinaryUnitModels&,const UnitModelServices&);
}

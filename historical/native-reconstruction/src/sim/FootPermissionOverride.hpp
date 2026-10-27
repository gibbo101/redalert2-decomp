// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
namespace ra2 {
struct FootPermissionOverrideActor {
    const std::uint8_t& active32d;
    const std::uint8_t& flag32c;
    const void* const& team4c4;
};
struct FootPermissionOverrideServices {
    std::function<std::uint8_t()> typeTrainAa0;
    std::function<std::int32_t()> mission;
    std::function<std::uint8_t(const void*)> teamPredicate;
};
// Complete4C8CA0. Initial associations and the nonnull Team6BA990 child are
// supplied. Preserve late actor reads and original short-circuit query order.
bool footPermissionOverride(FootPermissionOverrideActor,const FootPermissionOverrideServices&);
}

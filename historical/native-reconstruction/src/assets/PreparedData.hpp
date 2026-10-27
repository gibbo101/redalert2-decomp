// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Bytes.hpp"
#include <string_view>
namespace ra2 {
inline constexpr std::string_view DiscEngineSha="135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743";
inline constexpr std::string_view PatchedEngineSha="e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f";
std::string assetSha256(const Data&);
std::string verifiedEngineDataSource(const Data&);
// Exact file hashes include their source identity. Optional expected source
// prevents combining prepared files from different executable profiles.
void validatePreparedData(const Data&,std::size_t size,std::string_view discHash,
    std::string_view patchedHash,std::string_view expectedSource={});
std::filesystem::path preparedDataPath(std::string_view source,const char* filename);
}

// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/GameAssets.hpp"
namespace ra2 {
int runBootCampPreview(const GameAssets&,const std::string& renderPath,bool walking=false,const std::filesystem::path& smokeOutput={});
}

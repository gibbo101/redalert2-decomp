// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <string_view>
#include "assets/Bytes.hpp"
#include "sim/Drive.hpp"
namespace ra2 {
// Read verified tracks and optional prepared direction data. No original
// instructions are mapped for execution or called by the application.
std::shared_ptr<const DriveData> readDriveData(const Data& executable,const Data& directionData=Data{});
DirectionData readDirectionData(const Data& preparedData,std::string_view expectedSource={});
}

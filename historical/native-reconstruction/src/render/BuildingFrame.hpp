// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/BuildingImage.hpp"
#include <array>
#include <span>
namespace ra2 {
struct BuildingFrameSequence { std::int32_t start=0,count=0,duration=0; };
// Supplied startup, on the existing Type. Sequence0 borrows images.C8C/C90;
// sequences1..5 follow at twelve-byte intervals. No second image owner.
struct BuildingFrameTypeState {
    std::uint8_t flag1359=0,flag135a=0,flag121e=0;
    std::array<BuildingFrameSequence,5> sequences{};
};
struct BuildingFrameType {
    const BuildingImageState& images;
    const BuildingFrameTypeState& fields;
};
struct BuildingAnimationFrameFields {
    const std::int32_t& frameE0;
    const std::int32_t& stage42c;
    const std::int32_t& frame4ec;
    const std::int32_t& frame4f0;
    const std::int32_t& field564;
};
struct BuildingFrameServices {
    std::function<BuildingFrameType()> type;
    std::function<std::int32_t()> mission16c;
    std::function<double()> healthRatio5d4540;
    std::function<double()> threshold1368,threshold1370;
    // Read-only observation: subject0 actor, subject1 current/retained Type.
    std::function<void(int,int,std::int32_t)> read;
};
// Complete43BE20, including all returns. Children must be bound when entered.
// Initial frame/type/stage associations and thresholds remain supplied.
std::int32_t buildingAnimationFrame(BuildingAnimationFrameFields,const BuildingFrameServices&);
}

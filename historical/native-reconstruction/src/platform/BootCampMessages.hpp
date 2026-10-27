// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/GameAssets.hpp"
#include "render/OwnedMessagePresentation.hpp"
namespace ra2 {
// Supplied native startup for the current 1024x720 walking viewport. Original
// ColorScheme ordering/layout/audio association and UI scheduling remain open.
inline std::unique_ptr<OwnedMessagePresentation> makeBootCampMessages(const GameAssets& assets){
    auto font=std::make_shared<const GameFont>(assets.store.require("game.fnt"));
    MessagePresentationConfig c;c.surfaceWidth=1024;c.surfaceHeight=720;
    c.x=12;c.y=96;c.width=1000;c.maximumLines=6;c.lineStep=font->metrics().lineHeight;
    c.mode=0;c.clockStart=0;c.insertSound=-1;c.drawSound=-1;
    c.fillPolicy=MessageFillPolicy::softwareDisplay; // Explicit native software surface, not DirectDraw startup.
    c.colors.assign(9,assets.playerColors.at("lightgrey")); // Explicit temporary association, not original scheme order.
    c.packing={{11,3,0,3,5,2},{255,255,255}};
    return std::make_unique<OwnedMessagePresentation>(std::move(font),std::move(c));
}
}

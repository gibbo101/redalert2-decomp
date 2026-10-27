// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/OwnedMessagePresentation.hpp"
#include <type_traits>
namespace ra2 {
// Same-source mutation detector only: host object bytes/addresses are NOT a
// portable serialization, original layout, or cross-address clone comparison.
struct MessagePresentationInspection {
    static std::string snapshot(const OwnedMessagePresentation& p){
        std::string out;
        const auto value=[&]<class T>(const T& v){static_assert(std::is_trivially_copyable_v<T>);out.append(reinterpret_cast<const char*>(&v),sizeof(v));};
        const auto span=[&](const auto& v){value(v.data());value(v.size());for(const auto& x:v)value(x);};
        value(p.asset_.get());value(p.list_);value(p.globals_);value(p.metrics_);value(p.font_);value(p.milliseconds_);value(p.fillObserver_);
        value(p.nodes_.data());value(p.nodes_.capacity());value(p.nodes_.size());for(const auto& node:p.nodes_){value(node.get());value(*node);}
        span(p.pixels_);value(p.pixels_.capacity());span(p.colors_);value(p.colors_.capacity());
        value(p.draw_);value(p.blit_);
        value(p.text_.composition.data());value(p.text_.composition.size());value(p.text_.composition.capacity());for(auto c:p.text_.composition)value(c);
        value(p.text_.compositionLength);value(p.text_.compositionCursor);value(p.text_.extra);value(p.text_.highlightRgb);value(p.text_.cursorRgb);value(p.text_.cursorSuppression);
        span(p.sounds_);value(p.sounds_.capacity());span(p.fills_);value(p.fills_.capacity());span(p.lines_);value(p.lines_.capacity());
        const auto& c=p.config_;value(c.surfaceWidth);value(c.surfaceHeight);value(c.x);value(c.y);value(c.width);value(c.maximumLines);value(c.lineStep);
        value(c.mode);value(c.insertSound);value(c.drawSound);value(c.mode3);value(c.mode4);value(c.heapFill);value(c.clockStart);value(c.clockAccumulated);span(c.colors);value(c.colors.capacity());value(c.packing);value(c.fillPolicy);
        return out;
    }
};
}

// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/SurfacePixel.hpp"
#include "render/SurfaceRefreshMarks.hpp"
namespace ra2 {
struct SurfaceMarkPixelServices {
    // Pure stable borrowed view; no mirror geometry or extra width query.
    std::function<SurfacePixelView(RefreshSurface&)> view;
    std::function<void(RefreshSurface&,SurfaceMarkEntry&,std::uint32_t)> enter;
    std::function<void(RefreshSurface&,std::uint32_t,unsigned,std::uint32_t)> store;
    std::function<void(RefreshSurface&,std::int32_t)> locks;
    std::function<std::optional<SurfacePixelServices>(RefreshSurface&)> access;
};
// Inherited virtual24 uses the actual receiver lock/format/unlock services,
// retaining the stock BSurface facade when none are supplied. No queries on bind.
class SurfaceMarkPixelsBinding {
    SurfaceMarkServices& target_;
    decltype(SurfaceMarkServices::pixel24) saved_;
public:
    SurfaceMarkPixelsBinding(SurfaceMarkServices& target,const SurfaceMarkPixelServices& s):target_(target){
        decltype(saved_) replacement=[&s](RefreshSurface& surface,SurfaceMarkEntry& point,std::uint32_t color){
            if(s.enter)s.enter(surface,point,color); // Optional diagnostic entry probe.
            if(!s.view)throw std::invalid_argument("Missing mark pixel surface view");
            auto view=s.view(surface);
            const auto width=[&]{
                if(!surface.table||!surface.table->width7C)throw std::invalid_argument("Missing mark pixel width7C");
                return surface.table->width7C(surface);
            };
            const auto store=[&](auto p,auto n,auto v){if(s.store)s.store(surface,p,n,v);};
            const auto locks=[&](auto depth){if(s.locks)s.locks(surface,depth);};
            const auto access=s.access?s.access(surface):std::nullopt;
            if(access)(void)setSurfacePixelThrough({view.storage,view.words},point.x,point.y,color,*access,store);
            else (void)setSurfacePixel(view,point.x,point.y,color,store,width,locks);
        };
        saved_=std::move(target_.pixel24);target_.pixel24=std::move(replacement);
    }
    ~SurfaceMarkPixelsBinding(){target_.pixel24=std::move(saved_);}
    SurfaceMarkPixelsBinding(const SurfaceMarkPixelsBinding&)=delete;
    SurfaceMarkPixelsBinding& operator=(const SurfaceMarkPixelsBinding&)=delete;
    SurfaceMarkPixelsBinding(SurfaceMarkPixelsBinding&&)=delete;
    SurfaceMarkPixelsBinding& operator=(SurfaceMarkPixelsBinding&&)=delete;
};
}

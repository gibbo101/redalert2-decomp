// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/SurfaceCopy.hpp"
namespace ra2 {
struct SurfaceCopyServices {
    // Stable borrowed owners, including actual geometry/pixels/locks. Resolving
    // an owner must not query a surface, warm state or manufacture a mirror.
    std::function<CopySurface&(RefreshSurface&)> surface;
};
// Pixel entry points share the CopySurface allocation and actual receiver
// virtuals. An ordinary software record keeps its historical facade unchanged.
inline std::optional<SurfacePixelServices> copySurfacePixelAccess(CopySurface& s){
    if(!s.lock5C&&!s.bytes70&&!s.unlock60)return {};
    if(!s.lock5C||!s.bytes70||!s.unlock60)
        throw std::invalid_argument("Incomplete alternate surface pixel virtuals");
    return SurfacePixelServices{
        [&s](auto x,auto y){if(!s.lock5C)throw std::invalid_argument("Missing alternate pixel lock");return s.lock5C(x,y);},
        [&s]{if(!s.bytes70)throw std::invalid_argument("Missing alternate pixel format");return s.bytes70();},
        [&s]{if(!s.unlock60)throw std::invalid_argument("Missing alternate pixel unlock");s.unlock60();}};
}
// Explicit stock copy8 association below634030. No startup/constructor claim.
// Bind one stable virtual table; no surface or pixel queries during binding.
class SurfaceCopyBinding {
    RefreshSurfaceVirtuals& table_;
    decltype(RefreshSurfaceVirtuals::copy8) saved_;
public:
    SurfaceCopyBinding(RefreshSurfaceVirtuals& table,const SurfaceCopyServices& services):table_(table){
        decltype(saved_) replacement=[&services](RefreshSurface& d,RefreshRect* dr,RefreshSurface* s,RefreshRect* sr,std::uint32_t first,std::uint32_t second){
            if(!dr||!s||!sr||!services.surface)throw std::invalid_argument("Missing copy8 owner/rectangle");
            auto& dest=services.surface(d);auto& source=services.surface(*s);
            if(&dest.geometry!=&d||&source.geometry!=s)throw std::invalid_argument("Foreign copy8 geometry owner");
            (void)copySurface(dest,*dr,source,*sr,first,second);
        };
        saved_=std::move(table_.copy8);table_.copy8=std::move(replacement);
    }
    ~SurfaceCopyBinding(){table_.copy8=std::move(saved_);}
    SurfaceCopyBinding(const SurfaceCopyBinding&)=delete;
    SurfaceCopyBinding& operator=(const SurfaceCopyBinding&)=delete;
    SurfaceCopyBinding(SurfaceCopyBinding&&)=delete;
    SurfaceCopyBinding& operator=(SurfaceCopyBinding&&)=delete;
};
}

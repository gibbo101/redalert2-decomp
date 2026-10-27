// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/SurfaceCopyBinding.hpp"
#include "render/SurfaceMarkPixels.hpp"
#include <memory>
namespace ra2 {
// One explicit surface association for zero-mode copy -> mark rebuild -> pixel
// writes. All data comes from the same stable CopySurface records; no pixel or
// geometry mirror is accepted. An explicit policy can retain device copy8;
// pixel entry points then borrow that receiver's alternate virtuals.
// Startup and actor color services stay supplied.
class SurfaceRefreshPixelsBinding {
    SurfaceMarkPixelServices pixelServices_;
    std::unique_ptr<SurfaceCopyBinding> copy_;
    SurfaceMarkPixelsBinding pixels_;
    SurfaceRefreshMarksBinding finish_;
    static CopySurface& owner(const SurfaceCopyServices& services,RefreshSurface& surface){
        if(!services.surface)throw std::invalid_argument("Missing refresh pixel owner");
        auto& record=services.surface(surface);
        if(&record.geometry!=&surface)throw std::invalid_argument("Foreign refresh pixel owner");
        validateCopySurface(record);return record;
    }
    static SurfaceMarkPixelServices pixelServices(const SurfaceCopyServices& services,
            decltype(SurfaceMarkPixelServices::enter) enter){
        return {
            [&services](auto& surface){return owner(services,surface).pixels;},std::move(enter),
            [&services](auto& surface,auto at,auto n,auto value){
                auto& record=owner(services,surface);if(record.stores)record.stores(at,n,value);
            },
            [&services](auto& surface,auto depth){
                auto& record=owner(services,surface);if(record.locks)record.locks(depth);
            },
            [&services](auto& surface){return copySurfacePixelAccess(owner(services,surface));}
        };
    }
public:
    // Construction makes no owner, geometry, pixel, floor or renderer queries.
    // The optional entry probe is diagnostic; no supplied pixel writer is called.
    SurfaceRefreshPixelsBinding(RefreshSurfaceVirtuals& table,SurfaceRefreshServices& refresh,
            SurfaceMarkServices& marks,const SurfaceCopyServices& services,
            decltype(SurfaceMarkPixelServices::enter) enter={},bool retainCopy=false):
        pixelServices_(pixelServices(services,std::move(enter))),copy_(retainCopy?nullptr:std::make_unique<SurfaceCopyBinding>(table,services)),
        pixels_(marks,pixelServices_),finish_(refresh,marks){
        if(retainCopy&&!table.copy8)throw std::invalid_argument("Missing retained refresh copy8");
    }
    SurfaceRefreshPixelsBinding(const SurfaceRefreshPixelsBinding&)=delete;
    SurfaceRefreshPixelsBinding& operator=(const SurfaceRefreshPixelsBinding&)=delete;
    SurfaceRefreshPixelsBinding(SurfaceRefreshPixelsBinding&&)=delete;
    SurfaceRefreshPixelsBinding& operator=(SurfaceRefreshPixelsBinding&&)=delete;
};
}

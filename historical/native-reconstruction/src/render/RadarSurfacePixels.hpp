// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/SurfaceRadarPixel.hpp"
#include "render/SurfacePixel.hpp"
#include <vector>
namespace ra2 {
struct RadarSurfacePixelWorld {
    std::span<const RefreshSurfaceVirtuals* const> stockTables;
    std::function<SurfacePixelView(RefreshSurface&)> view;
    std::function<void(char,const RefreshSurfaceVirtuals*,RefreshSurface&,RefreshRect&,std::uint32_t)> before;
    std::function<void(std::uint32_t)> readResult;
    std::function<void(RefreshSurface&,std::uint32_t,unsigned,std::uint32_t)> store;
    std::function<void(RefreshSurface&,std::int32_t)> locks;
    std::function<std::optional<SurfacePixelServices>(RefreshSurface&)> access;
};
// Explicit stock table associations. Every read/write resolves the same borrowed
// allocation, width, format and lock fields; no second pixel copy or query on bind.
class RadarSurfacePixelsBinding {
    RadarPixelServices& target_;
    decltype(RadarPixelServices::pixels) saved_;
    struct Entry {const RefreshSurfaceVirtuals* table;RadarPixelVirtuals calls;};
    std::vector<Entry> entries_;
public:
    RadarSurfacePixelsBinding(RadarPixelServices& target,const RadarSurfacePixelWorld& world):target_(target){
        if(!world.view)throw std::invalid_argument("Missing radar surface pixel view");
        for(const auto* table:world.stockTables){
            if(!table)throw std::invalid_argument("Null stock radar pixel table");
            for(const auto& e:entries_)if(e.table==table)throw std::invalid_argument("Duplicate stock radar pixel table");
            const auto view=[&world](RefreshSurface& surface){auto v=world.view(surface);if(&v.width4!=&surface.width)throw std::invalid_argument("Radar pixel width is not the surface owner");return v;};
            const auto width=[](RefreshSurface& surface){if(!surface.table||!surface.table->width7C)throw std::invalid_argument("Missing radar pixel width7C");return surface.table->width7C(surface);};
            RadarPixelVirtuals calls;
            calls.get28=[&world,table,view,width](RefreshSurface& surface,RefreshRect& point){
                if(world.before)world.before('V',table,surface,point,0);
                const auto v=view(surface);
                const auto access=world.access?world.access(surface):std::nullopt;
                const auto result=access?getSurfacePixelThrough({v.storage,v.words},point[0],point[1],*access):
                    getSurfacePixel(v,point[0],point[1],[&]{return width(surface);},[&](auto depth){if(world.locks)world.locks(surface,depth);});
                if(world.readResult)world.readResult(result);return result;
            };
            calls.set24=[&world,table,view,width](RefreshSurface& surface,RefreshRect& point,std::uint32_t color){
                if(world.before)world.before('W',table,surface,point,color);
                const auto v=view(surface);
                const auto access=world.access?world.access(surface):std::nullopt;
                const auto store=[&](auto p,auto n,auto value){if(world.store)world.store(surface,p,n,value);};
                if(access)setSurfacePixelThrough({v.storage,v.words},point[0],point[1],color,*access,store);
                else setSurfacePixel(v,point[0],point[1],color,store,[&]{return width(surface);},[&](auto depth){if(world.locks)world.locks(surface,depth);});
            };
            entries_.push_back({table,std::move(calls)});
        }
        decltype(saved_) replacement=[this](const RefreshSurfaceVirtuals* table)->const RadarPixelVirtuals&{
            for(const auto& entry:entries_)if(entry.table==table)return entry.calls;
            throw std::invalid_argument("Unregistered radar stock pixel table");
        };
        saved_=std::move(target_.pixels);target_.pixels=std::move(replacement);
    }
    ~RadarSurfacePixelsBinding(){target_.pixels=std::move(saved_);}
    RadarSurfacePixelsBinding(const RadarSurfacePixelsBinding&)=delete;
    RadarSurfacePixelsBinding& operator=(const RadarSurfacePixelsBinding&)=delete;
    RadarSurfacePixelsBinding(RadarSurfacePixelsBinding&&)=delete;
    RadarSurfacePixelsBinding& operator=(RadarSurfacePixelsBinding&&)=delete;
};
}

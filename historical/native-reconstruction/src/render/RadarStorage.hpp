// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/RadarSurfaceStartup.hpp"
#include "render/RadarMapNotification.hpp"
#include "render/RadarProjection.hpp"
#include "render/SurfaceStartup.hpp"
#include "render/SurfacePixel.hpp"
#include "render/DeviceSurfacePixels.hpp"
#include "render/DeviceSurfaceCopy.hpp"
#include "render/RadarShapeBuckets.hpp"
#include "render/SurfaceRefreshMarks.hpp"
#include "render/RadarMarkerPlacement.hpp"
#include "render/RadarMarkerBuckets.hpp"
#include "render/RadarCellNotification.hpp"
#include <initializer_list>
#include <memory>
#include <utility>
#include <vector>

namespace ra2 {
// Native storage for the recovered radar startup/projection kernels. The first
// is a device-surface adapter, the second the ordinary software surface. Device
// allocation/description/clear/destruction are platform policy, not recovered
// DirectDraw behavior. Device pixels use recovered device locks, not BSurface
// locks. Copies from the owned software terrain use the recovered fallback.
class RadarStorage {
public:
    using Trace=std::function<void(char,std::initializer_list<std::int64_t>)>;
    using Colors=std::function<void(RefreshRect&,RefreshRect&,std::span<std::uint8_t>)>;
private:
    struct Surface {
        RefreshSurface geometry{};
        std::int32_t lock=0,bpp=2;
        std::uint32_t offset=0;
        std::vector<std::uint8_t> pixels;
        std::array<std::uint32_t,27> descriptor{};
        std::uint8_t flag=0,video=0;
        std::uint32_t deviceBytes=0;
        std::uintptr_t device=0;
        std::span<std::uint32_t> description;
    };
    RefreshSurfaceVirtuals firstTable_,secondTable_;
    std::unique_ptr<Surface> firstOwner_,secondOwner_;
    std::unique_ptr<CopySurface> firstCopy_,secondCopy_;
    SurfaceMarkBitmap markBitmap_{{},0};
    RefreshSurface *first_=nullptr,*second_=nullptr;
    std::vector<std::uint8_t> rgbOwner_,bitmapOwner_;
    std::span<std::uint8_t> rgb_,bitmap_;
    std::int32_t rgbWidth_=0,rgbHeight_=0;
    float scale_=0;
    const std::array<std::int32_t,6> shifts_;
    Trace trace_;
    NativeRadarShapeBuckets shapes_;
    // Supplied native startup for the existing Map1258 point queue and14D5.
    // Queue consumption and original constructor/scheduling are not inferred.
    RadarShapeVector dirtyPoints_;
    std::uint8_t dirty_=0,full14D6_=0;
    std::int32_t mode14AC_=0,mode14A8_=0; // Supplied startup; original mode producer remains open.
    std::vector<std::unique_ptr<RadarShapePoint[]>> dirtyAllocations_;
    SurfaceMarkBuckets markerBuckets_{};
    SurfaceMarkBuckets* markerBucketOwner_=&markerBuckets_;
    std::vector<std::unique_ptr<SurfaceMarkEntry[]>> markerAllocations_;
    void event(char k,std::initializer_list<std::int64_t> v={})const{if(trace_)trace_(k,v);}
    static std::size_t extent(std::int32_t w,std::int32_t h,unsigned bytes){
        if(w<=0||h<=0||std::uint64_t(w)*std::uint64_t(h)*bytes>16*1024*1024)
            throw std::invalid_argument("Native radar storage geometry");
        return std::size_t(w)*std::size_t(h)*bytes;
    }
    SurfacePixelView secondView(){
        if(!secondOwner_||second_!=&secondOwner_->geometry)throw std::invalid_argument("Native radar second owner");
        auto& s=*secondOwner_;return {s.geometry.width,s.lock,s.bpp,s.offset,s.pixels,{},true};
    }
    static constexpr std::uint32_t displayAddress=0x10000;
    const std::uint8_t deviceEnabled_=1,secondaryEnabled_=0;
    DeviceSurfacePixelView firstView(){
        if(!firstOwner_||first_!=&firstOwner_->geometry)
            throw std::invalid_argument("Native radar first owner");
        auto& s=*firstOwner_;
        return {s.lock,s.deviceBytes,s.offset,s.video,s.device,s.description};
    }
    DeviceSurfacePixelServices firstBackend(){
        DeviceSurfacePixelServices p{deviceEnabled_,secondaryEnabled_};
        p.lost=[](auto){return 0u;}; // Native memory cannot be lost to DirectDraw.
        p.lock=[this](auto device,auto descriptor,auto flags){
            if(device!=firstOwner_->device||flags!=1)
                throw std::invalid_argument("Native radar device lock");
            descriptor[4]=std::uint32_t(firstOwner_->geometry.width)*2;
            descriptor[9]=displayAddress;descriptor[21]=16;descriptor[26]=0x2040;
            return 0u;
        };
        p.unlock=[this](auto device,auto address){
            if(device!=firstOwner_->device||address!=displayAddress)
                throw std::invalid_argument("Native radar device unlock");
        };
        return p;
    }
    SurfacePixelServices firstPixels(){
        SurfacePixelServices p;
        p.lock=[this](auto x,auto y)->std::optional<std::uint32_t>{
            const auto address=lockDeviceSurfacePixels(firstView(),x,y,firstBackend());
            if(!address)return {};
            if(address<displayAddress)throw std::invalid_argument("Native radar pixel address");
            return address-displayAddress;
        };
        p.bytes70=[this]{return std::bit_cast<std::int32_t>(firstOwner_->deviceBytes);};
        p.unlock=[this]{(void)unlockDeviceSurfacePixels(firstView(),firstBackend());};
        return p;
    }
    bool copyFromTerrain(const RefreshRect& destination,const RefreshRect& source,
            std::uint32_t first,std::uint32_t second){
        auto device=firstView();
        auto& dest=copyOwner(*first_);auto& origin=copyOwner(*second_);
        DeviceSurfaceCopyServices services{firstBackend(),[](CopySurface&){return std::uint8_t(0);}};
        return copyDeviceSurface(dest,device,destination,origin,source,first,second,services);
    }
public:
    explicit RadarStorage(std::array<std::int32_t,6> shifts,Trace trace={})
        :shifts_(shifts),trace_(std::move(trace)){
        const auto width=[this](RefreshSurface& s){event('W',{s.width});return refreshSurfaceWidth(s);};
        const auto height=[this](RefreshSurface& s){event('H',{s.height});return refreshSurfaceHeight(s);};
        firstTable_.width7C=secondTable_.width7C=width;
        firstTable_.height80=secondTable_.height80=height;
        firstTable_.rect78=secondTable_.rect78=refreshSurfaceRect;
        firstTable_.copy8=[this](RefreshSurface& d,RefreshRect* dr,RefreshSurface* source,
                RefreshRect* sr,std::uint32_t first,std::uint32_t second){
            if(&d!=first_||source!=second_||!dr||!sr)
                throw std::invalid_argument("Native radar device copy owner");
            (void)copyFromTerrain(*dr,*sr,first,second);
        };
    }
    RadarStorage(const RadarStorage&)=delete;
    RadarStorage& operator=(const RadarStorage&)=delete;
    RadarStorage(RadarStorage&&)=delete;
    RadarStorage& operator=(RadarStorage&&)=delete;
    std::span<const std::uint8_t> terrainRGB()const{return rgb_;}
    std::span<const std::uint8_t> terrainPixels()const{return secondOwner_?std::span<const std::uint8_t>(secondOwner_->pixels):std::span<const std::uint8_t>{};}
    std::span<const std::uint8_t> displayPixels()const{return firstOwner_?std::span<const std::uint8_t>(firstOwner_->pixels):std::span<const std::uint8_t>{};}
    std::span<const std::uint8_t> bitmap()const{return bitmap_;}
    RefreshSurface* first()const{return first_;}
    RefreshSurface* second()const{return second_;}
    float scale()const{return scale_;}
    const float& scaleOwner()const{return scale_;}
    RefreshSurface* const& firstOwner()const{return first_;}
    RefreshSurface* const& secondOwner()const{return second_;}
    SurfaceMarkBitmap& markBitmap(){return markBitmap_;}
    SurfaceMarkBuckets* const& markerBucketsOwner()const{return markerBucketOwner_;}
    RadarMarkerBucketServices markerServices(RadarMarkerBucketServices s){
        s.vector=[this](unsigned index){
            if(index>=256)throw std::invalid_argument("Native radar marker bucket index");
            RadarMarkerVectorServices services;
            services.allocate=[this](auto bytes)->std::span<SurfaceMarkEntry>{
                if(!bytes||bytes%16||bytes>4096*16)throw std::invalid_argument("Native radar marker allocation bound");
                auto data=std::make_unique<SurfaceMarkEntry[]>(bytes/16);
                auto view=std::span<SurfaceMarkEntry>(data.get(),bytes/16);
                markerAllocations_.push_back(std::move(data));return view;
            };
            services.release=[this](auto entries){
                const auto it=std::find_if(markerAllocations_.begin(),markerAllocations_.end(),
                    [&](const auto& p){return p.get()==entries.data();});
                if(it==markerAllocations_.end())throw std::invalid_argument("Native radar marker allocation identity");
                markerAllocations_.erase(it);
            };return services;
        };
        s.queue632620=[this](auto point){queueDirtyPoint(point);};return s;
    }
    void insertMarker(const void* actor,std::int32_t x,std::int32_t y,const void* const& current,
            const RadarMarkerBucketServices& actors){
        const auto s=markerServices(actors);
        insertRadarMarker(actor,x,y,{first_,markerBucketOwner_,current,dirty_},s);
    }
    void removeMarker(const void* actor,std::int32_t x,std::int32_t y,const void* const& current,
            const RadarMarkerBucketServices& actors){
        const auto s=markerServices(actors);
        removeRadarMarker(actor,x,y,{first_,markerBucketOwner_,current,dirty_},s);
    }
    std::span<const RadarShapePoint> dirtyPoints()const{
        if(dirtyPoints_.count<0||std::size_t(dirtyPoints_.count)>dirtyPoints_.items.size())
            throw std::invalid_argument("Native radar dirty queue count");
        return dirtyPoints_.items.first(std::size_t(dirtyPoints_.count));
    }
    std::uint8_t dirtyFlag()const{return dirty_;}
    // Borrows the existing14D5 shared by Cell/marker updates, never a second flag.
    RadarMapNotificationView notificationView(){return {mode14AC_,mode14A8_,dirty_,full14D6_};}
    void supplyNotificationMode(std::int32_t ac,std::int32_t a8){mode14AC_=ac;mode14A8_=a8;}
    // Explicit operation on the same surface/bitmap owners used by refresh.
    // Does not place an actor or arrange a future SDL/frame callback.
    void notifyCell(TerrainCellPoint point,const std::int32_t& mapWidth,
            const std::int32_t& originX,const std::int32_t& originY){
        notifyRadarCell(point,{first_,mapWidth,originX,originY,rgbWidth_,rgbHeight_,scale_},
            {[this](const auto& p){queueDirtyPoint(p);}});
    }
    template<class Point=RadarShapePoint>
    void queueDirtyPoint(const Point& point){
        auto* bitmap=&markBitmap_;RadarDirtyServices services;
        services.vector.allocate=[this](auto bytes)->std::span<RadarShapePoint>{
            if(!bytes||bytes%8||bytes>8*1048576)throw std::invalid_argument("Native radar dirty allocation bound");
            auto data=std::make_unique<RadarShapePoint[]>(bytes/8);
            auto span=std::span<RadarShapePoint>(data.get(),bytes/8);
            dirtyAllocations_.push_back(std::move(data));return span;
        };
        services.vector.release=[this](auto points){
            const auto it=std::find_if(dirtyAllocations_.begin(),dirtyAllocations_.end(),
                [&](const auto& p){return p.get()==points.data();});
            if(it==dirtyAllocations_.end())throw std::invalid_argument("Native radar dirty allocation identity");
            dirtyAllocations_.erase(it);
        };
        queueRadarDirtyPoint(point,{first_,bitmap,dirtyPoints_,dirty_},services);
    }
    // Stable borrowed adapters, invalidated before startup replaces an owner.
    // Resolve only during entered operations; construction of a binding is pure.
    CopySurface& copyOwner(RefreshSurface& receiver){
        if(&receiver==first_&&first_){
            (void)firstView();
            if(!firstCopy_){auto& s=*firstOwner_;
                const auto& bytes=reinterpret_cast<const std::int32_t&>(s.deviceBytes);
                firstCopy_=std::make_unique<CopySurface>(CopySurface{s.geometry,
                    {s.geometry.width,s.lock,bytes,s.offset,s.pixels,{},true},{},{},{},{}});
                firstCopy_->bytes70=[this]{return std::bit_cast<std::int32_t>(firstOwner_->deviceBytes);};
                firstCopy_->pitch74=[this]{return firstOwner_->description[4];};
                firstCopy_->lock5C=[this](auto x,auto y){return firstPixels().lock(x,y);};
                firstCopy_->unlock60=[this]{firstPixels().unlock();};
            }
            return *firstCopy_;
        }
        if(&receiver==second_&&second_){
            if(!secondCopy_)secondCopy_=std::make_unique<CopySurface>(CopySurface{
                secondOwner_->geometry,secondView(),{},{},{},{}});
            return *secondCopy_;
        }
        throw std::invalid_argument("Foreign native radar copy owner");
    }
    std::int32_t colorWidth()const{return rgbWidth_;}
    std::int32_t colorHeight()const{return rgbHeight_;}
    std::uint32_t displayBytes()const{return firstOwner_?firstOwner_->deviceBytes:0;}
    std::uint8_t displayVideo()const{return firstOwner_?firstOwner_->video:0;}
    bool setDisplayPixel(std::int32_t x,std::int32_t y,std::uint32_t color){
        (void)firstView();
        return setSurfacePixelThrough({firstOwner_->pixels,{}},x,y,color,firstPixels());
    }
    std::uint32_t getDisplayPixel(std::int32_t x,std::int32_t y){
        (void)firstView();
        return getSurfacePixelThrough({firstOwner_->pixels,{}},x,y,firstPixels());
    }
    void initializeShapeBuckets(const RadarShapeDimensions& widths,const RadarShapeDimensions& heights){
        shapes_.initialize(scale_,widths,heights);
    }
    std::span<const RadarShapeVector,22> shapeBuckets()const{return shapes_.buckets();}
    // Geometry and startup policy belong to the caller. Colors must fill the
    // same live RGB span; finish632700 remains explicit and must be supplied.
    void initialize(RefreshRect& rectangle,const std::int32_t& originX,
            const std::int32_t& originY,const Colors& colors,
            const std::function<void()>& finish,std::uint8_t forcedSystem=0){
        const void* colorPointer=rgb_.empty()?nullptr:rgb_.data();
        const void* bitmapPointer=bitmap_.empty()?nullptr:bitmap_.data();
        RadarSurfaceStartupServices startup;
        startup.store=[this](auto off,auto v){event('M',{off,v});};
        startup.destroy=[this](auto* p,auto flag){
            if(flag!=1)throw std::invalid_argument("Native radar deleting flag");
            if(secondOwner_&&p==&secondOwner_->geometry){event('X',{2,flag});secondCopy_.reset();secondOwner_.reset();}
            else if(firstOwner_&&p==&firstOwner_->geometry){event('X',{1,flag});firstCopy_.reset();firstOwner_.reset();}
            else throw std::invalid_argument("Native radar destruction owner");
        };
        startup.release=[&](auto p){
            if(p==colorPointer){event('F',{3});rgb_={};rgbOwner_.clear();}
            else if(p==bitmapPointer){event('F',{4});bitmap_={};markBitmap_.bytes={};bitmapOwner_.clear();}
            else throw std::invalid_argument("Native radar release owner");
        };
        startup.buildSecond=[&](auto& out,auto& source,auto& region,auto update){
            if(&source!=&region||&source!=&rectangle)throw std::invalid_argument("Native radar startup alias");
            RadarProjectionServices projection;
            projection.mapStore=[this](auto o,auto v){event('M',{o,v});};
            projection.bufferStore=[this](auto k,auto at,auto n,auto v){event(k,{at,n,v});};
            projection.allocate=[this](auto n){
                event('A',{n});auto& owner=rgb_.empty()?rgbOwner_:bitmapOwner_;
                owner.assign(n,0xa5);return std::span<std::uint8_t>(owner);
            };
            projection.colors631250=[&](auto& a,auto& b){
                if(!colors)throw std::invalid_argument("Native radar terrain colors unbound");
                event('U');colors(a,b,rgb_);
            };
            projection.createSecond=[this](auto w,auto h){
                secondCopy_.reset();secondOwner_=std::make_unique<Surface>();auto& s=*secondOwner_;
                s.geometry={&secondTable_,w,h};
                const auto put=[this](auto o,auto n,auto v){event('S',{o,n,v});};
                put(8,4,std::uint32_t(h));put(4,4,std::uint32_t(w));put(12,4,0);put(0,4,2);put(16,4,2);
                put(20,4,0);put(24,4,std::uint32_t(w)*std::uint32_t(h)*2);put(28,1,0);
                event('A',{std::uint32_t(w)*std::uint32_t(h)*2});s.pixels.assign(extent(w,h,2),0xa5);
                put(20,4,1);put(28,1,1);put(0,4,3);return &s.geometry;
            };
            projection.clear=[this](auto&,auto color){event('Z',{color});std::fill(secondOwner_->pixels.begin(),secondOwner_->pixels.end(),0);};
            projection.lock=[this](auto&,auto x,auto y){
                event('K',{x,y});const auto at=lockSurfacePixels(secondView(),x,y,
                    [this]{return secondTable_.width7C(*second_);},[this](auto v){event('S',{12,4,std::uint32_t(v)});});
                if(!at||*at)throw std::invalid_argument("Native radar projection lock address");
                return std::span<std::uint8_t>(secondOwner_->pixels);
            };
            projection.unlock=[this](auto&){event('N');unlockSurfacePixels(secondView(),[this](auto v){event('S',{12,4,std::uint32_t(v)});});};
            buildRadarProjection(out,source,region,update,{second_,rgb_,rgbWidth_,rgbHeight_,bitmap_,scale_,shifts_},projection);
        };
        startup.allocateFirst=[this](auto n){
            if(n!=36)throw std::invalid_argument("Native radar device object extent");
            event('A',{n});firstCopy_.reset();firstOwner_=std::make_unique<Surface>();firstOwner_->geometry.table=&firstTable_;return &firstOwner_->geometry;
        };
        startup.initializeFirst=[&](auto* p,auto w,auto h,auto video){
            auto& s=*firstOwner_;
            struct Borrowed {
                std::int32_t &width4,&height8,&lockC;
                std::uint32_t &bytes10,&offset14;
                std::uint8_t &flag18,&video19;
                std::uintptr_t& surface1C;
                std::span<std::uint32_t>& descriptor20;
            } record{s.geometry.width,s.geometry.height,s.lock,s.deviceBytes,s.offset,s.flag,s.video,s.device,s.description};
            SurfaceStartupServices backend;
            backend.objectStore=[this](auto o,auto n,auto v){event('O',{o,n,v});};
            backend.descriptorStore=[this](auto o,auto n,auto v){event('D',{o,n,v});};
            backend.allocate=[&](auto n){if(n!=108)throw std::invalid_argument("Native radar descriptor extent");event('A',{n});return std::span<std::uint32_t>(s.descriptor);};
            backend.create=[&](auto d,auto& device){
                event('C',{d[0],d[1],d[2],d[3],d[26]});s.pixels.assign(extent(w,h,2),0xa5);device=1;event('O',{28,4,1});
            };
            backend.describe=[&](auto,auto d){
                event('G',{1});d[21]=16;event('D',{84,4,16});d[26]=0x2040;event('D',{104,4,0x2040});
            };
            initializeDeviceSurface(record,w,h,video,forcedSystem,backend);return p;
        };
        startup.clear=[this](auto&,auto color){event('L',{color});std::fill(firstOwner_->pixels.begin(),firstOwner_->pixels.end(),0);};
        startup.finish632700=[&]{markBitmap_.bytes=bitmap_;if(!finish)throw std::invalid_argument("Native radar startup finish unbound");event('Z');finish();};
        initializeRadarSurfaces({first_,second_,colorPointer,bitmapPointer,rectangle,originX,originY},startup);
        markBitmap_.bytes=bitmap_;
    }
};
}

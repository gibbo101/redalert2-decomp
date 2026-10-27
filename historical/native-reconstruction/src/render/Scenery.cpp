// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/Scenery.hpp"
#include "assets/GameAssets.hpp"
#include "render/SurfaceFill.hpp"
#include <algorithm>
#include <stdexcept>
namespace ra2 {
TerrainLifeServices staticSceneryServices(const GameAssets& assets) {
    const auto scale=worldHeightScale(assets.rasterData,assets.renderData);
    TerrainLifeServices services;
    services.groundHeight=[&assets](Coord p){
        const auto point=terrainCellPoint(p);const auto* cell=assets.cell(point.x,point.y);
        if(!cell)throw std::invalid_argument("Scenery height outside prepared map");
        return cell->z*104;
    };
    services.placementAllowed=[](auto){return true;}; // Existing map placements only; loader policy.
    services.projectWorld=[scale](Coord p){const auto screen=worldPixels(scale,p);return std::array<std::int32_t,2>{screen.x,screen.y};};
    return services;
}
void prepareStaticScenery(GameAssets& assets){assets.prepareSceneryLifecycle(staticSceneryServices(assets));}
std::array<TerrainDrawInputs,2> staticTerrainDrawInputs(int frames,int height,std::int16_t light) {
    if(frames!=2||height<-65536||height>65536)throw std::invalid_argument("Only healthy static two-frame terrain is recovered");
    return {{{0,0x4e00,-height-12,2,light},{frames/2,0x4e01,-height-3,0,1000}}};
}
BlitStats blitOrdinarySpriteFrame(const ShpImage& image,const TerrainDrawInputs& input,PixelPoint at,PixelRect clip,
                       const std::vector<Palette16>& palettes,int width,int height,
                       std::vector<std::uint16_t>& colors,std::vector<std::uint16_t>& depth,
                       const std::vector<std::uint16_t>& alpha,SpriteDepthInput auxiliary) {
    if(width<1||height<1||width>4096||height>4096||colors.size()!=std::size_t(width)*height||depth.size()!=colors.size()||alpha.size()!=colors.size())
        throw std::invalid_argument("Invalid terrain blit planes");
    for(int v:{at.x,at.y,clip.x,clip.y,clip.width,clip.height,input.zAdjust})
        if(std::abs(std::int64_t(v))>1048576)throw std::invalid_argument("Terrain blit outside bounded profile");
    const bool shadow=(input.flags==0x4e01||input.flags==0x6e01)&&input.gradient==0;
    const bool body=(input.flags==0x4e00||input.flags==0x6e00)&&(input.gradient==0||input.gradient==2);
    if(!shadow&&!body)throw std::invalid_argument("Unsupported ordinary sprite blitter");
    const auto& f=image.frames.at(std::size_t(input.frame));
    if(f.format!=1&&f.format!=3)throw std::invalid_argument("Unsupported terrain frame format");
    if(image.width<1||image.height<1||image.width>4096||image.height>4096||f.x<0||f.y<0||f.width<0||f.height<0||
       f.x+std::int64_t(f.width)>image.width||f.y+std::int64_t(f.height)>image.height||f.pixels.size()!=std::size_t(f.width)*f.height)
        throw std::invalid_argument("Invalid terrain frame");
    const ShpFrame* aux=nullptr;int auxX=0,auxY=0,cropWidth=f.width,cropHeight=f.height;
    if(auxiliary.image){
        if(std::uint32_t(auxiliary.frame)>=auxiliary.image->frames.size())return {};
        aux=&auxiliary.image->frames[std::size_t(auxiliary.frame)];
        if(aux->format!=1||aux->width<0||aux->height<0||aux->width>4096||aux->height>4096||
           aux->pixels.size()!=std::size_t(aux->width)*aux->height)
            throw std::invalid_argument("Unsupported sprite depth backing");
        auxX=fillAdd(fillSub(auxiliary.offset.x,image.width/2-f.x),aux->x);
        auxY=fillAdd(fillSub(auxiliary.offset.y,image.height/2-f.y),aux->y);
        // Negative adjusted origins enter original pointer-before-payload paths.
        // They remain refused until their backing/caller domain is recovered.
        if(auxX<0||auxY<0)throw std::invalid_argument("Unsupported negative sprite depth origin");
        const auto r=intersectFillRect({0,0,f.width,f.height},{fillSub(0,auxX),fillSub(0,auxY),aux->width,aux->height});
        cropWidth=r[2];cropHeight=r[3];
        if(cropWidth<=0||cropHeight<=0)return {};
    }
    // The SHP wrapper centers by signed canvas halves, adds the crop, then the
    // surface helper applies the clip origin. No padding of odd crop dimensions.
    at.x+=clip.x-image.width/2+f.x;at.y+=clip.y-image.height/2+f.y;
    const int left=std::max({0,clip.x,at.x}),top=std::max({0,clip.y,at.y});
    const int right=std::min({width,clip.x+clip.width,at.x+cropWidth});
    const int bottom=std::min({height,clip.y+clip.height,at.y+cropHeight});
    BlitStats stats;if(left>=right||top>=bottom)return stats;
    // Compressed surface drawing retains the original crop height even when
    // the bottom is clipped. Top clipping advances the original row phase.
    // Raw BSurface drawing initializes the depth phase from the clipped height.
    // RLE drawing uses the original crop and advances through clipped top rows.
    const int remaining=f.format==1?bottom-top:cropHeight-(top-at.y);
    const int base=int(std::uint16_t(f.format==1?32768-remaining-top+1:32768-cropHeight-at.y+1))+input.zAdjust;
    int candidate=input.gradient==0?int(std::uint16_t(32768-top))+input.zAdjust:(base/3)*3-remaining/3;
    int remainder=3-remaining%3;
    if(input.gradient==2&&remainder==3){remainder=0;++candidate;}
    if(aux&&f.format==3&&input.gradient==2)candidate=base;
    for(int y=top;y<bottom;++y) {
        int overshoot=0;
        if(aux&&f.format==3&&left>at.x){
            const auto row=std::size_t(y-at.y);
            if(row>=f.rleRows.size())throw std::invalid_argument("Missing sprite RLE run backing");
            const auto& encoded=f.rleRows[row];int x=0;
            for(std::size_t p=0;x<left-at.x;){
                if(p>=encoded.size())throw std::invalid_argument("Invalid sprite RLE skip");
                const auto v=encoded[p++];
                if(v)++x;
                else {if(p>=encoded.size()||!encoded[p])throw std::invalid_argument("Invalid sprite RLE skip run");x+=encoded[p++];}
            }
            overshoot=x-(left-at.x);
        }
        for(int x=left;x<right;++x) {
            const auto src=std::size_t(y-at.y)*f.width+x-at.x,dest=std::size_t(y)*width+x;
            if(!f.pixels[src])continue;
            int pixelDepth=candidate;
            if(aux&&f.format==3){
                const auto byte=aux->pixels.at(std::size_t(auxY+y-at.y)*aux->width+auxX+x-at.x-overshoot);
                pixelDepth-=byte<128?int(byte):int(byte)-256;
            }
            if(pixelDepth<int(depth[dest])) {
                colors[dest]=shadow?std::uint16_t((colors[dest]>>1)&0x7bef):
                    palettes.at(std::size_t(alphaShadeRow(alpha[dest],input.brightness,int(palettes.size()))))[f.pixels[src]];
                depth[dest]=std::uint16_t(pixelDepth);++stats.visible;
            } else ++stats.rejected;
        }
        if(aux&&f.format==3)continue; // Auxiliary rows advance their byte pointer, not the gradient phase.
        if(input.gradient==0)--candidate;
        else if(++remainder>=3){++candidate;remainder-=3;}
    }
    return stats;
}
BlitStats blitConvertedSpriteFrame(SpriteConverterFields converter,const ShpImage* image,
        const TerrainDrawInputs& input,PixelPoint at,PixelRect clip,int width,int height,
        std::vector<std::uint16_t>& colors,std::vector<std::uint16_t>& depth,const std::vector<std::uint16_t>& alpha,SpriteDepthInput auxiliary){
    if(!image)return {};
    converter.field17c=0; // Ordinary49EEA0 argument6 is zero, not the flags argument5.
    if(converter.stored)converter.stored();
    return blitOrdinarySpriteFrame(*image,input,at,clip,converter.palettes,width,height,colors,depth,alpha,auxiliary);
}
BlitStats blitTerrainFrame(const ShpImage& image,const TerrainDrawInputs& input,PixelPoint at,PixelRect clip,
                       const std::vector<Palette16>& palettes,int width,int height,
                       std::vector<std::uint16_t>& colors,std::vector<std::uint16_t>& depth,
                       const std::vector<std::uint16_t>& alpha) {
    if(!((input.flags==0x4e00&&input.gradient==2)||(input.flags==0x4e01&&input.gradient==0)))
        throw std::invalid_argument("Unsupported terrain blitter");
    return blitOrdinarySpriteFrame(image,input,at,clip,palettes,width,height,colors,depth,alpha);
}

}

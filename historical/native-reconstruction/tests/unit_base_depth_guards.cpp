// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitBaseDepth.hpp"
#include "render/PreparedFootDepth.hpp"
#include <cfenv>
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace ra2;
int main(){try{
    MapCellAttributes center,south,east,fallback;center.input.position={1,2};center.input.tile=0;
    MapTileImageInput image;image.columns=image.rows=1;image.width=60;image.height=36;image.subTiles={MapSubTileInput{}};
    std::array<MapTileAttributes,1> tiles;tiles[0].image=&image;
    std::array<MapOverlayType,2> overlays;overlays[1].rock=1;
    UnitBaseDepthWorld w;w.tiles=tiles;w.overlays=overlays;unsigned dimensions=0;
    w.dimensions=[&](int,int){++dimensions;};
    w.cell=[&](MapInputPosition p)->const MapCellAttributes&{if(p==MapInputPosition{1,2})return center;if(p==MapInputPosition{1,3})return south;if(p==MapInputPosition{2,2})return east;return fallback;};
    UnitBaseDepthInputs in;in.location={384,640,416};in.heightScale=.125;in.currentRamp=-7;in.neighborRamp=9;in.rock=23;
    const int old=std::fegetround();std::fesetround(FE_UPWARD);
    auto r=ordinaryUnitBaseDepth(in,w);
    if(r.depth!=-53||r.dimensionHeight!=36||dimensions!=3||std::fegetround()!=FE_UPWARD)throw std::runtime_error("Dimension threshold/FP restoration differs");
    image.height=37;dimensions=0;r=ordinaryUnitBaseDepth(in,w);
    if(r.depth!=-54||dimensions!=1)throw std::runtime_error("Tall TMP did not stop at first query");
    tiles[0].image=nullptr;in.dimensionHeight=37;r=ordinaryUnitBaseDepth(in,w);
    if(r.depth!=-54||r.dimensionHeight!=37)throw std::runtime_error("Missing image discarded caller scratch");
    in.dimensionHeight=36;r=ordinaryUnitBaseDepth(in,w);
    if(r.depth!=-53||r.dimensionHeight!=36)throw std::runtime_error("Missing image rewrote scratch");
    center.input.slope=1;south.overlay=0;east.overlay=1;r=ordinaryUnitBaseDepth(in,w);
    if(r.depth!=-59)throw std::runtime_error("Earlier nonrock failed to gate later rock");
    south.overlay=-1;r=ordinaryUnitBaseDepth(in,w);
    if(r.depth!=-30)throw std::runtime_error("Rock neighbor adjustment differs");
    center.input.slope=0;in.location.z=std::numeric_limits<int>::max();in.heightScale=1;in.dimensionHeight=0;r=ordinaryUnitBaseDepth(in,w);
    if(r.depth!=std::numeric_limits<int>::max())throw std::runtime_error("Height FTOL low-dword/wrapped negation differs");
    in.heightScale=0;bool refused=false;try{ordinaryUnitBaseDepth(in,w);}catch(const std::invalid_argument&){refused=true;}
    if(!refused||std::fegetround()!=FE_UPWARD)throw std::runtime_error("Invalid scale/rounding guard differs");
    PreparedFootDepthInputs foot;foot.unit=in;foot.unit.heightScale=.125;foot.unit.location.z=416;foot.unit.dimensionHeight=0;
    PreparedFootDepthWorld prepared;prepared.unit=w;
    refused=false;try{preparedFootDepth(foot,prepared);}catch(const std::invalid_argument&){refused=true;}
    if(!refused||std::fegetround()!=FE_UPWARD)throw std::runtime_error("Prepared Foot accepted missing-image caller scratch");
    foot.unit.dimensionHeight=37;refused=false;try{preparedFootDepth(foot,prepared);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Prepared Foot accepted a supplied nested scratch value");
    std::fesetround(old);std::cout<<"Ordinary base depth dimension threshold/retained scratch/overlay priority/FP guards: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}

// SPDX-License-Identifier: GPL-3.0-or-later
std::array<std::uint8_t,512> refreshBitmapBytes;refreshBitmapBytes.fill(std::uint8_t(refreshFields[4]));
SurfaceMarkBitmap refreshBitmap{refreshBitmapBytes,256};auto* bitmap=&refreshBitmap;
Bytes paletteBytes[2]={Bytes(65536),Bytes(65536)};
for(int k=0;k<2;++k)for(unsigned i=0;i<65536;++i)paletteBytes[k][i]=std::uint8_t(i*17+k*41+3);
SurfaceMarkPalette refreshPalettes[2]{{refreshFields[2],paletteBytes[0]},{1,paletteBytes[1]}};
for(int i=0;i<3;++i)schemeRecords[i]->palette30C=&refreshPalettes[i==1];
std::array<std::int32_t,3> markHouseIndexes=refreshFields[3]?std::array<std::int32_t,3>{2,1,0}:std::array<std::int32_t,3>{0,1,2};
SurfaceMarkServices marks{first,buckets,bitmap,schemeRegistry,{},[&](const void* h){return markHouseIndexes[hid(h)];},{},{},{},{},
 [&](const auto&,auto at,auto n,auto value){std::cout<<"m "<<at<<' '<<n<<' '<<value<<' ';}};
CopySurface surfaceOwners[2]{
 {surfaces[0],pixelWorld.view(surfaces[0]),{},[&](auto at,auto n,auto value){pixelWorld.store(surfaces[0],at,n,value);},[&](auto d){pixelWorld.locks(surfaces[0],d);},[&]{return tables[0].width7C(surfaces[0]);}},
 {surfaces[1],pixelWorld.view(surfaces[1]),{},[&](auto at,auto n,auto value){pixelWorld.store(surfaces[1],at,n,value);},[&](auto d){pixelWorld.locks(surfaces[1],d);},[&]{return tables[1].width7C(surfaces[1]);}}
};
for(int k=0;k<2;++k)surfaceOwners[k].observe=[&,k](char kind,auto,auto){if(kind=='R')std::cout<<"G "<<k<<' '<<surfaces[k].width<<' '<<surfaces[k].height<<' ';};
SurfaceCopyServices sharedSurfaces{[&](auto& surface)->CopySurface&{return surfaceOwners[sid(surface)];}};
std::array<RefreshSurfaceVirtuals*,2> sharedTables{&tables[0],&tables[1]};
SurfaceRefreshServices refresh{mode,first,second,{},{}};SurfaceRefreshScratch scratch{};
RadarRefreshProbes refreshProbes{pixelWorld.before,pixelWorld.readResult,[&](auto& surface,auto& entry,auto color){std::cout<<"P "<<sid(surface)<<' '<<(&entry-entries)<<' '<<entry.x<<' '<<entry.y<<' '<<color<<' ';}};
RadarRefreshBinding shared(refresh,marks,s,actorWorld,sharedTables,sharedSurfaces,refreshProbes);
for(int k=0;k<2;++k){const auto copy=tables[k].copy8;tables[k].copy8=[&,copy](auto& target,auto* dr,auto* source,auto* sr,auto a,auto b){std::cout<<"copy "<<sid(target)<<' ';for(auto v:*dr)std::cout<<v<<' ';std::cout<<sid(*source)<<' ';for(auto v:*sr)std::cout<<v<<' ';std::cout<<a<<' '<<b<<' ';copy(target,dr,source,sr,a,b);};}
#ifndef RA2_REFRESH_SETUP_ONLY
for(int stage=0;stage<refreshFields[1];++stage){mode=refreshFields[0]^stage;std::cout<<"step "<<mode<<' ';refreshSurfaces(refresh,scratch);}

#endif

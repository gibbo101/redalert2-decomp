#include "shared/rect.hpp"
#include "shared/unknown_map_generator.hpp"
#include "shared/cell.hpp"
#include "shared/cell_class.hpp"
#include "shared/dir_type.hpp"
#include "shared/map_generation_link.hpp"
#include "shared/map_generation_path.hpp"
#include "shared/tileset_index.hpp"
#include "shared/event.hpp"
extern int unknown_tileset_a6dd04;
extern UnknownMapGenerationPath unknown_generation_paths_a700a0[109];
unsigned int __fastcall Map_Random_Range_005797a0(unsigned int minimum,unsigned int maximum);
bool __fastcall Can_Use_Tile_Footprint_005894e0(int tile,Cell const &position,unsigned char check_mark,unsigned char reject_outside);
void __fastcall Place_Tile_Footprint_005883f0(int tile,Cell const &position,int region,int height);
void __fastcall Set_Tile_Footprint_Grid_Byte_00589780(int tile,Cell const &position,unsigned char value);
void __fastcall Erase_Tile_Footprint_00589670(int tile,Cell const &position);
// @ref ?Find_Dirt_Road_Tile_0058a6e0@@YI_NHABVCell@@HAAIAAV1@AAH@Z=0058a6e0
// @ref __real@8@3fe2b0000000b0000000=007a6068
// TibSun MapGeneratorClass::Find_Dirt_Road_Tile (fastcall in RA2: ECX facing, EDX cell).
bool __fastcall Find_Dirt_Road_Tile_0058a6e0(int facing,Cell const &cell,int max_connections,unsigned int &tile,Cell &origin,int &link_index);

// Same-file bodies of the road records' copy and member constructors; the out-of-line copies 0x58B140
// and 0x58B160 are accepted in their own population, this unit expands them.
inline UnknownMapGenerationPoint::UnknownMapGenerationPoint(UnknownMapGenerationPoint const &other)
    : Position(other.Position),unknown_04(other.unknown_04)
{
}
inline UnknownMapGenerationLink::UnknownMapGenerationLink(unsigned int value,Cell const &a,unsigned int next,Cell const &b,int index)
    : unknown_00(value),unknown_04(a),unknown_08(next),unknown_0c(b),unknown_10(index)
{
}

// TibSun facing.h Facing_Sub.
inline FacingType Facing_Sub(int first,int second)
{
    return (FacingType)((first-second)&7);
}

// TibSun Dirt_Road_Tile_Index: the dirt road library entry of a tile type.
inline int Dirt_Road_Tile_Index(int tile)
{
    if(tile>=unknown_tileset_a6e014 && tile<unknown_tileset_a6e014+101) {
        return tile-unknown_tileset_a6e014;
    }
    if(tile<unknown_tileset_a6dd04 || tile>=unknown_tileset_a6dd04+8) {
        return 0;
    }
    return tile-unknown_tileset_a6dd04+101;
}

// Lays a dirt road network out from a junction tile at cell (TibSun
// MapGeneratorClass::Generate_Rural_Roads): breadth-first over a 1024-entry
// queue of road pieces, each tile's links continued or capped.
// A road node field holding a tile (0xffff is the none value, TibSun ISOTILE_NONE).
inline bool Road_Tile_Set(unsigned int tile)
{
    return tile!=0xffff;
}

bool UnknownMapGenerator::Generate_Rural_Roads_0058a1b0(Cell const &cell)
{
    QueueClass<UnknownMapGenerationLink,1024> queue;

    int processed=0;

    unsigned int random_offset=Map_Random_Range_005797a0(0,10);
    int attempt=0;
    int junction;
    while(true) {
        junction=unknown_tileset_a6cb6c+(int)(random_offset+attempt)%11;
        if(Can_Use_Tile_Footprint_005894e0(junction,cell,false,false)) {
            break;
        }
        if(++attempt>=11) {
            return false;
        }
    }

    UnknownMapGenerationLink root(junction,cell,0xffff,cell,-1);
    queue.Add(root);
    while(queue.Count!=0) {
        if(queue.Count>=1020) {
            break;
        }
        bool success=true;
        UnknownMapGenerationLink node=queue.First();
        bool placed=Road_Tile_Set(node.unknown_00);

        int child_count=0;
        UnknownMapGenerationLink *children=0;

        if(placed) {
            if(Road_Tile_Set(node.unknown_08)) {
                Set_Tile_Footprint_Grid_Byte_00589780(node.unknown_08,node.unknown_0c,false);
            }
            Place_Tile_Footprint_005883f0(node.unknown_00,node.unknown_04,-1,-1);

            UnknownMapGenerationPath &tile=unknown_generation_paths_a700a0[Dirt_Road_Tile_Index(node.unknown_00)];

            if(tile.Count>1) {
                int link_count=tile.Count-(node.unknown_10!=-1);
                children=new UnknownMapGenerationLink[link_count];
                if(children!=0) {
                    UnknownMapGenerationLink *child=children;
                    for(int link_index=0;link_index<tile.Count;link_index++) {
                        if(link_index!=node.unknown_10) {
                            UnknownMapGenerationPoint link=tile.Points[link_index];
                            FacingType reverse=Facing_Sub(link.unknown_04,4);

                            Cell connection=CellClass::Adjacent_Cell(node.unknown_04+link.Position,link.unknown_04);
                            int cap_link=0;
                            if(Find_Dirt_Road_Tile_0058a6e0(reverse,connection,1,child->unknown_08,child->unknown_0c,cap_link)) {
                                if(!Find_Dirt_Road_Tile_0058a6e0(reverse,connection,4,child->unknown_00,child->unknown_04,child->unknown_10)) {
                                    child->unknown_10=cap_link;
                                } else {
                                    Set_Tile_Footprint_Grid_Byte_00589780(child->unknown_00,child->unknown_04,true);
                                }
                                Set_Tile_Footprint_Grid_Byte_00589780(child->unknown_08,child->unknown_0c,true);
                                child_count++;
                                child++;
                            } else {
                                success=false;
                                break;
                            }
                        }
                    }
                }
            }
        }

        if(placed && success) {
            if(children!=0) {
                UnknownMapGenerationLink *src=children;
                for(int j=0;j<child_count;j++) {
                    queue.Add(*src);
                    src++;
                }
            }
        } else {
            if(Road_Tile_Set(node.unknown_00)) {
                Erase_Tile_Footprint_00589670(node.unknown_00,node.unknown_04);
                UnknownMapGenerationLink *undo=children;
                while(child_count>0) {
                    if(Road_Tile_Set(undo->unknown_00)) {
                        Set_Tile_Footprint_Grid_Byte_00589780(undo->unknown_00,undo->unknown_04,false);
                    }
                    if(Road_Tile_Set(undo->unknown_08)) {
                        Set_Tile_Footprint_Grid_Byte_00589780(undo->unknown_08,undo->unknown_0c,false);
                    }
                    undo++;
                    --child_count;
                }
            }
            if(Road_Tile_Set(node.unknown_08)) {
                Place_Tile_Footprint_005883f0(node.unknown_08,node.unknown_0c,-1,-1);
            }
        }

        if(children!=0) {
            delete [] children;
        }

        queue.Next();
        processed++;
    }

    while(queue.Count!=0) {
        UnknownMapGenerationLink node=queue.First();
        Place_Tile_Footprint_005883f0(node.unknown_08,node.unknown_0c,-1,-1);
        queue.Next();
    }
    if(processed>1) {
        return true;
    }
    return false;
}

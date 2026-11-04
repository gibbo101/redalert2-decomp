// Place_Waterfall 0x57FF20: bank the river into a waterfall. Same flow as TibSun MapGeneratorClass::Place_Waterfall.
#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/map.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/tileset_index.hpp"
#include "shared/map_random.hpp"
#include "shared/random2.hpp"
#include "shared/crt_memory.hpp"
// @ref ?Grow_Water_Region_005820b0@UnknownMapGenerator@@=005820b0
// @ref ?Pick_Random_Tile_Variant@MapClass@@QAE_NHHHHAA_N_N@Z=0055d640
// @ref ?Unknown_004994D0@DisplayClass@@QAE?AVCell@@ABV2@@Z=004994d0
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &position);
bool UnknownMapGenerator::Place_Waterfall_0057ff20(int region_id,Cell const &cell1,Cell const &cell2,int direction,bool &placed,double &head_x,double &head_y)
{
	placed = false;

	Rect pre(0,0,0,0);

	Rect seed(0,0,0,0);
	Rect patch(0,0,0,0);
	Rect bounds_rect(0,0,0,0);
	Cell center;

	switch (direction) {
		case 0: {
			pre=Rect(cell1.X - 2,cell1.Y - 12,cell2.X - cell1.X + 5,12);

			seed=Rect(cell1.X,cell1.Y - 4,cell2.X - cell1.X + 1,4);

			patch=Rect(cell1.X,cell1.Y - 12,cell2.X - cell1.X + 1,8);

			bounds_rect = Rect(0, seed.Y, 0x200, 0x200 - seed.Y);
			center = Cell(seed.X, seed.Y);
			break;
		}
		case 4: {
			pre=Rect(cell2.X - 2,cell2.Y + 1,cell1.X - cell2.X + 5,12);

			seed=Rect(cell2.X,cell2.Y + 1,cell1.X - cell2.X + 1,4);

			patch=Rect(cell2.X,cell2.Y + 5,cell1.X - cell2.X + 1,8);

			bounds_rect = Rect(0, 0, 0x200, patch.Y - 1);
			center = Cell(seed.X, seed.Y);
			break;
		}
		case 2: {
			pre=Rect(cell1.X + 1,cell1.Y - 2,12,cell2.Y - cell1.Y + 5);

			seed=Rect(cell1.X + 1,cell1.Y,4,cell2.Y - cell1.Y + 1);

			patch=Rect(cell1.X + 5,cell1.Y,8,cell2.Y - cell1.Y + 1);

			bounds_rect = Rect(0, 0, patch.X - 1, 0x200);
			center = Cell(patch.X, patch.Y);
			break;
		}
		case 6: {
			pre=Rect(cell2.X - 12,cell2.Y - 2,12,cell1.Y - cell2.Y + 5);

			seed=Rect(cell2.X - 4,cell2.Y,4,cell1.Y - cell2.Y + 1);

			patch=Rect(cell2.X - 12,cell2.Y,8,cell1.Y - cell2.Y + 1);

			bounds_rect = Rect(seed.X, 0, 0x200 - seed.X, 0x200);
			center = Cell(seed.X, seed.Y);
			break;
		}
		default:
			break;
	}

	int yy;
	int xx;

	for (yy = pre.Y; yy < pre.Y + pre.Height; yy++) {
		for (xx = pre.X; xx < pre.X + pre.Width; xx++) {
			if (Generation_Cell_In_Bounds_0058da10(Cell(xx, yy))) {
				if (UnknownMapGenerationCell::Get_Region(Cell(xx, yy)) != 0) {
					return(true);
				}

				if (!Map[Cell(xx, yy)].unknown_47b590()) {
					return(true);
				}
			}
		}
	}

	for (yy = seed.Y; yy < seed.Y + seed.Height; yy++) {
		for (xx = seed.X; xx < seed.X + seed.Width; xx++) {
			if (Generation_Cell_In_Bounds_0058da10(Cell(xx, yy))) {
				int tile_index = Map_Random_Range_005797a0(0, 5);
				Map[Cell(xx, yy)].IsoTileIndex = tile_index+unknown_tileset_a52580;

				int subtile = Map_Random_Range_005797a0(0, 3);
				Map[Cell(xx, yy)].unknown_11a = subtile;

				if(unknown_map_cells_a70a24) {
								MapRegionClass::Get_Cell_Data(Cell(xx,yy)).RegionIndex=region_id;
							}
			}
		}
	}

	bool success = Grow_Water_Region_005820b0(unknown_308, 0.003f, bounds_rect, center, false);
	if (success) {
		success = Map.Unknown_0055C2C0(unknown_308,0);
		if (success) {
			success = Grow_Region_00581940(unknown_308, 2, bounds_rect, 0, 0);
			if (success) {
				int region = unknown_308;
				Map.Unknown_0055A550();
				CellClass * cptr = Map.Unknown_0055A490();
				while (cptr !=0) {
					Cell c = cptr->MapCoords;
					int other_region = UnknownMapGenerationCell::Get_Region(c);
					if (other_region == region) {
						cptr->unknown_11b += 4;
					}
					cptr = Map.Unknown_0055A490();
				}

				for (yy = patch.Y; yy < patch.Y + patch.Height; yy++) {
					for (xx = patch.X; xx < patch.X + patch.Width; xx++) {
						if (Generation_Cell_In_Bounds_0058da10(Cell(xx, yy))) {
							int tile_index = Map_Random_Range_005797a0(0, 5);
							Map[Cell(xx, yy)].IsoTileIndex = tile_index+unknown_tileset_a52580;

							int subtile = Map_Random_Range_005797a0(0, 3);
							Map[Cell(xx, yy)].unknown_11a = subtile;

							if(unknown_map_cells_a70a24) {
								MapRegionClass::Get_Cell_Data(Cell(xx,yy)).RegionIndex=region_id;
							}
						}
					}
				}

				bool place_ok = true;
				
				switch (direction) {
					case 2: {
						Cell base(patch.X, patch.Y + patch.Height);
						int height = Map[base + Cell(2, 0)].unknown_11b;

						Map.unknown_11a4 = IsoTileTypes[unknown_tileset_a52584];
						Map.Unknown_004994D0(base);
						Map.Pick_Random_Tile_Variant(0,0x10000,height,unknown_308,place_ok,false);

						Map.unknown_11a4 = IsoTileTypes[unknown_tileset_a52584+3];
						Map.Unknown_004994D0(base - Cell(0, patch.Height + 2));
						Map.Pick_Random_Tile_Variant(0,0x10000,height,unknown_308,place_ok,false);

						Cell top = base + Cell(0, 2);
						Cell bottom = base - Cell(0, patch.Height + 3);

						if (Generation_Cell_In_Bounds_0058da10(top)) {
							Map[top].IsoTileIndex = 0xffff;
							Map[top].unknown_11b += 4;
							Map[top].unknown_11a = 0;
							if(unknown_map_cells_a70a24) {
								MapRegionClass::Get_Cell_Data(top).RegionIndex=unknown_308;
							}
						}

						if (Generation_Cell_In_Bounds_0058da10(bottom)) {
							Map[bottom].IsoTileIndex = 0xffff;
							Map[bottom].unknown_11b += 4;
							Map[bottom].unknown_11a = 0;
							if(unknown_map_cells_a70a24) {
								MapRegionClass::Get_Cell_Data(bottom).RegionIndex=unknown_308;
							}
						}

						int seg = 0;
						if (seg < patch.Height) {
						int remaining = patch.Height;
						do {
							if (remaining % 2) {
								Map.Unknown_004994D0(base - Cell(0, seg + 1));
								Map.unknown_11a4 = IsoTileTypes[unknown_tileset_a52584 + 1];
								seg++;
								remaining--;
							} else {
								Map.Unknown_004994D0(base - Cell(0, seg + 2));
								Map.unknown_11a4 = IsoTileTypes[unknown_tileset_a52584 + 2];
								seg += 2;
								remaining -= 2;
							}
							Map.Pick_Random_Tile_Variant(0,0x10000,height,unknown_308,place_ok,false);
						} while (seg < patch.Height);
						}
						break;
					}

					case 6: {
						Cell base(seed.X - 2, patch.Y + patch.Height);
						int height = Map[base - Cell(2, 0)].unknown_11b;

						Map.unknown_11a4 = IsoTileTypes[unknown_tileset_a6cf58];
						Map.Unknown_004994D0(base);
						Map.Pick_Random_Tile_Variant(0,0x10000,height,unknown_308,place_ok,false);

						Map.unknown_11a4 = IsoTileTypes[unknown_tileset_a6cf58+3];
						Map.Unknown_004994D0(base - Cell(0, patch.Height + 2));
						Map.Pick_Random_Tile_Variant(0,0x10000,height,unknown_308,place_ok,false);

						Map[base - Cell(0, 1)].IsoTileIndex = 0xffff;
						Map[base + Cell(0, patch.Width + 2)].IsoTileIndex = 0xffff;

						for (int i = 0; i < patch.Height + 2; i++) {
							Map[base - Cell(0, i)].unknown_11b -= 4;
						}

						Cell top = base + Cell(1, 2);
						Cell bottom = base - Cell(-1, patch.Height + 3);

						if (Generation_Cell_In_Bounds_0058da10(top)) {
							Map[top].IsoTileIndex = 0xffff;
							Map[top].unknown_11b += 4;
							Map[top].unknown_11a = 0;
							if(unknown_map_cells_a70a24) {
								MapRegionClass::Get_Cell_Data(top).RegionIndex=unknown_308;
							}
						}

						if (Generation_Cell_In_Bounds_0058da10(bottom)) {
							Map[bottom].IsoTileIndex = 0xffff;
							Map[bottom].unknown_11b += 4;
							Map[bottom].unknown_11a = 0;
							if(unknown_map_cells_a70a24) {
								MapRegionClass::Get_Cell_Data(bottom).RegionIndex=unknown_308;
							}
						}

						int seg = 0;
						if (seg < patch.Height) {
						int remaining = patch.Height;
						do {
							if (remaining % 2) {
								Map.Unknown_004994D0(base - Cell(-1, seg + 1));
								Map.unknown_11a4 = IsoTileTypes[unknown_tileset_a6cf58 + 1];
								seg++;
								remaining--;
							} else {
								Map.Unknown_004994D0(base - Cell(-1, seg + 2));
								Map.unknown_11a4 = IsoTileTypes[unknown_tileset_a6cf58 + 2];
								seg += 2;
								remaining -= 2;
							}
							Map.Pick_Random_Tile_Variant(0,0x10000,height,unknown_308,place_ok,false);
						} while (seg < patch.Height);
						}
						break;
					}

					case 4: {
						Cell base(patch.X - 2, patch.Y);
						int height = Map[base + Cell(0, 2)].unknown_11b;

						Map.unknown_11a4 = IsoTileTypes[unknown_tileset_a52ea0];
						Map.Unknown_004994D0(base);
						Map.Pick_Random_Tile_Variant(0,0x10000,height,unknown_308,place_ok,false);

						Map.unknown_11a4 = IsoTileTypes[unknown_tileset_a52ea0+3];
						Map.Unknown_004994D0(base + Cell(patch.Width + 2, 0));
						Map.Pick_Random_Tile_Variant(0,0x10000,height,unknown_308,place_ok,false);

						Cell left = base + Cell(-1, 0);
						Cell right = base + Cell(patch.Width + 4, 0);

						if (Generation_Cell_In_Bounds_0058da10(left)) {
							Map[left].IsoTileIndex = 0xffff;
							Map[left].unknown_11b += 4;
							Map[left].unknown_11a = 0;
							if(unknown_map_cells_a70a24) {
								MapRegionClass::Get_Cell_Data(left).RegionIndex=unknown_308;
							}
						}

						if (Generation_Cell_In_Bounds_0058da10(right)) {
							Map[right].IsoTileIndex = 0xffff;
							Map[right].unknown_11b += 4;
							Map[right].unknown_11a = 0;
							if(unknown_map_cells_a70a24) {
								MapRegionClass::Get_Cell_Data(right).RegionIndex=unknown_308;
							}
						}

						int seg = 0;
						if (seg < patch.Width) {
						int remaining = patch.Width;
						do {
							if (remaining % 2) {
								Map.Unknown_004994D0(base + Cell(seg + 2, 0));
								Map.unknown_11a4 = IsoTileTypes[unknown_tileset_a52ea0 + 1];
								seg++;
								remaining--;
							} else {
								Map.Unknown_004994D0(base + Cell(seg + 2, 0));
								Map.unknown_11a4 = IsoTileTypes[unknown_tileset_a52ea0 + 2];
								seg += 2;
								remaining -= 2;
							}
							Map.Pick_Random_Tile_Variant(0,0x10000,height,unknown_308,place_ok,false);
						} while (seg < patch.Width);
						}
						break;
					}

					case 0: {
						Cell base(seed.X - 2, seed.Y - 2);
						int height = Map[base - Cell(0, 2)].unknown_11b;

						Map.unknown_11a4 = IsoTileTypes[unknown_tileset_a52ef0];
						Map.Unknown_004994D0(base);
						Map.Pick_Random_Tile_Variant(0,0x10000,height,unknown_308,place_ok,false);

						Map.unknown_11a4 = IsoTileTypes[unknown_tileset_a52ef0+3];
						Map.Unknown_004994D0(base + Cell(patch.Width + 2, 0));
						Map.Pick_Random_Tile_Variant(0,0x10000,height,unknown_308,place_ok,false);

						Map[base + Cell(1, 0)].IsoTileIndex = 0xffff;
						Map[base + Cell(patch.Width + 2, 0)].IsoTileIndex = 0xffff;

						for (int i = 0; i < patch.Width + 2; i++) {
							Map[base + Cell(i + 1, 0)].unknown_11b -= 4;
						}

						Cell left = base + Cell(-1, 1);
						Cell right = base + Cell(patch.Width + 4, 1);

						if (Generation_Cell_In_Bounds_0058da10(left)) {
							Map[left].IsoTileIndex = 0xffff;
							Map[left].unknown_11b += 4;
							Map[left].unknown_11a = 0;
							if(unknown_map_cells_a70a24) {
								MapRegionClass::Get_Cell_Data(left).RegionIndex=unknown_308;
							}
						}

						if (Generation_Cell_In_Bounds_0058da10(right)) {
							Map[right].IsoTileIndex = 0xffff;
							Map[right].unknown_11b += 4;
							Map[right].unknown_11a = 0;
							if(unknown_map_cells_a70a24) {
								MapRegionClass::Get_Cell_Data(right).RegionIndex=unknown_308;
							}
						}

						int seg = 0;
						if (seg < patch.Width) {
						int remaining = patch.Width;
						do {
							if (remaining % 2) {
								Map.Unknown_004994D0(base + Cell(seg + 2, 1));
								Map.unknown_11a4 = IsoTileTypes[unknown_tileset_a52ef0 + 1];
								seg++;
								remaining--;
							} else {
								Map.Unknown_004994D0(base + Cell(seg + 2, 1));
								Map.unknown_11a4 = IsoTileTypes[unknown_tileset_a52ef0 + 2];
								seg += 2;
								remaining -= 2;
							}
							Map.Pick_Random_Tile_Variant(0,0x10000,height,unknown_308,place_ok,false);
						} while (seg < patch.Width);
						}
						break;
					}

					default:
						break;
				}
			}
		}
	}

	int x_offsets[4] = { 0, 12, 0, -12 };
	int y_offsets[4] = { -12, 0, 12, 0 };

	if (success) {
		head_x += (double)x_offsets[direction / 2];
		head_y += (double)y_offsets[direction / 2];
	}

	placed = success;
	return(success);
}

#define ISOMETRIC_TILE_TYPE_DECLARE_STATICS
// CellClass::Clear_Icon for Load_Tiles (0x0052B2E0; guarded in shared/cell.hpp).
#define CELL_DECLARE_CLEAR_ICON
// The unit implements the vector accessors (its Load 0x0052E1C0 and slot 39 use them): the
// first source of the unit that includes vector_class.hpp defines them.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/isometric_tile_type.hpp"
// The isometric tile palette (0x00A6DD10) and its dynamic initializer (0x00528570).
#include "shared/convert.hpp"

PaletteClass IsoTilePalette;
// @ref ?IsoTilePalette@@3VPaletteClass@@A=00a6dd10

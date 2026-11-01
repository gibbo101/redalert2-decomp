// MapPreviewClass (TibSun preview.cpp): the scenario's map preview picture.

#include "shared/map_preview.hpp"
#include "shared/surface.hpp"
#include "shared/dsurface.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/ccini_class.hpp"
#include "shared/buffer_pipe.hpp"
#include "shared/lzo_pipe.hpp"
#include "shared/buffer_straw.hpp"
#include "shared/lzo_straw.hpp"
#include "shared/hicolor.hpp"
#include "shared/hicolor_pixel.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/ms_anim.hpp"
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
#include "shared/map_view.hpp"
#include "shared/wstring.hpp"
#include "shared/tactical.hpp"
#include "shared/cell_class.hpp"
#include "shared/overlay_type.hpp"
#include "shared/terrain.hpp"
#include "shared/id_source.hpp"
#include "shared/coord.hpp"
#include "shared/crt_memory.hpp"
#include "shared/debug_printf.hpp"

UnknownPreview_0061D430::UnknownPreview_0061D430() :
    unknown_00(0)
{
}

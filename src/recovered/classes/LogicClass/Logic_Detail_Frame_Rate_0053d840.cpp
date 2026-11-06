#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/logic.hpp"
#include "shared/main_loop.hpp"
#include "shared/queue.hpp"
#include "shared/rules.hpp"
#include "shared/id_source.hpp"
#include "shared/special.hpp"
#include "shared/map_view.hpp"
#include "shared/foot.hpp"
#include "shared/scenario_tags.hpp"
#include "shared/tag.hpp"
#include "shared/anim.hpp"
#include "shared/building_light.hpp"
#include "shared/bullet.hpp"
#include "shared/infantry.hpp"
#include "shared/particle_system.hpp"
#include "shared/terrain.hpp"
#include "shared/voxel_anim.hpp"
#include "shared/wave.hpp"
#include "shared/aircraft.hpp"
#include "shared/saveload_lists.hpp"
#include "shared/kamikaze_tracker.hpp"
#include "shared/tiberium.hpp"
#include "shared/spot_light.hpp"
#include "shared/laser_draw.hpp"
#include "shared/lightning_storm.hpp"
#include "shared/radsite.hpp"
#include "shared/light_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/vector_class.hpp"
#include "shared/abstract.hpp"
#include "shared/empulse_class.hpp"
#include "shared/alpha_shape.hpp"
#include "shared/tactical.hpp"
#include "shared/factory_class_decl.hpp"
#include "shared/house.hpp"

extern unsigned int unknown_detail_frame_rate_7dfb34;   // 0x007DFB34 (set by 0x0053D820)
extern unsigned int unknown_detail_buffer_zone_7dfb38;  // 0x007DFB38 (set by 0x0053D830)
extern bool unknown_detail_reduced_a6eb28;              // 0x00A6EB28
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
bool Unknown_0051FC70();                                // 0x0051FC70 (dominator state 2; hypothesis)
void Unknown_00521A70();                                // 0x00521A70

unsigned int Unknown_0053D840()
{
    if (unknown_detail_reduced_a6eb28) {
        if (unknown_a6eb1c >= unknown_detail_frame_rate_7dfb34 + unknown_detail_buffer_zone_7dfb38) {
            unknown_detail_reduced_a6eb28 = false;
            return unknown_detail_frame_rate_7dfb34;
        }
        return unknown_detail_frame_rate_7dfb34 + unknown_detail_buffer_zone_7dfb38;
    }
    if (unknown_a6eb1c < unknown_detail_frame_rate_7dfb34) {
        unknown_detail_reduced_a6eb28 = true;
        return unknown_detail_frame_rate_7dfb34 + unknown_detail_buffer_zone_7dfb38;
    }
    return unknown_detail_frame_rate_7dfb34;
}
// @ref ?unknown_detail_frame_rate_7dfb34@@3IA=007dfb34
// @ref ?unknown_detail_buffer_zone_7dfb38@@3IA=007dfb38
// @ref ?unknown_detail_reduced_a6eb28@@3_NA=00a6eb28
// @ref ?unknown_a6eb1c@@3IA=00a6eb1c

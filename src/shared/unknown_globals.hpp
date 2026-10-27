// Scalar and pointer globals of the data segment that several headers need (one declaration
// each; addresses in the comments).
#ifndef RA2_SHARED_UNKNOWN_GLOBALS_HPP
#define RA2_SHARED_UNKNOWN_GLOBALS_HPP

class Surface;
class HouseClass;
class ConvertClass;

extern int unknown_int_7add80;
extern ConvertClass *unknown_drawer_8323cc;  // 0x008323CC
extern bool unknown_flag_8373c1;  // 0x008373C1 the power bar is shown (Power AI/Draw_It, Radar 0x00630350)
extern bool unknown_flag_8373c3;  // 0x008373C3
extern bool unknown_flag_83740c;
extern int unknown_int_839630;
extern int unknown_int_839634;
extern int unknown_int_839638;  // 0x00839638 sidebar x offset
extern int unknown_int_839648;  // 0x00839648 screen width
extern Surface *unknown_surface_839948;  // 0x00839948 (sidebar surface)
extern Surface *unknown_surface_839950;  // 0x00839950 screen
extern Surface *unknown_surface_839954;  // 0x00839954 (Get_Input draws the buttons on it)
extern Surface *unknown_surface_839958;  // 0x00839958 background
extern Surface *unknown_surface_83995c;  // 0x0083995C current drawing surface
extern Surface *unknown_surface_839964;  // 0x00839964 the surface Render composes
extern bool unknown_flag_839c4c;  // 0x00839C4C
extern int unknown_8523e0;  // 0x008523E0 VQA frame width (hypothesis)
extern int unknown_8523e4;  // 0x008523E4 VQA frame height (hypothesis)
extern bool unknown_flag_852fd7;  // 0x00852FD7
extern HouseClass *unknown_player_a35db4;  // 0x00A35DB4 the player's house
extern int unknown_game_mode_a3d298;  // 0x00A3D298
extern int unknown_a40774;  // 0x00A40774 (a live-object count; BuildingClass, FactoryClass, ...)
extern bool unknown_flag_a40958;  // 0x00A40958 (the destructor then calls ObjectClass slot 52)
extern bool unknown_flag_a40b30;  // 0x00A40B30 the sidebar is on the left
extern float unknown_volume_a40b44;  // 0x00A40B44 sound effect volume scale
extern bool unknown_flag_a40d04;  // 0x00A40D04 (FootClass::Detach keeps a live parasite while it is set)
extern bool unknown_a40d13;
extern bool unknown_flag_a40d13;  // 0x00A40D13
extern int unknown_ini_format_a40d24;
extern bool unknown_flag_a40d28;  // 0x00A40D28 application active (focus)
extern bool unknown_flag_a40d44;  // 0x00A40D44
extern long unknown_com_objects_a6eb14;  // 0x00A6EB14 (live COM object count; hypothesis)
extern bool unknown_flag_abcd84;  // 0x00ABCD84
extern int unknown_b263d8;  // 0x00B263D8

#endif

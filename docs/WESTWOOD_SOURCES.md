# Westwood source releases

Electronic Arts published the Westwood sources of several Command & Conquer
games under GPL-3.0 with EA's additional terms (section 7: no EA trademarks,
modified versions marked as such, notice retained). Red Alert 2's own source
was not released, but RA2 is the same lineage: its library layer is the
Westwood library that Renegade ships as `wwlib`, and its game classes descend
from Red Alert's `CODE/` through Tiberian Sun.

The clones live under the ignored `private/reference/` and are never staged.
Nothing is copied from them into `src/`: GPL text would change this project's
provenance, and it is not RA2's source anyway. They are read for the shape of
Westwood's code, which is what decides VC6's output: names, member and
statement order, which helpers are inline, which clamps are macros. Every
hypothesis taken from them is verified on the exact target like any other
([REFERENCES.md](REFERENCES.md)); the matching rules they explain are in
[VC6_MATCHING_NOTES.md](VC6_MATCHING_NOTES.md) under "Westwood source idioms".

| Repository | Pinned commit | Checked out |
|---|---|---|
| `electronicarts/CnC_Red_Alert` | `0dc09bb1d6188d1ec79ab4765b22a48b75ffee32` | everything: `CODE/` (1996-97 game and library classes), `WIN32LIB/`, `IPX/`, `WINVQ/`, `WWFLAT32/` |
| `electronicarts/CnC_Renegade` | `3e00c3a1b97381bb28be89a35b856375e0629a08` | sparse: `Code/wwlib` (2001-02 library), `Code/WWOnline`, `Code/wwsaveload`, `Code/wwnet`, `Code/wwutil`, `Code/wwdebug` |
| `electronicarts/CnC_Tiberian_Dawn` | `e0d372dc582c053a699114942b984dad0457f9b3` | repository only, no checkout (older copy of the Red Alert code) |

Not cloned: `CnC_Remastered_Collection` (the 2020 release of the same two
games with remaster changes) and `CnC_Generals_Zero_Hour` (the SAGE engine,
a different lineage). Renegade's `Code/WWMath` (Vector3, Matrix3D,
Quaternion) can be added to the sparse checkout when a lane needs it.

## Which version RA2 is closest to

- **Library classes match Renegade's `wwlib` text almost verbatim:**
  VectorClass/DynamicVectorClass (Add's grow test
  `(IsAllocated || !VectorMax) && GrowthStep > 0`, GrowthStep 10, the
  ActiveCount clamp in Resize), IndexClass (NodeElement {ID, Data}, lazy
  qsort then Binary_Search, the Archive cache), GenericNode/GenericList and
  Node<T>/List<T>, Straw/Pipe with ChainTo/ChainFrom, the Random classes
  with their SIGNIFICANT_BITS enums and Pick_Random_Number, TRect/TPoint2D,
  the timers (Started is -1 while stopped), CRC, SHA, Blowfish, PK/MPMath,
  LCW, LZO, Base64, the file classes and the surfaces. Red Alert's `CODE/`
  has the 1996 versions of most of them (unsigned sizes, `int` booleans).
- **Game classes descend from Red Alert's `CODE/`.** Of the 68 original RA2
  unit names the executable embeds ([ORIGINAL_SOURCE_FILES.md](ORIGINAL_SOURCE_FILES.md)),
  31 have a same-named file in Red Alert: Connect, Conquer, Display, Egos,
  Event, GOptions, GameDlg, House, Infantry, Ini, Init, LoadDlg, MPLayer,
  MapSel, NetDlg, NullDlg, NullMgr, Options, Power, Queue, Radar, Scenario,
  SendFile, Session, Sidebar, Startup, Super, TAction, Techno, ToolTip and
  Unit. The RA2 names with an upper-case `.CPP` extension are the files that
  survived from the DOS-era tree; the lower-case `.cpp` ones (MPCoop, WDT*,
  Tactical, MapGen, Skirmish, ...) are Tiberian Sun or RA2 additions with no
  public ancestor. For a surviving unit, Red Alert's file of the same name
  shows the original order of the file-level helpers and statics.
- **Differences RA2 has over both public versions (keep them):** INIClass
  holds SectionList and SectionIndex by value (+0x04/+0x20) with LineComments
  and per-entry column records (wwlib holds two pointers and no comments);
  VectorClass slot 6 `Fetch`; DynamicVectorClass::Insert_After;
  ReferenceCounted/rc_ptr are the shape of `WWOnline/RefCounted.h` and
  `RefPtr.h` (AddReference/ReleaseReference, count at +0x04, a base with a
  virtual destructor holding the pointer), not wwlib's RefCountClass;
  Wstring and WideString are not wwlib's StringClass/WideStringClass.

## Where to look: recovered header to reference file

Paths are relative to `private/reference/CnC_Red_Alert/CODE/` (RA1),
`.../CnC_Red_Alert/WIN32LIB/` (W32) and `.../CnC_Renegade/Code/` (RG).

| `src/shared/` | Reference |
|---|---|
| vector_class, vector_class_decl, type_list | RG wwlib/vector.h; RA1 VECTOR.H, VECTOR.CPP |
| ini_class, ccini_class (INIClass, INISection, INIEntry, IndexClass) | RG wwlib/ini.h, inisup.h, ini.cpp, index.h, bsearch.h; RA1 INI.H, INI.CPP, CCINI.H, SEARCH.H |
| GenericList/Node/List (in ini_class), link_prefix_layout | RG wwlib/listnode.h; RA1 LISTNODE.H, LINK.H |
| straw, pipe, buffer_straw/pipe, file_straw/pipe, cache_straw | RG wwlib/straw.h, pipe.h, xstraw.h, xpipe.h, cstraw.h; RA1 STRAW.H, PIPE.H, XSTRAW.H, XPIPE.H, CSTRAW.H |
| lcw, lcw_straw/pipe, lzo, lzo_straw/pipe | RG wwlib/lcw.h, lcwstraw.h, lcwpipe.h, lzo.h, lzo1x.h, lzostraw.h, lzopipe.h; RA1 same names |
| blowfish_engine, blow_straw/pipe, pkey, pk_straw/pipe, sha, sha_pipe, mpmath, int | RG wwlib/blowfish.h, blwstraw.h, blowpipe.h, pk.h, rsacrypt.h, pkstraw.h, pkpipe.h, sha.h, shastraw.h, shapipe.h, mpmath.h, int.h; RA1 BLOWFISH.H, PK.H, SHA.H, MP.H, INT.H |
| crc_memory, crc_stream, wwcrc_engine, base64 | RG wwlib/crc.h, crcstraw.h, crcpipe.h, realcrc.h, base64.h, b64straw.h, b64pipe.h; RA1 CRC.H, CRCSTRAW.H, BASE64.H |
| random, random2, random3, random_straw | RG wwlib/random.h, rndstraw.h; RA1 RANDOM.H, RNDSTRAW.H |
| rect (TRect, TPoint2D, Point2D) | RG wwlib/trect.h, point.h; RA1 RECT.H |
| raw_file_class, buffer_io_file_class, ram_file_class, cc_file_class, cd_file_class, mix_file_class, file_entry | RG wwlib/wwfile.h, rawfile.h, bufffile.h, ramfile.h, mixfile.h, ffactory.h; RA1 RAWFILE.H, BFIOFILE.H, RAMFILE.H, CCFILE.H, CDFILE.H, MIXFILE.H |
| cd_timer, t_timer, system_timer | RA1 FTIMER.H; RG wwlib/timer.h, stimer.h, systimer.h |
| surface, surface_blit, dsurface, gdi_bitmap_surface, blit, blitter, the *_blitters headers, convert, palette, hsv_class, rgb_class | RG wwlib/surface.h, xsurface.h, dsurface.h, bsurface.h, blit.h, blitblit.h, blitter.h, convert.h, palette.h, hsv.h, rgb.h; RA1 SURFACE.H, HSV.H, RGB.H |
| wwmouse, mouse, keyboard, mono_class, text_print, msfont | RG wwlib/wwmouse.h, keyboard.h, mono.h, wwfont.h; RA1 MOUSE.H, KEYBOARD.H, MONOC.H; W32 KEYBOARD/, MOUSE/, MONO/, FONT/ |
| reference_counted (ReferenceCounted, rc_ptr) | RG WWOnline/RefCounted.h, RefPtr.h (shape); wwlib/refcount.h, ref_ptr.h differ |
| wol_* | RG WWOnline/WOLChannel.h, WOLLadder.h, WOLSession.h, WOLConnect.h, ... |
| hash_object, hash_string | RG wwlib/hashtemplate.h, hash.h, hashcalc.h (not yet compared) |
| noinit (NoInitClass), swizzle | RG wwlib/noinit.h; RA1 FTIMER.H; RG wwsaveload/pointerremap.h |
| abstract, abstract_class, abstract_type | RA1 ABSTRACT.H |
| object, object_type, techno, techno_type, foot, unit, unit_type, infantry, infantry_type, aircraft, aircraft_type, building, building_type, bullet, bullet_type, anim, anim_type, overlay, overlay_type, smudge, smudge_type, terrain, terrain_type, warhead_type, weapon_type, super | RA1 file of the same name (OBJECT.H, TECHNO.H, FOOT.H, UNIT.H, ...) and its .CPP |
| house, house_type, team, team_type, trigger, trigger_type, taction, tevent, mission, radio, target, facing, stage, layer, cell, map, display, radar, power, sidebar, tab, scroll, gscreen, mouse_class | RA1 HOUSE.H, TEAM.H, TEAMTYPE.H, TRIGGER.H, TRIGTYPE.H, TACTION.H, TEVENT.H, MISSION.H, RADIO.H, TARGET.H, FACING.H, STAGE.H, LAYER.H, CELL.H, MAP.H, DISPLAY.H, RADAR.H, POWER.H, SIDEBAR.H, TAB.H, SCROLL.H, GSCREEN.H, MOUSE.H |
| event, options, rules, special, theme, score_anim, score_font, tool_tip, message_list, carryover, base, factory_class, scenario_checkpoint, savegame_info | RA1 EVENT.H, OPTIONS.H, RULES.H, SPECIAL.H, THEME.H, SCORE.H, TOOLTIP.H, MSGLIST.H, CARRY.H, BASE.H, FACTORY.H, SCENARIO.H, SAVELOAD.CPP |
| gadget, check_list, color_list, game_options_dialog, game_controls_dialog | RA1 GADGET.H, CONTROL.H, TOGGLE.H, TEXTBTN.H, SHAPEBTN.H, LIST.H, CHEKLIST.H, COLRLIST.H, EDIT.H, SLIDER.H, GAUGE.H, MSGBOX.H, GOPTIONS.H, GAMEDLG.H |
| ipx_address, ipx_conn, ipx_global_conn, ipx_manager, ipx_interface, connection, conn_man, comm_buffer, null_modem, session_blocks, packet_field | RA1 IPXADDR.H, IPXCONN.H, IPXGCONN.H, IPXMGR.H, CONNECT.H, CONNMGR.H, COMBUF.H, NULLCONN.H, NULLMGR.H, SESSION.H, FIELD.H, PACKET.H; RG wwnet/ |
| movie, audio, sound_play, shape_file, buffer, dial8 | RA1 MOVIE.H, AUDIO.H, DIAL8.H; W32 MOVIE/, AUDIO/, SHAPE/, BUFFER.H |
| vector3, matrix3d, quaternion | RG Code/WWMath (add to the sparse checkout) |

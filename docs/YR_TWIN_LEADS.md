# Yuri's Revenge twin leads

Leads from the Yuri's Revenge matching decompilation
([gibbo101/ra2-decomp](https://github.com/gibbo101/ra2-decomp), GPL-3.0 with EA's
section 7 terms, commit `d074f09995`). Each row is an RA2 function, not in this project's
accepted regions at `dfb0df0992`, whose body is byte-identical to a function that matches
there in `gamemd.exe` 1.001, apart from absolute addresses and call targets.

They are hypotheses under [REFERENCES.md](REFERENCES.md): verify each on the supplied
target before accepting it. The linked source uses that project's headers and names.

**Method.** Each matched YR body was masked at absolute addresses and rel32 branch
targets and searched for in an RA2 1.006 `game.exe` of the same size as the supplied
target. A row needs one unique hit of 32 bytes or more that ends at padding. The same
search finds 3,875 functions already accepted here, each inside its manifest region.

**39 functions, 20,193 bytes.** Nine are original assembly from the TibSun archive
(`.asm`), which this project ledgers separately from recovered C/C++.

| RA2 address | Bytes | YR name | YR address | YR source |
|---|---:|---|---|---|
| `0x00403F80` | 401 | `AudioEventCloseDown` | `0x00403FA0` | [src/wpaudio/audevent.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/wpaudio/audevent.cpp#L187) |
| `0x004041B0` | 1,316 | `AudioServiceAllEvents` | `0x004041D0` | [src/wpaudio/audevent.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/wpaudio/audevent.cpp#L343) |
| `0x00405A10` | 184 | `audioEventSampleDone` | `0x00405A00` | [src/wpaudio/audevent.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/wpaudio/audevent.cpp#L1034) |
| `0x00408760` | 228 | `STM_StreamDestroy` | `0x00408840` | [src/wpaudio/audstrm.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/wpaudio/audstrm.cpp#L122) |
| `0x004090E0` | 237 | `STM_AccessAdvance` | `0x004091C0` | [src/wpaudio/audstrm.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/wpaudio/audstrm.cpp#L507) |
| `0x0040A260` | 714 | `audioStart` | `0x0040A340` | [src/wpaudio/drv_dsnd.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/wpaudio/drv_dsnd.cpp#L823) |
| `0x0040AF00` | 49 | `??_I@YGXPAXIHP6EX0@Z@Z` | `0x0040AFD0` | [src/_astar.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/_astar.cpp#L49) |
| `0x004237B0` | 988 | `AnimClass::Next_Flaming_Guy_Coord` | `0x00425D10` | [src/anim.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/anim.cpp#L1141) |
| `0x004861C0` | 70 | `?BlitForward@?$BlitTransXlat@G@@UBEXPAXPBXHH00HH@Z` | `0x004912B0` | [src/convert.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/convert.cpp#L1073) |
| `0x004E09D0` | 197 | `GScreenClass::Input` | `0x004F4320` | [src/gscreen.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/gscreen.cpp#L163) |
| `0x004E1350` | 108 | `rgb24_to_rgb1555` | `0x004F4E40` | [src/hicolor.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/hicolor.cpp#L47) |
| `0x00523C80` | 106 | `IPXConnClass::Start_Listening` | `0x0053F540` | [src/ipxconn.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/ipxconn.cpp#L159) |
| `0x00534D40` | 407 | `LCW_Comp` | `0x00551E50` | [src/lcw.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/lcw.cpp#L86) |
| `0x00535530` | 482 | `LCW_Uncompress` | `0x00552640` | [src/lcwstraw.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/lcwstraw.cpp#L89) |
| `0x005395C0` | 281 | `LineTrail::Draw` | `0x00556C00` | [src/link2.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/link2.cpp#L103) |
| `0x00575D20` | 726 | `Create_Zone_Region` | `0x00594420` | [src/mapgen.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/mapgen.cpp#L1752) |
| `0x00577010` | 404 | `MapGeneratorClass::MapGeneratorClass` | `0x00595740` | [src/mapgen.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/mapgen.cpp#L1922) |
| `0x0057C780` | 605 | `MapGeneratorClass::Seed_Land_Type1` | `0x0059AFA0` | [src/mapgen.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/mapgen.cpp#L6513) |
| `0x0057C9E0` | 1,231 | `MapGeneratorClass::Seed_Land_Type2` | `0x0059B200` | [src/mapgen.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/mapgen.cpp#L6567) |
| `0x00581EE0` | 459 | `MapGeneratorClass::Build_Region_Border_Cell_List` | `0x005A0700` | [src/mapgen.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/mapgen.cpp#L4133) |
| `0x00586B40` | 1,913 | `MapGeneratorClass::Create_Urban_Area` | `0x005A5360` | [src/mapgen.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/mapgen.cpp#L5069) |
| `0x0058FF50` | 263 | `Matrix3D::Matrix3D` | `0x005AE750` | [src/matrix3d.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/matrix3d.cpp#L130) |
| `0x005ABF70` | 450 | `Get_RDTSC_CPU_Speed` | `0x005CAFC0` | [src/mpu.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/mpu.cpp#L57) |
| `0x005C2DA0` | 384 | `_DrawMessage` | `0x005E2820` | [src/netshare.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/netshare.cpp#L221) |
| `0x00622400` | 367 | `operator*` | `0x00645ED0` | [src/quat.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/quat.cpp#L77) |
| `0x0063DE10` | 127 | `RocketLocomotionClass::Pitch_To_Target` | `0x00662240` | [src/rocket.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/rocket.cpp#L122) |
| `0x006A88A0` | 619 | `Tactical::Draw_Tile_Shadows` | `0x006D8260` | [src/tactical.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/tactical.cpp#L1349) |
| `0x0072BEF0` | 170 | `WDTState::WDTState` | `0x0076ABE0` | [src/wdtnet.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/wdtnet.cpp#L125) |
| `0x007743C0` | 748 | `XSurface::Fill_Rect` | `0x007BB050` | [src/xsurface.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/xsurface.cpp#L443) |
| `0x00775980` | 45 | `?BlitForward@?$BlitTrans@E@@UBEXPAXPBXHH00HH@Z` | `0x007BC610` | [src/xsurface.cpp](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/xsurface.cpp#L800) |
| `0x0077F08E` | 96 | `Confine_Rect` | `0x007C5E7E` | [src/cliprect.asm](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/cliprect.asm#L214) |
| `0x0077F282` | 70 | `Processor` | `0x007C6072` | [src/detproc.asm](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/detproc.asm#L236) |
| `0x0077F3DF` | 148 | `Iso_Blit_Asm2` | `0x007C61CF` | [src/isoasm.asm](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/isoasm.asm#L233) |
| `0x0077F4BC` | 871 | `General_sosCODECDecompressData` | `0x007C62AC` | [src/olsosdec.asm](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/olsosdec.asm#L203) |
| `0x0077F830` | 266 | `Asm_Ripple_Deform_Points` | `0x007C6620` | [src/smartdeform_.asm](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/smartdeform_.asm#L41) |
| `0x0077F962` | 1,046 | `sosCODECDecompressData` | `0x007C6752` | [src/soscodec.asm](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/soscodec.asm#L177) |
| `0x0077FE89` | 198 | `ASM_UnVQ1_C1_TABLE_ALT` | `0x007C6C79` | [src/unvq_asm.asm](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/unvq_asm.asm#L294) |
| `0x0078047A` | 228 | `ASM_UnVQ_10` | `0x007C726A` | [src/unvq_asm.asm](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/unvq_asm.asm#L1758) |
| `0x00780581` | 2,991 | `VQA_sosCODECDecompressData` | `0x007C7371` | [src/vqa_sos.asm](https://github.com/gibbo101/ra2-decomp/blob/d074f099953e4a26b0636473635d5aa21601a32e/src/vqa_sos.asm#L166) |

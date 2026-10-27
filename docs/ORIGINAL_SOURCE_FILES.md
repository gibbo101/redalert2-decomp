# Original source files

The executable embeds 73 original source paths (`D:\Ra2\House.CPP`, ...)
through assertion and debug macros. `tools/original_target/source_files.py`
finds every function that references one of these strings and records it in
`manifests/original_source_files.json` (file → anchor functions).

The anchors show that **the linker placed object files in alphabetical order
of their source file names** (case-insensitive): `AbsType.cpp` at 0x4106E0,
`Beacon.CPP` 0x42E370, `CampScor.cpp` 0x465C20, `CD.CPP` 0x46E520, ...,
`Unit.CPP` 0x70A0E0, `wonline.cpp` 0x73C580, `WorldDom.cpp` 0x7689C0,
`wwmous.cpp` 0x771900. VC6 keeps each object file's functions together, so
every function belongs to the source file whose alphabetical slot contains
its address.

Consequences for recovery:

- A class's methods normally share one source file and translation unit; the
  file name follows from its address range (RawFileClass at 0x638AC0 lies
  between Radar.CPP and Restate.cpp: `RawFile.cpp`; CCFileClass at 0x468F50
  between CampScor.cpp and CD.CPP: `CCFile.cpp`; CDFileClass after CD.CPP:
  `CDFile.cpp`).
- Acceptance plans should group one source file's functions (address order),
  which reproduces the original inlining decisions.
- Unanchored files are inferred names; anchored ones are evidence. Keep the
  distinction when naming directories.

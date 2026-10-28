# Handoff — original-target decompilation

Current state only; rewritten 2026-10-28. Numbers: [STATUS.md](STATUS.md).
Workflow: [process](ORIGINAL_TARGET_PROCESS.md). Commands:
[build](ORIGINAL_TARGET_BUILD.md). Matching rules: [VC6 notes](VC6_MATCHING_NOTES.md).
Earlier owner periods: [history/HANDOFF_CODEX_OWNER_20261024.md](history/HANDOFF_CODEX_OWNER_20261024.md),
[history/CLAUDE_HANDOFF_20261026.md](history/CLAUDE_HANDOFF_20261026.md).

## Owner and lanes

Claude (Mac) owns integration. Mac lanes (Opus, at most four at once; the Mac
has 16 GB): Tact47 (display-chain action/drawing family), Near48 (sweep
near misses and promotions), Big49 (closest big misses). Windows: one Codex lead
(LEAD.md in the coordination folder) staffing codex1 (Sol) pathfinding
0x570000-0x58FFFF, codex2 (Sol) BuildingClass, codex3 (Terra) bound evidence;
the lead itself owns seed tooling and sweeps. BOARD.md is the lane authority.
Each lane's resume notes are in `build/class-work/<Lane>/NOTES*` (ignored).

## Integration loop

1. Take a delivery: frozen `d/rN/` folder with plans, drafts, header copies,
   base commit. Plans use forward-slash paths and LF endings.
2. Merge header copies with `git merge-file src/shared/H BASE COPY` (BASE = the
   header at the worker's base commit). New headers are copied.
3. Accept each plan: `$RA2_PYTHON -B tools/original_target/accept_sources.py
   --config private/original-target.interactive.json --output
   private/original-target-20261020/accept-NAME PLAN` (accepted == candidates).
4. Land with `private/tools/land.sh "message"`: rehash, full build, commit only
   if `"whole_file_exact": true`, sync Windows, publish the GitHub snapshot,
   prune old build outputs.
5. Signature/name changes land alone through
   `tools/original_target/apply_rename.py SPEC --dry-run`, then with
   `--config private/original-target.interactive.json`, then `land.sh`.

Cadence: build after every accept (a land takes about a minute: tests, full
build, status and source index, commit, sync, publish), so a header change that
breaks another unit is isolated at once; rename batches land alone. Remote
compilation is configured by `RA2_REMOTE_COMPILE` (value in the owner's private
notes) (ssh needs the sandbox off; the user approved that for remote-compile
commands only). A worker check without `--build` can miss header impact on
other units; the full build is the gate.

## Time box and targets

Per function: about 30 minutes per KB of body, capped at four hours; record a
plateau with its best score and draft, then move on. A repeat delivery with no
new bytes is not a delivery. 489 unrecovered functions over 1 KB hold about
1 MB; big functions are worked with the controlled-study method (lab
experiments that yield a rule, then the rule applied), as in the VC6 notes.

## Open debt and resumable misses

- Map.cpp Cell tables (0x5441E0, 0x5461A0, 0x55B520, 0x55CBC0, 0x56B330, ~15.7 KB):
  exact with `Cell(short, short) { Set(x, y); }`; TechFoot39 is finishing the
  0x54AB00 and Overlay Read_INI 0x5DB670 refits.
- CounterClass: HouseClass::~HouseClass calls 0x491C20, which is accepted as the
  `template class VectorClass<int>` destructor; an out-of-line ~CounterClass matches House
  but makes the VectorClass<int> unit emit an extra destructor (Clean45 spec/counter2.json).
- Duplicates left (Clean45 d/globals/README.md): unknown_a40d13 vs unknown_flag_a40d13 (same
  bool), class-typed globals declared in several headers (MainWindow, Houses, Infantry,
  TeamTypes, IsoTileTypes, ...), unknown_object_index_abff58 typed UnknownIndexClass in
  building.hpp but IndexClass elsewhere.
- RulesClass Sides 0x64BC10 needs DynamicVectorClass::ID with `Count()`, which makes
  142 explicit-instantiation units emit an unaccounted Count COMDAT.
- HouseClass::Write_INI 0x4EC230 returns void (rename pending).
- Display chain parked on register tie-breaks (Disp52 NOTES): RTacticalClass::Action 0x62FE30
  97.18, DisplayClass slot 48 0x49BB20 78.29 (needs a slot 46/48 + 0x6D8F60 rename and header
  moves listed there), 0x4991D0 49.4.
- Write_Scenario_INI 0x65F980 uses an inline accessor on PreviewClass (YRpp name; its member is
  `DSurface *ImageSurface`); no plain member form comes close (21-43), so the accessor stays as an
  inline split (AGENTS.md lists inline splits as normal iteration).
- Best misses by lane: WarheadType Read_INI 0x7204E0 99.80, Sidebar Draw_It
  0x67CF80 99.43, TechnoType Load 0x6DE260 98.19 (cached-zero register),
  command registration 0x5173C0 76.7 (holds 47 destructors).
- The catalog is sharded per population under `manifests/original_target/` (index.json +
  populations/); load and write it only through `tools/original_target/catalog_io.py`.

## Environment

- Python with capstone/pefile: `private/matching-pilot/20261020T123117Z/env/bin/python`
  (`RA2_PYTHON` for `build.command`/`test.command`).
- Working copy `/Users/ivalice/Code/redalert2-native`. On the Mac `cp`/`mv`/`rm`
  are interactive aliases: use `/bin/cp -f` etc.; zsh noclobber is on (`>|`).
- Windows PC: host, key and mount are in the owner's private notes and
  `private/tools/sync_windows.sh`. Mirror `C:\ra2\repo`, worktrees `C:\ra2\w\codex1..4`,
  remote-compile jobs `C:\ra2\remote`. Windows full builds work with LLVM's
  clang as the scaffold assembler (`assembler` in the worker configs).
- Cold storage and the private GitHub snapshot: `private/tools/move_cold.sh`,
  `private/tools/publish_github.sh`.

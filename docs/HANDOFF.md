# Handoff — original-target decompilation

Current state only; rewritten 2026-10-28. Numbers: [STATUS.md](STATUS.md).
Workflow: [process](ORIGINAL_TARGET_PROCESS.md). Commands:
[build](ORIGINAL_TARGET_BUILD.md). Matching rules: [VC6 notes](VC6_MATCHING_NOTES.md).
Earlier owner periods: [history/HANDOFF_CODEX_OWNER_20261024.md](history/HANDOFF_CODEX_OWNER_20261024.md),
[history/CLAUDE_HANDOFF_20261026.md](history/CLAUDE_HANDOFF_20261026.md).

## Owner and lanes

Claude (Mac) owns integration. Mac lanes (Opus, at most four at once; the Mac
has 16 GB): TechFoot39 (Techno/Foot, Map.cpp Cell tables), Big41 (largest
functions outside class lanes), Study42 (stack-slot study), Verify43 (parallel
build verifier). Windows Codex workers (coordination
`C:\ra2\coordination\ra2-recovery-w1`, board `BOARD.md`): codex1 (Sol)
pathfinding 0x570000-0x58FFFF, codex2 (Sol) BuildingClass, codex3 (Terra)
bound evidence, codex4 (Terra) rename-spec cleanup. Each lane's resume notes
are in `build/class-work/<Lane>/NOTES*` (ignored).

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

Cadence: batch several accepted plans per build (one `land.sh` every two to
three hours, not per plan); rename batches still land alone. Set
`RA2_REMOTE_COMPILE='ssh://mike@192.168.4.38/C:/ra2/remote?identity=~/.ssh/mike-gaming&jobs=6'`
(ssh needs the sandbox off; the user approved that for remote-compile
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
- `UnknownPoint2D` stand-in duplicates `Point2D` (Tactical 0x6A2900, BuildingType
  MuzzleFlash/DamageFireOffset); `unknown_84ed10` declared in two Building
  sources; codex4 owns both.
- RulesClass Sides 0x64BC10 needs DynamicVectorClass::ID with `Count()`, which makes
  142 explicit-instantiation units emit an unaccounted Count COMDAT.
- HouseClass::Write_INI 0x4EC230 returns void (rename pending).
- Best misses by lane: WarheadType Read_INI 0x7204E0 99.80, Sidebar Draw_It
  0x67CF80 99.43, TechnoType Load 0x6DE260 98.19 (cached-zero register),
  command registration 0x5173C0 76.7 (holds 47 destructors).
- Manifest `manifests/original_target.json` is 97 MB; sharding is planned
  (GitHub snapshot refuses at 104 MB).

## Environment

- Python with capstone/pefile: `private/matching-pilot/20261020T123117Z/env/bin/python`
  (`RA2_PYTHON` for `build.command`/`test.command`).
- Working copy `/Users/ivalice/Code/redalert2-native`. On the Mac `cp`/`mv`/`rm`
  are interactive aliases: use `/bin/cp -f` etc.; zsh noclobber is on (`>|`).
- Windows PC `ssh -i ~/.ssh/mike-gaming mike@192.168.4.38`, C: mounted at
  `/Volumes/mike-gaming/`; mirror `C:\ra2\repo`, worktrees `C:\ra2\w\codex1..4`,
  remote-compile jobs `C:\ra2\remote`. Windows full builds stop at scaffold
  assembly (no i386 assembler there).
- Cold storage: `/Volumes/Lesalia/Code/redalert2-native-cold`
  (`private/tools/move_cold.sh`). Private repo snapshot:
  `git@github.com:meastes/redalert2-decomp.git` (`private/tools/publish_github.sh`).

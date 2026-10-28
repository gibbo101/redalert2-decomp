# Handoff — original-target decompilation

Current state only (2026-10-28). Numbers: [STATUS.md](STATUS.md). Workflow:
[process](ORIGINAL_TARGET_PROCESS.md). Commands: [build](ORIGINAL_TARGET_BUILD.md). Matching rules:
[VC6 notes](VC6_MATCHING_NOTES.md). Open misses and debt: [OPEN_MISSES.md](OPEN_MISSES.md).
Earlier owner periods are in [history/](history/).

## Owner, lanes and pacing

Claude (Mac) owns integration; a Codex session on the Mac may take over as standby owner using this
file, BOARD.md on Windows and git. Usage rules (2026-10-28 review, Pro plan):
- At most four Mac lanes. Each lane gets one function or one small family, hands back when it lands
  or its time box ends, and the next target gets a fresh lane (shared brief:
  `build/class-work/LANE_BRIEF.md`, "Scope and budget").
- Stop a lane past about 150 output tokens per landed byte or after two zero-byte handbacks;
  record its best score and draft in its NOTES.
- Sweep promotion and near-miss hill-climbing are the Windows lead's (Codex) work.
- Opus for class lanes with recovered layouts; Sonnet for mechanical loops.
- The owner session restarts from this file when its context passes about 200K tokens.

Running Mac lanes (Opus): Score132 ScoreFontClass 0x667B60/0x667C70 and ScorePrintClass 0x6680F0; Base134
BaseClass 0x42BF70/0x42CA50/0x42C6A0; IPX135 IPXGlobalConnClass 0x524B50/0x524870. Landed this period: Map129,
Obj126, Para131, Iso128 (0x527A80), MSAnim133 (MSPrintAnim slot 4 0x5AEDA0). Register/scheduling-tie near
misses (see OPEN_MISSES.md) go to the Windows lead. Lanes use tools/original_target/lane_tools.py.
Windows lead backlog in landing: r17 and r19 landed (8f8247fe, 9d6af74f); next r20 (region-helpers-r53-r55,
drafts being copied from the Windows worktrees), then r22, r24, r27, r29, r32, r36 source rounds, then the
seed-tool patches r21-r40 and the bounds rounds (zero source credit). Packets copied to
build/class-work/lead/d/; plans point at C:/ paths, so missing drafts come from the mount
(/Volumes/mike-gaming/Users/Mike/.codex/worktrees/ra2-seed-lead/repo and /Volumes/mike-gaming/ra2/w/codexN). Closed 2026-10-28 (resume folders `build/class-work/<Lane>/`): Seed118 (callee-pops
`lea` rule; Speech_Load, Voc_Static_Load), Seed119 (Speech_Update), Coop120 (MessageListClass::Input), Cd121
(0x715230), Cd124 (0x715300), Coop122 (fill combo 0x5B70B0, fill list 0x5B71E0; 0x5B8490 open), Seed123 and
Seed125 (zero bytes; Tactical family parked; 0x6AAFD0 is a register-tie near miss for Windows). Their misses
are in OPEN_MISSES.md.
Next-lane candidates: Voc_Static_Save 0x714A90 74.12, Seed116's fresh.json (613 functions in 0x680000-0x770000; sweep work, so
Windows), the rest of OPEN_MISSES.md.

Windows: one Codex lead (LEAD.md in the coordination folder) staffing codex1 pathfinding
0x570000-0x58FFFF, codex2 BuildingClass, codex3 bound evidence; the lead owns seed tooling, sweeps
and, from 2026-10-28, near-miss hill-climbing (queue in messages/2026-10-28T2200Z-owner-to-lead.md).
BOARD.md is the lane authority. MPGameMode.cpp and MPCoop.cpp compile as one unit (population-2861),
so MPCooperative functions that call a base body need separate units.

## Integration loop

1. Take a delivery: frozen `d/rN/` folder with plans, drafts, header copies,
   base commit. Plans use forward-slash paths and LF endings.
2. `private/tools/land_round.sh DIR "message" PLAN...` merges DIR/shared against DIR/BASE (a header
   new at BASE that already landed is replaced only by a superset copy), reheads, accepts and lands;
   `private/tools/land_rename.sh SPEC "message"` applies a rename alone and lands. On a header
   conflict, resolve by hand and rerun with SKIP_HEADERS=1. Frozen whole-population plans carry context drafts from their base commit; when later landings
   rewrote those sources, `private/tools/rehead_plan.py PLAN` writes PLAN.head.json with unchanged
   context rows re-pointed at HEAD sources (drafts that rewrite a source are kept; missing population
   rows are added; Windows `C:/` prefixes are stripped). Accept the .head.json.
3. Merge header copies with `git merge-file src/shared/H BASE COPY` (BASE = the
   header at the worker's base commit). New headers are copied.
4. Accept each plan: `$RA2_PYTHON -B tools/original_target/accept_sources.py
   --config private/original-target.interactive.json --output
   private/original-target-20261020/accept-NAME PLAN` (accepted == candidates).
5. Land with `private/tools/land.sh "message"`: rehash, full build, commit only
   if `"whole_file_exact": true`, sync Windows, publish the GitHub snapshot,
   prune old build outputs.
6. Signature/name changes land alone through
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

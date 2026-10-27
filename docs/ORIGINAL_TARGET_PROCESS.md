# Original-binary-first process

Workflow and full-phase completion contract. [AGENTS.md](../AGENTS.md) holds the
fixed constraints; [STATUS.md](STATUS.md) the generated numbers; [HANDOFF.md](HANDOFF.md)
current work; [ORIGINAL_TARGET_BUILD.md](ORIGINAL_TARGET_BUILD.md) tools and commands.
Per-batch records up to A15 are in [history/](history/).

## Phases

1. **Reference foundation (done):** original-byte scaffolding, original data and
   PE metadata link and package to the exact supplied file. Zero source credit.
2. **Source recovery (active):** replace scaffolding with exact-matching C/C++.
3. **Native adaptation (later):** portable C++20/SDL on Apple Silicon from the
   recovered source. Not a gate on phase 2.

## The recovery loop

The unit of progress is matched body bytes. The loop is designed to be short:

```text
select ──> seed ──> diff/iterate ──> promote exact ──> build ──> commit
  ^                     │                                          │
  └──── best-score misses stay in the queue ◄──────────────────────┘
```

**Select.** Two ranked queues:

- `class_inventory.py` → `build/classes/classes.md`: vtables, their slot
  functions, vptr writers (constructor/destructor candidates), accepted vs
  remaining bytes, and the vtable sharing most slots (base/sibling hint).
- `sweep_seeds.py` → `build/sweep/queue.md`: every unrecovered contiguous
  function seeded from Ghidra, compiled and scored. Byte-exact rows promote
  directly; rows scoring ≥75 are quick iteration targets.

Prefer class work for the large connected hierarchies (recover the layout once,
then sweep members) and seed sweeps for bulk. Consult
`historical/native-reconstruction/` notes for names and field meanings, checking
that their addresses refer to this target.

**Seed and iterate.** `seed_candidate.py ENTRY` writes
`build/candidates/ENTRY/candidate.cpp`. `diff_candidate.py FILE --entry ENTRY
[--watch]` compiles under each recorded option set and prints:

- `score`: exact instruction agreement after alignment (100 = identical).
- `loose`: agreement ignoring absolute addresses and unresolved references.
- `shape`: agreement of the mnemonic sequence (structure, ignoring registers).

High shape with low score means control flow is right and register allocation
or scheduling differs. Change statement order, temporaries, types, signedness,
expression grouping, loop form, inlining or the option variant. Replace Ghidra
type names with shared types as the layout becomes clear. Time-box each function
(default ~30 minutes of attempts); record the best score in the handoff or queue
and move on. Misses are never closed permanently; anyone may resume one.

**Promote.** Build a candidate population (bounds from the frozen inventory,
padding from the gap inventory, references bound by name) and run
`compile_candidates.py`. Its strict audit is the acceptance test. Install exact
sources under a descriptive path in `src/recovered/` and add the regions to
`manifests/original_target.json`. No separate reviewer is required for
source, tool or build changes: the strict audit and the exact whole-file build
are the checks.

**Worker rules.** Workers iterate in private scratch folders and hand the owner
plans; the owner accepts, builds and commits.

- **Writes.** Write only under your own `build/class-work/<Worker>/` folder plus
  plan JSONs beside it. Never write `src/`, `manifests/`, `docs/`, `tools/` or
  the private configs, and never run `accept_sources.py` or `build.command`
  against the main tree.
- **Frozen inputs.** Once a plan is delivered, its drafts and header copies are
  frozen. A later round uses a new folder; never edit or rename a delivered draft
  in place, since acceptance reads it.
- **Plan shape.** A plan is one translation unit in address order. It takes a
  hand-written population whole unless it sets `allow_split`, which is only for
  separate-unit populations. Where the inventory bound is wrong, state
  `body_bytes` with evidence.
- **Shared headers.** Propose changes as header copies (`<Worker>/shared/`),
  based on the current `src/shared`; rebase after each commit.
- **Honest source.** Nothing added only to steer the inliner or register
  allocator: no empty or dead inline calls, `if (0)` code, `__forceinline`, or
  aliases declared only to force an out-of-line call. A natural Westwood shape
  (an inline helper that is a real operation, a macro, a local) is fine.
- **Kept elsewhere.** Bind a compiler-generated copy as kept elsewhere only to a
  real copy found at another address. Never bind a non-matching instance to its
  own address, and never treat output that the original has no copy of as dead:
  its absence means the source shape is wrong.
- **Check before delivery.** `tools/original_target/check_plans.sh NAME HEADER_DIR
  PLAN...` runs the real acceptance in a throwaway worktree (set `RA2_CONFIG` to
  your own compiler config). A plan is deliverable only when it accepts there
  with nothing missed. When a delivery changes a shared header, add `--build`
  (`check_plans.py --build ...`): the full build then runs in the same worktree
  and catches units outside the plans that the header change breaks.
- **Reports.** One consolidated report per round: plans with item counts and
  bytes, header changes, best-score misses, and decisions needed. Append notes
  to your folder's `NOTES` file so a successor can resume.
- **Shell.** On the owner's Mac `cp`, `mv` and `rm` are interactive aliases
  that hang background commands at a prompt; use `/bin/cp -f`, `/bin/mv -f`,
  `/bin/rm -f`. On Windows, `check_plans.py` needs `RA2_CHECK_ROOT` set to a
  short folder (paths stay under 260 characters).
- **Keep running.** Send round reports as messages and continue straight into
  the next round; a final hand-back ends the run. End it only when you are
  blocked on an owner decision with nothing else to do, or out of work.

**Build and commit.** Run `./build.command` once before committing accepted
source or build-logic changes; it must reproduce the complete packaged file.
Run `status.py --write` and `source_index.py`, update `HANDOFF.md` in a few
lines, commit.

## Accounting

The canonical manifest and git history are the record. `status.py` reports
regions, body bytes, frozen padding, remaining `.text` scaffold and matched
bytes per hour from the manifest's commit history. Keep these categories
separate in any claim:

- Recovered C/C++ body bytes (exact receipts in the manifest).
- Compiler padding/alignment: no source credit.
- Remaining original machine-code scaffold.
- Evidenced original handwritten assembly, with justification.
- Identified library components with provenance and license boundary; unclassified
  bytes are never silently excluded as library code.
- Original data, resources, zero tails, PE headers, file padding and overlay.
- Unresolved or conflicting ranges, boundaries, signatures and references.

Region counts are not verified function counts; no whole-game percentage beyond
the `.text` byte ratio.

## Full-phase completion criteria

The original-target decompilation is complete only when a final auditable record
demonstrates all of these:

1. **Complete justified coverage.** The whole supplied image is accounted for with
   defensible nonoverlapping ranges/categories and connections. No unexamined
   potential game code, unresolved game/library split or uncertain code/data area
   is omitted to manufacture completion; boundary, dispatch, signature and ABI
   issues affecting the claim are resolved.
2. **Game/program code recovered.** All game/program machine code builds from
   recovered readable C/C++, except evidenced original handwritten assembly and
   identified, reproducibly supplied or rebuilt library components. No hidden
   scaffold, instruction arrays, lifted runtime or opaque library bucket. The
   source is navigable: descriptive function/symbol names and filenames where
   operations are understood, meaningful parameter/local names, observed
   layouts/interfaces, purpose-based grouping and documented subsystem
   relationships, entry points, key data and interactions, with address mappings
   and explicit bounded uncertainties. Anonymous exact matches alone do not meet
   this. Unknown original developer/class names and perfect field knowledge are
   not gates; unresolved behavior, coverage, references or ABI cannot be excused
   as naming uncertainty.
3. **Reproducible complete exact build.** A fresh compile/assemble/link/package
   from documented source, legitimate frozen inputs and identified tools
   reproduces every supplied byte and the SHA256, without masks. Retained data/PE
   metadata and raw-linker differences are explicit. Matched padding is not
   source recovery; cached binaries do not replace a fresh build.
4. **Reviewed final accounting.** The final sources, build logic, range ledger,
   provenance, library/assembly exceptions and unresolved-work audit are reviewed,
   stating what was independently reviewed versus locally checked.

These complete base original-target decompilation, not native porting,
playability, YR recovery or distribution. Never mark unfinished work complete
because time, usage or a ready queue ran out.

## Canonical layout

Accepted source lives in tracked `src/recovered/` (descriptive purpose
directories, address suffixes); evidenced shared layouts in `src/shared/`, pinned
by the manifest. Fresh builds compile tracked sources grouped by recorded
population/options in source order. Scratch candidates, sweeps and Ghidra seeds
live under ignored `build/`. Private inputs are configured, pinned by hash, and
never executed as authored tooling.

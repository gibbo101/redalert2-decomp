# Exact-match recovery playbook

What this project learned about reproducing a compiled game from recovered
source, written for the next target: Yuri's Revenge, or a new game. It records
the process that worked, the measurements behind each rule, and the things that
were tried and did not pay. `AGENTS.md` remains the governing text for this
repository; this is the rationale and the order of operations.

Sources: this project's own history (`docs/history/`, the throughput and
treemap tools), the Fallout: New Vegas exact-match project that finished on
2026-11-02 (70,611 functions, 11.54 MB, MSVC 2008, about 23 days), and the
r/decomps discussion of token cost. Where a number below comes from FNV it says
so; everything else was measured here.

## 1. Fix the target and the scope before anything else

- One executable, one size, one hash. Hash before using any address. A later
  patch or a second game is a separate target with its own manifest.
- Decide what counts. The C runtime and compiler-generated code (about 2% of
  this target's `.text`) are never source credit; report the in-scope share as
  well as the raw `.text` share so progress is not understated.
- Clean the index early, not late. Inventory rows that are non-contiguous,
  unbounded or really tails, jump tables and padding sit outside every lane's
  pool. Here 484 rows (272 KB) reached the last third of the project unworked
  for that reason. FNV did the same cleanup as two late milestones. Do it in
  the first week: every remaining byte is either in a workable row or
  explicitly out of scope.
- Accept only exact. Masks, trimmed prefixes and candidate-derived bounds turn
  the acceptance test into an opinion. The whole-file rebuild is the only
  regression test the project has, and it only works if every region in it is
  exact.

## 2. Layouts first, then sweep

- Recover a class's layout once from its constructors and vptr stores, put it
  in a shared header, then sweep its slots and constructors against it. The
  executable's RTTI gives the class names and inheritance for free.
- FNV measured that about a third of all build failures were missing fields in
  shared class declarations, and that one layout fix unblocks many functions.
  Our half-done classes (Locomotion, Cell, Map, Tactical, Display, Techno,
  Building at 36-59%) are where the remaining bytes sit; finish their layouts
  as a deliberate pass before sending lanes at their slots.
- Keep type, ABI and class hypotheses explicit until a match evidences them.
  A wrong layout matches nothing and costs every lane that touches it.

## 3. Lane protocol

- A lane takes a unit (a source file or a class family sharing one layout),
  never a single function. Measured 2026-10-28/29: one-function lanes cost
  about three times the tokens per matched byte of unit lanes, because most
  spend is re-reading context.
- Fresh lane per unit, 1-3 KB deliveries, hand back at about 200 tool calls
  or 200K context. Edit in place rather than rewriting files. No tool building
  inside lanes; tool ideas go in the notes.
- Brief with the machine code, the classes used and a few proven matches of
  similar shape (FNV's brief). Adding nearest accepted examples by instruction
  pattern to the seed is a tool worth building for the next target.
- Time-box misses: about 30 minutes per KB of body, capped at four hours.
  Record the best score and move on. A miss is never closed; anyone may resume
  it when a new mechanism or ruling applies.

## 4. Near misses

- "Close is not nearly done." FNV had 741 functions one or two instructions
  off; a tool that permuted instructions fixed none of the 40 it tried. The
  last difference is almost always a misunderstanding, not an ordering. Our
  own hill-climbing rule was withdrawn for the same reason.
- Structured near-miss work does pay: recent passes here returned about 1.8 KB
  per lane run against 2.9 KB for fresh-unit runs. The rules that make it pay:
  highest recorded score first, one time-boxed attempt per function, a retry
  only when a new compiler mechanism or an owner ruling applies, and owner
  rulings resolved before assignment so nobody grinds around a pending header
  decision.
- Write every discovered compiler mechanism into `VC6_MATCHING_NOTES.md` the
  day it is found; each one closes other misses.

## 5. Models and effort

- Same byte check for every model, so a match from a cheap model is worth
  exactly as much as one from the most expensive. Tier by function size: FNV
  generated 22,000 boilerplate functions by script, sent sub-256-byte functions
  to a fine-tuned local model, medium ones to cheap models, and only 512 B and
  up to the top models. The tier only helps while a large small-function pool
  exists; here it was consumed early (953 remaining functions under 256 B hold
  60 KB, while 229 over 1 KB hold 507 KB).
- Thinking effort has a sweet spot. FNV: on 20 large functions Claude matched
  12 at the lightest setting and 17 at the heaviest, with less code per unit
  of effort, so they ran it in the middle. Measure this per target with the
  throughput tool before fixing a setting.
- Expect low per-try success. FNV measured 42 tries that do not build, 55 that
  build and differ, and 3 that match per hundred, on a better-behaved compiler
  than VC6. Count the same three outcomes here; the "does not build" share is
  the layout-gap signal.
- Never throttle to stretch a week. Efficiency changes that keep throughput
  are fine; model downgrades, lane cuts and pauses to make usage last are not.

## 6. Landing

- Land continuously, in bulk, with the strict audit and the exact whole-file
  build as the only reviewers. A separate human reviewer per function does not
  scale and adds nothing the audit does not check.
- Make the round cheap. Before 2026-10-31 a landing round took about 11.5
  minutes, dominated by the full rebuild; binding caches and a per-group object
  cache (`build/object-cache`) took it to about 1.8 minutes with the rebuild at
  48 seconds. Measure the round when the queue grows; the queue is a symptom.
- Keep landings small and frequent so that a failure stops one round, not a
  day; the status history then measures throughput per commit for free.

## 7. Measure what matters

- Bytes, not functions. FNV: functions came easily and flattered progress;
  the last third of the bytes sat in the largest functions. Our long tail
  behaves the same way.
- Per worker per day (`tools/original_target/throughput.py`). The Windows
  workers fell from 108 KB/day to 34 KB/day in two days when their fresh units
  ran out and they were handed leftovers; nobody noticed until the table
  existed.
- Where the remaining bytes are (`tools/original_target/treemap.py`): one box
  per function, grouped by class, done first. It shows which classes block a
  launch and where the unattributed tail is.
- Worker health, not just deliveries: status-file age, the prerequisites a
  worker names, time since its last landing. More than two hours without a
  landing means redirect. Paid worker time is spend, not free capacity.

## 8. Usage and accounts

- Measure burn with the fine-grained window (the five-hour card), not the
  weekly counter, and only over stretches when lanes were actually running.
  A rate read across downtime once suggested tripling the lane count.
- Needed rate = points to the stop divided by hours to the reset; lane count
  follows it with a dead band. End a week on the limit: nothing unspent
  survives the reset, and a lane cut at the limit keeps its scratch state.
- Two weekly accounts fit two continuous lanes almost exactly: about 92 hours
  on the first account and 72 on the second per week at this project's
  measured per-lane cost. Three lanes leave about two days a week with no
  owner.

## 9. Integration and the end state

- The per-function file layout is bookkeeping for the manifest, not a design.
  Consolidate into the original source units at the end, scripted, verified by
  the rebuild. FNV merged about 1,400 full-file reworks in two days to produce
  its released tree.
- Readability and exact match pull against each other: inline wrappers,
  statement order and materialised temporaries exist to make the compiler emit
  the original bytes. Rename and merge freely under the byte test; restructure
  only on the native fork, where behaviour becomes the test.
- A native port needs the executed set of functions, which the static call
  graph cannot give on a vtable-heavy codebase. Trace the original once to get
  it, and rank remaining work by whether a launch needs it.

## 10. Yuri's Revenge specifically

Measured against gamemd.exe 1.001 on 2026-10-31: about 44% of this project's
accepted bodies appear in YR identical apart from relocations (54% by a looser
whole-program mask), another 15-20% within small edits, and the rest changed
or new, concentrated in the INI readers, RulesClass and the new unit logic.
YR's `.text` is 7.7% larger. Plan: retarget the catalog and inventory as a
second target, transfer the identical bodies mechanically through the same
audit, re-derive the layouts that grew, then recover the remainder. YRpp and
Phobos document that exact binary and are a richer hypothesis source than RA2
ever had. Expect about a third of the RA2 effort.

User decisions, 2026-11-06. The YR matching decompilation gibbo101/ra2-decomp
(same VC6 SP3) now exists and runs the other way too:
1. Its source and the TibSun archive's may be adopted into `src/` as candidates,
   adapted to our shared headers, keeping their SPDX and copyright lines (and the
   EA line where present), with a THIRD_PARTY.md entry at the pinned commit and
   "from ra2-decomp <YR address>" / "from TibSun <file>" in the commit subject.
   Acceptance is unchanged: strict audit, exact whole-file build, no masks.
2. The 97 unaccepted RA2 functions with byte-identical matched YR twins
   (build/ra2decomp/twins-unaccepted.md) are adopted directly.
3. Tier 0: compile the TibSun archive unchanged with our compiler and options,
   search each emitted body in our .text with address-sized operands masked, and
   measure exact finds among unaccepted functions before accepting any (YR got
   1,321 functions / 173 KB that way).
The 171 functions we hold that YR lacks (build/ra2decomp/reciprocity.md) are
offered back by the user.

## 11. Host limits (added 2026-11-03)

- A 16 GiB host runs one full build at a time. Lanes and the landing runner
  take the same lock before any whole-file build; the lock carries the owner's
  pid so a reboot or a killed lane cannot leave it stale. Two concurrent builds
  (four Wine sessions each) exhausted memory and forced a reboot on 2026-11-03.
- Disk is a build input. Lane scratch, hill-climb output and fetched worker
  packets filled the main drive in hours and wedged Wine. Alert below 30 GiB
  free, start no lanes below 20 GiB, prune at every hand-back, move landed
  packets to cold storage, and keep Spotlight off the build and private trees.
- A wedged Wine (compiles idle, ps hanging) is checked in this order: disk,
  then memory, then the per-prefix wineserver. The project uses several Wine
  prefixes, so a reset must name each one.
- Paid workers never block. A worker whose unit is exhausted takes the next
  item from a standing fallback queue; if that is empty it polls every 15
  minutes and keeps its status file current. Questions go into status and
  never stop work. Only capacity errors need a human to resume a thread.

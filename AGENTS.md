# Red Alert 2 original-target decompilation

Reproduce the exact supplied base RA2 executable from recovered C/C++, replacing
original machine-code scaffolding function by function. Exact compiler output is
the acceptance test; everything else exists to raise matched bytes per hour.

Read `docs/HANDOFF.md` (current work), `docs/STATUS.md` (generated numbers) and
`docs/ORIGINAL_TARGET_PROCESS.md` (workflow and completion criteria). Use
`docs/ORIGINAL_TARGET_BUILD.md` for tools/commands, `docs/ARCHITECTURE.md` and
`docs/RECOVERY.md` for build layers and evidence reuse, `docs/VC6_MATCHING_NOTES.md`
for source-shape rules that reproduce VC6 output, `docs/REFERENCES.md` for
external material. `docs/history/` holds per-batch records: consult, don't reload.

## Fixed constraints

- **Target:** 4,485,392 bytes, SHA256
  `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`. Hash before
  using addresses. Base RA2 only; Yuri's Revenge is a later separate target.
- **Exact means exact:** a region is accepted only when the fresh VC6 object
  reproduces the complete independently bounded original body, references and
  frozen padding. No masks, prefix/tail trimming or candidate-derived bounds.
  Unknown extents, references or constants refuse acceptance.
- **No fake source:** no instruction arrays or original inline assembly in C
  candidates. Original-byte scaffolding, original data, identified library code
  and evidenced handwritten assembly are separate ledger categories.
- **Fidelity:** preserve widths, wrapping, signed division, FP stores, layouts and
  ordered reads/writes/calls. Type/ABI/class hypotheses stay explicit until evidenced.
- **Private material:** executables, assets, compiler/media, extracted data,
  dumps, disassembly, Ghidra exports, scaffolding, experiments and build outputs
  stay ignored under `private/` or `build/`; never stage them. Original
  installations and `outpost2-native` are read-only. Tracked: accepted source in
  `src/`, authored tools/tests, byte-free manifests, docs.
- **External references:** public/recomp/YRpp material supplies hypotheses only;
  verify on the exact target and check licenses (`THIRD_PARTY.md`). Do not adopt
  a lifted runtime or OpenRA gameplay.
- **Native phase is later:** no native/SDL/arm64/gameplay check per recovery
  batch. Preserve `historical/native-reconstruction/`. The shipped game will be
  native arm64 with no Wine/CrossOver, Rosetta, VM, emulation or original code.

## How to work

1. **Pick by class or family, not by single function.** `class_inventory.py`
   ranks vtables by remaining bytes; `sweep_seeds.py` ranks every unrecovered
   function by how close its Ghidra seed already compiles. Recover a class's
   layout once from its constructors/vptr stores, put it in `src/shared/`, then
   sweep its slots and constructors with those types.
2. **Seed, then iterate.** `seed_candidate.py` turns the Ghidra export into a
   compilable scratch candidate; `diff_candidate.py [--watch]` compiles it with
   the real compiler and shows an aligned, scored instruction diff. Iterating on
   near misses (statement order, temporaries, types, expression shape, inline
   splits, option variant) is the normal work, not a forbidden "steering". A
   miss is never "closed": record its best score and move on when the time box
   (about 30 minutes per KB of body, capped at four hours) runs out; anyone may resume it.
3. **Accept in bulk.** Promote exact candidates through `compile_candidates.py`
   (strict audit) into `src/recovered/` and the canonical manifest. No
   separate reviewer is required for source, tools or build changes; the
   strict audit and the exact whole-file build are the checks.
4. **Build periodically.** Run the full `./build.command` before each commit
   that changes accepted source or build logic, not for every candidate.
5. **Record briefly.** Commit accepted source with a short message. Regenerate
   numbers with `tools/original_target/status.py --write`; update `HANDOFF.md`
   with what is in flight and the next target. No per-batch cost receipts, hash
   tables or prose ledgers; the manifest and git history are the record.

## Readable source

The executable carries MSVC RTTI: original class names and inheritance for
every polymorphic class (`docs/CLASS_HIERARCHY.md`, `manifests/rtti_classes.json`).
Class-owned sources live in `src/recovered/classes/<Class>/`; use the original
class names for shared layouts and members.

Name understood operations, parameters and fields as you match them, with the
original address as a suffix; keep honest `unknown_0xNN` names for the rest.
Prefer real shared types over per-function owner classes and register-named
locals. Existing transliterated sources (`unsigned int ecx = ...`) may be
replaced whenever a class sweep touches them, provided the replacement still
matches exactly. Formatting and renaming earn no matched-byte credit but are
welcome. Canonical source in `src/recovered/` is authoritative. Accepted seed sources
carry a `seed-generated` marker line: `regenerate_seeds.py` may rewrite marked
files (the build proves they still match); delete the marker when editing a
file by hand and it is never regenerated. Ghidra type names come from
`src/shared/ghidra_types.hpp` until real types replace them.

## Ownership and workers

One owner session integrates: canonical manifest, shared headers, build logic,
`STATUS.md`/`HANDOFF.md`, commits. Workers (up to six, raised from two by the user on 2026-10-21; when the user starts the
recovery goal) take a class or sweep slice, iterate in private scratch
directories and hand back exact candidates plus best-score misses. Serialize
only the compiler/linker bottle (`shared/compiler.lock`, handled by the tools);
analysis and seeding run concurrently. Before shared writes check HEAD/status
and preserve unexpected changes rather than overwriting them.

## Controls

The prepared goal text lives in `docs/ORIGINAL_TARGET_GOAL.md`; do not create,
start, resume or change a goal or automation unless the user asks. Honor
pauses. Routine continuation does not authorize downloads, publication,
messages, system/Xcode/DRM changes, license acceptance or global tool changes.
Honor `DEVELOPER_DIR`; use the existing local toolchain and Wine host (see the build doc).

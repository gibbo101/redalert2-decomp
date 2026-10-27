# Goal reference and optional condition

Read-only review on 2026-10-20 confirmed that the existing goal is **paused**.
It explicitly says "following AGENTS.md and docs/ORIGINAL_TARGET_PROCESS.md" and
requires "all full-phase completion criteria in docs/ORIGINAL_TARGET_PROCESS.md".
Those authoritative files now capture the agreed semantic, naming, navigation and
subsystem-delivery requirements. **A goal replacement is not technically required**;
the existing condition already incorporates them by reference.

The optional condition below makes the maintainable-source endpoint explicit when
read on its own and leaves ongoing procedures in repository files. It contains no
one-time migration/first-family obligations. Migration and the first readability
application were completed in `d190902d` and `d7358c51`; neither is a repeating gate.

Preparation only: this file does not create, replace, resume or otherwise change
the goal. The user controls any goal edit or activation/resumption. The currently
installed condition was not changed by this documentation update. Current recovery
accounting and incomplete-phase limits remain in [STATUS.md](STATUS.md).

## Optional replacement condition

Exact character count: **2081**, counting the text inside the fence,
including paragraph-separating newlines, excluding the fence and final newline.

```text
Complete the exact supplied base RA2 original-target decompilation as a maintainable source delivery, following AGENTS.md and all full-phase completion criteria in docs/ORIGINAL_TARGET_PROCESS.md. Keep accepted state in docs/STATUS.md and docs/HANDOFF.md and reproduction guidance in docs/ORIGINAL_TARGET_BUILD.md.

Finish only with reviewed, justified accounting for the complete supplied image and its connections; all required game/program code recovered as readable C/C++ except evidenced original handwritten assembly and identified reproducible libraries; no unrecovered game-code scaffold, hidden exclusions or unresolved behavior/coverage/ABI/reference issues; and a fresh complete compile/assemble/link/package build matching every supplied byte and SHA256, with retained data/PE metadata and raw-linker differences explicit.

Deliver navigable source with descriptive function/symbol names wherever operations are understood, meaningful parameter/local names, observed layouts/interfaces, stable address provenance, purpose-based grouping and concise documented subsystem relationships, entry points, key data and interactions. Capture this understanding during recovery. Keep bounded uncertainties explicit: original developer/class names and perfect knowledge of every field are not required, but unresolved behavior or coverage cannot be dismissed as naming uncertainty. Formatting alone or anonymous exact matches alone do not satisfy the maintainable-source endpoint.

Preserve authoritative tracked source, tools, manifests and regression checks; generation must not overwrite manual semantic improvements. Keep bulk recovery dominant under the repository procedures, record exact matching coverage separately from semantic/source-organization progress, and preserve existing native work and private-input boundaries. One exact batch, byte reassembly or empty queue is not completion. Native portability adaptation, enhancements, playability, Yuri's Revenge and publication remain outside this phase. Honor user pauses/cancellations and change no other chat's goal.
```

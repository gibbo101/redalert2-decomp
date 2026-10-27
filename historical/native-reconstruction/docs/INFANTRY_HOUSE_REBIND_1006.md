# Rebind recruited GIs to the current House

The first Day1 Team's Script20/13 must hand four existing GIs to the player.
The discarded actual-owner transfer now passes owner1B4, new threat and House
registration, reads actual radio slot0 and reaches the guarded Infantry+414
child. No partly completed clone is adopted, and live Team/Script20/arrival/SDL
objective scheduling remains off. This supersedes the pre-owner refusal in
[CELL_THREAT_CHANGE_1006.md](CELL_THREAT_CHANGE_1006.md).

## Native ownership repair

`InfantryWalkBinding` now holds rebindable borrowed references for House index,
country speed and134/135 control bytes. `InfantryMembershipActor` similarly lends
its House index through a reference wrapper. Their existing constructor callers
retain the same owners and behavior. `PreparedInfantryWalk::rebindHouse` validates
the destination House/index identity and actual membership Owner field before
changing any binding. It then retargets those references and stores the single
actual mission Owner. It allocates no new actor, map, membership, callbacks or
simulation state and does not reconstruct `bindWorld` or eagerly rewrite Cell
occupation. Later command/head/Process/occupation calls read the new references;
admission and Mark already borrowed that same live logical Owner.

The enclosing private transfer callback passes actual mission House fields and
its existing House speed input. `player()` now compares the actual Owner with
the current player House. Walking-preview picking uses that method, and palette
lookup selects the current Owner's cached House palette each draw. Static preview
retains its existing behavior. Palettes still use supplied map Color associations
and the existing temporary unlit blending; these changes do not recover original
sprite palette selection, lighting, animation or automatic deselection effects.
No transferred actor is inserted into ordinary SDL through this checkpoint.

## Continued original transfer order

The same actual GI now stores owner1B4/372, obtains threat through the existing
complete6D3E50 kernel and adds it through complete476B20 on the same saved Cell.
Stock E1 kind15 never reads Building field564/rulesBE8; its threat598 startup
association remains supplied. Actual new-House registered5480 increments through
complete4ED610 with the existing Type/accounting fields.636E10 reads actual
radioLinksCC[0] independently of radioCountD0. Its16-byte original span was
fingerprinted/reinspected, and the native helper now supplies the existing616-
sequence transfer fixture too. Null slot0 is original-compared; nonnull lookup
and bounds refusals also have native checks. The linked-radio parent continuation
still refuses. This does not prove general radio behavior or heap construction.

The next explicit guard is named `sight414` in the old transfer service API.
Exact-base Infantry vtable inspection identifies **503C00**, which first calls
4C6F10 and then virtual438. Do not substitute arrival's sight418/41C children.
The subsequent slots424/420 are6D7500/6D74D0 radar removal/registration, already
recovered in [RADAR_ACTOR_MARKERS_1006.md](RADAR_ACTOR_MARKERS_1006.md).
Their transfer binding remains unjoined. Later wrapper54 is a4CCE70 jump thunk
to5D5410, and wrapper1A0 is41B320; inspection windows are private. A window that
ends at an early RET or contains only a prefix is inspection, not complete-path
recovery. Recover the complete entered503C00/4C6F10 path and actual children
before enabling this transfer; reuse existing radar owners instead of inventing
new sight services or marker mirrors.

## Verification and limits

No new original expectations were generated for these native binding changes.
The exact supplied executable remains4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
authenticity remain separate. Original answers/receipts stay immutable; current
native runners always execute with current source identities recorded separately.
No worker, Windows action/transfer, new runtime executable read, downloaded code,
new dependency, system/Xcode/DRM change or tracked proprietary material was added.

The low-level owner check verifies foreign/copied index and unknown-House refusal,
no rebind query or route/timer/list mutation, independent actor ownership, actual
occupation using a changed new-House index and live control135 command bypass.
Actual Boot Camp checks run before recruitment and after the real sixth Team
tick. They verify old/new grid effects, new Owner/372, registration, unchanged
Tag identity/count and unfired event7, all four Walk references plus membership
index aliasing, current-player association and original same-House no-op.
Warm clones survive source destruction. Explicit committed-head Process calls
on independent clones move the same transferred GI faster with new-House speed1
than.5 while poisoning old-House speed3; the source/other actor stays unchanged.
Explicit occupation consumes the new House index. These are native owner tests,
not new original-composed transfer or original speed/command traces.

The Process diagnostic supplies a committed head so it enters no route or Team
permission child. Actual new routing for recruited members can enter the still
unbound Foot permission Team6BA990 service. Do not clear the real Team to make
orders pass or infer general transferred-GI movement from the bounded diagnostic.
The full transfer and first tutorial transition remain incomplete. Ordinary SDL
checks retain startup-player walking/pause/Stop/repeated orders/drawing; they do
not verify live recruitment/ownership transfer or objective success. Only Apple
Silicon macOS is tested; sanitizer SDL app is not built. Local checks are not
independent acceptance or whole-frame fidelity.

## Commands

```sh
./build.command
./run.command --boot-camp-walk
./test.command
build/native/prepared-infantry-walk-check
build/native/boot-camp-walk-check private/official-1006-probe
```

Current normal/sanitizer comparisons explicitly replay21,013 original sequences:
1,204 Cell threat,616 transfer,1,136 House accounting,398 tagged discovery,
92 Walk world,10 E1 Walk inputs,285 Infantry membership and17,272 Mark redraw.
Exact commands/origin paths are retained in
`private/house-rebind-20261020/validate.py` and each validation cost/audit report.
For example, use a new private audit/report name for this supported replay:

```sh
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/transfer-rebind-next.audit.json \
  tests/compare_techno_house_transfer.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/techno-house-transfer-vectors \
  --expectations private/techno-transfer-20261019/fresh-a1/expected.json \
  --report private/transfer-rebind-next.json
```

Select `build/sanitize/techno-house-transfer-vectors` and fresh output names for
the sanitizer build. The earlier616 original transfer answers retain supplied
map/threat/draw/effect children; their replay is regression evidence, not a new
complete original transfer proof. Final checks, costs, failed build attempts and
next work are recorded in opening HANDOFF and the ignored receipt/validation lane.

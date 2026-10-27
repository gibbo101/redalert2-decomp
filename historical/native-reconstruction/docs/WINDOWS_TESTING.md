# Original-game research on mike-gaming

October 14, 2026. User reports Codex installed on **mike-gaming**, original RA2
installed at **`D:\Games\RA2`**, and a launch compatibility failure. The user
believes official and no-CD patches have been applied. Both base and YR research
startup now work in separate copies. The base engine was transferred with explicit
approval and exactly matches the supplied 1.006 patch output;
[BASELINE_1006.md](BASELINE_1006.md) records that identity and scoped verification.
YR and the entire installation are not certified pristine.

The user's **Red Alert 2 Windows** task is now visible at `D:\Games\RA2`, thread
`01a13a90-a4fa-7fb3-92b8-cbcedc276dbb`, remote host
`remote-control:env_e_6acf7d2c9818832583c3e661f3c977a3`. Its first completed turn
collected 13 executable hashes and wrote `executable-hashes-sha256.csv` in the
installation before our read-only follow-up. Preserve that existing report.
We read its results and, after explicit human authorization, sent scoped diagnostics/
isolated-copy instructions and the latest modification-provenance correction.
No direct Windows shell from this Mac was used. Further output belongs outside
the source installation; results will be retrieved with read_thread.

| Installed file | Bytes | Reported SHA-256 |
| --- | ---: | --- |
| `game.exe` | 4,485,392 | `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f` |
| `gamemd.exe` | 4,813,072 | `7b8a068535d6af06845edf95ae829b113d00c02909330e16f197426cd7db94b6` |
| `gamemd.bak.exe` | 4,813,072 | `b29c47a94d6d414fad3b53ab0f9ebcd0ce22f0a98ca2be6f0c6920c4dd7e2fe2` |

Base `game.exe` is now locally inspected and byte-compared with supplied patch
output. YR entries remain Windows-task-reported, not locally inspected files.
YR's active/backup contents differ despite equal sizes; neither is certified
pristine. The Windows patch-package hashes match both Mac supplied packages.
`ra2.exe` was absent from that executable listing. Clean baseline and compatibility
cause remain pending. The installed base `game.exe` reports FileVersion/ProductVersion
`1.08`, with PE timestamp 2001-06-06 23:25:33 UTC. The disc build reports the same
embedded version with a different date/hash; version strings do not establish
binary equivalence. Windows `Ra2.bak.exe` hashes to
`9525f221e8750616d2623a56b3f5835f86259e205ab57ba61944a6d6e96ca39c`, matching
our locally hash-checked untouched Allied-disc `ra2.exe`. That establishes backup
launcher identity only, not the stock identity of either game engine executable.

Official [OpenAI remote guidance](https://developers.openai.com/blog/mastering-codex-remote-for-engineering)
describes selecting a connected host and workspace for a task. That feature's
availability does not establish that mike-gaming is connected to this session.
The user started the Windows task and approved directing it for diagnostics and
isolated-copy experiments. The reusable prompt below applies to future research
tasks; no additional task needs to be created for the current investigation.

## Completed startup observation

The Windows task inventoried 167 top-level files, copied **354 files** into
`D:\RA2Research\private\investigation-20261014-082701\ra2-copy`, and verified
each copied file against the source manifest. The user clarified their usual
launch is `RA2MD.exe`, producing a black screen followed by a crash. That launcher
selects **Yuri's Revenge**, rather than base RA2.

Launching the copied `RA2MD.exe` with the copy as its working directory created
the copied `gamemd.exe`; it remained responsive during the observation period
with no matching Application crash event. The user then confirmed **"That worked"**
in the Windows task. This is user-observed successful startup; no gameplay,
rendering, timing or native-port parity measurement was made. No renderer wrapper,
official patch, no-CD patch or system change was applied during the experiment.
The earlier direct copied `game.exe` probe exited with code 0 within 15 seconds
and no matching crash event; base RA2 startup remains unresolved.

The final Windows check reported **zero changed source hashes and zero new source
files** against its pre-investigation manifest. Its report is
`D:\RA2Research\private\investigation-20261014-082701\findings.txt`, reported
SHA-256 `9cbf006c178bd0335573f03d55cadcc2363211bbbdf36ae012cdb38a3bebb1e`.
Registry InstallPath values point to a different, existing Origin Games installation;
this discrepancy and the missing base launcher are findings, not a proven cause
of the user's earlier Yuri failure. Do not claim a compatibility fix from the
successful copied launch alone. Leave the working research copy available.

To reproduce the successful launch in PowerShell on mike-gaming:

```powershell
Set-Location 'D:\RA2Research\private\investigation-20261014-082701\ra2-copy'
.\RA2MD.exe
```

The diagnostic collector's separate Windows validation completed successfully,
as recorded below.

## Allied media and stock base-launcher observation

The user authorized backup executables and confirmed the Allied disc is mounted
at **F:**. The Windows task independently recorded volume **RA1**, serial
`DA9A981C`, `Ra1.dsk` and an autorun reference to `ALLIED.ICO`. These identify the
observed mounted media; no whole-disc hash is claimed. Read-only hashes of
`F:\INSTALL\game.exe`, `Ra2.exe` and `Game1.CAB` match the Mac's existing Allied
imports. No image was mounted by this Mac task.

A fresh 354-file copy at
`D:\RA2Research\private\base-ra2-20261014-084353\ra2-copy` passed its copy
manifest check. Only there, the verified `Ra2.bak.exe` was copied as `ra2.exe`.
The original launcher (`9525f221...`, full hash above) was tested against copied
installed engine `e6418111...`, whose pristine provenance remains unresolved.
No patch or configuration change was applied; the working YR copy was preserved.

The launch at **2026-10-14 13:44:38 UTC**, with no arguments and the copy as its
working directory, remained at a responsive **"Access Denied"** window after
15 seconds. The recorded process snapshot contained only that launcher, with no
`game.exe`, and no matching Application crash event. The dialog's exact body text
was supplied by the user: **"Please login with admin privileges and try again."**
The user then explicitly authorized an admin launch in the Windows task.

The `RunAs` retry at **2026-10-14 13:54:33 UTC** exited with code **1** within
15 seconds. No game engine remained running. Two matching Service Control Manager
event-7000 entries report **"The Secdrv service failed to start ... This driver
has been blocked from loading."** This establishes a legacy-driver startup blocker
on the actual Windows 11 research host; it does not establish a renderer failure.
The task reported no manual driver/security changes. Protected-launcher tests are
now superseded by the user's direction to use the existing no-CD versions.

Private admin-launch report:
`D:\RA2Research\private\base-ra2-20261014-084353\launch-admin-20261014-085434.json`,
reported SHA-256 `b9b96f3e4f8bbea792ed69f9aebfaa88280aba0f5901a46da2340fd87fc56cb4`.
Local follow-up summary: `private/patch-inspection/windows-secdrv.json`; the earlier
`windows-base-ra2.json` retains its initial, pre-retry observation.

Private media report:
`D:\RA2Research\private\base-ra2-media-20261014-084223.json`, SHA-256
`0d090ebbdbe436923b5bf946ff7a5f7ee641b4170e382461af2cf71a3d01bac0`.
The base-copy setup/launch outputs are in the Windows task. Its final comparison
reported **zero changed hashes and zero new files** across all 354 source files;
the working YR copy remained present. The selected InstallPath values stayed the
same. Private findings:
`D:\RA2Research\private\base-ra2-20261014-084353\findings-base.txt`, reported
SHA-256 `891d44dc534f118ec2107ebc96119915a3394f200d3f3596b840934ac6ec8200`.

The Windows task also prepared clean inputs directly from legitimate mounted
media in `D:\RA2Research\private\clean-allied-inputs-20261014-084544\ra2-clean`,
extracting only into fresh research storage. Its engine matches our retained
`135a57a0...` oracle. The 158,758,291-byte cabinet hashes to
`74f714560536804ad184b326fafa8134c38de7617bef9ab89b86c59899a29a62`.
The two expanded archives independently match the Mac's prepared copies:

| Clean archive | Bytes | SHA-256 |
| --- | ---: | --- |
| `ra2.mix` | 281,074,192 | `adea10f3125700257362bc73a3ac73647036335a0a705632a29330a390f20f43` |
| `language.mix` | 53,105,368 | `1e5687827f2ef7e94e0a08d5f69dd951ef4cfbda0a8b6202a34dbaa3fb76b46d` |

Clean-input provenance report:
`D:\RA2Research\private\clean-allied-inputs-20261014-084544\provenance.json`,
reported SHA-256 `f292d54ced0ac63153d27962f2a3daa58ce7fd3074136e95152623fe80cee65c`.
These inputs enable safe patch preparation without a runnable original game UI;
the preferred pristine patched output remains pending. Static analysis and isolated routine tests
need no mounted disc. Local evidence summary: `private/patch-inspection/windows-base-ra2.json`.

## Verified base startup and private transfer

Working base copy:
`D:\RA2Research\private\base-renderer-20261014-092256\ra2-copy`.
The source lacked base `Ra2.exe`; the task copied the supplied generic `RA2MD.exe`
byte-for-byte to that name only in private storage. Launcher SHA-256
`4c5678a72d28a857e20386e75cc2839469ccaaaa82d4ce7180bb07ada07f1352`, 94,208 bytes;
supplied `Ra2.lcf` selects `game.exe`. `Ra2.exe -SPEEDCONTROL` started the copied
base engine. No launcher instructions changed. Direct-engine exit-0 observations
and embedded handshake strings support a launcher requirement; no exact branch
has been recovered.

Native fullscreen played the intro, then the user reported black output after
minimization. `-WIN` displayed **"This product requires a 16bit pixel depth!"**;
the desktop was not changed. The selected **cnc-ddraw v7.1.0.0** route uses global
`windowed=true`, `fullscreen=false`, `renderer=gdi`, 800×600, border enabled, empty
shader and preserved game presets. Game-internal fullscreen remains enabled;
`-WIN` is omitted. Loaded-module evidence confirms this private wrapper.
The user observed the intro and answered **"Yes"** to menu and minimize/restore
success. This establishes base startup/presentation, not gameplay, timing,
original pixels or a native Windows build. UI automation stopped on user Escape.

The preserved shortcut is
`D:\RA2Research\private\base-renderer-20261014-092256\Launch base RA2.lnk`.
Its `findings.txt` SHA-256 is
`6771ca068b285a58b1b3646208979494a4122e365f01813830fef9d6ffd33be3`.
Final checks reported 354 source files, zero hash changes/new files, unchanged
source registry/backups and preserved YR copy. No Origin files are used in this
route. No new bypass or security/driver change was made.

cnc-ddraw is MIT research-host compatibility tooling, not a native dependency or
pixel oracle. [Release v7.1.0.0](https://github.com/FunkyFr3sh/cnc-ddraw/releases/tag/v7.1.0.0):
archive 2,688,079 bytes, locally computed SHA-256
`0b13ab89a64c9918189b1dadd449ef6ed3cb3b7b19cabd96d8adbd95505bb908`;
release API had no supplied asset digest. DLL 411,648 bytes, SHA-256
`85e0f7d530dfda134793a57cb3e76b0287dcc96892ee57162dd68f47283b03a9`.
License/download record:
`D:\RA2Research\private\cnc-ddraw-7.1-20261014-092132`.
Runtime/config hashes are in `research-runtime-final.csv` beside the working copy.

`D:\RA2Research\private\baseline-20261014-094604` records 18 stable base asset/
config candidates. `base-assets.csv` SHA-256:
`86ce84ecd957f53ff8633f17730eb8bc48dc6f7bd98230a7ae1c04efddafa6dd`;
findings SHA-256:
`902fefccb36979da40846e082da2624250fc99cb1c5e520e57d00293016cb38b`.
Windows inspected the official DLL statically; it did not execute the patch.
Effective archive/loose-member precedence remains unverified.

The user confirmed Z: maps to Ivalice `/Volumes/Lesalia`. After a fresh shared
identity-marker check, explicit user approval authorized copying only base engine
to `Z:\Code\redalert2-native\private\windows-baseline-20261014\game.exe`.
Reparse/overwrite/hash/stability checks passed. Receipt
`D:\RA2Research\private\game-exe-transfer-20261014-100539.json`, SHA-256
`3064bf7a378819874ef1fdad2a82118a14b894d4d8588e9d4bd6bb06fc0e9242`,
reports stable source metadata and matching destination. No additional proprietary
payload was transferred; Mac metadata was distilled from the task's report.

The supplied Mac patch output is byte-identical to the copied engine. Eleven
output archive/map hashes/sizes match Windows metadata. This corrects an assumption
that the base engine itself must contain no-CD edits; launcher/wrapper/entire-install
provenance remains separate. BASELINE_1006.md records isolated patched Facing
verification and remaining migration; startup success is not that oracle evidence.

## Current no-CD research policy

The user explicitly directs **existing supplied no-CD versions** for Windows
testing. Use fresh isolated copies, preserve all installations/backups and the
working YR copy, and pin launcher/engine/asset/configuration hashes. Base RA2 is
first; the earlier direct exit-0 limitation is superseded by the supplied-launcher
working route above.
An existing legitimate alternative installation may be inventoried read-only for
its launcher/engine provenance. No new bypass or replacement game download is
needed or authorized by this policy, and no driver/security changes are needed.

The native app already reads supplied local data without CD checks or original
code execution. SafeDisc/launcher reconstruction is outside its scope. A no-CD
Windows build is a practical observation target, not automatically a pristine
oracle: identify changed routines and distinguish their observed behavior from
unchanged isolated-original tests. Keep clean media inputs for independent official
patch materialization. The native data/profile gates still select the retained
disc hash until patched mappings are verified; no-CD selection for research does
not disable them. Ordinary no-CD launch tests need no mounted-media gate.

## Reusable initial diagnostic prompt

Paste this in Codex **on mike-gaming**, in a separate research workspace:

```text
Inspect my legitimate Red Alert 2 installation at D:\Games\RA2 to diagnose why
it will not launch. This supports the native redalert2-native reconstruction.
Start read-only: do not launch the game, apply patches, download files, edit the
installation, change registry entries, install drivers or modify system security.
Keep reports under D:\RA2Research\private\windows, outside the installation.

Record Windows build, CPU architecture, desktop/RDP context, GPU/driver, SHA-256
and PE/version metadata for game.exe, ra2.exe and any gamemd.exe/ra2md.exe, and
hashes for top-level MIX archives and renderer DLLs. Inspect only relevant video
settings, installation-path registry values and recent game crash/hang events;
never print CD keys. If tools/windows_diagnostics.ps1 is available, run it with
-Install D:\Games\RA2 -OutputFile D:\RA2Research\private\windows\inventory.json.
Do not assume an official patch is installed from the folder name/version alone.

Report the evidence and the smallest next diagnostic step. Separate failure to
start from black-screen/audio-only/rendering failure. Do not change anything yet.
```

This initial prompt intentionally collects evidence. Follow-up original launches,
compatibility experiments and official patch application belong in an isolated
copy, with the exact action and destination established. No automatic cross-task
messages should be sent without direct human authorization. The current task
has that authorization; startup investigation and collector validation completed.

## Read-only collector

Copy our own `tools/windows_diagnostics.ps1` source to the research workspace, or
make the repository available there without copying private game material into Git.
Run in PowerShell:

```powershell
& .\tools\windows_diagnostics.ps1 -Install 'D:\Games\RA2' `
  -OutputFile 'D:\RA2Research\private\windows\inventory.json'
```

The collector hashes all top-level files, records PE machine/timestamp and file
version metadata for EXE/DLL files, reads selected video/speed settings, Westwood
InstallPath values, recent relevant Application crash/hang events, OS/GPU context
and secdrv service presence. It never launches original code or changes the
installation, registry or services. It refuses reparse-point ancestors/source files,
source-tree output, non-private/non-build output and overwrites. Serial/CD keys
are excluded. Reports remain private; Application events can contain local paths.

Close any game processes before accepting an inventory as a stable baseline.
Check `changed_during_read`, `active_game_processes` and `event_query_error`;
missing events or a missing service are not a diagnosis. Top-level scope excludes
nested content. The script uses PowerShell 5.1+ syntax; **PowerShell 7.6.5 on
mike-gaming** is its tested runtime. PowerShell 5.1 remains untested. No Windows
build/test support is claimed for the native game.

Windows validation used the canonical script with SHA-256
`d5acce7d35187a4ad86e1a513eb9e3f04b68386f9d91eb48c42f3416fc18cbeb`, matching
the Mac source exactly. A first transcription missed one regex escape; the agent
preserved that artifact and reconstructed the canonical hash before execution.
No source fix was needed. Syntax parsing passed, and all three requested output
guards rejected source-tree/non-private/existing-report paths without writes or
changing the existing report. Six independently computed executable/package hashes
matched the report. All 167 top-level files were stable; the collector launched
no game and applied no patches.

Private Windows evidence:

- `D:\RA2Research\private\scripts\windows_diagnostics-canonical.ps1` — exact source.
- `D:\RA2Research\private\windows\baseline-20261014-083649.json` — report SHA-256
  `36ad81ccdf1e93456e7edd0435c9ccea0a4db274ef9bd0b2c6995a0d57752221`.
- `D:\RA2Research\private\windows\validation-20261014-083649.json` — validation SHA-256
  `b7f285203ae7a90a83abf8179b675fbf5076294e5e6fa2886f3e96564cf50108`.

The Mac read these results from the Windows task; it did not execute a Windows
shell directly. Local summary: `private/patch-inspection/windows-validation.json`.

## Compatibility diagnosis after inventory

Record the user's exact launch command, error text, desktop versus RDP context,
whether a process survives, audio output, window behavior and matching event time.
Then use a fresh research copy for one change at a time, keeping source hashes intact.

| Evidence | Next bounded question |
| --- | --- |
| No window/process, launcher error, no game crash | Does the launcher reach game.exe? Does the legitimate distribution require unavailable legacy copy-protection or platform components? Inspect imports/logs; version/hash/provenance decide the branch. |
| Explicit DLL/dependency error | Identify the missing module and architecture from the actual message. Record existing local DLL hashes before any experiment. |
| Game process survives, audio works, black/partial screen | Test original DirectDraw initialization/presentation under the local desktop, then a separately identified renderer wrapper in the copy. Record wrapper configuration/version/hash. |
| Access violation or hang | Retain the faulting module, code/offset, exact executable hash and reproduction before selecting a fix. |
| Failure only over RDP | Compare with a local interactive desktop at identical resolution/settings; RDP success/failure is a distinct observation. |

[cnc-ddraw](https://github.com/FunkyFr3sh/cnc-ddraw) is a potential **research-host
presentation compatibility tool**, not our native renderer or an original pixel
oracle. Its upstream README lists RA2 and describes black-screen/display fixes;
its [LICENSE](https://github.com/FunkyFr3sh/cnc-ddraw/blob/master/LICENSE) was inspected
as MIT on October 14. It was initially a static lead; the later Windows research
copy pins and tests v7.1.0.0 above. Nothing is installed in the native app/source game.
If selected after diagnosis, pin the actual release/hash and configuration, preserve
its license, and disclose altered presentation/input/timing in observations.
It does not establish a remedy for an unidentified launch failure. Avoid gameplay
mods for a stock behavior baseline. The current policy above authorizes using
existing supplied no-CD builds; creating/downloading a new bypass or changing
drivers/security is outside this procedure.

## Useful observations once runnable

First pin patched game executable and effective asset/rules hashes, launcher,
renderer, wrapper settings, map, house color, game speed, detail, resolution and
capture cadence. A video without this context cannot identify a numeric baseline.

- Loading/lifecycle: record the selected map's initial visible scenery, their
  coordinates/elevation and ordering at fixed camera positions; compare candidate
  redraw/eligibility boundaries from [LIFECYCLE.md](LIFECYCLE.md).
- Movement: an undamaged unpromoted Rhino on flat road/grass; repeat ten-cell
  cardinal/diagonal routes and changed orders mid-turn five times. Record command,
  heading, first translation and arrival frames. Distinguish simulation timing
  from display capture timing.
- Presentation: same map/light/color at eight body headings, aligned/offset turret,
  flat grass and cliff-edge occlusion. Wrapper output remains observed host output;
  exact isolated original buffers remain the arithmetic/pixel-kernel evidence.

Full-game integration observations supplement [PATCH_BASELINE.md](PATCH_BASELINE.md)
and the subsystem differential harnesses. They do not replace them or complete
the reconstruction.

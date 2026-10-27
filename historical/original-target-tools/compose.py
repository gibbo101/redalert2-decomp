#!/usr/bin/env python3
"""Audit frozen compiler outputs, compose nonoverlapping intervals, link and check.
Uses existing private build scaffold; never recompiles unchanged candidate matrices.
"""
import argparse
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import sys
import time

from verify_manifest import Audit, require


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--research-root', type=Path, required=True)
    parser.add_argument('--manifest', type=Path, action='append', required=True,
                        help='Priority order: an earlier exact interval wins overlaps')
    parser.add_argument('--tag', default=None)
    args = parser.parse_args()
    root = args.research_root.resolve()
    repository = root.parents[1]
    tag = args.tag or 'composed-' + str(time.time_ns())
    require(tag and Path(tag).name == tag and tag not in ('.', '..'), 'Invalid build tag')
    destination = root / 'build' / tag
    destination.mkdir(exist_ok=False)
    started = time.monotonic()
    audit = Audit(repository, root / 'inputs/game.exe')
    chosen = []
    rejected = []
    inputs = []
    for path in args.manifest:
        path = path.resolve()
        checked = audit.audit(path)
        manifest = audit.document(path)
        (destination / ('input-' + str(len(inputs)) + '-audit.json')).write_text(json.dumps(checked, indent=2))
        inputs.append(dict(path=str(path), sha256=checked['manifest_sha256'],
                           regions=checked['matched_source_regions'], body_bytes=checked['body_bytes']))
        for row in sorted(manifest['accepted'], key=lambda r: r['entry']):
            first = row['entry']
            last = first + row['full_extent_bytes']
            overlap = [r for r in chosen if r['entry'] < last and first < r['entry'] + r['full_extent_bytes']]
            if overlap:
                rejected.append(dict(entry=first, source=str(path), existing_entries=[r['entry'] for r in overlap],
                                     reason='Earlier frozen exact interval retained; no boundary merging'))
                continue
            row = dict(row)
            row.setdefault('accepted_batch_manifest', str(path))
            chosen.append(row)
    validation_seconds = time.monotonic() - started
    manifest = dict(executable_sha256=checked['executable_sha256'], accepted=sorted(chosen, key=lambda r: r['entry']),
                    matched_source_regions=len(chosen), unique_functions=len(chosen),
                    body_bytes=sum(r['body_bytes'] for r in chosen),
                    frozen_padding_bytes=sum(r['padding_bytes'] for r in chosen),
                    full_extent_bytes=sum(r['full_extent_bytes'] for r in chosen),
                    inputs=inputs, overlap_refusals=rejected,
                    source_function_boundaries_certified=False,
                    policy='Verified compiler-output intervals with frozen independent bound provenance; retained earlier extents; no recovered-function-count claim')
    output_manifest = destination / 'accepted.json'
    output_manifest.write_text(json.dumps(manifest, indent=2) + '\n')
    tools = destination / 'acceptance-tools'
    tools.mkdir()
    for name in ('coff.py', 'verify_manifest.py', 'compose.py'):
        shutil.copy2(Path(__file__).with_name(name), tools / name)
    # Audit merged metadata before build too; preserve each row's true population owner.
    combined = audit.audit(output_manifest)
    (destination / 'combined-provenance-audit.json').write_text(json.dumps(combined, indent=2))

    def run(script, *arguments):
        command = [sys.executable, str(script), *map(str, arguments)]
        before = time.monotonic()
        result = subprocess.run(command, cwd=repository, capture_output=True, text=True)
        log = destination / (script.stem + '-command.json')
        log.write_text(json.dumps(dict(command=command, returncode=result.returncode,
                                      seconds=time.monotonic() - before,
                                      stdout=result.stdout, stderr=result.stderr), indent=2))
        require(result.returncode == 0, 'Build failed; inspect ' + str(log))
        return time.monotonic() - before

    integration_seconds = run(root / 'scripts/integrate.py', output_manifest, tag)
    link_seconds = run(destination / 'link.py')
    packaging_seconds = run(root / 'scripts/package.py', tag)
    run(root / 'scripts/describe_link.py', tag)
    receipt = json.loads((destination / 'reference-receipt.json').read_text())
    original = audit.read(root / 'inputs/game.exe')
    output = (destination / 'reference.exe').read_bytes()
    require(output == original and receipt['whole_file_exact'], 'Complete packaged file differs')
    receipt.update(matched_source_regions=len(chosen), accepted_manifest=str(output_manifest),
                   accepted_manifest_sha256=hashlib.sha256(output_manifest.read_bytes()).hexdigest(),
                   input_validation_seconds=validation_seconds, integration_seconds=integration_seconds,
                   link_seconds=link_seconds, packaging_seconds=packaging_seconds,
                   composition_seconds=time.monotonic() - started, input_manifests=inputs,
                   recompile_scope='Hash-verified compiler outputs reused; unchanged original/compiler matrices not rerun. New sources compiled in referenced worker sweeps.',
                   acceptance_tool_hashes={p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in tools.iterdir()})
    (destination / 'composition-receipt.json').write_text(json.dumps(receipt, indent=2) + '\n')
    print(json.dumps(dict(receipt=str(destination / 'composition-receipt.json'), regions=len(chosen),
                         body_bytes=manifest['body_bytes'], padding_bytes=manifest['frozen_padding_bytes'],
                         full_file_sha256=receipt['output_sha256'], seconds=receipt['composition_seconds'])))


if __name__ == '__main__':
    main()

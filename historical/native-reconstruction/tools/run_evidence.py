#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Run an evidence driver with guarded inspection reuse and an immutable audit.

Requires explicit executable and native runner paths. The driver's own original,
receipt and replay validation stays intact. --uncached provides the same identity
guards and audit without inspection reuse, for end-to-end comparison.
Reviewed drivers can separately opt into --original-cache after the driver name.
"""
import argparse
import hashlib
import importlib
import json
from pathlib import Path
import sys
import time

from inspection_reuse import InspectionReuse

ROOT = Path(__file__).resolve().parents[1]


def hash_file(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def source_identities(root=ROOT, paths=None):
    if paths is not None:
        return {p: hash_file(root / p) for p in sorted(paths)}
    files = {root / 'CMakeLists.txt'}
    for name in ('src', 'tools', 'tests', 'cmake'):
        folder = root / name
        if folder.exists():
            files.update(path for path in folder.rglob('*') if path.is_file() and
                         (path.suffix in ('.cpp', '.hpp', '.h', '.py', '.cmake') or
                          path.name == 'CMakeLists.txt'))
    return {str(path.relative_to(root)): hash_file(path) for path in sorted(files)}


def driver_sources(driver, module, root=ROOT):
    """Guard declared dependencies, transitive local Python and quoted headers.

    The identified runner is already built. Unrelated checkout files are not
    inputs to this invocation. Older drivers without a source declaration retain
    the conservative whole-source guard.
    """
    if not hasattr(module, 'SOURCES'):
        return None
    import re
    from original_results import python_closure
    paths = set(module.SOURCES)
    paths.update(python_closure(driver, {'sources': dict.fromkeys(paths)}, root))
    pending = [p for p in paths if Path(p).suffix in ('.cpp', '.hpp', '.h')]
    while pending:
        path = pending.pop()
        for name in re.findall(r'^#include "([^"]+)"', (root/path).read_text(), re.M):
            local = (root/path).parent/name
            child = local if local.is_file() else root/'src'/name
            relative = str(child.resolve(strict=True).relative_to(root.resolve()))
            if relative not in paths:
                paths.add(relative)
                pending.append(relative)
    for path in paths:
        (root/path).resolve(strict=True).relative_to(root.resolve())
    return paths


def option(arguments, name, required=False):
    # Existing drivers use argparse, which also permits --option=value.
    values = []
    for index, arg in enumerate(arguments):
        if arg == name:
            if index + 1 == len(arguments):
                raise ValueError('Missing value for ' + name)
            values.append(arguments[index + 1])
        elif arg.startswith(name + '='):
            values.append(arg.split('=', 1)[1])
    if len(values) > 1 or (required and not values):
        raise ValueError('One explicit ' + name + ' is required')
    return Path(values[0]).resolve() if values else None


def input_identities(arguments):
    paths = [option(arguments, name, required=True) for name in ('--exe', '--native')]
    paths += [p for name in ('--legacy-native', '--direction-data', '--render-data',
                            '--raster-data', '--geometry-data', '--palette', '--subcell-data', '--map-data')
              if (p := option(arguments, name)) is not None]
    expectations = option(arguments, '--expectations')
    if expectations is not None:
        option(arguments, '--report', required=True)
        paths += [expectations, expectations.parent / 'report.json']
    return {str(path): hash_file(path) for path in paths}


def check_identities(before, after):
    if before != after:
        raise ValueError('Evidence input/source/runner/CMake identities changed during invocation')


def main():
    start = time.monotonic()
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--audit', type=Path, required=True)
    parser.add_argument('--uncached', action='store_true')
    parser.add_argument('--uncached-byte-histograms', action='store_true',
                        help='Keep verifier reuse but recount PE bytes, for a scoped control')
    parser.add_argument('driver', type=Path)
    parser.add_argument('arguments', nargs=argparse.REMAINDER)
    args = parser.parse_args()
    driver = args.driver.resolve()
    if driver.parent != ROOT / 'tests' or not driver.name.startswith('compare_') or driver.suffix != '.py':
        raise ValueError('An existing tests/compare_*.py evidence driver is required')
    sys.path[:0] = [str(ROOT / 'tests'), str(ROOT / 'tools')]
    from presentation_evidence import private_path
    exe = option(args.arguments, '--exe', required=True)
    audit = private_path(args.audit, exe)
    output = option(args.arguments, '--output')
    report = option(args.arguments, '--report') or (output / 'report.json' if output else None)
    expectations = option(args.arguments, '--expectations')
    protected = {p for p in (report, expectations, output / 'expected.json' if output else None,
                 expectations.parent / 'report.json' if expectations else None) if p}
    if audit in protected or audit.exists():
        raise ValueError('A new, separate private inspection audit is required')
    if report is None:
        raise ValueError('Use explicit --output or --report for the evidence result')
    driver_hash = hash_file(driver)
    module = importlib.import_module(driver.stem)
    if Path(module.__file__).resolve() != driver:
        raise ValueError('Evidence driver import path differs')
    paths = driver_sources(driver, module)
    before = {'sources': source_identities(paths=paths), 'inputs': input_identities(args.arguments)}
    if hash_file(driver) != driver_hash:
        raise ValueError('Evidence driver changed during import')
    sys.argv = [str(driver), *args.arguments]
    reuse = InspectionReuse(byte_histograms=not args.uncached_byte_histograms)
    passed = False
    error = None
    try:
        with reuse:
            if not args.uncached:
                reuse.install_loaded_verifiers(ROOT / 'tools')
            module.main()
        check_identities(before, {'sources': source_identities(paths=paths), 'inputs': input_identities(args.arguments)})
        passed = True
    except BaseException as failure:
        error = type(failure).__name__ + ': ' + str(failure)
        raise
    finally:
        record = {'passed': passed, 'error': error, 'driver': str(driver),
                  'arguments': args.arguments, 'identities': before,
                  'source_guard_scope': 'driver-dependency-closure-v1' if paths is not None else 'whole-source-legacy',
                  'inspection_reuse': not args.uncached, 'inspection_invocation_local_only': True,
                  'byte_histogram_reuse': not (args.uncached or args.uncached_byte_histograms),
                  'invocation_local_only': option(args.arguments, '--original-cache') is None,
                  'original_execution_or_result_cache': option(args.arguments, '--original-cache') is not None,
                  'cache': reuse.stats,
                  'elapsed_seconds': time.monotonic() - start,
                  'driver_report': str(report),
                  'driver_report_sha256': hash_file(report) if report.is_file() else None}
        audit.parent.mkdir(parents=True, exist_ok=True)
        with audit.open('x') as stream:
            json.dump(record, stream, indent=2)
            stream.write('\n')
        print('Inspection audit:', audit, 'PASS' if passed else 'FAIL', flush=True)


if __name__ == '__main__':
    main()

#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect the two supplied RTPatch packages without executing or applying them.

Research-only; requires requirements-research.txt. The hashes identify supplied
packages, not their authenticity or the resulting game executable's identity.
"""
import argparse
import hashlib
import json
import struct
from pathlib import Path

import pefile

PACKAGES = {
    '9b66734863c12f7634c44ef9a401a136d897010eed10f3aafe28d5a424e48156': {
        'game': 'Red Alert 2', 'target': '1.006',
        'banner': b'Command & Conquer: Red Alert 2 1.006 Patch',
        'registry_hint': r'HKLM.SOFTWARE\Westwood\Red Alert 2.InstallPath',
        'overlay_sha256': 'ab94ac694862f93735a54155376cc34283f5ba4b6b43fba049745b572ac7228e',
    },
    '49acccbec1e5264bc1538b497682a8eae0cab790b5a4d858e9812a2b10e9b104': {
        'game': "Yuri's Revenge", 'target': '1.001',
        'banner': b"Command & Conquer: Yuri's Revenge 1.001 Patch",
        'registry_hint': r"HKLM.SOFTWARE\Westwood\Yuri's Revenge.InstallPath",
        'overlay_sha256': '5775644db479da5167e28c8c8de4763013d811a68c597b1dcb2bd4f39be8f336',
    },
}
ENGINE_SHA256 = '8b8d253f39d734611644d4d0833cf5c297c63dd9acaca55d5117a8f0af8eb7a2'


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def inspect(data):
    digest = sha256(data)
    if digest not in PACKAGES:
        raise ValueError('Unsupported patch hash; inspect and pin a new package separately')
    package = PACKAGES[digest]
    if package['banner'] not in data or package['registry_hint'].encode() not in data:
        raise ValueError('Expected patch banner/registry hint is absent')
    with pefile.PE(data=data) as pe:
        if pe.FILE_HEADER.Machine != 0x14c or pe.OPTIONAL_HEADER.Magic != 0x10b:
            raise ValueError('Expected PE32 i386 patch wrapper')
        overlay_offset = pe.get_overlay_data_start_offset()
        if overlay_offset is None:
            raise ValueError('RTPatch overlay is absent')
        overlay = data[overlay_offset:]
        if overlay[:4] != b'K*\x08\x02' or sha256(overlay) != package['overlay_sha256']:
            raise ValueError('Unexpected RTPatch overlay')
        leaves = []
        for resource in pe.DIRECTORY_ENTRY_RESOURCE.entries:
            if resource.id != 20530:
                continue
            for name in resource.directory.entries:
                if name.id == 19274:
                    for language in name.directory.entries:
                        if language.id == 1033:
                            leaf = language.data.struct
                            leaves.append(pe.get_data(leaf.OffsetToData, leaf.Size))
        if len(leaves) != 1:
            raise ValueError('Expected one patch-engine resource')
        resource = leaves[0]
        if len(resource) < 4 or struct.unpack_from('<I', resource)[0] != len(resource) - 4:
            raise ValueError('Patch-engine resource length mismatch')
        engine = resource[4:]
        if sha256(engine) != ENGINE_SHA256:
            raise ValueError('Unexpected embedded patch-engine hash')
        with pefile.PE(data=engine) as dll:
            exports = sorted(e.name.decode('ascii') for e in dll.DIRECTORY_ENTRY_EXPORT.symbols if e.name)
        versions = {}
        for block in getattr(pe, 'FileInfo', []):
            for entry in block:
                for table in getattr(entry, 'StringTable', []):
                    versions.update({k.decode(errors='replace'): v.decode(errors='replace')
                                     for k, v in table.entries.items()})
        return {
            'schema': 1, 'sha256': digest, 'bytes': len(data),
            'game': package['game'], 'advertised_patch_target': package['target'],
            'identity_status': 'supplied package pinned; resulting game executable not inspected',
            'wrapper': {'machine': 'PE32 i386', 'image_base': hex(pe.OPTIONAL_HEADER.ImageBase),
                        'entry_rva': hex(pe.OPTIONAL_HEADER.AddressOfEntryPoint),
                        'timestamp': pe.FILE_HEADER.TimeDateStamp, 'version_strings': versions,
                        'security_directory_bytes': pe.OPTIONAL_HEADER.DATA_DIRECTORY[4].Size},
            'registry_install_lookup_hint': package['registry_hint'],
            'payload': {'format': 'RTPatch delta overlay', 'offset': overlay_offset,
                        'bytes': len(overlay), 'sha256': sha256(overlay)},
            'embedded_engine': {'resource': '20530/19274/1033', 'bytes': len(engine),
                                'sha256': sha256(engine), 'exports': exports},
            'patch_applied': False,
            'resulting_executable_sha256': None,
            'runtime_support': False,
        }


def write_report(source, destination, report):
    """Refuse source-tree, public-tree, symlink and overwrite destinations."""
    source = source.resolve(strict=True)
    destination = destination.absolute()
    if any(p.is_symlink() for p in (destination, *destination.parents)):
        raise ValueError('Symlink output paths are refused')
    destination = destination.resolve()
    if destination.is_relative_to(source.parent):
        raise ValueError('Output must be outside the source package directory')
    root = Path(__file__).resolve().parents[1]
    if not any(destination.is_relative_to(root / local) for local in ('private', 'build')):
        raise ValueError('Report must remain under this project private/ or build/')
    destination.parent.mkdir(parents=True, exist_ok=True)
    with destination.open('x', encoding='utf-8') as output:
        output.write(json.dumps(report, indent=2) + '\n')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('patch', type=Path)
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    try:
        report = inspect(args.patch.read_bytes())
        report['source'] = str(args.patch.resolve())
        if args.output:
            write_report(args.patch, args.output, report)
            print(f'Inspection saved: {args.output}')
        else:
            print(json.dumps(report, indent=2))
    except (ValueError, OSError, pefile.PEFormatError) as error:
        raise SystemExit(str(error)) from error


if __name__ == '__main__':
    main()

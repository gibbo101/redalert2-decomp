#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Prepare a private decoded overlay fixture from manifest-checked owned slices.

This is a host Format80/INI adapter, not executed original parsing. Images are
deliberately supplied resident; temporary constructor effects belong to the test
runner. No original image availability or placement behavior follows.
"""
import argparse
import base64
import configparser
import hashlib
import json
import struct
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
STREAM_SIZE = 512 * 512


def decode_lcw(source, wanted):
    """Bounded Format80 adapter following our GameAssets.cpp reader."""
    output = bytearray()
    cursor = 0

    def read(count):
        nonlocal cursor
        if count > len(source) - cursor:
            raise ValueError('Truncated Format80 command')
        result = source[cursor:cursor + count]
        cursor += count
        return result

    def word():
        return struct.unpack('<H', read(2))[0]

    def append(data):
        if len(data) > wanted - len(output):
            raise ValueError('Format80 output overflow')
        output.extend(data)

    def copy(start, count):
        if not 0 <= start < len(output) or count > wanted - len(output):
            raise ValueError('Invalid Format80 copy')
        for offset in range(count):
            output.append(output[start + offset])

    while cursor < len(source):
        command = read(1)[0]
        if not command & 128:
            distance = ((command & 15) << 8) | read(1)[0]
            copy(len(output) - distance, ((command >> 4) & 7) + 3)
        elif not command & 64:
            count = command & 63
            if not count:
                break
            append(read(count))
        elif command == 254:
            count = word()
            append(read(1) * count)
        else:
            count = word() if command == 255 else (command & 63) + 3
            copy(word(), count)
    if len(output) != wanted:
        raise ValueError('Format80 output length mismatch')
    return bytes(output)


def decode_pack(section):
    try:
        packed = base64.b64decode(''.join(value for _, value in
            sorted(section.items(), key=lambda item: int(item[0]))), validate=True)
    except (ValueError, TypeError) as error:
        raise ValueError('Invalid numbered base64 overlay section') from error
    output = bytearray()
    cursor = 0
    while cursor < len(packed):
        if len(packed) - cursor < 4:
            raise ValueError('Truncated overlay chunk header')
        compressed, wanted = struct.unpack_from('<HH', packed, cursor)
        cursor += 4
        if compressed == wanted == 0:
            if cursor != len(packed):
                raise ValueError('Trailing overlay chunks after terminator')
            break
        if not compressed or not 0 < wanted <= 8192 or compressed > len(packed) - cursor:
            raise ValueError('Invalid overlay chunk bounds')
        if wanted > STREAM_SIZE - len(output):
            raise ValueError('Overlay stream overflow')
        output.extend(decode_lcw(packed[cursor:cursor + compressed], wanted))
        cursor += compressed
    if len(output) != STREAM_SIZE:
        raise ValueError('Overlay stream length mismatch')
    return bytes(output)


def parse_ini(data):
    ini = configparser.ConfigParser(interpolation=None, strict=False,
        allow_no_value=True, inline_comment_prefixes=(';',))
    ini.read_string(data.decode('latin1'))
    return ini


def prepare(fixture_dir, output, map_name='mp03t4.map'):
    source = fixture_dir.resolve()
    destination = output.resolve()
    if (not destination.is_relative_to(ROOT / 'private') or output.is_symlink()
            or destination.exists()):
        raise ValueError('Choose a new ignored private fixture file')
    if destination.is_relative_to(source) or source.is_relative_to(destination):
        raise ValueError('Fixture output must be separate from supplied inputs')
    if Path(map_name).name != map_name or map_name in ('.', '..'):
        raise ValueError('Map must be a single filename')
    manifest = json.loads((fixture_dir / 'manifest.json').read_text())
    paths = [fixture_dir / map_name, fixture_dir / 'rules.ini']
    contents = [path.read_bytes() for path in paths]
    hashes = {str(path): hashlib.sha256(data).hexdigest()
              for path, data in zip(paths, contents)}
    for path in paths:
        if hashes[str(path)] != manifest['files'][path.name]['sha256']:
            raise ValueError('Manifest source hash differs: ' + path.name)
    ini, rules = map(parse_ini, contents)
    streams = [decode_pack(ini[section]) for section in ('OverlayPack', 'OverlayDataPack')]
    names = [name.strip() for name in rules['OverlayTypes'].values()]
    if not 0 < len(names) <= 255:
        raise ValueError('Unsupported overlay registry size')
    size = list(map(int, ini['Map']['Size'].split(',')))
    if len(size) != 4 or not (0 < size[2] and 0 < size[3] and size[2] + size[3] <= 256):
        raise ValueError('Unsupported fixture map geometry')
    width, height = size[2:]
    indices = [y * 512 + x for y in range(512) for x in range(512)
        if x + y > width and x - y < width and y - x < width and x + y <= width + 2 * height]
    # Availability is supplied, never inferred from the names or source files.
    types = [[1, 0, int(rules.get(name, 'Crate', fallback='no').lower().startswith(('y', 't', '1'))), 0]
             for name in names]
    active = [(index, value) for index, value in enumerate(streams[0]) if value != 255]
    if any(value >= len(types) for _, value in active):
        raise ValueError('Overlay byte outside supplied registry')
    data = [(index, value) for index, value in enumerate(streams[1]) if value]
    values = [0, 2, width, height, 0, 1, 1, STREAM_SIZE, STREAM_SIZE, 0, 1,
        len(types), *[value for row in types for value in row], len(indices), *indices,
        len(active), *[value for row in active for value in row],
        len(data), *[value for row in data for value in row]]
    result = {'source_hashes': hashes,
        'decoded_sha256': [hashlib.sha256(stream).hexdigest() for stream in streams],
        'type_names': names, 'cell_count': len(indices), 'active_overlays': len(active),
        'all_images_resident_supplied': True, 'values': values}
    # Recheck read-only inputs before creating any output; exclusive creation
    # also refuses a destination that appeared after initial validation.
    if any(hashlib.sha256(path.read_bytes()).hexdigest() != hashes[str(path)] for path in paths):
        raise ValueError('Source inputs changed during preparation')
    destination.parent.mkdir(parents=True, exist_ok=True)
    with destination.open('x') as stream:
        stream.write(json.dumps(result, indent=2) + '\n')
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--fixture-dir', type=Path, required=True)
    parser.add_argument('--map', default='mp03t4.map')
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    result = prepare(args.fixture_dir, args.output, args.map)
    print(f"{result['cell_count']} Cells / {result['active_overlays']} overlay bytes prepared privately; images supplied resident")


if __name__ == '__main__':
    main()

#!/usr/bin/env python3
"""Read a supplied MODE1/2352 BIN or ISO; copy selected files to private storage.
No disc is mounted or modified. Does not execute installers or download content.
"""
import argparse
import hashlib
import json
import struct
from pathlib import Path

class Disc:
    def __init__(self, path):
        self.file = path.open('rb')
        try:
            self.file.seek(16 * 2048 + 1)
            self.stride, self.offset = (2048, 0) if self.file.read(5) == b'CD001' else (2352, 16)
            pvd = self.read(16, 2048)
            if pvd[:7] != b'\x01CD001\x01':
                raise ValueError('Expected ISO9660 ISO or MODE1/2352 BIN')
            self.root = pvd[156:190]
        except Exception:
            self.file.close()
            raise
    def __enter__(self):
        return self
    def __exit__(self, *_):
        self.file.close()
    def read(self, sector, size):
        out = bytearray()
        while size:
            self.file.seek(sector * self.stride + self.offset)
            part = self.file.read(min(2048, size))
            if not part:
                raise ValueError('Truncated disc')
            out.extend(part)
            size -= len(part)
            sector += 1
        return bytes(out)
    def entries(self, record=None, prefix=''):
        record = self.root if record is None else record
        sector, size = struct.unpack_from('<I', record, 2)[0], struct.unpack_from('<I', record, 10)[0]
        data, pos = self.read(sector, size), 0
        while pos < size:
            length = data[pos]
            if not length:
                pos = (pos // 2048 + 1) * 2048
                continue
            rec = data[pos:pos + length]
            pos += length
            if len(rec) < 34 or 33 + rec[32] > len(rec):
                raise ValueError('Malformed ISO directory record')
            name = rec[33:33 + rec[32]].decode('ascii').split(';')[0]
            if name in ('\0', '\1'):
                continue
            if '/' in name or '\\' in name or name in ('.', '..'):
                raise ValueError('Unsafe disc filename')
            path = prefix + name
            if rec[25] & 2:
                yield from self.entries(rec, path + '/')
            else:
                yield path, struct.unpack_from('<I', rec, 2)[0], struct.unpack_from('<I', rec, 10)[0]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('image', type=Path)
    parser.add_argument('--output', type=Path)
    parser.add_argument('--files', nargs='+', default=['INSTALL/GAME.EXE', 'INSTALL/RA2.EXE', 'INSTALL/GAME1.CAB', 'MAPS01.MIX', 'MULTI.MIX'])
    args = parser.parse_args()
    disc = Disc(args.image)
    entries = list(disc.entries())
    if not args.output:
        for name, _, size in entries:
            print(f'{size:12d} {name}')
        return
    args.output.mkdir(parents=True, exist_ok=True)
    manifest = {'source': str(args.image.resolve()), 'files': []}
    for name in args.files:
        match = next((e for e in entries if e[0].upper() == name.upper()), None)
        if match is None:
            raise ValueError(f'Missing disc file: {name}')
        dest = args.output / Path(match[0]).name.lower()
        if dest.exists():
            raise FileExistsError(f'Refusing to overwrite {dest}')
        data = disc.read(match[1], match[2])
        dest.write_bytes(data)
        digest = hashlib.sha256(data).hexdigest()
        manifest['files'].append({'disc_path': match[0], 'size': len(data), 'sha256': digest})
        print(dest.name, len(data), digest)
    (args.output / 'import-manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')
if __name__ == '__main__':
    main()

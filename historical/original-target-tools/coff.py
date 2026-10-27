"""Read classic i386 COFF with bounded symbols/sections; no game payloads."""
from bisect import bisect_left, bisect_right
import struct


class Coff:
    def __init__(self, data):
        self.data = data
        if len(data) < 20:
            raise ValueError('Truncated COFF header')
        machine, count, _, symbols_at, symbol_count, optional, _ = struct.unpack_from('<HHIIIHH', data)
        if machine != 0x14c or optional:
            raise ValueError('Expected classic i386 COFF')
        if 20 + 40 * count > len(data):
            raise ValueError('Truncated COFF section table')
        strings_at = symbols_at + 18 * symbol_count
        if symbols_at < 20 + 40 * count or strings_at + 4 > len(data):
            raise ValueError('Invalid COFF symbol/string table')
        length = struct.unpack_from('<I', data, strings_at)[0]
        if length < 4 or strings_at + length > len(data):
            raise ValueError('Truncated COFF string table')
        strings = data[strings_at:strings_at + length]

        def string(offset):
            if not 4 <= offset < len(strings):
                raise ValueError('Invalid COFF string offset')
            end = strings.find(b'\0', offset)
            if end < 0:
                raise ValueError('Unterminated COFF string')
            return strings[offset:end].decode('ascii')

        self.sections = []
        for index in range(count):
            name, _, _, size, raw_at, reloc_at, _, reloc_count, _, flags = struct.unpack_from('<8sIIIIIIHHI', data, 20 + 40 * index)
            name = name.rstrip(b'\0').decode('ascii')
            if name.startswith('/'):
                name = string(int(name[1:]))
            if raw_at and (raw_at < 20 + 40 * count or raw_at + size > len(data)):
                raise ValueError('Invalid COFF section data range')
            if size and not raw_at and (not flags & 0x80 or flags & 0x60):
                raise ValueError('Initialized/code section has no file backing')
            if reloc_count and (not reloc_at or reloc_at + 10 * reloc_count > len(data)):
                raise ValueError('Invalid COFF relocation range')
            if flags & 0x1000000:
                raise ValueError('Extended relocation count unsupported')
            self.sections.append(dict(name=name, size=size, data=data[raw_at:raw_at + size] if raw_at else b'',
                                      flags=flags, relocs=[struct.unpack_from('<IIH', data, reloc_at + 10 * i) for i in range(reloc_count)]))
        self.symbols = {}
        index = 0
        while index < symbol_count:
            raw, value, section, typ, storage, auxiliary = struct.unpack_from('<8sIhHBB', data, symbols_at + 18 * index)
            if index + auxiliary >= symbol_count:
                raise ValueError('Truncated COFF auxiliary symbols')
            name = string(struct.unpack_from('<I', raw, 4)[0]) if raw[:4] == bytes(4) else raw.rstrip(b'\0').decode('ascii')
            if section > count:
                raise ValueError('Invalid COFF symbol section')
            extra = data[symbols_at + 18 * (index + 1):symbols_at + 18 * (index + 1 + auxiliary)]
            self.symbols[index] = dict(name=name, value=value, section=section, type=typ, storage=storage,
                                       size=struct.unpack_from('<I', extra, 4)[0] if typ & 0x20 and auxiliary else 0)
            index += 1 + auxiliary
        for section in self.sections:
            for offset, symbol, kind in section['relocs']:
                if offset + 4 > len(section['data']) or symbol not in self.symbols:
                    raise ValueError('Invalid/cross-section COFF relocation')

        # Parsed objects are immutable snapshots. Index selectors and subsequent
        # function offsets once instead of scanning every symbol for every row.
        self._functions = sorted(
            (s for s in self.symbols.values() if s['section'] > 0 and s['type'] & 0x20),
            key=lambda s: s['name'])
        self._function_names = [s['name'] for s in self._functions]
        offsets = {}
        for symbol in self._functions:
            offsets.setdefault(symbol['section'], set()).add(symbol['value'])
        self._section_offsets = {section: sorted(values) for section, values in offsets.items()}

    def function(self, prefix):
        matches = []
        for index in range(bisect_left(self._function_names, prefix), len(self._functions)):
            symbol = self._functions[index]
            if not symbol['name'].startswith(prefix):
                break
            matches.append(symbol)
            if len(matches) > 1:
                break
        if len(matches) != 1:
            raise ValueError('Function symbol ambiguous/missing: ' + prefix)
        symbol = matches[0]
        section = self.sections[symbol['section'] - 1]
        start = symbol['value']
        offsets = self._section_offsets[symbol['section']]
        later = bisect_right(offsets, start)
        end = (start + symbol['size'] if symbol['size'] else
               min(offsets[later], len(section['data'])) if later < len(offsets) else len(section['data']))
        if not 0 <= start < end <= len(section['data']):
            raise ValueError('Invalid COFF function extent')
        return symbol, section, start, end

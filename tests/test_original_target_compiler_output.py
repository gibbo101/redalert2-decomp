"""Adversarial closed-output accounting tests using entirely synthetic bytes."""
import copy
import json
from pathlib import Path
import struct
import sys
import unittest
from types import SimpleNamespace

sys.path.insert(0, str(Path(__file__).resolve().parents[1]/'tools/original_target'))
from coff import Coff
from compiler_output import classify, structure_hash, sha
from build import verify_discard_transfer, write_coff


def fixture():
    # One source file, one game function, one implicit helper and its FPO record.
    sections = [('.text', b'\xc3', 0x60501020, []),
                ('.text', b'\x90\xc3\x90\x90', 0x60501020, []),
                ('.debug$F', struct.pack('<IIII', 0, 2, 0, 0x14000004), 0x42101048, [(0, 6, 7)])]
    def sym(name, section, typ, storage, aux=b''):
        return struct.pack('<8sIhHBB', name.encode(), 0, section, typ, storage, len(aux)//18) + aux
    def aux(size, relocations, association, selection):
        return struct.pack('<IHHIhB3s', size, relocations, 0, 0, association, selection, bytes(3))
    records = [sym('.file', -2, 0, 103, b'fixture.cpp'.ljust(18,b'\0')),
               sym('.text', 1, 0, 3, aux(1,0,0,2)), sym('_game',1,32,2),
               sym('.text',2,0,3,aux(4,0,0,2)),sym('_helper',2,32,2),
               sym('.debug$F',3,0,3,aux(16,1,2,5))]
    # Indices: file0+aux1, section2+aux3, game4, helpersection5+aux6,
    # helper7, debugsection8+aux9. Reference uses actual helper7 below.
    sections[2][3][0] = (0, 7, 7)
    start=20+40*len(sections); payload=bytearray(); headers=[]
    for name,data,flags,relocs in sections:
        raw=start+len(payload); payload.extend(data)
        at=start+len(payload) if relocs else 0
        for relocation in relocs: payload.extend(struct.pack('<IIH',*relocation))
        headers.append(struct.pack('<8sIIIIIIHHI',name.encode(),0,0,len(data),raw,at,0,len(relocs),0,flags))
    return struct.pack('<HHIIIHH',0x14c,3,0,start+len(payload),10,0,0)+b''.join(headers)+payload+b''.join(records)+struct.pack('<I',4)


class ClosedOutputTests(unittest.TestCase):
    def setUp(self):
        self.coff = Coff(fixture())
        self.sources = [dict(source_sha256='source')]
        self.options = ['/O2','/Ob2','/G5','/Gy']
        self.compiler = {'compiler':'pinned'}
        self.headers = [dict(path='src/shared/fixture.hpp',sha256=sha(b'header'))]
        self.policy = dict(schema='ra2-closed-compiler-output-v1', original_image_credit=0,
                           sources=['source'], options=self.options, compiler=self.compiler,
                           inventory_sha256='inventory',gaps_sha256='gaps',headers=self.headers,
                           object_structure_sha256=structure_hash(self.coff),
                           helper=dict(symbol='_helper',bytes=4,body_bytes=2,sha256=sha(self.coff.sections[1]['data']),
                                       debug_sha256=sha(self.coff.sections[2]['data'])),
                           original_identity=dict(entry=0x401000,readiness_path='readiness.json',readiness_sha256='ready'))
        self.bounds=({0x401000:dict(entry_references=[1]),0x401004:dict(entry_references=[2])},
                     {0x401002:dict(length=2)})
        for key,row in [('body_inventory_row_sha256',self.bounds[0][0x401000]),
                        ('gap_row_sha256',self.bounds[1][0x401002]),
                        ('following_inventory_row_sha256',self.bounds[0][0x401004])]:
            self.policy['original_identity'][key]=sha(json.dumps(row,sort_keys=True,separators=(',', ':')).encode())
        self.facts=dict(status='independently-ready-original-helper',entry=0x401000,body_bytes=2,padding_bytes=2,
                        region_sha256=self.policy['helper']['sha256'])

    def check(self, coff=None, policy=None, sources=None, options=None, compiler=None, headers=None):
        coff = self.coff if coff is None else coff
        policy = self.policy if policy is None else policy
        def document(path, expected):
            if Path(path).as_posix()=='manifests/policy.json':
                if expected != sha(json.dumps(policy).encode()): raise ValueError('policy drift')
                return policy
            return self.facts
        audit=SimpleNamespace(document=document,read=lambda p,h:b'header',
                              original=lambda va,size:self.coff.sections[1]['data'])
        return classify(audit,coff,dict(path='manifests/policy.json',sha256=sha(json.dumps(policy).encode())),
                        self.sources if sources is None else sources,
                        self.options if options is None else options,
                        self.compiler if compiler is None else compiler,'inventory','gaps',
                        self.headers if headers is None else headers, self.bounds)

    def test_positive_has_zero_image_credit_and_whole_section(self):
        receipt=self.check()[0]
        self.assertEqual((receipt['first'],receipt['last'],receipt['original_image_credit']), (0,4,0))

    def test_closed_population_toolchain_options_and_headers_refuse(self):
        for kwargs in [dict(sources=[dict(source_sha256='other')]),dict(options=['/O1']),
                       dict(compiler={}),dict(headers=[]),dict(headers=self.headers*2)]:
            with self.subTest(kwargs=kwargs),self.assertRaises(ValueError):self.check(**kwargs)

    def test_every_section_hash_length_flags_and_padding_are_pinned(self):
        for i in range(3):
            for key,value in [('data',self.coff.sections[i]['data']+b'X'),('size',999),('flags',0)]:
                changed=copy.deepcopy(self.coff);changed.sections[i][key]=value
                with self.subTest(i=i,key=key),self.assertRaises(ValueError):self.check(changed)

    def test_runtime_data_alias_and_unknown_references_refuse(self):
        for source, target, kind in [(0,7,20),(0,5,6),(0,7,7),(2,5,7),(2,7,20)]:
            changed=copy.deepcopy(self.coff);changed.sections[source]['relocs'].append((0,target,kind))
            with self.subTest(source=source,target=target,kind=kind),self.assertRaises(ValueError):self.check(changed)

    def test_unsupported_topology_still_refuses_if_digest_repinned(self):
        for mutate in [lambda c:c.sections[0]['relocs'].append((0,5,6)),
                       lambda c:c.sections[1]['relocs'].append((0,4,20)),
                       lambda c:c.sections[2].update(flags=0x60100020),
                       lambda c:c.symbols[7].update(value=1),
                       lambda c:c.symbols.update({10:dict(c.symbols[7],name='_alias')})]:
            changed=copy.deepcopy(self.coff);mutate(changed)
            policy=copy.deepcopy(self.policy);policy['object_structure_sha256']=structure_hash(changed)
            with self.assertRaises(ValueError):self.check(changed,policy)

    def test_unknown_directive_data_or_extra_body_refuses(self):
        for name,flags in [('.drectve',0x100a00),('.data',0xc0100040),('.text',0x60501020)]:
            changed=copy.deepcopy(self.coff)
            changed.sections.append(dict(name=name,size=4,data=b'ROOT',flags=flags,relocs=[]))
            with self.subTest(name=name),self.assertRaises(ValueError):self.check(changed)

    def test_original_provenance_never_substitutes_for_object_identity(self):
        self.facts['padding_bytes']=1
        with self.assertRaisesRegex(ValueError,'original provenance'):self.check()

    def test_header_characteristics_line_state_and_trailing_storage_refuse(self):
        for offset,fmt,value in [(18,'<H',0x2000),(28,'<I',1),(48,'<I',1),(54,'<H',1)]:
            raw=bytearray(fixture());struct.pack_into(fmt,raw,offset,value)
            with self.subTest(offset=offset),self.assertRaises(ValueError):structure_hash(Coff(raw))
        with self.assertRaises(ValueError):structure_hash(Coff(fixture()+b'unknown'))

    def test_duplicate_file_metadata_refuses(self):
        changed=copy.deepcopy(self.coff)
        changed.symbols[10]=copy.deepcopy(changed.symbols[0])
        with self.assertRaisesRegex(ValueError,'duplicate'):structure_hash(changed)

    def test_transfer_proves_selector_omission_not_original_byte_absence(self):
        component=self.check()[0]
        audit=SimpleNamespace(discarded_outputs={'obj':[component]},sha=sha,read=lambda p:b'object')
        transfers=[dict(object='obj',section_index=1,section_start=0,section_end=1,bytes=1)]
        parts=[('.text$00402000',b'\xc3')]
        result=verify_discard_transfer(audit,transfers,parts,write_coff(parts))
        self.assertEqual(result['original_image_credit'],0)
        transfers[0]['section_index']=2
        with self.assertRaisesRegex(ValueError,'entered transfer'):verify_discard_transfer(audit,transfers,parts,write_coff(parts))
        with self.assertRaisesRegex(ValueError,'container differs'):verify_discard_transfer(audit,[],parts,write_coff(parts+[('.text$00403000',b'X')]))


if __name__=='__main__':unittest.main()

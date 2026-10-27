"""Synthetic end-to-end acceptance failures, with no proprietary fixture bytes."""
import copy
import json
from pathlib import Path
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch
from types import SimpleNamespace

sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))
import capstone
from canonical import CanonicalAudit, sha, source_path, validate_catalog, validate_includes, write_manifest
from build import check_tail, write_coff, wine_command, win
from coff import Coff
from verify_manifest import TARGET_SHA256, TARGET_BYTES


def synthetic_object(payload, relocation=None, extra=None):
    sections=[('.text',payload,0x60100020)] + ([] if extra is None else [extra])
    symbols=[struct.pack('<8sIhHBB',b'_fixture',0,1,0x20,2,0)]
    if relocation: symbols.append(struct.pack('<8sIhHBB',b'_target',0,0,0,2,0))
    offset=20+40*len(sections); headers=[];data=bytearray()
    for index,(name,blob,flags) in enumerate(sections):
        raw=offset+len(data);data.extend(blob)
        reloc=b'' if not relocation or index else struct.pack('<IIH',relocation[0],1,relocation[1])
        reloc_at=offset+len(data) if reloc else 0;data.extend(reloc)
        headers.append(struct.pack('<8sIIIIIIHHI',name.encode(),0,0,len(blob),raw,reloc_at,0,int(bool(reloc)),0,flags))
    return struct.pack('<HHIIIHH',0x14c,len(sections),0,offset+len(data),len(symbols),0,0)+b''.join(headers)+data+b''.join(symbols)+struct.pack('<I',4)


class CanonicalBuildTests(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory();self.addCleanup(self.tmp.cleanup);self.root=Path(self.tmp.name)
        (self.root/'src/recovered').mkdir(parents=True)
        self.source=self.root/'src/recovered/00401000.cpp';self.source.write_text('void fixture() {}\n')

    def row(self, original=b'\xc3'):
        return dict(entry=0x401000,method='401000',symbol='_fixture',symbol_prefix='_fixture',
                    source='src/recovered/00401000.cpp',source_sha256=sha(self.source.read_bytes()),
                    population='p',source_order=0,options=['/O2','/Ob2','/G5','/Gy'],
                    body_bytes=len(original),body_sha256=sha(original),padding_bytes=0,padding_sha256=sha(b''),
                    full_extent_bytes=len(original),full_extent_sha256=sha(original),references={},relocations=[])

    def catalog(self,rows):
        return dict(schema='ra2-canonical-source-v1',target=dict(size=TARGET_BYTES,sha256=TARGET_SHA256),
                    populations=[dict(id='p')],regions=rows)

    def verify(self, row, original, obj):
        # Pin a synthetic original boundary and use the actual canonical adapter
        # and inherited strict V4 verifier. Only the PE input loader is replaced.
        audit=CanonicalAudit.__new__(CanonicalAudit)
        audit.repository=self.root;audit.base=0x400000;audit.catalog={'regions':[row]}
        audit.blobs={};audit.documents={};audit.coffs={};audit.validated_objects=set();audit.groups={}
        audit.decoder=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);audit.decoder.detail=True
        audit.original=lambda address,size: original[address-0x401000:address-0x401000+size]
        audit.pe=SimpleNamespace(get_section_by_rva=lambda rva: object() if 0x1000<=rva<0x100000 else None)
        bound=dict(entry='00401000',ranges=[dict(start='00401000',end_inclusive='%08x'%(0x401000+len(original)-1),bytes_hex=original.hex())])
        audit.bounds={'p':({0x401000:bound},{})}
        path=self.root/'fresh.obj';path.write_bytes(obj)
        return audit.verify_fresh(self.root,[([row],path)])

    def test_source_catalog_hash_and_count(self):
        row=self.row();validate_catalog(self.root,self.catalog([row]))
        self.source.write_text('changed')
        with self.assertRaisesRegex(ValueError,'Source hash drift'):validate_catalog(self.root,self.catalog([row]))

    def test_uncatalogued_source_refuses(self):
        (self.source.parent/'00402000.cpp').write_text('void extra() {}')
        with self.assertRaisesRegex(ValueError,'Uncatalogued'):validate_catalog(self.root,self.catalog([self.row()]))

    def test_path_escape_refuses(self):
        for path in ['../outside.cpp','src/recovered/../../../outside.cpp','/src/recovered/a.cpp','src//recovered/a.cpp',
                     'src/recovered/family/../a.cpp','src/recovered/./a.cpp',
                     'src/recovered/family/evil\\name.cpp','src/recovered/family/a.h']:
            with self.subTest(path=path),self.assertRaises(ValueError):source_path(self.root,path)

    def test_nested_descriptive_catalog_path_is_authoritative(self):
        row=self.row();row['semantic_name']='KnownOperation_00401000'
        row['source']='src/recovered/purpose/KnownOperation_00401000.cpp'
        nested=self.root/row['source'];nested.parent.mkdir();self.source.rename(nested)
        validate_catalog(self.root,self.catalog([row]))
        self.assertEqual(source_path(self.root,row['source']),nested.resolve())
        row['semantic_name']='DifferentOperation_00401000'
        with self.assertRaisesRegex(ValueError,'descriptive filename'):
            validate_catalog(self.root,self.catalog([row]))

    def test_source_symlink_escape_refuses(self):
        outside=self.root/'outside.cpp';outside.write_text('void outside() {}')
        alias=self.source.parent/'alias.cpp';alias.symlink_to(outside)
        with self.assertRaisesRegex(ValueError,'escapes tree'):
            source_path(self.root,'src/recovered/alias.cpp')
        directory=self.source.parent/'escape';directory.symlink_to(self.root,target_is_directory=True)
        with self.assertRaisesRegex(ValueError,'escapes tree'):
            source_path(self.root,'src/recovered/escape/outside.cpp')

    def test_duplicate_mapping_and_missing_source_refuse(self):
        first=self.row();second=dict(first,entry=0x402000,source_order=1)
        with self.assertRaisesRegex(ValueError,'Duplicate'):
            validate_catalog(self.root,self.catalog([first,second]))
        self.source.unlink()
        with self.assertRaises(FileNotFoundError):validate_catalog(self.root,self.catalog([first]))

    def test_overlap_and_duplicate_order_refuse(self):
        first=self.row();second=dict(first,entry=0x401001,source='src/recovered/00401001.cpp')
        (self.root/second['source']).write_bytes(self.source.read_bytes())
        with self.assertRaisesRegex(ValueError,'Duplicate'):validate_catalog(self.root,self.catalog([first,second]))
        second['entry']=first['entry']
        with self.assertRaises(ValueError):validate_catalog(self.root,self.catalog([first,second]))

    def test_shared_header_hash_and_closure(self):
        directory=self.root/'src/shared';directory.mkdir()
        header=directory/'layout.hpp';header.write_text('#ifndef SHARED_LAYOUT\n#define SHARED_LAYOUT\nstruct Layout { int count; };\n#endif\n')
        self.source.write_text('#include "shared/layout.hpp"\nvoid fixture() {}\n')
        catalog=self.catalog([self.row()]);catalog['headers']=[dict(path='src/shared/layout.hpp',sha256=sha(header.read_bytes()))]
        validate_catalog(self.root,catalog)
        header.write_text('changed')
        with self.assertRaisesRegex(ValueError,'Header hash drift'):validate_catalog(self.root,catalog)

    def test_hidden_private_and_computed_includes_refuse(self):
        for data in [b'#include "../../private/input.h"',b'#include <windows.h>',b'#include HEADER',
                     b'#/**/include "private.h"',b'#inc\\\nlude "private.h"',b'%:include "private.h"',
                     b'??=include "private.h"',b'#pragma include_alias("shared/x.hpp", "private.h")',
                     b'#import "private.tlb"']:
            with self.subTest(data=data),self.assertRaises(ValueError):validate_includes(data,{'shared/x.hpp':b''})
        validate_includes(b'/* #include "absent.h" */\n#include "shared/x.hpp" // retained comment',{'shared/x.hpp':b''})

    def test_complete_fresh_extent_passes(self):
        result=self.verify(self.row(),b'\xc3',synthetic_object(b'\xc3'))
        self.assertEqual(result['matched_source_regions'],1)

    def test_streamed_manifest_equals_compact_json(self):
        shared={'_a':1,'?b@@':0x402000,'\u00fc':3}
        rows=[dict(entry=1,references=shared,name='x\u00e9\0'),dict(entry=2,references={}),dict(entry=3),
              dict(entry=4,references=shared,relocations=[dict(symbol='_a')]),dict(entry=5,references=dict(shared))]
        manifest=dict(executable_sha256=TARGET_SHA256,accepted=rows,matched_source_regions=len(rows))
        digest,spans=write_manifest(self.root/'m.json',manifest)
        data=(self.root/'m.json').read_bytes()
        self.assertEqual(data,(json.dumps(manifest)+'\n').encode());self.assertEqual(digest,sha(data))
        for (index,start,length),row in zip(spans,rows):self.assertEqual(json.loads(data[start:start+length]),row)

    def test_worker_and_inline_audits_write_identical_reports(self):
        # Two compile groups audited in forked worker processes and in-process.
        second=self.root/'src/recovered/00401001.cpp';second.write_text('void other() {}\n')
        rows=[self.row(),dict(self.row(),entry=0x401001,method='401001',source='src/recovered/00401001.cpp',
                              source_sha256=sha(second.read_bytes()),source_order=1,options=['/O2','/Ob2','/G6','/Gy'])]
        original=b'\xc3\xc3';outputs=[]
        for jobs in (2,1):
            audit=CanonicalAudit.__new__(CanonicalAudit)
            audit.repository=self.root;audit.base=0x400000;audit.catalog={'regions':rows}
            audit.blobs={};audit.documents={};audit.coffs={};audit.validated_objects=set();audit.groups={}
            audit.decoder=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);audit.decoder.detail=True
            audit.original=lambda address,size: original[address-0x401000:address-0x401000+size]
            audit.pe=SimpleNamespace(get_section_by_rva=lambda rva: object() if 0x1000<=rva<0x100000 else None)
            bounds={}
            for row in rows:
                body=original[row['entry']-0x401000:][:1]
                bounds[row['entry']]=dict(entry='%08x'%row['entry'],ranges=[dict(start='%08x'%row['entry'],end_inclusive='%08x'%row['entry'],bytes_hex=body.hex())])
            audit.bounds={'p':(bounds,{})}
            out=self.root/'out';out.mkdir()
            groups=[]
            for index,row in enumerate(rows):
                path=out/('g%d.obj'%index);path.write_bytes(synthetic_object(b'\xc3'));groups.append(([row],path))
            manifest=audit.verify_fresh(out,groups,jobs=jobs)
            self.assertEqual(manifest['matched_source_regions'],2)
            audit.verify_inputs_unchanged()
            # A source read only by a worker is still checked (by hash) at the end.
            saved=second.read_bytes();second.write_text('changed')
            with self.assertRaisesRegex(ValueError,'Proof input changed'):audit.verify_inputs_unchanged()
            second.write_bytes(saved)
            self.assertEqual(set(audit.coffs),{out/'g0.obj',out/'g1.obj'})
            outputs.append({p.name:p.read_bytes() for p in out.iterdir()})
            import shutil;shutil.rmtree(out)
        self.assertEqual(outputs[0],outputs[1])
        self.assertIn('fresh-verification.json',outputs[0])

    def test_wrong_extent_and_unaccounted_sections_refuse(self):
        for obj in [synthetic_object(b'\xc3\x90'),synthetic_object(b'\xc3',extra=('.text',b'\xc3',0x60100020)),
                    synthetic_object(b'\xc3',extra=('.data',b'X',0xc0100040))]:
            with self.subTest(obj=obj),self.assertRaises(ValueError):self.verify(self.row(),b'\xc3',obj)

    def test_direct_call_binding_and_unbound_refusal(self):
        target=0x402000;original=b'\xe8'+struct.pack('<i',target-0x401005)+b'\xc3'
        row=self.row(original);row['references']={'_target':target}
        row['relocations']=[dict(offset=1,kind=20,symbol='_target',target=target,addend=0,resolved=target-0x401005)]
        obj=synthetic_object(b'\xe8\0\0\0\0\xc3',(1,20))
        self.verify(row,original,obj)
        row['references']={}
        with self.assertRaisesRegex(ValueError,'Unbound'):self.verify(row,original,obj)

    def test_wrong_call_target_refuses_before_byte_comparison(self):
        target=0x402000;original=b'\xe8'+struct.pack('<i',target-0x401005)+b'\xc3'
        row=self.row(original);row['references']={'_target':target+1}
        with self.assertRaisesRegex(ValueError,'direct call/jump'):self.verify(row,original,synthetic_object(b'\xe8\0\0\0\0\xc3',(1,20)))

    def test_dir32_operand_validation(self):
        target=0x402000;original=b'\xb8'+struct.pack('<I',target)+b'\xc3';row=self.row(original)
        row['references']={'_target':target};row['relocations']=[dict(offset=1,kind=6,symbol='_target',target=target,addend=0,resolved=target)]
        self.verify(row,original,synthetic_object(b'\xb8\0\0\0\0\xc3',(1,6)))
        row['references']={'_target':target+1}
        with self.assertRaisesRegex(ValueError,'DIR32 operand'):self.verify(row,original,synthetic_object(b'\xb8\0\0\0\0\xc3',(1,6)))

    def test_cross_extent_relocation_refuses(self):
        # A relocation at the end of a compiler section fails COFF bounds first.
        with self.assertRaisesRegex(ValueError,'relocation'):
            self.verify(self.row(),b'\xc3',synthetic_object(b'\xc3',(0,20)))

    def test_missing_extra_changed_duplicate_or_reordered_compile_groups_refuse(self):
        audit=CanonicalAudit.__new__(CanonicalAudit)
        row=self.row(); second=dict(row,entry=0x402000,source_order=1)
        audit.catalog={'regions':[row,second]}
        for groups in [[], [([row],None)], [([row,second,row],None)],
                       [([second,row],None)], [([dict(row,symbol='_other'),second],None)],
                       [([row],None),([second],None)]]:
            with self.subTest(groups=groups),self.assertRaisesRegex(ValueError,'complete canonical source plan'):
                audit.verify_fresh(self.root,groups)

    def test_windows_temp_assignment_quotes_metacharacters(self):
        directory=self.root/'build&name';directory.mkdir()
        config=dict(bottle=str(self.root/'bottle'),wine='/unused/wine',lock=str(self.root/'lock'))
        with patch('build.run',return_value=dict(returncode=0,seconds=0)):
            wine_command(config,directory,['rem synthetic'],'quoted-temp')
        text=(directory/'quoted-temp.cmd').read_text()
        self.assertIn('set "TMP='+win(directory/'tmp')+'"',text)
        self.assertIn('set "TEMP='+win(directory/'tmp')+'"',text)

    def test_virtual_tail_requires_complete_zero_backing(self):
        check_tail(bytes(8),8)
        for tail in [bytes(7),bytes(9),bytes(7)+b'X']:
            with self.assertRaisesRegex(ValueError,'virtual tail'):check_tail(tail,8)

    def test_transfer_container_preserves_every_part(self):
        coff=Coff(write_coff([('.text$00401000',b'abc'),('.text$00402000',b'de')]))
        self.assertEqual([(s['name'],s['data'],s['relocs']) for s in coff.sections],
                         [('.text$00401000',b'abc',[]),('.text$00402000',b'de',[])])


if __name__=='__main__':unittest.main()

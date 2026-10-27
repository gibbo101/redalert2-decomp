"""Evidence overlays preserve byte coverage, original labels and archive identity."""
from pathlib import Path
import sys
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))
from source_ledger import overlay


class SourceLedgerTests(unittest.TestCase):
    def test_split_preserves_independent_evidence_and_source_identity(self):
        prior=[dict(file_start=0,file_end_exclusive=10,bytes=10,category='unknown',
                    exact_archive_section_identity=['archive-object'],ghidra_evidence_bits=3)]
        source=dict(entry=4,source='src/recovered/family/Named.cpp',source_sha256='source',object_sha256='object')
        out=overlay(prior,[(2,5,'accepted_C_body',source),(5,6,'accepted_frozen_NOP_padding',source)])
        self.assertEqual([(r['file_start'],r['file_end_exclusive'])for r in out],[(0,2),(2,5),(5,6),(6,10)])
        self.assertEqual(sum(r['bytes']for r in out),10)
        self.assertTrue(all(r['exact_archive_section_identity']==['archive-object'] and
                            r['ghidra_evidence_bits']==3 and r['original_partition_category']=='unknown' for r in out))
        self.assertEqual(out[1]['source_sha256'],'source')

    def test_prior_source_cannot_silently_remain_credited(self):
        prior=[dict(file_start=0,file_end_exclusive=2,bytes=2,category='accepted_C_body')]
        with self.assertRaisesRegex(ValueError,'disappeared'):overlay(prior,[])

    def test_overlap_and_hole_refuse(self):
        prior=[dict(file_start=0,file_end_exclusive=10,bytes=10,category='unknown')]
        with self.assertRaisesRegex(ValueError,'overlap'):overlay(prior,[(2,5,'body',{}),(4,8,'body',{})])
        with self.assertRaisesRegex(ValueError,'contiguous'):
            overlay([prior[0],dict(file_start=11,file_end_exclusive=12,bytes=1,category='unknown')],[])

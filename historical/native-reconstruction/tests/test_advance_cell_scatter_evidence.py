# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_advance_cell_scatter import command,parse,defaults,FLAGS,SOURCES,source_closure,validate
from compare_original import PATCHED_EXPECTED
from verify_advance_cell_scatter import verify
class AdvanceCellEvidence(unittest.TestCase):
 def fixture(self):
  current=dict(sources={'one':'two'},inspection={'three':'four'},direction_data_sha256='direction',render_data_sha256='render',raster_data_sha256='raster',geometry_data_sha256='geometry')
  meta=dict(FLAGS,identities=current,evidence_mode='fresh-original',native_sha256='runner')
  e=dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[command()],labels=['fixture'],expected=[['state',*['actor']*4,'geometry','scratch']],evidence=meta)
  return e,dict(meta,expectations_sha256='fingerprint'),copy.deepcopy(current)
 def test_block_roundtrip_and_shared_head(self):
  self.assertEqual(parse(command()),defaults());e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_exact_binary_and_domain(self):
  with self.assertRaises(ValueError):verify(b'other')
  for kw in ({'scratch':-1},{'scratch':1<<32},{'candidate':[1<<31,0,0]},{'cell':5},{'actions':[[1,0,0,1,1,100]]},{'actions':[[0,0,0,0,1,100]]}):
   with self.subTest(kw=kw),self.assertRaises(ValueError):parse(command(**kw))
 def test_block_cannot_be_relabelled_complete(self):
  for k,v in FLAGS.items():
   e,r,c=self.fixture();e['evidence'][k]=r[k]=not v
   with self.subTest(k=k),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_input_source_and_result_identity(self):
  self.assertTrue(set(source_closure())<=set(SOURCES))
  for k in self.fixture()[2]:
   e,r,c=self.fixture();c[k]='changed'
   with self.subTest(k=k),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture();e['expected']=[['state']]
  with self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
if __name__=='__main__':unittest.main()

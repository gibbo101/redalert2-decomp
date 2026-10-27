# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_frame_depth_refresh as d
class FrameDepthEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(d.scenarios());identity=dict(original={'inspection':'exact','sources':{'oracle':'original'}},native_sources={'kernel':'old'})
  meta=dict(d.FLAGS,identities=identity,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False)
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],labels=[s for s,_ in rows],expected=[['F',*['0']*12,'0'*64] for _ in rows],evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),copy.deepcopy(identity)
 def test_domains(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),607);[d.parse(c) for _,c in rows]
  for args in (dict(w=65),dict(mode=8),dict(h=33),dict(words=2),dict(offset=-1),dict(end=2048)):
   with self.assertRaises(ValueError):d.parse(d.command(**args))
 def test_original_reuse_native_current(self):
  e,r,c=self.fixture();c['native_sources']['kernel']='new';d.validate(e,r,'receipt',c)
  c['original']['sources']['oracle']='changed'
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
 def test_receipt_scope_and_rows(self):
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):d.validate(e,r,'wrong',c)
  for key in ('commands','labels','expected'):
   bad=copy.deepcopy(e);bad[key]=bad[key][1:]
   with self.assertRaises(ValueError):d.validate(bad,r,'receipt',c)
  e['evidence']['actual_stock_surface_children']=False;r=dict(e['evidence'],expectations_sha256='receipt')
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
  for row in ([],['F'],['F','F'],['11','0','0','0','0','F',*['0']*12,'0'*64],['F',*['0']*12,'x'*64]):
   with self.assertRaises(ValueError):d.validate_row(row)
 def test_engine_refusal(self):
  with self.assertRaises(ValueError):d.verify(b'wrong engine')
if __name__=='__main__':unittest.main()

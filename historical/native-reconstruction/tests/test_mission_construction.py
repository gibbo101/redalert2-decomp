# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_mission_construction as d
class MissionConstructionEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(d.scenarios());identity=dict(original={'inspection':'exact','sources':{'oracle':'original'}},native_sources={'kernel':'old'})
  meta=dict(d.FLAGS,identities=identity,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False)
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],labels=[s for s,_ in rows],expected=[['F',*['0']*166] for _ in rows],evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),copy.deepcopy(identity)
 def test_domain(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),291);[d.parse(c) for _,c in rows]
  for kw in (dict(type=2),dict(frame=2**31),dict(op=4),dict(mutation=6),dict(profile=6),dict(event=51),dict(trueByte=0),dict(permissions=16)):
   with self.assertRaises(ValueError):d.parse(d.command(**kw))
 def test_native_current_original_reused(self):
  e,r,c=self.fixture();c['native_sources']['kernel']='new';d.validate(e,r,'receipt',c)
  c['original']['sources']['oracle']='changed'
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
 def test_receipts_rows_scope(self):
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):d.validate(e,r,'wrong',c)
  for key in ('commands','labels','expected'):
   bad=copy.deepcopy(e);bad[key]=bad[key][1:]
   with self.assertRaises(ValueError):d.validate(bad,r,'receipt',c)
  e['evidence']['heap_resize_and_timer_padding_supplied']=False;r=dict(e['evidence'],expectations_sha256='receipt')
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
  for row in ([],['F'],['F','F'],['5',*['0']*5,'F',*['0']*166]):
   with self.assertRaises(ValueError):d.validate_row(row)
 def test_wrong_engine(self):
  with self.assertRaises(ValueError):d.verify(b'wrong engine')
if __name__=='__main__':unittest.main()

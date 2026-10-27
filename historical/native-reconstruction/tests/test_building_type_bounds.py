# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_building_type_bounds as d
class BuildingTypeEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(d.scenarios());identity=dict(original={'inspection':'exact','sources':{'oracle':'original'},'asset_rows':[]},native_sources={'kernel':'old'},native_input_producer={'binary':'old'})
  meta=dict(d.FLAGS,identities=identity,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False)
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],labels=[s for s,_ in rows],expected=[['F','0','0','0','0','-1','-1','0','0'] for _ in rows],evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),copy.deepcopy(identity)
 def test_header_domains_and_wrapped_index(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),355);[d.parse(c) for _,c in rows]
  d.parse(d.command(op=1,index=-2147483648,images=[d.image(count=-1)]*3))
  with self.assertRaises(ValueError):d.parse(d.command(op=1,index=0x10000000,images=[d.image(count=-1)]*3))
  for index,value in ((0,3),(1,7),(10,3),(12,256),(19,4),(17,32768)):
   bad=list(map(int,rows[0][1].split()));bad[index]=value
   with self.assertRaises(ValueError):d.parse(' '.join(map(str,bad)))
 def test_reuse_matches_actual_inputs_and_recomputes_native(self):
  e,r,c=self.fixture();c['native_sources']['kernel']='current';c['native_input_producer']['binary']='new';d.validate(e,r,'receipt',c)
  c['original']['asset_rows']=[['changed','inputs']]
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
  e,r,c=self.fixture();c['original']['sources']['oracle']='changed'
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
 def test_receipts_rows_and_scope(self):
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):d.validate(e,r,'wrong',c)
  for key in ('commands','labels','expected'):
   bad=copy.deepcopy(e);bad[key]=bad[key][1:]
   with self.assertRaises(ValueError):d.validate(bad,r,'receipt',c)
  e['evidence']['image_getters_supplied']=False;r=dict(e['evidence'],expectations_sha256='receipt')
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
  for row in ([],['F'],['F','F'],['11','0','0','0','F','0','0','0','0','-1','-1','0','0']):
   with self.assertRaises(ValueError):d.validate_row(row)
 def test_engine_refusal(self):
  with self.assertRaises(ValueError):d.verify(b'wrong engine')
if __name__=='__main__':unittest.main()

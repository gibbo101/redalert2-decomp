# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_cell_visibility_discovery as c
class CellVisibilityDiscoveryEvidence(unittest.TestCase):
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),64)
  for _,cmd in rows:self.assertEqual(len(c.parse(cmd)['records']),8)
  self.assertIn('src/sim/CellVisibilityDiscovery.cpp',c.NATIVE)
 def test_input_and_binary_guards(self):
  good=next(c.scenarios())[1]
  for cmd in ('',good+' 0',good.replace('V ','X ',1)):
   with self.assertRaises(ValueError):c.parse(cmd)
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_reuse_scope_guard(self):
  identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');rows=list(c.scenarios());expected=[]
  for _,cmd in rows:expected.append(['C','0','0','0','L','0','0']*7+['R'])
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=expected,evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}));bad=copy.deepcopy(e);bad['evidence']['production_discovery_schedule']=True
  with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()

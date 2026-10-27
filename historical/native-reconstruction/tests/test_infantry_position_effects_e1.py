# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_infantry_position_effects_e1 as c
class InfantryPositionEffectsE1Evidence(unittest.TestCase):
 def test_sequences_and_wrapping(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),80)
  for _,cmd in rows:c.parse(cmd)
  self.assertEqual(c.cell(-1),0);self.assertEqual(c.cell(-257),-1)
  self.assertEqual(c.cell(8388608),-32768);self.assertEqual(c.cell(-8388608),-32768)
 def test_guards(self):
  good=next(c.scenarios())[1]
  for cmd in ('',good+' 0',good.replace('F ','X ',1)):
   with self.assertRaises(ValueError):c.parse(cmd)
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_reuse_scope(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');expected=[['Q','0','m','2','m','2','m','2','m','2','P','0','0','C','0','0','G','0','6','7','E','B','0','0','1','C','0','0','C','0','0','D','7'] for _ in rows]
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=expected,evidence=meta);r=dict(meta,expectations_sha256='receipt')
  with self.assertRaises(ValueError):c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
  bad=copy.deepcopy(e);bad['evidence']['production_position_effect_schedule']=True
  with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()

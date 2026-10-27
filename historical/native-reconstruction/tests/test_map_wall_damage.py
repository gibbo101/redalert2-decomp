# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_map_wall_damage as d
class WallDamageEvidence(unittest.TestCase):
 def test_prefix_and_cases(self):
  rows=list(d.scenarios());self.assertGreater(len(rows),500)
  for _,cmd in rows:
   prefix,v=d.parse(cmd);self.assertEqual(len(prefix),6)
   with self.assertRaises(AssertionError):d.parent.parse(cmd)
 def test_invalid_commands(self):
  for cmd in ('','D 0','D '+ '0 '*6+'C 2 0 -1 1 2 3 4 5 0',d.command()+' trailing'):
   with self.assertRaises((ValueError,AssertionError)):d.parse(cmd)
 def test_exact_original_and_coverage(self):
  with self.assertRaises(ValueError):d.verify(b'wrong executable')
  with self.assertRaises(ValueError):d.check_coverage(dict(cases=1,audited_complete_roots=1,counts={}))
 def test_receipt_and_scope(self):
  meta=dict(cases=1,audited_complete_roots=1,counts={k:1 for k in ('0x475fe0','0x47604e','0x4761df','0x476223','0x4763b4','0x4763c3','random','draw','rejected')},
   Unit_caller_excluded=True,runtime_enabled=False,identities={'sources':{'fixture':'one'}},evidence_mode='fresh-original')
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[d.command()],labels=['fixture'],expected=[['0']],evidence=meta)
  r=dict(meta,expectations_sha256='fingerprint');d.validate(e,r,'fingerprint',meta['identities'])
  with self.assertRaises(ValueError):d.validate(e,r,'wrong',meta['identities'])
  for field in ('Unit_caller_excluded','runtime_enabled'):
   changed=copy.deepcopy(e);changed['evidence'][field]=not meta[field];receipt=dict(changed['evidence'],expectations_sha256='fingerprint')
   with self.assertRaises(ValueError):d.validate(changed,receipt,'fingerprint',meta['identities'])
  with self.assertRaises(ValueError):d.validate(e,r,'fingerprint',{'sources':{'fixture':'changed'}})
if __name__=='__main__':unittest.main()

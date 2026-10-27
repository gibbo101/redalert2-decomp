# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_mission_event as d
class MissionEventEvidence(unittest.TestCase):
 def test_streams(self):
  rows=list(d.scenarios());self.assertGreater(len(rows),500)
  for _,cmd in rows:d.parse(cmd)
 def test_invalid_streams_and_engine(self):
  for cmd in ('','E 33 0 33 0 0 -1 0 -1','E 33 0 33 256 0 -1 0 0','E 1 0 1 0 0 -1 0 0'):
   with self.assertRaises((ValueError,IndexError)):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong engine')
 def test_receipt_guards(self):
  identity={'sources':{'fixture':'one'}};meta=dict(identities=identity,scheduler_and_runtime_excluded=True,evidence_mode='fresh-original')
  cmd=next(d.scenarios())[1];e=dict(executable_sha256=d.PATCHED_EXPECTED,commands=[cmd],labels=['fixture'],expected=[['R','0']],evidence=meta)
  r=dict(meta,expectations_sha256='fingerprint');d.validate(e,r,'fingerprint',identity)
  with self.assertRaises(ValueError):d.validate(e,r,'changed',identity)
  with self.assertRaises(ValueError):d.validate(e,r,'fingerprint',{'sources':{'fixture':'changed'}})
  altered=copy.deepcopy(e);altered['evidence']['scheduler_and_runtime_excluded']=False
  with self.assertRaises(ValueError):d.validate(altered,dict(altered['evidence'],expectations_sha256='fingerprint'),'fingerprint',identity)
if __name__=='__main__':unittest.main()

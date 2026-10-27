# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_surface_fill as c
class SurfaceFillEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(c.scenarios());identity=dict(original={'binary':'exact'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original')
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=[['R','1','B','pixels','T','stores','L','3'] for _ in rows],evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),identity
 def test_cases_and_scope(self):
  rows=[c.parse(cmd) for _,cmd in c.scenarios()];self.assertEqual(len(rows),751)
  self.assertEqual({r['op'] for r in rows},{'E','F'});self.assertEqual({r['offset']%4 for r in rows},{0,1,2,3})
  self.assertEqual({r['bpp'] for r in rows},{1,2});self.assertTrue(any(r['color']>65535 for r in rows))
  self.assertFalse(c.FLAGS['message_global_surface_identified']);self.assertFalse(c.FLAGS['production_UI_enabled'])
 def test_input_and_binary_guards(self):
  for cmd in ('','F','X',c.command(bpp=4),c.command(offset=0),c.command(lock=2**31),c.command(color=-1),c.command(rect=(2**31,0,1,1)),c.command()+' extra'):
   with self.assertRaises(ValueError):c.parse(cmd)
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_replay_identity_and_receipt_guards(self):
  e,r,i=self.fixture();c.validate(e,r,'receipt',dict(i,native_sources={'rebuilt':'new'}))
  with self.assertRaises(ValueError):c.validate(e,r,'receipt',dict(i,original={'binary':'other'}))
  with self.assertRaises(ValueError):c.validate(e,r,'bad receipt',i)
  for flag in c.FLAGS:
   bad=copy.deepcopy(e);bad['evidence'][flag]=not c.FLAGS[flag]
   with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',i)
  for key,value in (('commands',[]),('labels',[]),('expected',[]),('profile','other'),('executable_sha256','other')):
   bad=copy.deepcopy(e);bad[key]=value
   with self.assertRaises(ValueError):c.validate(bad,r,'receipt',i)
if __name__=='__main__':unittest.main()

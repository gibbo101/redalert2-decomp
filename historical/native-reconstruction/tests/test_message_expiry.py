# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_message_expiry as c
class MessageExpiryEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original')
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=[['R','0',*['END']*len(c.parse(cmd)['operations'])] for _,cmd in rows],evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),identity
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),606);parsed=[c.parse(cmd) for _,cmd in rows]
  self.assertEqual({p['mutation'] for p in parsed},set(range(8)));self.assertTrue(any(any(op[0]=='I' for op in p['operations']) for p in parsed));self.assertTrue(any(slot==-1 for p in parsed for _,slot in p['nodes']))
  self.assertFalse(c.FLAGS['glyph_drawing_recovered']);self.assertFalse(c.FLAGS['production_scheduling_enabled'])
 def test_input_and_binary_guards(self):
  for cmd in ('',c.command()+' 0',c.command(expiries=(2**32,)),c.command(slots=(14,0,1)),c.command(mutation=8),c.command(times=()),c.command(operations=()),c.command(operations=(('I',2**31,'a'),)),c.command(operations=(('I',0,'a'*513),))):
   with self.assertRaises(ValueError):c.parse(cmd)
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_reuse_allows_rebuilt_native_only(self):
  e,r,i=self.fixture();c.validate(e,r,'receipt',dict(i,native_sources={'native':'new'}))
  with self.assertRaises(ValueError):c.validate(e,r,'receipt',dict(i,original={'engine':'changed'}))
  with self.assertRaises(ValueError):c.validate(e,r,'changed receipt',i)
 def test_scope_and_inputs_cannot_be_relabelled(self):
  e,r,i=self.fixture()
  for flag in c.FLAGS:
   bad=copy.deepcopy(e);bad['evidence'][flag]=not c.FLAGS[flag]
   with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',i)
  for key,value in (('commands',e['commands'][::-1]),('labels',[]),('expected',[]),('profile','other'),('executable_sha256','other')):
   bad=copy.deepcopy(e);bad[key]=value
   with self.assertRaises(ValueError):c.validate(bad,r,'receipt',i)
if __name__=='__main__':unittest.main()

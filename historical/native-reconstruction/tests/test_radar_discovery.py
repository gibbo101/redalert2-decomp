# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_radar_discovery as c
class RadarDiscoveryEvidence(unittest.TestCase):
 def row(self,cmd):return ['R','1','0','0']*(1 if c.parse(cmd)[4]==0 else 2)
 def test_domain(self):
  rows=list(c.scenarios());self.assertGreater(len(rows),1000)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd);c.validate_row(cmd,self.row(cmd))
 def test_inputs(self):
  for at,v in ((0,0),(0,2**31),(1,2**31),(4,3),(5,262144),(6,32768),(8,2**32),(10,2**31)):
   f=c.parse(c.command());f[at]=v
   with self.assertRaises(ValueError):c.parse(c.command(f))
  f=c.parse(c.command());f[0]=-1;f[3]=-2**31
  with self.assertRaises(ValueError):c.parse(c.command(f))
  f=c.parse(c.command());f[11]=f[5]
  with self.assertRaises(ValueError):c.parse(c.command(f))
  with self.assertRaises(Exception):c.verify(b'wrong')
 def test_traces(self):
  for row in (['R','2','0','0'],['X','0'],['n','4','3','R','0','0','0'],['c','0',str(2**31),'R','0','0','0'],['R','1','0','0','R','0','0','0']):
   with self.assertRaises(ValueError):c.validate_row(c.command(),row)
 def test_reuse(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[cmd for _,cmd in rows],labels=[label for label,_ in rows],expected=[self.row(cmd) for _,cmd in rows],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
  for change in ('identity','flag','commands','trace','receipt'):
   bad=copy.deepcopy(e);report=copy.deepcopy(r);current=copy.deepcopy(identity);fingerprint='receipt'
   if change=='identity':current['original']['engine']='changed'
   if change=='flag':bad['evidence']['production_or_SDL_adoption']=True;report['production_or_SDL_adoption']=True
   if change=='commands':bad['commands'][0]='V 0'
   if change=='trace':bad['expected'][0][0]='X'
   if change=='receipt':fingerprint='wrong'
   with self.assertRaises(ValueError):c.validate(bad,report,fingerprint,current)
if __name__=='__main__':unittest.main()

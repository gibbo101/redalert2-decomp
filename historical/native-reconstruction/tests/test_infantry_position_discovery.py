# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import compare_infantry_position_discovery as c
class InfantryPositionDiscoveryEvidence(unittest.TestCase):
 def test_domain(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),360)
  calls=queues=0
  for _,cmd in rows:
   f=c.parse(cmd);entered=bool(f['onMap'] and not f['discovered'] and f['revealed']&16)
   calls+=entered;queues+=entered and not f['human'] and f['mission']==14
  self.assertEqual((calls,queues),(36,6))
 def test_reject_unsupported_or_malformed(self):
  good=next(c.scenarios())[1]
  for cmd in ('',good+' 0',good.replace('D ','F ',1)):
   with self.assertRaises((ValueError,IndexError)):c.parse(cmd)
  parts=good.split();parts[12]='15'
  with self.assertRaises(ValueError):c.parse(' '.join(parts))
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
if __name__=='__main__':unittest.main()

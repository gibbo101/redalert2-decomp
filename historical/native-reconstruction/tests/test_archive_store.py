# SPDX-License-Identifier: GPL-3.0-or-later
"""Authored nested MIX fixtures for initial registration and read-only provenance."""
import hashlib,shlex,struct,subprocess,tempfile,unittest,zlib
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]

def mix_id(name):
 data=name.upper().encode('ascii');r=len(data)%4
 if r:data+=bytes([r])+bytes([data[-r]])*(3-r)
 return zlib.crc32(data)

def mix(files):
 # Fixture IDs sorted as signed words; arbitrary authored payloads, no game data.
 entries=sorted(((mix_id(name),data) for name,data in files.items()),key=lambda e:e[0] if e[0]<0x80000000 else e[0]-0x100000000)
 body=bytearray();index=bytearray()
 for key,data in entries:index+=struct.pack('<III',key,len(body),len(data));body+=data
 return struct.pack('<IHI',0,len(entries),len(body))+index+body

class ArchiveStoreTests(unittest.TestCase):
 def fixture(self,root):
  (root/'ra2.mix').write_bytes(mix({'cache.mix':mix({'test.dat':b'cache'}),'local.mix':mix({'test.dat':b'local'}),
      'conquer.mix':mix({'test.dat':b'conquer'}),'generic.mix':mix({'test.dat':b'generic'})}))
  (root/'language.mix').write_bytes(mix({'cameo.mix':mix({'test.dat':b'cameo'})}))
  (root/'maps01.mix').write_bytes(mix({'test.dat':b'maps'}))
  (root/'multi.mix').write_bytes(mix({'test.dat':b'multi'}))
 def inspect(self,root):
  before={p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in root.iterdir()}
  result=subprocess.run([str(ROOT/'build/native/archive-inspect'),str(root)],input='test.dat\nabsent.dat\n',text=True,capture_output=True,check=True)
  self.assertEqual(before,{p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in root.iterdir()})
  rows=[shlex.split(line) for line in result.stdout.splitlines()];self.assertEqual(rows[-1],['M','absent.dat'])
  return [r for r in rows if r[0]=='A'],next(r for r in rows if r[0]=='Q')
 def test_nested_cache_precedes_local_and_later_archives_with_physical_source(self):
  with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
   root=Path(folder);self.fixture(root);archives,q=self.inspect(root)
   self.assertEqual([a[2] for a in archives],['language.mix','ra2.mix','cache.mix','local.mix','conquer.mix','cameo.mix','maps01.mix','multi.mix','generic.mix'])
   self.assertEqual(q[2:4],['1','2']);self.assertEqual(Path(q[4]),root/'ra2.mix')
   payload=(root/'ra2.mix').read_bytes()[int(q[5]):int(q[5])+int(q[6])]
   self.assertEqual(payload,b'cache');self.assertEqual(q[7],hashlib.sha256(payload).hexdigest())
 def test_descending_expansions_win_before_ra2(self):
  with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
   root=Path(folder);self.fixture(root)
   for n in [0,99]:(root/f'expand{n:02d}.mix').write_bytes(mix({'test.dat':f'expand{n}'.encode()}))
   archives,q=self.inspect(root);self.assertEqual([a[2] for a in archives[:4]],['language.mix','expand99.mix','expand00.mix','ra2.mix'])
   self.assertEqual(q[2:4],['1','1']);self.assertEqual(Path(q[4]),root/'expand99.mix')
 def test_language_registration_and_case_folded_loose_override(self):
  with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
   root=Path(folder);self.fixture(root)
   (root/'language.mix').write_bytes(mix({'test.dat':b'language','cameo.mix':mix({})}))
   _,q=self.inspect(root);self.assertEqual(q[2:4],['1','0'])
   (root/'TEST.DAT').write_bytes(b'loose');_,q=self.inspect(root)
   self.assertEqual(q[2:4],['0','0']);self.assertEqual(Path(q[4]),root/'TEST.DAT');self.assertEqual(q[5:7],['0','5'])
 def test_ambiguous_case_and_missing_required_family_fail_closed(self):
  with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
   root=Path(folder);self.fixture(root)
   (root/'RA2.MIX').write_bytes((root/'ra2.mix').read_bytes())
   result=subprocess.run([str(ROOT/'build/native/archive-inspect'),str(root)],capture_output=True,text=True)
   # Case-insensitive APFS names refer to one file. Exercise ambiguity only on
   # filesystems that can actually create two distinct case variants.
   if not (root/'RA2.MIX').samefile(root/'ra2.mix'):
    self.assertNotEqual(result.returncode,0);self.assertIn('Ambiguous',result.stderr)
    (root/'RA2.MIX').unlink()
   (root/'multi.mix').unlink()
   result=subprocess.run([str(ROOT/'build/native/archive-inspect'),str(root)],capture_output=True,text=True)
   self.assertNotEqual(result.returncode,0);self.assertIn('requires conquer/cameo/maps/multi',result.stderr)

if __name__=='__main__':unittest.main()

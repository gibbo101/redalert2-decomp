"""Synthetic ISO sectors only; no proprietary disc bytes or fixtures."""
import importlib.util
import struct
import tempfile
import unittest
from pathlib import Path
spec=importlib.util.spec_from_file_location('import_disc',Path(__file__).resolve().parents[1]/'tools/import_disc.py')
module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)

def record(name,sector,size,flags=0):
    n=33+len(name)+(len(name)%2==0)
    b=bytearray(n);b[0]=n;struct.pack_into('<I',b,2,sector);struct.pack_into('>I',b,6,sector);struct.pack_into('<I',b,10,size);struct.pack_into('>I',b,14,size);b[25]=flags;b[28]=1;b[31]=1;b[32]=len(name);b[33:33+len(name)]=name
    return b

class DiscTests(unittest.TestCase):
    def test_iso_and_mode1_read_only(self):
        image=bytearray(23*2048);image[16*2048:16*2048+7]=b'\x01CD001\x01';root=record(b'\0',20,2048,2);image[16*2048+156:16*2048+156+len(root)]=root
        entry=record(b'TEST.TXT;1',21,3);image[20*2048:20*2048+len(entry)]=entry;image[21*2048:21*2048+3]=b'abc'
        raw=b''.join(bytes(16)+image[i:i+2048]+bytes(288) for i in range(0,len(image),2048))
        with tempfile.TemporaryDirectory() as temp:
            for name,data in [('test.iso',image),('test.bin',raw)]:
                path=Path(temp)/name;path.write_bytes(data);disc=module.Disc(path)
                self.assertEqual(list(disc.entries()),[('TEST.TXT',21,3)])
                self.assertEqual(disc.read(21,3),b'abc');disc.file.close();self.assertEqual(path.read_bytes(),data)
    def test_reject_unknown_image(self):
        with tempfile.TemporaryDirectory() as temp:
            path=Path(temp)/'bad.bin';path.write_bytes(bytes(40*2352))
            with self.assertRaises(ValueError):module.Disc(path)
if __name__=='__main__':unittest.main()

# SPDX-License-Identifier: GPL-3.0-or-later
"""Preparation refusals must not overwrite supplied or existing private files."""
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from prepare_map_runtime_data import extract
ROOT=Path(__file__).resolve().parents[1]
class MapRuntimeDataTests(unittest.TestCase):
    def test_wrong_executable_is_refused(self):
        for data in (b'',b'MZ'+bytes(4096)):
            with self.assertRaisesRegex(ValueError,'Exact supplied patched engine'):extract(data)
    def test_refusal_preserves_source_and_destination(self):
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder);install=root/'install';install.mkdir();source=install/'game.exe';source.write_bytes(b'owned original sentinel')
            output=root/'derived.bin';output.write_bytes(b'existing private sentinel')
            for destination in (source,install/'derived.bin',output):
                result=subprocess.run([sys.executable,str(ROOT/'tools/prepare_map_runtime_data.py'),'--exe',str(source),'--output',str(destination)],capture_output=True)
                self.assertNotEqual(result.returncode,0)
                self.assertEqual(source.read_bytes(),b'owned original sentinel')
                self.assertEqual(output.read_bytes(),b'existing private sentinel')
                self.assertFalse((install/'derived.bin').exists())
if __name__=='__main__':unittest.main()

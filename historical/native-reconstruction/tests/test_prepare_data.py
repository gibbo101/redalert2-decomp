"""Preparation safety checks with synthetic input, no proprietary fixtures."""
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
TOOLS=Path(__file__).resolve().parents[1]/'tools'
sys.path.insert(0,str(TOOLS))
import prepare_direction_data
import prepare_render_data
import prepare_raster_data
class PreparationTests(unittest.TestCase):
    def test_map_light_export_protects_source_and_symlinks(self):
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder);source=root/'install';source.mkdir();output=root/'research';output.mkdir()
            native=TOOLS.parent/'build/native/map-light-vectors'
            result=subprocess.run([str(native),'--export',str(source),str(source/'research')],capture_output=True,text=True)
            self.assertNotEqual(result.returncode,0);self.assertIn('outside source installation',result.stderr)
            (output/'mp03t4.map').symlink_to(source/'missing.map')
            result=subprocess.run([str(native),'--export',str(source),str(output)],capture_output=True,text=True)
            self.assertNotEqual(result.returncode,0);self.assertIn('Symlink',result.stderr)
            self.assertFalse((source/'missing.map').exists())
    def test_staging_export_protects_source_and_symlinks(self):
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder);source=root/'install';source.mkdir();output=root/'research';output.mkdir()
            native=TOOLS.parent/'build/native/staging-vectors'
            result=subprocess.run([str(native),'--export',str(source),str(source/'research')],capture_output=True,text=True)
            self.assertNotEqual(result.returncode,0);self.assertIn('outside source installation',result.stderr)
            (output/'temperat.pal').symlink_to(source/'missing.pal')
            result=subprocess.run([str(native),'--export',str(source),str(output)],capture_output=True,text=True)
            self.assertNotEqual(result.returncode,0);self.assertIn('Symlink',result.stderr)
            self.assertFalse((source/'missing.pal').exists())
    def test_shadow_color_export_protects_source_and_symlinks(self):
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder);source=root/'install';source.mkdir();output=root/'research';output.mkdir()
            native=TOOLS.parent/'build/native/shadow-color-vectors'
            result=subprocess.run([str(native),'--export',str(source),str(source/'research')],capture_output=True,text=True)
            self.assertNotEqual(result.returncode,0);self.assertIn('outside source installation',result.stderr)
            (output/'unittem.pal').symlink_to(source/'missing.pal')
            result=subprocess.run([str(native),'--export',str(source),str(output)],capture_output=True,text=True)
            self.assertNotEqual(result.returncode,0);self.assertIn('Symlink',result.stderr)
            self.assertFalse((source/'missing.pal').exists())
    def test_vpl_export_protects_source_tree(self):
        with tempfile.TemporaryDirectory() as folder:
            source=Path(folder);output=source/'research'/'voxels.vpl'
            native=TOOLS.parent/'build/native/presentation-vectors'
            result=subprocess.run([str(native),'--export-vpl',str(source),str(output)],capture_output=True,text=True)
            self.assertNotEqual(result.returncode,0)
            self.assertIn('outside the source installation',result.stderr)
            self.assertFalse(output.exists())
    def test_unknown_executable_refused(self):
        for module in (prepare_direction_data,prepare_render_data,prepare_raster_data):
            with self.subTest(module=module.__name__),self.assertRaisesRegex(ValueError,'Unsupported executable hash'):
                module.extract(bytes(512))
    def test_source_tree_is_read_only(self):
        with tempfile.TemporaryDirectory() as folder:
            source=Path(folder)/'game.exe';original=b'MZ synthetic';source.write_bytes(original)
            output=Path(folder)/'cache'/'directions.bin'
            for module in (prepare_direction_data,prepare_render_data,prepare_raster_data):
                with self.subTest(module=module.__name__):
                    result=subprocess.run([sys.executable,str(TOOLS/(module.__name__+'.py')),'--exe',str(source),'--output',str(output)],capture_output=True,text=True)
                    self.assertNotEqual(result.returncode,0)
                    self.assertIn('outside the source installation',result.stderr)
                    self.assertFalse(output.exists())
                    self.assertEqual(source.read_bytes(),original)
    def test_raster_export_rejects_source_symlink(self):
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder);source=root/'install';source.mkdir();output=root/'research';output.mkdir()
            (output/'htnk.vxl').symlink_to(source/'missing.vxl')
            native=TOOLS.parent/'build/native/raster-vectors'
            result=subprocess.run([str(native),'--export',str(source),str(output)],capture_output=True,text=True)
            self.assertNotEqual(result.returncode,0)
            self.assertIn('outside the source installation',result.stderr)
            self.assertFalse((source/'missing.vxl').exists())
    def test_composition_export_rejects_source_symlink(self):
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder);source=root/'install';source.mkdir();output=root/'research';output.mkdir()
            (output/'clear01.tem').symlink_to(source/'missing.tem')
            native=TOOLS.parent/'build/native/composition-vectors'
            result=subprocess.run([str(native),'--export',str(source),str(output)],capture_output=True,text=True)
            self.assertNotEqual(result.returncode,0)
            self.assertIn('outside the source installation',result.stderr)
            self.assertFalse((source/'missing.tem').exists())
if __name__=='__main__':unittest.main()

# SPDX-License-Identifier: GPL-3.0-or-later
"""Static request receipts use the shared strict engine/source/receipt guards."""
import unittest
from test_redraw_evidence import RedrawEvidenceGuards
from verify_static_redraw import verify
class StaticRedrawEvidenceGuards(RedrawEvidenceGuards):
    def test_unsupported_binary_refused(self):
        with self.assertRaisesRegex(ValueError,'executable'):verify(b'synthetic unsupported executable')
# Avoid discovering the imported base as an additional test suite.
del RedrawEvidenceGuards
if __name__=='__main__':unittest.main()

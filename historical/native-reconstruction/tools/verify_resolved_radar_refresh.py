# SPDX-License-Identifier: GPL-3.0-or-later
import hashlib,pefile
from verify_stock_radar_refresh import verify as refresh_verify
from verify_scheme_resolver import verify as resolver_verify
def verify(data):
 r=dict(refresh=refresh_verify(data),resolver=resolver_verify(data),scope='Actual stock actor and complete663D30/locale-zero CRT below complete zero-mode copy/mark/pixel refresh. Shared registry/schemes/House/pixels; startup/production remain supplied or open.')
 p=pefile.PE(data=data)
 if p.get_data(0x7ebfc4-0x400000,10)!=b'LightGrey\0':raise ValueError('Mark fixed scheme key differs')
 r['mark_key']=dict(address='0x7ebfc4',bytes=10,sha256=hashlib.sha256(b'LightGrey\0').hexdigest());return r

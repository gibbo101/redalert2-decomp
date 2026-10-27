#!/usr/bin/env python3
"""Compatibility entrypoint for the canonical fresh build; see build.py --help.
Historical manifest-composition code is preserved under historical/original-target-tools.
"""
from build import main

if __name__ == '__main__':
    main()

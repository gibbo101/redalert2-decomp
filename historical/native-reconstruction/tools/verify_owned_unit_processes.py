#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the complete owned-world, moving-admission and selected Drive boundaries."""
from verify_owned_unit_world import verify as world_verify
from verify_moving_unit_admission import verify as moving_verify
from verify_ground_drive_stores import verify as stores_verify


def verify(disc, data):
    return {'world': world_verify(disc, data), 'moving': moving_verify(data),
            'Drive_stores': stores_verify(data),
            'scope': 'Two genuine original actors/Drives on one shared graphics guest; '
                     'complete supported Process, live membership and interleaved drawing. '
                     'Selected ordered stores and logged coordinate/floor/word queries, '
                     'not every original machine store. Initial records and named services '
                     'remain supplied; runtime commands and scheduling are excluded.'}

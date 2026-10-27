// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/BorrowedPreparedUnitAdmission.hpp"
#include "assets/CellNearbyScatterWorld.hpp"
namespace ra2 {
// Separate, unwired views. Admission, snapshot dispatch, Scatter and nearby
// policy are the same kernels as the retained value APIs. No motion refresh.
using BorrowedUnitScatterWorldView=BasicUnitScatterWorldView<BorrowedUnitAdmissionWorld,BorrowedAdmissionMotionWorld>;
using BorrowedCellUnitScatterView=BasicCellUnitScatterView<BorrowedUnitAdmissionWorld,BorrowedAdmissionMotionWorld>;
}

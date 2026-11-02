// LightSourceClass::Unknown_00537830(int time, bool force) (0x00537830): TibSun's Process_Lighting. Picks
// the drawers of the pending cells (newest first, checking the time budget every 16 cells unless forced);
// when every pending cell has its values and there is time (or forced), applies them all and frees the list;
// with time left, frees unused tile drawers every _update_interval frames.

void __fastcall LightSourceClass::Unknown_00537830(int time, bool force)
{
    static unsigned _update_frames = 0;

    double update_start_time = MillisecondTimer;

    static unsigned _update_interval = 50;
    static unsigned _last_update_frame = 0;
    static int _pending_index = 0;
    static int _pending_remaining = 0;
    static bool _commit_ready = false;

    _update_frames++;

    if (PendingCellClass::Array.Count() && !_commit_ready) {
        if (_pending_index <= 0) {
            _pending_remaining = PendingCellClass::Array.Count();
            _pending_index = _pending_remaining - 1;
        }
        for (; _pending_index >= 0; _pending_index--) {
            if (!force && ((unsigned)_pending_index % 16) == 15) {
                if (MillisecondTimer - update_start_time >= time) {
                    break;
                }
            }

            if (PendingCellClass::Array[_pending_index]->Converter != 0) {
                _pending_remaining--;
            } else {
                LightConvertClass *drawer;
                int intensity, ambient, brightness, tile_brightness, alt_brightness;
                Map[PendingCellClass::Array[_pending_index]->CellID].Pick_Drawer(drawer, intensity, ambient, brightness, tile_brightness, alt_brightness);
                PendingCellClass::Array[_pending_index]->Converter = drawer;
                PendingCellClass::Array[_pending_index]->Intensity = intensity;
                PendingCellClass::Array[_pending_index]->Ambient = ambient;
                PendingCellClass::Array[_pending_index]->Brightness = brightness;
                PendingCellClass::Array[_pending_index]->TileBrightness = tile_brightness;
                PendingCellClass::Array[_pending_index]->AltBrightness = alt_brightness;
                _pending_remaining--;
            }
        }
        if (_pending_remaining <= 0) {
            _commit_ready = true;
        }
    }

    double time_left = time - (MillisecondTimer - update_start_time);

    if (_commit_ready) {
        if (force || time_left >= time - 1) {
            for (int i = 0; i < PendingCellClass::Array.Count(); i++) {
                PendingCellClass *pending = PendingCellClass::Array[i];
                Map[pending->CellID].Init_Drawer(pending->Converter, pending->Intensity, pending->Ambient, pending->Brightness, pending->TileBrightness, pending->AltBrightness);
                delete pending;
            }
            PendingCellClass::Array.Clear();
            _commit_ready = false;
            Map.Flag_To_Redraw(true);
        }
    }

    time_left = time - (MillisecondTimer - update_start_time);

    if (time_left > 0.0 && _update_frames > (_last_update_frame + _update_interval)) {
        bool more_to_free = Unknown_00529710(time_left * 0.5 < 1.0 ? time_left * 0.5 : 1.0, false);
        _last_update_frame = _update_frames;
        _update_interval = more_to_free ? 1 : 50;
    }
}
// @ref ??BMillisecondTimerClass@@QBENXZ=005935e0
// @ref ?MillisecondTimer@@3VUnknownMillisecondTimer@@A=00837448
// @ref ?Unknown_00529710@@YI_NH_N@Z=00529710
// @ref _?_update_frames@?1??Unknown_00537830@LightSourceClass@@SIXH_N@Z@4IA=00a6e874
// @ref _?_update_interval@?1??Unknown_00537830@LightSourceClass@@SIXH_N@Z@4IA=007df634
// @ref _?_last_update_frame@?1??Unknown_00537830@LightSourceClass@@SIXH_N@Z@4IA=00a6e878
// @ref _?_pending_index@?1??Unknown_00537830@LightSourceClass@@SIXH_N@Z@4HA=00a6e87c
// @ref _?_pending_remaining@?1??Unknown_00537830@LightSourceClass@@SIXH_N@Z@4HA=00a6e880
// @ref _?_commit_ready@?1??Unknown_00537830@LightSourceClass@@SIXH_N@Z@4_NA=00a6e884

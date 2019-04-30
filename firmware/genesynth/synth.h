#ifndef THEA_SYNTH_H
#define THEA_SYNTH_H

#include <SdFat.h>

#include "ym2612.h"

/*
Synthesizer core. This handles all of the "management" of the synth engine -
polyphony, triggering notes, patches, etc.

This exposes interfaces used by the MIDI interface and display to interact
with the synth core.
*/

namespace thea {
namespace synth {

enum NoteMode { POLY, MONO, UNISON };

extern thea::ym2612::ChannelPatch patch;
extern thea::ym2612::ChannelPatch::WriteOption last_write_option;
extern unsigned long last_patch_modify_time;

void init();
void loop();

void play_note(uint8_t note, float pitch);
void stop_note(uint8_t note);
void stop_all_notes();
/* Offset is between -1.0 and 1.0. */
void pitch_bend(float offset);

void enable_lfo();
void disable_lfo();
void set_lfo_freq(uint8_t value);
void set_lfo_fms(uint8_t value);
void set_lfo_ams(uint8_t value);

// Change the note mode. If notes are playing, they will be stopped.
void set_note_mode(NoteMode mode);
NoteMode get_note_mode();

// Set the glide amount.
void enable_glide();
void disable_glide();
bool glide_enabled();
void set_glide_amount(float glide);
float get_glide();

// Set the number of unison voices.
void set_unison_voices(int voices);
int get_unison_voices();

// Set the unison spread.
void set_unison_spread(float spread);
float get_unison_spread();

/* Change a patch parameter.

Args:
    option: Which parameter to modify.
    normalized value: New parameter value (0-127).
*/
void modify_patch_parameter(thea::ym2612::ChannelPatch::WriteOption option, uint8_t normalized_value);

/* Mark the patch as externally modified, forcing the synth to sync it to the FM chip.

This is useful for MIDI control.

Args:
    option: Which parameter(s) have been modified. By default, it syncs the entire patch.
*/
void update_patch(thea::ym2612::ChannelPatch::WriteOption option = thea::ym2612::ChannelPatch::WriteOption::ALL);

/* Load the current active patch from the SD

Args:
    file: The SdFile to read.
    folder: The folder the file lives in. This is optional, as it leave it as nullptr will result in the loaded patch
        just using the patch name for the bank name.
*/
void load_patch(SdFile &file, SdFile *folder = nullptr);

/* Load the last used patch before the synth was powered off. */
void load_last_patch();

/* Save the patch to the SD card */
void save_patch(SdFile &file);

} // namespace synth
} // namespace thea

#endif

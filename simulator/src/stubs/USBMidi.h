#ifndef _USB_MIDI_H
#define _USB_MIDI_H

#include <stdint.h>

typedef void (*note_on_handler_t)(uint8_t, uint8_t, uint8_t);
typedef void (*note_off_handler_t)(uint8_t, uint8_t, uint8_t);
typedef void (*pitch_change_handler_t)(uint8_t, int);
typedef void (*control_change_handler_t)(uint8_t, uint8_t, uint8_t);
typedef void (*sysex_handler_t)(uint8_t *, unsigned int);

class USBMidi {
public:
  USBMidi(){};

  void setHandleNoteOn(note_on_handler_t handler) { note_on_handler = handler; };
  void setHandleNoteOff(note_off_handler_t handler) { note_off_handler = handler; };
  void setHandlePitchChange(pitch_change_handler_t){};
  void setHandleControlChange(control_change_handler_t handler) { control_change_handler = handler; };
  void setHandleSystemExclusive(sysex_handler_t handler) { sysex_handler = handler; };
  void begin(){};
  bool read();
  void sendSysEx(uint32_t length, uint8_t *data, bool hasTerm);

private:
  note_on_handler_t note_on_handler;
  note_off_handler_t note_off_handler;
  control_change_handler_t control_change_handler;
  sysex_handler_t sysex_handler;
};

extern USBMidi usbMIDI;

#endif

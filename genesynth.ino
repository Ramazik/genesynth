#include <util/delay.h>

#include "ym2612.h"
#include "display.h"
#include "vgm.h"
#include "midi.h"
#include "opn_parser.h"
#include "thea.h"

#define STATUS_LED 13
#define YM_CLOCK 4
#define PSG_CLOCK 5

static void wait_for_serial_monitor() {
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, HIGH);
  /* Waits for the serial monitor to be opened. */
  while (!Serial.dtr()) {
    delay(10);
    digitalWrite(STATUS_LED, HIGH);
    delay(10);
    digitalWrite(STATUS_LED, LOW);
  }
}

static void setup_ym_clock() {
  /* Temporary. Uses PWM to generate an 8Mhz clock for the YM2612 */
  pinMode(YM_CLOCK, OUTPUT);
  analogWriteFrequency(YM_CLOCK, 7670000);
  analogWrite(YM_CLOCK, 128);
}

static void setup_psg_clock() {
  /* Temporary. Uses PWM to generate an 4Mhz clock for the PSG */
  pinMode(PSG_CLOCK, OUTPUT);
  analogWriteFrequency(PSG_CLOCK, 3570000);
  analogWrite(PSG_CLOCK, 128);
}

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  //wait_for_serial_monitor();
  Serial.println("Started");


  // Initialize the display
  display_init();
  thea::show_thea(&display);

  // Setup clocks
  setup_ym_clock();
  setup_psg_clock();
  delay(50); // wait a second for the clock.

  // Setup sound chips.
  thea::ym2612::setup();
  thea::ym2612::reset();
  psg_setup();
  psg_reset();


  // Load patch
  auto patch = parse_opn_patch();
  patch.write_to_channel(0);
  patch.write_to_channel(1);
  patch.write_to_channel(2);


  // Setup MIDI
  midi_setup();

  // Initialize the VGM player.
  //thea::vgm::init();
}

void loop() {
  midi_loop();
  //thea::vgm::vgm_loop();
}

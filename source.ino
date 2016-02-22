
// confguration
#define STRIPE_PIN D6
#define SPEAKER_PIN D0
#define PIXEL_COUNT 5
#define SECONDS_TO_RING 3


// includes
#include "neopixel/neopixel.h"


// definitions
#define RGB(red, green, blue) uint32_t((uint32_t(red & 0xff) << uint32_t(16)) | (uint32_t(green & 0xff) << uint32_t(8)) | uint32_t(blue & 0xff))
#define RED(rgb) ((uint32_t(rgb) >> 16) & 0xff)
#define GREEN(rgb) ((uint32_t(rgb) >> 8) & 0xff)
#define BLUE(rgb) (uint32_t(rgb) & 0xff)
uint32_t random_color(uint8_t brightness = 255);
SYSTEM_MODE(AUTOMATIC);

enum BellState {WAITING, RINGING};

// initialization

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, STRIPE_PIN);

BellState state = WAITING;

void setup() {
  strip.begin();
  strip.show();
  Particle.function("bell",startRinging);
}


void loop() {
    switch (state) {
        case WAITING: wait(); break;
        case RINGING: ring(); break;
        
    }
}

#define DEC(i) (i > 0 ? i - 1 : 0)

void wait() {
    for (int i = 0; i < PIXEL_COUNT; i++) {
        uint32_t color = strip.getPixelColor(i);
        if (color) {
            uint32_t red = RED(color); red = DEC(red);
            uint32_t green = GREEN(color); green = DEC(green);
            uint32_t blue = BLUE(color); blue = DEC(blue);
            strip.setPixelColor(i, RGB(red, green, blue));
            break;
        }
    }
    strip.show();
    delay(5);
}


int ring_i = 0;
long end_time = 0;
void ring() {
    ring_i = (ring_i + 1) % PIXEL_COUNT;
    if (random(2)) {
        strip.setPixelColor(ring_i, 0);
    } else {
        strip.setPixelColor(ring_i, random_color());
    }
    strip.show();
    delay(30);
    if (end_time < millis()) {
        stopRinging();
    }
}

void stopRinging() {
    strip.show();
    state = WAITING;
}

void startRinging() {
    state = RINGING;
    end_time = millis() + SECONDS_TO_RING * 1000;
}

int startRinging(String command) {
    // see https://docs.particle.io/guide/getting-started/examples/photon/
    startRinging();
    return SECONDS_TO_RING;
}

uint32_t random_color(uint8_t brightness)
{
  int c1 = random(int(brightness) + 1);
  int c2 = random(int(brightness) + 1);
  int b = random(3);
  int red;
  int green;
  int blue;
  switch (b)
  {
    case 0:
      red = brightness;
      green = c1;
      blue = c2;
      break;
    case 1:
      red = c1;
      green = brightness;
      blue = c2;
      break;
    case 2:
      red = c1;
      green = c2;
      blue = brightness;
      break;
  }
  return RGB(red, green, blue);
}


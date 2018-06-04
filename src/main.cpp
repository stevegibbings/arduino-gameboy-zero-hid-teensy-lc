#include <Arduino.h>
#include <Keyboard.h>
#include <Bounce2.h>

#define NUM_KEYS 12

struct Key {
  char keycode;
  Bounce* bounce;
};

Key keys[NUM_KEYS];

Key key(char keycode, int pin) {
  Key *ret = new Key;
  ret->keycode = keycode;
  ret->bounce = new Bounce();
  // pinMode(pin, INPUT_PULLUP);
  ret->bounce->attach(pin, INPUT_PULLUP);
  ret->bounce->interval(10);
  return *ret;
}

void setupKeys() {
  keys[0] = key('w', 2);
  keys[1] = key('s', 3);
  keys[2] = key('a', 4);
  keys[3] = key('d', 5);
  keys[4] = key('p', 6);
  keys[5] = key('l', 7);
  keys[6] = key('o', 8);
  keys[7] = key('k', 9);
  keys[8] = key('x', 10);
  keys[9] = key('z', 16);
  keys[10] = key('q',14);
  keys[11] = key('e',15);
}

void setup() {
  setupKeys();
  Keyboard.begin();
  //  pinMode(0, INPUT_PULLUP);
}

void loop() {
  for (int i = 0; i < NUM_KEYS; i++) {
    keys[i].bounce->update();
    if (keys[i].bounce->fell()) {
      Keyboard.press(keys[i].keycode);
    } else if (keys[i].bounce->rose()) {
      Keyboard.release(keys[i].keycode);
    }
  }
}

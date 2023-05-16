#include <LedControl.h>

const int DIN_PIN = 8;
const int CS_PIN = 9;
const int CLK_PIN = 7;
int happiness = 0;
int moisture = 0;

const uint64_t IMAGES[] = {
  0x1020140202142010,
  0x0000340202340000,
  0x8050920202121000,
  0x0050320404325000,
  0x2038220404223820,
  0x5020530505532050,
  0x1f3f163d1d361f3f,
  0x4020130505132040
};
const int IMAGES_LEN = sizeof(IMAGES) / 8;


LedControl display = LedControl(DIN_PIN, CLK_PIN, CS_PIN);


void setup() {
  display.clearDisplay(0);
  display.shutdown(0, false);
  display.setIntensity(0, 10);
}

void displayImage(uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte row = (image >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++) {
      display.setLed(0, i, j, bitRead(row, j));
    }
  }
}

int i = 0;

void loop() {
  // displayImage(IMAGES[i]);
  // if (++i >= IMAGES_LEN) {
  //   i = 0;
  // }
  happiness += 10;
  moisture += 10;

  if (happiness >= 100) {
    happiness = 0;
    moisture = 0;
  }

  defineMood(happiness, moisture);

  delay(100);
}

void defineMood(int happiness, int moisture) {
  if (happiness >= 70 && moisture >= 40 && moisture <= 60) {
    expression("happy");
  } else if (happiness == 50 && moisture >= 40 && moisture <= 60) {
    expression("default");
  } else if (happiness <= 30 && moisture >= 40 && moisture <= 60) {
    expression("bored");
  } else if (happiness <= 10 && moisture >= 70 && moisture <= 60) {
    expression("upset");
  } else if (moisture >= 90) {
    expression("cry");
  } else if (moisture == 0) {
    expression("dead");
  } else if (moisture == 100) {
    expression("drown");
  } else if (happiness <= 10) {
    expression("angry");
  } else {
    expression("default");
  }
}

void expression(String expression) {
  if (expression == "happy") {
    displayImage(IMAGES[0]);
  } else if (expression == "default") {
    displayImage(IMAGES[1]);
  } else if (expression == "bored") {
    displayImage(IMAGES[2]);
  } else if (expression == "upset") {
    displayImage(IMAGES[3]);
  } else if (expression == "cry") {
    displayImage(IMAGES[4]);
  } else if (expression == "dead") {
    displayImage(IMAGES[5]);
  } else if (expression == "drown") {
    displayImage(IMAGES[6]);
  } else if (expression == "angry") {
    displayImage(IMAGES[7]);
  }
}
// homework 2 task 2
// Name: Arooj Fatima
// Reg no: 24-NTU-CS-FL-1019
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int redLed = 18;
const int yellowLed = 19;

const int redChannel = 0;
const int yellowChannel = 2;

const int redFrequency = 1000;
const int yellowFrequency = 5000;
const int resolution = 8;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

int redDuty = 0;
int yellowDuty = 255;

int redStep = 5;
int yellowStep = -5;

void setup() {
  Serial.begin(115200);

  ledcSetup(redChannel, redFrequency, resolution);
  ledcSetup(yellowChannel, yellowFrequency, resolution);

  ledcAttachPin(redLed, redChannel);
  ledcAttachPin(yellowLed, yellowChannel);

  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while (true) {
      delay(100);
    }
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Dual LED PWM");
  display.println("OLED Starting...");
  display.display();
  delay(1000);
}

void loop() {
  ledcWrite(redChannel, redDuty);
  ledcWrite(yellowChannel, yellowDuty);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);

  display.println("Dual LED Monitor");
  display.println("----------------");

  display.print("Red Duty: ");
  display.print((redDuty * 100) / 255);
  display.println("%");

  display.print("Red Freq: ");
  display.print(redFrequency);
  display.println(" Hz");

  display.println();

  display.print("Yellow Duty: ");
  display.print((yellowDuty * 100) / 255);
  display.println("%");

  display.print("Yellow Freq: ");
  display.print(yellowFrequency);
  display.println(" Hz");

  display.display();

  redDuty += redStep;
  yellowDuty += yellowStep;

  if (redDuty >= 255) {
    redDuty = 255;
    redStep = -5;
  }

  if (redDuty <= 0) {
    redDuty = 0;
    redStep = 5;
  }

  if (yellowDuty >= 255) {
    yellowDuty = 255;
    yellowStep = -5;
  }

  if (yellowDuty <= 0) {
    yellowDuty = 0;
    yellowStep = 5;
  }

  delay(30);
}
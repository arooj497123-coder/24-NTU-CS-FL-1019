// Week3-Lecture2
// Timer Interrupt (Internal)
// Embedded IoT System Fall-2026

// Name: xyz                  Reg#: 1234


#include <Arduino.h>

#define LED 4

hw_timer_t *My_timer = NULL;
// Creates a hardware timer pointer and sets it to NULL initially.
void ARDUINO_ISR_ATTR onTimer() {          // Defines the interrupt function that runs when the timer triggers.
  digitalWrite(LED, !digitalRead(LED));    // Toggles the LED state from ON to OFF or OFF to ON.
}

void setup() {             // Runs once when the ESP32 starts.
  pinMode(LED, OUTPUT);
// Sets the LED pin as an output.
  // 1 MHz timer tick (1 tick = 1 µs)
  My_timer = timerBegin(1000000);
// Creates a timer with a frequency of 1 MHz (1 tick = 1 microsecond).
  // attach ISR (new signature: no edge/level arg)
  timerAttachInterrupt(My_timer, &onTimer);
// Connects the timer interrupt to the onTimer function.
  // call ISR every 1,000,000 µs; autoreload=true; unlimited reloads (0)
  timerAlarm(My_timer, 1000000, true, 0);   // Triggers the interrupt every 1,000,000 microseconds (1 second) repeatedly.
}
void loop() {
  // nothing needed, all handled by interrupts
}
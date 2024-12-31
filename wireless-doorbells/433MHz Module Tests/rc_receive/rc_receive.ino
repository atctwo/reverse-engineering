/**
 * @file rc_receive.ino
 * @author alex barnes (atctwo)
 * @brief script to receive and parse wireless doorbells
 * @version 0.1
 * @date 2024-11-26
 * 
 * @copyright Copyright (c) 2024
 * 
 * Made for Queen's University Belfast Amateur Radio Society (QUB_ARES)!
 * 
 * This script listents for a signal transmitted by things like wireless doorbells
 * and switches, usually transmitted over 433.92 MHz.  It tries to parse the
 * signals to determine their format and contents.
 * 
 * This script uses rc-switch, and is basically identical to the advanced
 * receive demo: https://github.com/sui77/rc-switch/tree/master/examples/ReceiveDemo_Advanced
 * 
 * LED_PIN will get pulled high when no signal is received, and low when a signal
 * is received.  In other words, if an LED is connected it will usually be on, and will
 * briefly turn off when a signal is received.
 */

#include <RCSwitch.h>

#define LED_PIN 25
#define RX_PIN 21
RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(115200);
  RCSwitch::Protocol proto = {35, {1, 26}, {1, 3}, {3, 1}, false};
  mySwitch.setProtocol(proto);
  mySwitch.enableReceive(digitalPinToInterrupt(RX_PIN));  // Receiver on interrupt 0 => that is pin #2
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  if (mySwitch.available()) {
    
    digitalWrite(LED_PIN, LOW);
    output(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(),mySwitch.getReceivedProtocol());
    mySwitch.resetAvailable();
    
  }
  else {
    digitalWrite(LED_PIN, HIGH);
  }
}
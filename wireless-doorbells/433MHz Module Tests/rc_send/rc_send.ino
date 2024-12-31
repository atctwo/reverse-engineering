/**
 * @file rc_send.ino
 * @author alex barnes (atctwo)
 * @brief script to spoof wireless doorbells
 * @version 0.1
 * @date 2024-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
 * Made for Queen's University Belfast Amateur Radio Society (QUB_ARES)!
 * 
 * This script just transmits some signal when a condition _becomes_ true, and
 * optionally when it _becomes_ false.  That is, stuff will only happen when the
 * condition state changes.
 * 
 * The condition is usually something like a pin connected to a button going high,
 * but it could be anything.  Because this script was tested using a RPi Pico,
 * the default condition is just the BOOTSEL object
 * 
 * The pin defined as LED_PIN will stay low when the condition is false, and will
 * go high when the condition is true.  If an LED is connected it will light up
 * when transmitting!
 * 
 * The only way I was able to get this working was by using a modified version of
 * the rc-switch library which transmits the sync pulse before the data sections,
 * rather than after.  Please refer to ../../rc-switch-modified/
 */

#include <RCSwitch.h>

#define LED_PIN 25              // pin for the status LED
#define TX_PIN  19              // pin to output the generated signal
#define CONDITION BOOTSEL       // expression that evaluates as true or false

#define PULSE_LEN 200           // time in microseconds for one pulse
#define TX_TRUE  7836460        // code to send when the condition becomes true
#define TX_FALSE 7836452        // code to send when the condition becomes false
#define TX_BITS  24             // number of bits in the message to send

RCSwitch mySwitch = RCSwitch();

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);

    mySwitch.setProtocol(1);  // make sure to call first since this overrides custom pulse length
    mySwitch.setPulseLength(PULSE_LEN);
    mySwitch.enableTransmit(TX_PIN);
}

bool pressed = false;
bool hello = false;
void loop() {

    if (CONDITION) {
        if (!pressed) {

            #ifdef TX_TRUE
                if (hello) {
                mySwitch.send(TX_TRUE, TX_BITS);
                hello = false;
                } else {
                  mySwitch.send(TX_FALSE, TX_BITS);
                  hello = true;
                }
            #endif
            pressed = true;
            digitalWrite(LED_PIN, 1);

        }
    } else {
        if (pressed) {

            #ifdef TX_FALSE
                // mySwitch.send(TX_FALSE, TX_BITS);
            #endif
            pressed = false;
            digitalWrite(LED_PIN, 0);

        }
    }
}

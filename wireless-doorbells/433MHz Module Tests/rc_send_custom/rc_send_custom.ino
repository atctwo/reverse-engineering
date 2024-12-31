/**
 * @file rc_send_custom.ino
 * @author alex barnes (atctwo)
 * @brief script to spoof wireless doorbells
 * @version 0.1
 * @date 2024-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
 * Made for Queen's University Belfast Amateur Radio Society (QUB_ARES)!
 * 
 * Modified version of rc_send.ino using a custom protocol definition
 *
 * This is for a doorbell with much smaller and tighter timings
 */

#include <RCSwitch.h>

#define LED_PIN 2               // pin for the status LED
#define TX_PIN  27              // pin to output the generated signal
#define CONDITION !digitalRead(0)       // expression that evaluates as true or false

#define PULSE_LEN 40           // time in microseconds for one pulse
#define TX_TRUE  13025585        // code to send when the condition becomes true
// #define TX_FALSE 7836452        // code to send when the condition becomes false
#define TX_BITS  24             // number of bits in the message to send

RCSwitch mySwitch = RCSwitch();

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    pinMode(0, INPUT);

    RCSwitch::Protocol proto = {35, {1, 26}, {1, 3}, {3, 1}, false};
    mySwitch.setProtocol(proto);
    mySwitch.enableTransmit(TX_PIN);
}

bool pressed = false;
void loop() {

    if (CONDITION) {
        if (!pressed) {

            #ifdef TX_TRUE
                mySwitch.send(TX_TRUE, TX_BITS);
            #endif
            pressed = true;
            digitalWrite(LED_PIN, 1);

        }
    } else {
        if (pressed) {

            #ifdef TX_FALSE
                mySwitch.send(TX_FALSE, TX_BITS);
            #endif
            pressed = false;
            digitalWrite(LED_PIN, 0);

        }
    }
}

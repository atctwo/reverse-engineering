/**
 * @file rh_send.ino
 * @author your name (you@domain.com)
 * @brief radiohead transmitter test
 * @version 0.1
 * @date 2024-11-26
 * 
 * @copyright Copyright (c) 2024
 * 
 * Made for Queen's University Belfast Amateur Radio Society (QUB_ARES)!
 * 
 * Just a little test script to transmit a string using Radiohead's ASK
 * format.
 * 
 * When CONDITION becomes true (rising edge), a message will be sent.
 * The pin LED_PIN is normally low, but will go high when CONDITION is true
 */

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

#define SPEED 2000
#define LED_PIN 25
#define RX_PIN 21
#define TX_PIN 19
#define PTT_PIN 20
#define PTT_INVERTED false

#define CONDITION BOOTSEL
#define TX_MSG "QUB_ARES"

RH_ASK driver(SPEED, RX_PIN, TX_PIN, PTT_PIN, PTT_INVERTED);
const char *msg = TX_MSG;
bool pressed = false;

void setup()
{
    Serial.begin(115200);
    Serial.println("QUB_ARES Radiohead transmitter");
    pinMode(LED_PIN, OUTPUT);

    delay(1000);

    if (!driver.init()) Serial.println("init failed");
}

void loop()
{
    
    if (CONDITION) {
        if (!pressed) {

            Serial.printf("Sending \"%s\"...\n", msg);
            driver.send((uint8_t *)msg, strlen(msg));
            driver.waitPacketSent();

            pressed = true;
            digitalWrite(LED_PIN, 1);

        }
    } else {
        if (pressed) {

            pressed = false;
            digitalWrite(LED_PIN, 0);

        }
    }

}

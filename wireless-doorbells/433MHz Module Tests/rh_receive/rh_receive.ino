/**
 * @file rh_send.ino
 * @author your name (you@domain.com)
 * @brief radiohead receiver test
 * @version 0.1
 * @date 2024-11-26
 * 
 * @copyright Copyright (c) 2024
 * 
 * Made for Queen's University Belfast Amateur Radio Society (QUB_ARES)!
 * 
 * Just a little test script to receive a string using Radiohead's ASK
 * format.
 * 
 * The pin LED_PIN is normally low but will go high briefly when a
 * signal is received.
 * 
 * Includes code from the ask_receiver.ino example:
 * https://www.airspayce.com/mikem/arduino/RadioHead/ask_receiver_8ino-example.html
 */

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

#define SPEED 2000
#define LED_PIN 25
#define RX_PIN 21
#define TX_PIN 19
#define PTT_PIN 20
#define PTT_INVERTED false

RH_ASK driver(SPEED, RX_PIN, TX_PIN, PTT_PIN, PTT_INVERTED);

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println("QUB_ARES Radiohead transmitter");
    pinMode(LED_PIN, OUTPUT);

    if (!driver.init()) Serial.println("Radiohead init failed");
}

void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);
 
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
        // Message with a good checksum received, dump it.
        digitalWrite(LED_PIN, 1);

        Serial.printf("Received: \"");
        Serial.write(buf, buflen);
        Serial.printf("\", hex: ");
        for (int i = 0; i < buflen; i++) { Serial.printf("%02x ", buf[i]); }
        Serial.println("");

        delay(250);
        digitalWrite(LED_PIN, 0);
    }
}

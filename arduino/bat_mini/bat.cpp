/*!
 * @file bat.cpp
    ____  _____      _    ____    _  ___     ____ ____
   |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___|
   | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \
   | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
   |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/


   Author : e @p0lr_ @mzbat @theDevilsVoice @dead10c5
   Date   : May 29, 2018
   Version: 0.3
 * 
 * https://www.arduino.cc/en/Tutorial/ArduinoISP
 * Board: Attiny 24/44/84
 * Processor: ATtiny84
 * Clock: Internal 1MHz
 * Programmer: arduino as ISP
 */

#include "bat.h"


/*
 * Pulse the Internal LED
 */
void MyBat::led_breath() {
     //ramp increasing intensity, Inhalation: 
  for (int i=1;i<BRIGHT;i++){
    digitalWrite(left_eye, LOW);
    digitalWrite(right_eye, LOW);          // turn the LED on.
    delayMicroseconds(i*10);                 // wait
    digitalWrite(right_eye, HIGH);         // turn the LED off.
    digitalWrite(left_eye, HIGH);
    delayMicroseconds(PULSE-i*10);           // wait
    delay(0);                                //to prevent watchdog firing.
  }
}


void MyBat::led_half_breath() {
  //ramp decreasing intensity, Exhalation (half time):
  for (int i=BRIGHT-1;i>0;i--){
    digitalWrite(left_eye, LOW);          // turn the LED on.
    digitalWrite(right_eye, LOW);
    delayMicroseconds(i*10);          // wait
    digitalWrite(left_eye, HIGH);         // turn the LED off.
    digitalWrite(right_eye, HIGH);
    delayMicroseconds(PULSE-i*10);  // wait
    i--;
    delay(0);                        //to prevent watchdog firing.
  }
  delay(REST);                       //take a rest...
}

/* Converts a color from HSV to RGB.
 * h is hue, as a number between 0 and 360.
 * s is the saturation, as a number between 0 and 255.
 * v is the value, as a number between 0 and 255. */
rgb_color MyBat::hsvToRgb(uint16_t h, uint8_t s, uint8_t v)
{
    uint8_t f = (h % 60) * 255 / 60;
    uint8_t p = (255 - s) * (uint16_t)v / 255;
    uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t r = 0, g = 0, b = 0;
    switch((h / 60) % 6){
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
    }
    return rgb_color(r, g, b);
}

/**
 * @file main.ino
 * @author Jorge A. Macias Z
 * @brief  LED Blinking
 * @version 0.1
 * @date 2022-09-04
 *
 * @copyright Copyright (c) 2022
 *
 */

const int LEDPIN = 5;

void setup()
{
    pinMode(LEDPIN, HIGH);
}

void loop()
{
    digitalWrite(LEDPIN, HIGH);
    delay(500);
    digitalWrite(LEDPIN, LOW);
    delay(500);
}
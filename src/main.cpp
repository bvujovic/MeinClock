//* Mein Clock (display)
//* Testing buttons without ClickButton.h

// TODO Napraviti klasu koja ce sadrzati podatke o jednom tasteru: buttonState, lastButtonState, msLastDebounce
// TODO U tu klasu dodati metodu koja radi ono sto je sada u loop-u
// TODO Testirati da li se ovakvo koriscenje tastera tj. pinova slaze sa radom sa displejem

#include <Arduino.h>

#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_64X48_ER_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE); // EastRising 0.66" OLED breakout board, Uno: A4=SDA, A5=SCL, 5V powered

//! pinovi D5, D6 i D7 se mogu koristiti sa INPUT_PULLUP
const int pinBtnCenter = D6;
const int pinLed = LED_BUILTIN;

int ledState = LOW;        // the current state of the output pin
int buttonState;           // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin

ulong msLastDebounce = 0; // the last time the output pin was toggled
ulong itvDebounce = 50;   // the debounce time; increase if the output flickers

void ledOn(bool on) { digitalWrite(pinLed, !on); }

void setup()
{
  pinMode(pinBtnCenter, INPUT_PULLUP);
  pinMode(pinLed, OUTPUT);

  ledOn(ledState);
}

void loop()
{
  int reading = digitalRead(pinBtnCenter);
  if (reading != lastButtonState)
    msLastDebounce = millis();

  if ((millis() - msLastDebounce) > itvDebounce)
  {
    if (reading != buttonState)
    {
      buttonState = reading;
      if (buttonState == LOW)
        ledState = !ledState;
    }
  }
  ledOn(ledState);
  lastButtonState = reading;
}

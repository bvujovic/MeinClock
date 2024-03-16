//* Mein Clock

// TODO U Btn klasu dodati mogucnost za dupli ili dugi klik (ili obe mogucnosti)

#include <Arduino.h>

#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_SSD1306_64X48_ER_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE); // EastRising 0.66" OLED breakout board, Uno: A4=SDA, A5=SCL, 5V powered

const int pinLed = LED_BUILTIN;

#include "Btn.h"
Btn btnLeft(D5);
Btn btnCenter(D6);
Btn btnRight(D7);

void ledOn(bool on) { digitalWrite(pinLed, !on); }

void setup()
{
  Serial.begin(115200);
  pinMode(pinLed, OUTPUT);
  ledOn(false);
  u8g2.begin();
  u8g2.setFont(u8g2_font_logisoso24_tn);
}

int i = 0;

void loop()
{
  delay(10);
  // ulong ms = millis();

  // if (btnLeft.check(ms))
  //   Serial.println("btnLeft");
  // if (btnCenter.check(ms))
  //   Serial.println("btnCenter");
  // if (btnRight.check(ms))
  //   Serial.println("btnRight");

  char m_str[3];
  strcpy(m_str, u8x8_u8toa(i++, 2));
  u8g2.firstPage();
  do
  {
    u8g2.drawStr(0, 40, "02");
    u8g2.drawStr(29, 40, ":");
    u8g2.drawStr(35, 40, m_str);
  } while (u8g2.nextPage());

  delay(1000);
}

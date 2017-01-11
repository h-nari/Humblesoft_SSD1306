#include <Adafruit_GFX.h>
#include <Fontx.h>
#include <FsFontx.h>
#include <Humblesoft_GFX.h>
#include <Humblesoft_SSD1306.h>

#define OLED_DC		15
#define OLED_RESET	16	
#define OLED_CS		 2

#include <fontx/ILGH16XB.h>
#include <fontx/ILGZ16XB.h>

Humblesoft_SSD1306 oled(OLED_DC, OLED_RESET, OLED_CS);
RomFontx fontx(ILGH16XB,ILGZ16XB);

void setup()
{
  Serial.begin(115200);
  delay(100);
  Serial.println("\n\nReset:");

  oled.begin();
  oled.clear();
  oled.setTextWrap(false);
  oled.setRotation(2);
  oled.setFont(&fontx);
  oled.println("漢字 Kanji");
  oled.setTextSize(2);
  oled.println("表示可能");
  oled.setFont();
  oled.setTextSize(1);
  oled.println("Default Font");
  oled.println("kanjiDisp");
  oled.display();
}

void loop()
{
}

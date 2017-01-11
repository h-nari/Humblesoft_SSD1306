#include "conf.h"

#if USE_OTA
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "ota_util.h"
#endif

#include <Adafruit_GFX.h>
#include <Fontx.h>
#include <FsFontx.h>
#include <Humblesoft_GFX.h>
#include <Humblesoft_SSD1306.h>

#define OLED_DC		15
#define OLED_RESET	16	
#define OLED_CS		 2

Humblesoft_SSD1306 oled(OLED_DC, OLED_RESET, OLED_CS);
FsFontx fontx("/ILGH16XB.FNT","/ILGZ16XB.FNT");

void setup()
{
  Serial.begin(115200);
  delay(100);
  Serial.println("\n\nReset:");

  if(!SPIFFS.begin())
    Serial.println("SPIFFS.begin() failed.");

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
  oled.println("kanjiDisp_SPIFFS_OTA");
  oled.display();

#if USE_OTA
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }
  Serial.println();
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  static int8_t ota_col;
  ota_init();
#endif
}

void loop()
{
#if USE_OTA
  ArduinoOTA.handle();
#endif
}

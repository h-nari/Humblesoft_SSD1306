#include <Adafruit_GFX.h>
#include <Fontx.h>
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
  oled.setCursor(0,0);
  oled.setTextSize(1);

  oled.setRotation(2);
  oled.setTextWrap(false);
  oled.setFont();
  oled.setTextSize(2);
  oled.print("128 x 64\n");
  oled.setTextSize(1);
  
  for(int c = 0x20;c<0x7f;c+=0x10){
    for(int i=0;i<16;i++)
      oled.print((char)(c+i));
    oled.println();
  }

  oled.setCursor(0,0);
  oled.setFont(&fontx);
  int x = oled.width() - 16;
  int y = 0;
  char *ss[] = {"漢","字","表","示",NULL};
  for(char **p=ss; *p; p++){
    oled.setCursor(x,y);
    oled.print(*p);
    y += 16;
  }
  oled.display();
}

void loop()
{
}

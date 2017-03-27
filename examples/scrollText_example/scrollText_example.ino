#include <Adafruit_GFX.h>		
#include <Fontx.h>			/* https://github.com/h-nari/Fontx */
#include <Humblesoft_GFX.h>		/* https://github.com/h-nari/FontxGfx */
#include <Humblesoft_SSD1306.h>		/* https://github.com/h-nari/Humblesoft_SSD1306 */
#include <ScrollText.h>			/* included in Humblesoft_SSD1306 */
#include <fontx/ILGH16XB.h>		/* included in Fontx */
#include <fontx/ILGZ16XB.h>		/* included in Fontx */

#define OLED_DC		15
#define OLED_RESET	16	
#define OLED_CS		 2

RomFontx fontx(ILGH16XB,ILGZ16XB);
Humblesoft_SSD1306 oled(OLED_DC, OLED_RESET, OLED_CS);
ScrollText scroll(&oled);

void setup()
{
  Serial.begin(115200);
  delay(100);
  Serial.println("\n\nReset:");

  oled.setTextSize(2);
  oled.begin();
  oled.clear();
  oled.display();

  scroll.setSpeed(32.0f);	/* scroll speed 32dot per sec */ 
  scroll.setTextSize(2);
  scroll.setFont(&fontx);
  scroll.setScrollArea(0,32,128,32);
  scroll.setPos();		/* set y-offset for valign center */ 
}

float speeds[] = { 60, 120, 240, 480};

void loop()
{
  static uint8_t i;

  if(!scroll.update()){
    if(i >= sizeof(speeds)/sizeof(speeds[0])) i = 0;
    oled.fillScreen(0);
    oled.posPrintf(0,0,"%d dps", (int)speeds[i]);
    oled.display();
    scroll.setSpeed(speeds[i++]);
    scroll.print("漢字 ABCDEFG");
    scroll.scrollOut();
  }
}

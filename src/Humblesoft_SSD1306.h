#ifndef _humblesoft_ssd1306_h_
#define _humblesoft_ssd1306_h_

#include <Arduino.h>
#include <Humblesoft_GFX.h>

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64
#define SSD1306_BUF_SIZE (SSD1306_WIDTH / 8 * SSD1306_HEIGHT)

class Humblesoft_SSD1306 : public Humblesoft_GFX {
 public:
  enum COLOR { BLACK, WHITE, INVERT };
 protected:
  int8_t m_cs;
  int8_t m_dc;
  int8_t m_rst;
  bool m_modified;
  unsigned long m_tModified;
  unsigned long m_timeout;
  uint8_t m_imgBuf[SSD1306_BUF_SIZE];

 public:
  Humblesoft_SSD1306(int8_t dc=15, int8_t rst=-1, int8_t cs=2);
  uint16_t rgb(uint8_t r, uint8_t g, uint8_t b) override {
    return (r == 0 && g == 0 && b == 0) ? BLACK : WHITE;
  }
  void clear() { memset(m_imgBuf, 0, SSD1306_BUF_SIZE);}
  void clearDisplay() { clear();}
  bool modified() { return m_modified;}
  void begin(bool reset=true);
  void drawPixel(int16_t x, int16_t y, uint16_t color) override;
#if 0
  void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) override;
  void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) override;
#endif
  void setContrast(uint8_t v);
  void display(uint8_t c0 = 0, uint8_t c1 = SSD1306_WIDTH-1,
	       uint8_t p0 = 0, uint8_t p1 = SSD1306_HEIGHT/8-1,
	       const uint8_t *buf = NULL);
  void update();
  void writeData(uint8_t *data, uint32_t data_len);
  
 protected:
  void writeCmd(uint8_t cmd);
};


#endif /* _humblesoft_ssd1306_h_ */

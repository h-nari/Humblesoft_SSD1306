#ifndef _scroll_text_h_
#define _scroll_text_h_

#include <Humblesoft_SSD1306.h>
#include <Bitmap.h>

#ifndef SC_IMAGE_WIDTH 
#define SC_IMAGE_WIDTH 64
#endif
#ifndef SC_IMAGE_HEIGHT
#define SC_IMAGE_HEIGHT 64
#endif

class ScrollText : public Print {
 protected:
  Humblesoft_SSD1306 *m_oled;
  String 	m_str;
  Bitmap 	m_bitmap;
  uint8_t 	m_ri;		// bitmap read index
  uint8_t	m_gw;		// glyph width
  uint8_t	m_gh;		// glyph height
  uint8_t	m_oy;		// y offset
  int16_t	m_scx;		// scroll area x
  int16_t	m_scy;		// scroll area y
  uint16_t	m_scw;		// scroll area w
  uint16_t	m_sch;		// scroll area h
  int16_t	m_xi;		// draw position
  uint16_t	m_cBlank;	// output blank line
  uint16_t	m_cText;	// text color
  uint16_t	m_cBg;		// backgound color
  unsigned long m_tUpdate;
  unsigned long m_period;
  float		m_dotPerSec;

 public:
  ScrollText(Humblesoft_SSD1306 *oled);
  size_t write(uint8_t) override;
  bool update();
  void clear(int16_t x=0);
  void setScrollArea(int16_t x, int16_t y, uint16_t w, uint16_t h);
  void setWritePosition(int16_t x);
  void setTextSize(uint8_t s) { m_bitmap.setTextSize(s);}
  void setFont(const GFXfont *f = NULL) {m_bitmap.setFont(f);}
  void setFont(Fontx *fontx) {m_bitmap.setFont(fontx);}
  void setPos();
  void setPos(int8_t oy);
  void setTextColor(uint16_t color);
  void scrollOut(int16_t count=0);
  float setSpeed(float dotPerSec);
  
 protected:
  bool get_a_char(char *buf, size_t buf_len);
};

#endif /* _scroll_text_h_ */

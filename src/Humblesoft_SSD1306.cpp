#include <Humblesoft_SSD1306.h>
#include <SPI.h>

Humblesoft_SSD1306::Humblesoft_SSD1306(int8_t dc, int8_t rst, int8_t cs) :
  Humblesoft_GFX(SSD1306_WIDTH, SSD1306_HEIGHT)
{
  m_cs  = cs;
  m_dc  = dc;
  m_rst = rst;
  setTextColor(WHITE);
  m_timeout = 10;		/* ms */
}

void Humblesoft_SSD1306::writeCmd(uint8_t cmd)
{
  digitalWrite(m_dc, LOW);
  digitalWrite(m_cs, LOW);
  SPI.transfer(cmd);
  digitalWrite(m_cs, HIGH);
}

void Humblesoft_SSD1306::begin(bool reset)
{
  pinMode(m_dc, OUTPUT);
  pinMode(m_cs, OUTPUT);
  pinMode(m_cs, HIGH);
  SPI.begin();
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));

  if(reset && reset >= 0) {
    pinMode(m_rst, OUTPUT);
    digitalWrite(m_rst, HIGH);
    delay(1);
    digitalWrite(m_rst, LOW);
    delay(10);
    digitalWrite(m_rst, HIGH);
  }

  writeCmd(0xae); 		// Set Display OFF
  writeCmd(0xd5);		// set display clock div
  writeCmd(0x80);
  writeCmd(0xa8);		// set multiplex
  writeCmd(SSD1306_HEIGHT-1);
  writeCmd(0xd3);		// set display offset;
  writeCmd(0);
  writeCmd(0x40);		// set start line, 0
  writeCmd(0x8d); 		// set charge pump enable
  writeCmd(0x14); 		// charge pump ON
  writeCmd(0x20);		// set memory mode
  writeCmd(0);			// page mode
  writeCmd(0xa0 | 1);		// seg remap
  writeCmd(0xc8);		// com scan dec
  writeCmd(0xda);		// set comp pins
  writeCmd(0x12);
  setContrast(0xcf);
  writeCmd(0xd9);		// set pre charge
  writeCmd(0xf1);
  writeCmd(0xdb);		// set vcom detect
  writeCmd(0x40);
  writeCmd(0xa4);		// display all on resume
  writeCmd(0xa6);		// normal display
  writeCmd(0x2e); 		//Deactivate scroll
  writeCmd(0xaf); 		//Entire display ON
}

void Humblesoft_SSD1306::setContrast(uint8_t v)
{
  writeCmd(0x81);
  writeCmd(v);
}

void Humblesoft_SSD1306::drawPixel(int16_t x0, int16_t y0, uint16_t color)
{
  if(x0 < 0 || x0 >= width() || y0 < 0 || y0 >= height())
    return;

  int16_t x, y;
  switch(getRotation() & 3){
  default:
    x = x0;
    y = y0;
    break;
  case 1:
    x = SSD1306_WIDTH - y0 - 1;
    y = x0;
    break;
  case 2:
    x = SSD1306_WIDTH  - x0 - 1;
    y = SSD1306_HEIGHT - y0 - 1;
    break;
  case 3:
    x = y0;
    y = SSD1306_HEIGHT - x0 - 1;
    break;
  }
  
  uint8_t m = 1 << (y & 7);
  if(color == WHITE) 
    m_imgBuf[x + y / 8 * SSD1306_WIDTH] |= m;
  else if(color == BLACK)
    m_imgBuf[x + y / 8 * SSD1306_WIDTH] &= ~m;
  else
    m_imgBuf[x + y / 8 * SSD1306_WIDTH] ^= m;
  
  if(!m_modified){
    m_modified = true;
    m_tModified = millis();
  }
}


void Humblesoft_SSD1306::display(uint8_t c0, uint8_t c1, uint8_t p0, uint8_t p1,
				 const uint8_t *buf)
{
  if(!buf) buf = m_imgBuf;
  
  writeCmd(0x21);		// set colum addr
  writeCmd(c0);
  writeCmd(c1);
  writeCmd(0x22);		// set page addr
  writeCmd(p0);
  writeCmd(p1);

  digitalWrite(m_dc, HIGH);
  digitalWrite(m_cs, LOW);
  for(uint8_t p=p0; p <= p1; p++){
    const uint8_t *b = buf + p * SSD1306_WIDTH + c0;
    for(uint8_t c=c0; c<=c1; c++)
      SPI.transfer(*b++);
  }
  digitalWrite(m_cs, HIGH);
  m_modified = false;
}

void Humblesoft_SSD1306::update()
{
  if(m_modified && millis() - m_tModified > m_timeout)
    display();
}

void Humblesoft_SSD1306::writeData(uint8_t *data, uint32_t data_len)
{
  uint8_t c0 = 0;
  uint8_t c1 = SSD1306_WIDTH-1;
  uint8_t p0 = 0;
  uint8_t p1 = SSD1306_HEIGHT/8-1;
  
  writeCmd(0x21);		// set colum addr
  writeCmd(c0);
  writeCmd(c1);
  writeCmd(0x22);		// set page addr
  writeCmd(p0);
  writeCmd(p1);
  digitalWrite(m_dc, HIGH);
  digitalWrite(m_cs, LOW);
  SPI.writeBytes(data, data_len);
  digitalWrite(m_cs, HIGH);
}


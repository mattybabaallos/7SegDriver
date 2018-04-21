

#ifndef SEG_H
#define SEG_H

#include <Arduino.h>
#include <SPI.h>
#include <inttypes.h>
#include <errno.h>

#define INTENSITY_REG 0x0A
#define SCANLIMIT_REG 0x0B
#define SHUTDOWN_REG 0x0C
#define DECODE_REG 0x09

#define DEFAULT_INTENSITY 0x0F	//Full intensity
#define DEFAULT_NUM_DIGITS 0x07 //All digits
#define DEFAULT_CS_PINT 0x02		//Pin 2


class sev_seg
{
public:
	sev_seg();
	sev_seg(uint cs_pin);
	int set_intensity(uint intensity);
	int set_segments(uint segments);
	int set_num_digits(uint digit);
	int display(int num);
	int display(uint digit, uint num);
  void all_off();

private:
	void write_out(uint reg, uint val);
	void set_spi();
	void init();
	uint m_cs_pin;
	uint m_intensity;
	uint m_num_digits;
};

#endif /* SEG_H */

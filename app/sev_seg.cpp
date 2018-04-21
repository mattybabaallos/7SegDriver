
#include "sev_seg.h"

sev_seg::sev_seg() : m_cs_pin(DEFAULT_CS_PINT), m_intensity(m_intensity),
								 m_num_digits(DEFAULT_NUM_DIGITS)
{
	set_spi();
	write_out(SHUTDOWN_REG,0x01); //Exit shutdown mode;
	write_out(DECODE_REG,0xFF); //Code B decode for digits 7–0
	write_out(INTENSITY_REG,m_intensity); //set intensity
	write_out(SCANLIMIT_REG,m_num_digits); //set number of digits to light
}

sev_seg::sev_seg(uint cs_pin) : m_cs_pin(cs_pin), m_intensity(m_intensity),
											m_num_digits(DEFAULT_NUM_DIGITS)
{
	set_spi();
	write_out(SHUTDOWN_REG,0x01); //Exit shutdown mode;
	write_out(DECODE_REG,0xFF); //Code B decode for digits 7–0
	write_out(INTENSITY_REG,m_intensity); //set intensity
	write_out(SCANLIMIT_REG,m_num_digits); //set number of digits to light
}

int sev_seg::set_intensity(uint intensity)
{
	if (intensity > 0xF)
		return EINVAL;
	m_intensity = intensity;
	write_out(INTENSITY_REG, m_intensity);
	return 0;
}

int sev_seg::set_num_digits(uint digits)
{
	if (digits > 0x7)
		return EINVAL;
	m_num_digits = digits;
	return 0;
}

void sev_seg::write_out(uint reg, uint val)
{
	digitalWrite(m_cs_pin, LOW);
	SPI.transfer(reg);
	SPI.transfer(val);
	digitalWrite(m_cs_pin, HIGH);
}

void sev_seg::set_spi()
{
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);

  digitalWrite(m_cs_pin, HIGH);
  pinMode(m_cs_pin, OUTPUT);
  SPI.begin();
}

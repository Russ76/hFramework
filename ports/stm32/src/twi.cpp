#include <hFramework.h>
#include <twi.h>
#include <stdint.h>

void twi_init(void) {
	TWI_P.setDataRate(TWI_FREQ);
}

void twi_disable(void) {
  #ifdef I2C
	TWI_P.pinScl.setOutOD();
	TWI_P.pinSda.setOutOD();
  #endif
}

uint8_t I2C_ADDR = 0;
void twi_setAddress(uint8_t adress)
{
	I2C_ADDR = adress;
}

void twi_setFrequency(uint32_t freq) {
	TWI_P.setDataRate(freq);
}

uint8_t twi_readFrom(uint8_t adress, uint8_t* data, uint8_t length, uint8_t sendStop)
{
	if(TWI_P.read(adress, data, length))
		return  length;
	return 0;
}

uint8_t twi_writeTo(uint8_t address, uint8_t* data, uint8_t length, uint8_t wait, uint8_t sendStop)
{
	if(TWI_P.write(address, data, length))
		return 0;
	return 4;
}

uint8_t twi_transmit(uint8_t* data, uint8_t length)
{
	return twi_writeTo(I2C_ADDR, data, length, 0, 0);
}

void twi_attachSlaveRxEvent(void (*)(uint8_t*, int)) {}
void twi_attachSlaveTxEvent(void (*)(void)) {}

void twi_reply(uint8_t data) {} //TODO:

void twi_stop(void)
{
  #ifdef I2C
	TWI.pinScl.write(false);
	TWI.pinSda.write(false);
	TWI.pinScl.write(true);
	TWI.pinSda.write(true);
  #endif
}

void twi_releaseBus(void) {}

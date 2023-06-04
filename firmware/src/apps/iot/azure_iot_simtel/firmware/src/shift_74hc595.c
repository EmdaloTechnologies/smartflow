/*
 * shift_74hc595.c
 *
 * Created: 27/02/2020 10:31:32
 *  Author: adam
 */ 

#include "shift_74hc595.h"
#include "smartflow_pins.h"
#include "d51_pins.h"
#include "tx_api.h"

uint32_t OutputBits_74HCT595 = 0x00000000;

#define FAST_PIN_DS_PORT					1
#define FAST_PIN_SH_CP_PORT					1
#define FAST_PIN_ST_CP_PORT					1

#define FAST_PIN_DS_BIT						12
#define FAST_PIN_SH_CP_BIT					13
#define FAST_PIN_ST_CP_BIT					14

uint32_t outputBits;
uint32_t pinDS;
uint32_t pinSH_CP;
uint32_t pinST_CP;

void Fast_Port_Pin(int port, int pin, int state)
{
	if (state)
		PORT_REGS->GROUP[port].PORT_OUTSET = (1 << pin);
	else
		PORT_REGS->GROUP[port].PORT_OUTCLR = (1 << pin);
}

void Fast_Port_FAST_PIN_Init(int port, int pin, int dir)
{
	if (dir)
		PORT_REGS->GROUP[port].PORT_DIRSET = (1 << pin); // 1 for output
	else
		PORT_REGS->GROUP[port].PORT_DIRCLR = (1 << pin);
}

void cd74hc595_shift_data(void)
{
	// q0 is first flip flop in the chain so we must end with bit 0 done last
	uint32_t temp_value = outputBits;
	int temp_bit;
	
	for (int x = 0; x < 32; x++)
	{
		if ((temp_value & 0x80000000) == 0x80000000)
			temp_bit = 1;
		else
			temp_bit = 0;
		
		Fast_Port_Pin(FAST_PIN_DS_PORT, FAST_PIN_DS_BIT, temp_bit);
		
		Fast_Port_Pin(FAST_PIN_SH_CP_PORT, FAST_PIN_SH_CP_BIT, 1);
		temp_value <<= 1;
		Fast_Port_Pin(FAST_PIN_SH_CP_PORT, FAST_PIN_SH_CP_BIT, 0);
	}
	
	Fast_Port_Pin(FAST_PIN_ST_CP_PORT, FAST_PIN_ST_CP_BIT, 1);
	Fast_Port_Pin(FAST_PIN_ST_CP_PORT, FAST_PIN_ST_CP_BIT, 0);
}

void cd74hc595_update(uint32_t value)
{
    outputBits = value;
}

void cd74hc595_output_on(uint32_t mask)
{
    outputBits |= mask;
}

void cd74hc595_output_off(uint32_t mask)
{
    outputBits &= ~mask;
}

void cd74hc595_setup(void)
{
    pinMode(PIN_OUTPUTS_OE, OUTPUT);
    digitalWrite(PIN_OUTPUTS_OE, LOW);
    
    /* cd74hc595_output_on(SO_LED_GSM_R |
        SO_LED_GSM_G | SO_LED_GSM_B |
        SO_LED_REMOTE_R | SO_LED_REMOTE_G |
        SO_LED_REMOTE_B | SO_LED_MAIN_BOTTOM |
        SO_LED_MAIN_TOP | SO_LED_MAIN_LEFT |
        SO_LED_MAIN_RIGHT | SO_LED_VALVE_1 |
        SO_LED_VALVE_2 | SO_LED_VALVE_3 |
        SO_LED_VALVE_4 | SO_LED_VALVE_5); */
    
    cd74hc595_shift_data();
    
    tx_thread_sleep(100);
}

void cd74hc595_init(uint32_t _pinDS, uint32_t _pinSH_CP, uint32_t _pinST_CP)
{
    pinDS = _pinDS;
    pinSH_CP = _pinSH_CP;
    pinST_CP = _pinST_CP;
    
    pinMode(pinDS, OUTPUT);
    pinMode(pinSH_CP, OUTPUT);
    pinMode(pinST_CP, OUTPUT);
    
    outputBits = 0;
    cd74hc595_shift_data();
}
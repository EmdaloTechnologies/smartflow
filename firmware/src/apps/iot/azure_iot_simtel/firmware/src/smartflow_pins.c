/*
 * Created: 26/02/2020 18:24:43
 *  Author: adam
 */ 

#include "smartflow_pins.h"
#include "d51_pins.h"
#include "definitions.h"

static const PinDescription pinDescription[] =
{
	// 0..13 - Digital pins
	// 0/1 - SERCOM/UART (Serial1)
	{ PORTA, 23, PIO_SERCOM, PIN_ATTR_PWM_G, No_ADC_Channel, TCC0_CH3, TC4_CH1, EXTERNAL_INT_7 }, // RX: SERCOM3/PAD[1] / 0
	{ PORTA, 22, PIO_SERCOM, PIN_ATTR_PWM_G, No_ADC_Channel, TCC0_CH2, TC4_CH0, EXTERNAL_INT_6 }, // TX: SERCOM3/PAD[0] / 1
	{ PORTB, 17, PIO_DIGITAL, PIN_ATTR_PWM_G, No_ADC_Channel, TCC0_CH5, NOT_ON_TIMER,  EXTERNAL_INT_1 }, // 2
	{ PORTB, 16, PIO_DIGITAL, PIN_ATTR_PWM_G, No_ADC_Channel, TCC0_CH4, NOT_ON_TIMER, EXTERNAL_INT_0 }, // 3
	{ PORTB, 13, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC3_CH1, TC4_CH1, EXTERNAL_INT_13 }, // 4
	{ PORTB, 14, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC4_CH0, TC5_CH0, EXTERNAL_INT_14 }, // 5
	{ PORTB, 15, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC4_CH1, TC5_CH1, EXTERNAL_INT_15 }, // 6
	{ PORTB, 12, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC3_CH0, TC4_CH0, EXTERNAL_INT_12 }, // 7
	{ PORTA, 21, PIO_DIGITAL, PIN_ATTR_PWM_G, No_ADC_Channel, TCC0_CH1, NOT_ON_TIMER, EXTERNAL_INT_5 }, // 8
	{ PORTA, 20, PIO_DIGITAL, PIN_ATTR_PWM_G, No_ADC_Channel, TCC0_CH0, NOT_ON_TIMER, EXTERNAL_INT_4 }, // 9
	{ PORTA, 18, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH2, TC3_CH0, EXTERNAL_INT_2 }, // 10
	{ PORTA, 19, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH3, TC3_CH1, EXTERNAL_INT_3 }, // 11
	{ PORTA, 17, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH1, TC2_CH1, EXTERNAL_INT_1 }, // 12
	{ PORTA, 16, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH0, TC2_CH0, EXTERNAL_INT_0 }, // 13
	// 14..19 - Analog pins
	{ PORTA,  2, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 }, // 14
	//{ PORTA,  5, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel5, NOT_ON_PWM, TC0_CH1, EXTERNAL_INT_5 }, // 15
    { PORTA,  5, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, NOT_AN_INTERRUPT }, // 15 RX    
	//{ PORTA,  6, PIO_ANALOG, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel6, TC1_CH0, TC1_CH0, EXTERNAL_INT_6 }, // 16
    { PORTA,  6, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, NOT_AN_INTERRUPT }, // 16	RTS    
	//{ PORTA,  4, PIO_ANALOG, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel4, TC0_CH0, TC0_CH0, EXTERNAL_INT_4 }, // 17
    { PORTA,  4, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, NOT_AN_INTERRUPT }, // 17 TX    
	{ PORTB,  8, PIO_ANALOG, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel2, TC4_CH0, TC4_CH0, EXTERNAL_INT_8 }, // 18
	{ PORTB,  9, PIO_ANALOG, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel3, TC4_CH1, TC4_CH1, EXTERNAL_INT_9 }, // 19
	// Extra Analog pins! 20..21
	{ PORTB,  2, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel14, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 }, // 20 same as sda
	{ PORTB,  3, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel15, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3 }, //21 same as scl
	// 22..23 I2C pins (SDA/SCL)
	{ PORTB,  2, PIO_SERCOM_ALT, PIN_ATTR_PWM_F, No_ADC_Channel, TCC2_CH2, NOT_ON_TIMER, EXTERNAL_INT_2 }, // 22 sda
	{ PORTB,  3, PIO_SERCOM_ALT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3 }, // 23 scl
	// 24..26 - SPI pins (ICSP:MISO,SCK,MOSI)
	{ PORTA, 14, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC3_CH0, TC3_CH0, EXTERNAL_INT_14 },
	{ PORTA, 13, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC2_CH1, TC2_CH1, EXTERNAL_INT_13 },
	{ PORTA, 12, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC2_CH0, TC2_CH0, EXTERNAL_INT_12 },
	// 27..28
	{ PORTB,  6, PIO_OUTPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6 }, // used as output only
	{ PORTA, 27, PIO_OUTPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11 }, // used as output only
	// 29..31
	{ PORTB,  7, PIO_COM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7 }, // USB Host enable
	{ PORTA, 24, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_8 }, // USB/DM
	{ PORTA, 25, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9 }, // USB/DP
	// 32..34
	{ PORTA, 18, PIO_SERCOM, PIO_SERCOM, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 }, //same as d10
	{ PORTA, 19, PIO_SERCOM, PIO_SERCOM, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3 }, //same as d11
	{ PORTA, 17, PIO_SERCOM, PIO_SERCOM, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1 }, //same as d12
	// 35
	{ PORTA, 16, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_0 }, //same as d10
	// 36
	{ PORTA,  3, PIO_ANALOG, PIN_ATTR_ANALOG, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3 }, // DAC/VREFP
	// 37..38
	{ PORTA,  2, PIO_ANALOG, PIN_ATTR_ANALOG, DAC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 }, // DAC/VOUT[0]
	//{ PORTA,  5, PIO_ANALOG, PIN_ATTR_ANALOG, DAC_Channel1, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5 }, // DAC/VOUT[1]
    { PORTA,  5, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, NOT_AN_INTERRUPT }, // UART RX
	// 39
	{ PORTA, 16, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH0, TC2_CH0, EXTERNAL_INT_0 },
	{ PORTB, 22, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6 }, // used as output only
	// 41 - 46 QSPI (SCK, CS, IO0, IO1, IO2, IO3)
	{ PORTB, 10, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_10 },
	{ PORTB, 11, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11 },
	{ PORTA,  8, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NMI },
	{ PORTA,  9, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9 },
	{ PORTA, 10, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_10 },
	{ PORTA, 11, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11 },
	//{ PORTA,  7, PIO_DIGITAL, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, NOT_AN_INTERRUPT },	// 47
	{ PORTA,  7, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, NOT_AN_INTERRUPT }, // 56	CTS    
	{ PORTB,  4, PIO_DIGITAL, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, NOT_AN_INTERRUPT },	// 48
	{ PORTB,  5, PIO_DIGITAL, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, NOT_AN_INTERRUPT },	// 49
	{ PORTA, 15, PIO_DIGITAL, PIN_ATTR_PWM_E, No_ADC_Channel, TC3_CH1, TC3_CH1, EXTERNAL_INT_15 }, // 50
	{ PORTB, 23, PIO_DIGITAL, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, NOT_AN_INTERRUPT },	// 51
	{ PORTB, 31, PIO_DIGITAL, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, NOT_AN_INTERRUPT },	// 52
	{ PORTB,  0, PIO_DIGITAL, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, NOT_AN_INTERRUPT },	// 53
	{ PORTB,  1, PIO_DIGITAL, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, NOT_AN_INTERRUPT },	// 54
	{ PORTA,  4, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, NOT_AN_INTERRUPT }, // 55 PIN_SERIAL0_TX
	{ PORTA,  5, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, NOT_AN_INTERRUPT }, // 56	PIN_SERIAL0_RX
};

void pinMode(uint32_t pinIndex, uint32_t mode)
{
	uint32_t port = pinDescription[pinIndex].port;
	uint32_t pin = pinDescription[pinIndex].pin;
	uint32_t pinType = pinDescription[pinIndex].pinType;
	uint32_t pinMask = (1ul << pin);

	// Handle the case the pin isn't usable as PIO
	if (pinType == PIO_NOT_A_PIN)
		return ;

	// Set pin mode according to chapter '22.6.3 I/O Pin Configuration'
	switch (mode) {
	case INPUT:
		// Set pin to input mode
		PORT_REGS->GROUP[port].PORT_PINCFG[pin] = (uint8_t)(PORT_PINCFG_INEN_Msk);
		PORT_REGS->GROUP[port].PORT_DIRCLR = pinMask;
	break;

	case INPUT_PULLUP:
		// Set pin to input mode with pull-up resistor enabled
		PORT_REGS->GROUP[port].PORT_PINCFG[pin] = (uint8_t)(PORT_PINCFG_INEN_Msk | PORT_PINCFG_PULLEN_Msk);
		PORT_REGS->GROUP[port].PORT_DIRCLR = pinMask;

		// Enable pull level (cf '22.6.3.2 Input Configuration' and '22.8.7 Data Output Value Set')
		PORT_REGS->GROUP[port].PORT_OUTSET = pinMask;
	break;

	case INPUT_PULLDOWN:
		// Set pin to input mode with pull-down resistor enabled
		PORT_REGS->GROUP[port].PORT_PINCFG[pin] = (uint8_t)(PORT_PINCFG_INEN_Msk | PORT_PINCFG_PULLEN_Msk);
		PORT_REGS->GROUP[port].PORT_DIRCLR = pinMask;

		// Enable pull level (cf '22.6.3.2 Input Configuration' and '22.8.6 Data Output Value Clear')
		PORT_REGS->GROUP[port].PORT_OUTCLR = pinMask;
	break;

	case OUTPUT:
		// enable input, to support reading back values, with pullups disabled
		PORT_REGS->GROUP[port].PORT_PINCFG[pin] = (uint8_t)(PORT_PINCFG_INEN_Msk);

		// Set pin to output mode
		PORT_REGS->GROUP[port].PORT_DIRSET = pinMask;
	break;

	default:
		// do nothing
	break;
	}
}

int pinPeripheral(uint32_t pinIndex, PioType peripheral )
{
	volatile uint32_t port = pinDescription[pinIndex].port;
	volatile uint32_t pin = pinDescription[pinIndex].pin;
	volatile uint32_t pinType = pinDescription[pinIndex].pinType;

	// Handle the case the pin isn't usable as PIO
	if (pinType == PIO_NOT_A_PIN)
		return -1 ;

	switch (peripheral) {
	case PIO_DIGITAL:
	break;

	case PIO_INPUT:
		pinMode(pinIndex, INPUT);
	break;

	case PIO_INPUT_PULLUP:
		pinMode(pinIndex, INPUT_PULLUP);
	break;

	case PIO_OUTPUT:
		pinMode(pinIndex, OUTPUT) ;
	break ;

	case PIO_ANALOG:
	case PIO_SERCOM:
	case PIO_SERCOM_ALT:
	case PIO_TIMER:
	case PIO_TIMER_ALT:
	case PIO_EXTINT:
	#if defined(__SAMD51__)
	case PIO_TCC_PDEC:
	case PIO_COM:
	case PIO_SDHC:
	case PIO_I2S:
	case PIO_PCC:
	case PIO_GMAC:
	case PIO_AC_CLK:
	case PIO_CCL:
	#else
	case PIO_COM:
	case PIO_AC_CLK:
	#endif
		if (pin & 1) // is pin odd?
		{
			volatile uint32_t temp ;

			temp = (PORT_REGS->GROUP[port].PORT_PMUX[pin >> 1]) & PORT_PMUX_PMUXE(0xf);
			// Set new muxing
			PORT_REGS->GROUP[port].PORT_PMUX[pin >> 1] = temp | PORT_PMUX_PMUXO(peripheral);
			// Enable port mux
			PORT_REGS->GROUP[port].PORT_PINCFG[pin] |= PORT_PINCFG_PMUXEN_Msk | PORT_PINCFG_DRVSTR_Msk;
		}
		else // even pin
		{
			uint32_t temp ;

			temp = (PORT_REGS->GROUP[port].PORT_PMUX[pin >> 1]) & PORT_PMUX_PMUXO(0xf);
			PORT_REGS->GROUP[port].PORT_PMUX[pin >> 1] = temp | PORT_PMUX_PMUXE(peripheral);
			PORT_REGS->GROUP[port].PORT_PINCFG[pin] |= PORT_PINCFG_PMUXEN_Msk | PORT_PINCFG_DRVSTR_Msk;
		}
	break ;

	case PIO_NOT_A_PIN:
		return -1l;
	break;
	}

	return 0l;
}

void digitalWrite(uint32_t pinIndex, uint32_t val)
{
	uint32_t port = pinDescription[pinIndex].port;
	uint32_t pin = pinDescription[pinIndex].pin;
	uint32_t pinType = pinDescription[pinIndex].pinType;
	uint32_t pinMask = (1ul << pin);

	// Handle the case the pin isn't usable as PIO
	if (pinType == PIO_NOT_A_PIN)
		return ;

	// the pin is not an output, disable pull-up if val is LOW, otherwise enable pull-up
	if ((PORT_REGS->GROUP[port].PORT_DIRSET & pinMask) == 0) {
		uint32_t tmp = PORT_REGS->GROUP[port].PORT_PINCFG[pin];
        tmp &= ~PORT_PINCFG_PULLEN_Msk;
        if (val != LOW) {            
            tmp |= PORT_PINCFG_PULLEN_Msk;
            PORT_REGS->GROUP[port].PORT_PINCFG[pin] = tmp;
        }
    }

	switch (val) {
	case LOW:
		PORT_REGS->GROUP[port].PORT_OUTCLR = pinMask;
	break;

	default:
		PORT_REGS->GROUP[port].PORT_OUTSET = pinMask;
	break;
	}
}

int digitalRead(uint32_t pinIndex)
{
	uint32_t port = pinDescription[pinIndex].port;
	uint32_t pin = pinDescription[pinIndex].pin;
	uint32_t pinType = pinDescription[pinIndex].pinType;

	// Handle the case the pin isn't usable as PIO
	if (pinType == PIO_NOT_A_PIN )
		return LOW ;

	if ((PORT_REGS->GROUP[port].PORT_IN & (1ul << pin)) != 0)
		return HIGH ;

	return LOW ;
}
/*
 * shift_74Hc595.h
 *
 * Created: 27/02/2020 10:31:32
 *  Author: adam
 */ 
#ifndef _SHIFT_74HC595_H_
#define _SHIFT_74HC595_H_

#include <sam.h>

#define SO_V3_OPEN		0x00000002
#define SO_V3_CLOSE		0x00000004
#define SO_V2_OPEN		0x00000008
#define SO_V2_CLOSE		0x00000010
#define SO_V1_OPEN		0x00000020
#define SO_V1_CLOSE		0x00000040

#define SO_GSM_SW		0x00000400
#define SO_GSM_PWR		0x00000800
#define SO_V5_OPEN		0x00001000
#define SO_V5_CLOSE		0x00002000
#define SO_V4_OPEN		0x00004000
#define SO_V4_CLOSE		0x00008000

#define SO_LED_MAIN_LEFT		0x00020000
#define SO_LED_VALVE_5		0x00040000
#define SO_LED_VALVE_4		0x00080000
#define SO_LED_VALVE_3		0x00100000
#define SO_LED_VALVE_2		0x00200000
#define SO_LED_VALVE_1		0x00400000
#define SO_LED_MAIN_TOP		0x00800000

#define SO_LED_MAIN_BOTTOM		0x01000000
#define SO_LED_MAIN_RIGHT		0x02000000
#define SO_LED_REMOTE_B		0x04000000
#define SO_LED_REMOTE_G		0x08000000
#define SO_LED_REMOTE_R		0x10000000
#define SO_LED_GSM_B		0x20000000
#define SO_LED_GSM_G		0x40000000
#define SO_LED_GSM_R		0x80000000


#define LED_MAIN_LEDS_OFF_MASK	0xFFFFFFFF ^ (LED_MAIN_LEFT | \\
    LED_MAIN_RIGHT | LED_MAIN_TOP | LED_MAIN_BOTTOM)

//void Fast_Port_Pin(int port, int pin, int state);
//void Fast_Port_Pin_Init(int port, int pin, int dir);
//void Shift_74HC595_Data(void);
void cd74hc595_output_off(uint32_t mask);
void cd74hc595_output_on(uint32_t mask);
void cd74hc595_update(uint32_t value);
void cd74hc595_shift_data(void);
void cd74hc595_init(uint32_t _pinDS, uint32_t _pinSH_CP, uint32_t _pinST_CP);
void cd74hc595_setup(void);
#endif
/*******************************************************************************
 CLOCK PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_clock.c

  Summary:
    CLOCK PLIB Implementation File.

  Description:
    None

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#include "plib_clock.h"
#include "device.h"

static void OSCCTRL_Initialize(void)
{

}

static void OSC32KCTRL_Initialize(void)
{
    /* Configure 32K External Oscillator */
    OSC32KCTRL_REGS->OSC32KCTRL_XOSC32K = OSC32KCTRL_XOSC32K_STARTUP(2U) |
					  OSC32KCTRL_XOSC32K_ENABLE_Msk |
					  OSC32KCTRL_XOSC32K_CGM(1U) |
					  OSC32KCTRL_XOSC32K_EN1K_Msk |
					  OSC32KCTRL_XOSC32K_EN32K_Msk |
					  OSC32KCTRL_XOSC32K_XTALEN_Msk;

    while (!((OSC32KCTRL_REGS->OSC32KCTRL_STATUS & OSC32KCTRL_STATUS_XOSC32KRDY_Msk) ==
	  OSC32KCTRL_STATUS_XOSC32KRDY_Msk))
	;

    OSC32KCTRL_REGS->OSC32KCTRL_RTCCTRL = OSC32KCTRL_RTCCTRL_RTCSEL(0U);
}

/*
static void FDPLL0_Initialize(void)
{
    OSCCTRL_REGS->DPLL[0].OSCCTRL_DPLLCTRLB = OSCCTRL_DPLLCTRLB_FILTER(0U) | OSCCTRL_DPLLCTRLB_LTIME(0x0U)| OSCCTRL_DPLLCTRLB_REFCLK(1U) ;


    OSCCTRL_REGS->DPLL[0].OSCCTRL_DPLLRATIO = OSCCTRL_DPLLRATIO_LDRFRAC(12U) | OSCCTRL_DPLLRATIO_LDR(609U);

    while((OSCCTRL_REGS->DPLL[0].OSCCTRL_DPLLSYNCBUSY & OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Msk) == OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Msk)
        ;
 
    OSCCTRL_REGS->DPLL[0].OSCCTRL_DPLLCTRLA = OSCCTRL_DPLLCTRLA_ENABLE_Msk   ;

    while((OSCCTRL_REGS->DPLL[0].OSCCTRL_DPLLSYNCBUSY & OSCCTRL_DPLLSYNCBUSY_ENABLE_Msk) == OSCCTRL_DPLLSYNCBUSY_ENABLE_Msk )
        ;
 
    while((OSCCTRL_REGS->DPLL[0].OSCCTRL_DPLLSTATUS & (OSCCTRL_DPLLSTATUS_LOCK_Msk | OSCCTRL_DPLLSTATUS_CLKRDY_Msk)) !=
		(OSCCTRL_DPLLSTATUS_LOCK_Msk | OSCCTRL_DPLLSTATUS_CLKRDY_Msk))
           ;
}
*/


static void DFLL_Initialize(void)
{
    /* DFLL Configuration in Open Loop mode */
    OSCCTRL_REGS->OSCCTRL_DFLLCTRLA = 0;
	OSCCTRL_REGS->OSCCTRL_DFLLMUL = OSCCTRL_DFLLMUL_CSTEP(0x1) |
                                    OSCCTRL_DFLLMUL_FSTEP(0x1) |
                                    OSCCTRL_DFLLMUL_MUL(0);

	while (OSCCTRL_REGS->OSCCTRL_DFLLSYNC & OSCCTRL_DFLLSYNC_DFLLMUL_Msk)
		;

	OSCCTRL_REGS->OSCCTRL_DFLLCTRLB = 0;
	while (OSCCTRL_REGS->OSCCTRL_DFLLSYNC & OSCCTRL_DFLLSYNC_DFLLCTRLB_Msk)
		;

	OSCCTRL_REGS->OSCCTRL_DFLLCTRLA |= OSCCTRL_DFLLCTRLA_ENABLE_Msk;
	while (OSCCTRL_REGS->OSCCTRL_DFLLSYNC & OSCCTRL_DFLLSYNC_ENABLE_Msk)
        ;

	OSCCTRL_REGS->OSCCTRL_DFLLCTRLB = OSCCTRL_DFLLCTRLB_WAITLOCK_Msk |
				  OSCCTRL_DFLLCTRLB_CCDIS_Msk |
				  OSCCTRL_DFLLCTRLB_USBCRM_Msk;

	while (!(OSCCTRL_REGS->OSCCTRL_STATUS & OSCCTRL_DPLLSTATUS_CLKRDY_Msk))
		;
}

static void GCLK0_Initialize(void)
{
	/* Put Generic Clock Generator 3 as source for Generic Clock Gen 0 (DFLL48M reference) */

	/* selection of the CPU clock Division */
	MCLK_REGS->MCLK_CPUDIV = MCLK_CPUDIV_DIV(0x01U);

	while((MCLK_REGS->MCLK_INTFLAG & MCLK_INTFLAG_CKRDY_Msk) != MCLK_INTFLAG_CKRDY_Msk)
		;

	GCLK_REGS->GCLK_GENCTRL[0] = GCLK_GENCTRL_SRC(GCLK_GENCTRL_SRC_OSCULP32K_Val) | GCLK_GENCTRL_GENEN_Msk;

	while((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL_GCLK0) == GCLK_SYNCBUSY_GENCTRL_GCLK0)
		;
}

/*
static void GCLK1_Initialize(void)
{
    GCLK_REGS->GCLK_GENCTRL[1] = GCLK_GENCTRL_DIV(2U) | GCLK_GENCTRL_SRC(7U) | GCLK_GENCTRL_GENEN_Msk;

    while((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL_GCLK1) == GCLK_SYNCBUSY_GENCTRL_GCLK1)
      ;
}

static void GCLK2_Initialize(void)
{
    GCLK_REGS->GCLK_GENCTRL[2] = GCLK_GENCTRL_DIV(48U) | GCLK_GENCTRL_SRC(5U) | GCLK_GENCTRL_GENEN_Msk;

    while((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL_GCLK2) == GCLK_SYNCBUSY_GENCTRL_GCLK2)
       ;
}
*/

static void GCLK3_Initialize(void)
{
	/* Put XOSC32K as source of Generic Clock Generator 3 */
	GCLK_REGS->GCLK_GENCTRL[3] = GCLK_GENCTRL_SRC(5U) | GCLK_GENCTRL_GENEN_Msk;

	while ((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL_GCLK3) == GCLK_SYNCBUSY_GENCTRL_GCLK3)
		;
}

void CLOCK_Initialize (void)
{
    /* Function to Initialize the Oscillators */
    OSCCTRL_Initialize();

    /* Function to Initialize the 32KHz Oscillators */
    OSC32KCTRL_Initialize();

    GCLK3_Initialize();
    GCLK0_Initialize();
    DFLL_Initialize();
/*
    FDPLL0_Initialize();
    GCLK2_Initialize();
    GCLK1_Initialize();
*/

     /* 5) Switch Generic Clock Generator 0 to DFLL48M. CPU will run at 48MHz */
    GCLK_REGS->GCLK_GENCTRL[0] =
            GCLK_GENCTRL_SRC(GCLK_GENCTRL_SRC_DFLL) |
            GCLK_GENCTRL_IDC(1) |
            GCLK_GENCTRL_OE(1) |
            GCLK_GENCTRL_GENEN(1);

    while (GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL(0))
        ;

    /*
     * Now that all system clocks are configured, we can set CLKDIV .
     * These values are normally the ones present after Reset.
     */
    MCLK_REGS->MCLK_CPUDIV = MCLK_CPUDIV_DIV(1);

#if 0    
    /* Selection of the Generator and write Lock for EIC */
    GCLK_REGS->GCLK_PCHCTRL[4] = GCLK_PCHCTRL_GEN(0x1U)  | GCLK_PCHCTRL_CHEN_Msk;

    while ((GCLK_REGS->GCLK_PCHCTRL[4] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
    {
	/* Wait for synchronization */
    }
    /* Selection of the Generator and write Lock for USB */
    GCLK_REGS->GCLK_PCHCTRL[10] = GCLK_PCHCTRL_GEN(0x1U)  | GCLK_PCHCTRL_CHEN_Msk;

    while ((GCLK_REGS->GCLK_PCHCTRL[10] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
    {
	/* Wait for synchronization */
    }
    /* Selection of the Generator and write Lock for SERCOM2_CORE */
    GCLK_REGS->GCLK_PCHCTRL[23] = GCLK_PCHCTRL_GEN(0x1U)  | GCLK_PCHCTRL_CHEN_Msk;

    while ((GCLK_REGS->GCLK_PCHCTRL[23] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
    {
	/* Wait for synchronization */
    }
    /* Selection of the Generator and write Lock for SERCOM5_CORE */
    GCLK_REGS->GCLK_PCHCTRL[35] = GCLK_PCHCTRL_GEN(0x1U)  | GCLK_PCHCTRL_CHEN_Msk;

    while ((GCLK_REGS->GCLK_PCHCTRL[35] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
    {
	/* Wait for synchronization */
    }
    /* Selection of the Generator and write Lock for ADC0 */
    GCLK_REGS->GCLK_PCHCTRL[40] = GCLK_PCHCTRL_GEN(0x1U)  | GCLK_PCHCTRL_CHEN_Msk;

    while ((GCLK_REGS->GCLK_PCHCTRL[40] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
    {
	/* Wait for synchronization */
    }

    /* Configure the AHB Bridge Clocks */
    MCLK_REGS->MCLK_AHBMASK = 0xffffffU;

    /* Configure the APBA Bridge Clocks */
    MCLK_REGS->MCLK_APBAMASK = 0x7ffU;

    /* Configure the APBB Bridge Clocks */
    MCLK_REGS->MCLK_APBBMASK = 0x18257U;

    /* Configure the APBD Bridge Clocks */
    MCLK_REGS->MCLK_APBDMASK = 0x82U;
#endif
}

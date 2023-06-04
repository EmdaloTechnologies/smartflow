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
    //OSC32KCTRL_REGS->OSC32KCTRL_XOSC32K = 0x401e;
    OSC32KCTRL_REGS->OSC32KCTRL_XOSC32K =
        OSC32KCTRL_XOSC32K_CGM(OSC32KCTRL_XOSC32K_CGM_XT_Val) |
        OSC32KCTRL_XOSC32K_STARTUP(OSC32KCTRL_XOSC32K_STARTUP_CYCLE2048_Val) |
        OSC32KCTRL_XOSC32K_ONDEMAND(0) |
        OSC32KCTRL_XOSC32K_RUNSTDBY(0) |
        OSC32KCTRL_XOSC32K_EN1K(1) |
        OSC32KCTRL_XOSC32K_EN32K(1) |
        OSC32KCTRL_XOSC32K_XTALEN(1) |            
        OSC32KCTRL_XOSC32K_ENABLE(1);
    
    OSC32KCTRL_REGS->OSC32KCTRL_CFDCTRL =
            OSC32KCTRL_CFDCTRL_CFDPRESC(0) |
            OSC32KCTRL_CFDCTRL_SWBACK(0) |
            OSC32KCTRL_CFDCTRL_CFDEN(0);
    
    OSC32KCTRL_REGS->OSC32KCTRL_EVCTRL = OSC32KCTRL_EVCTRL_RESETVALUE;

            
	while((OSC32KCTRL_REGS->OSC32KCTRL_STATUS &
            OSC32KCTRL_STATUS_XOSC32KRDY_Msk) == 0)
		;

    /* RTC Src is 1KHz from external 32.768 kHz crystal */
    OSC32KCTRL_REGS->OSC32KCTRL_RTCCTRL =
            OSC32KCTRL_RTCCTRL_RTCSEL(OSC32KCTRL_RTCCTRL_RTCSEL_XOSC1K_Val);
}

static void FDPLL0_Initialize(void)
{
#if 0
    /* DPLL0 Initialisation */
    /* Source GCLK_Peripheral Control[1] from GCLK2 (and enable) */
    /* Source GCLK_OSCCTRL_FPDLL0 from GCLK2 - i.e from DFLL48/48 - 1 MHz */
    GCLK_REGS->GCLK_PCHCTRL[1] = GCLK_PCHCTRL_GEN(GCLK_PCHCTRL_GEN_GCLK2_Val) |
            GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[1] & GCLK_PCHCTRL_CHEN_Msk) !=
            GCLK_PCHCTRL_CHEN_Msk)
        ;

    /* Configure DPLL0 - disable filter, infinite lock time, GCLK reference -TODO what does this mean */
    OSCCTRL_REGS->DPLL[0].OSCCTRL_DPLLCTRLB = OSCCTRL_DPLLCTRLB_FILTER(0) |
            OSCCTRL_DPLLCTRLB_LTIME(0x0)|
            OSCCTRL_DPLLCTRLB_REFCLK(OSCCTRL_DPLLCTRLB_REFCLK_GCLK_Val);
    /* Set up a fractional divider of 0 and an integral divider of 119 */
    /* I *think* GCLK is 1 MHz, therefore PLL[0] is 1 MHz * (119 + 1) -> 120 MHz */
    OSCCTRL_REGS->DPLL[0].OSCCTRL_DPLLRATIO = OSCCTRL_DPLLRATIO_LDRFRAC(0) |
            OSCCTRL_DPLLRATIO_LDR(119);
    while((OSCCTRL_REGS->DPLL[0].OSCCTRL_DPLLSYNCBUSY &
            OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Msk) ==
            OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Msk)
        ;
    
    /* Enable DPLL[0] */
    OSCCTRL_REGS->DPLL[0].OSCCTRL_DPLLCTRLA = OSCCTRL_DPLLCTRLA_ENABLE_Msk;
    while((OSCCTRL_REGS->DPLL[0].OSCCTRL_DPLLSYNCBUSY &
            OSCCTRL_DPLLSYNCBUSY_ENABLE_Msk) == OSCCTRL_DPLLSYNCBUSY_ENABLE_Msk)
        ;

    while((OSCCTRL_REGS->DPLL[0].OSCCTRL_DPLLSTATUS &
            (OSCCTRL_DPLLSTATUS_LOCK_Msk | OSCCTRL_DPLLSTATUS_CLKRDY_Msk)) !=
            (OSCCTRL_DPLLSTATUS_LOCK_Msk | OSCCTRL_DPLLSTATUS_CLKRDY_Msk))
        ;
#else
    /* DPLL0 Initialisation */
    /* Source GCLK_Peripheral Control[1] from GCLK2 (and enable) */
    /* Source GCLK_OSCCTRL_FPDLL0 from GCLK2 - i.e from DFLL48/48 - 1 MHz */
    //GCLK_REGS->GCLK_PCHCTRL[1] = GCLK_PCHCTRL_GEN(GCLK_PCHCTRL_GEN_GCLK2_Val) |
    //        GCLK_PCHCTRL_CHEN_Msk;
    //while ((GCLK_REGS->GCLK_PCHCTRL[1] & GCLK_PCHCTRL_CHEN_Msk) !=
    //        GCLK_PCHCTRL_CHEN_Msk)
    //    ;

    /* Configure DPLL0 - disable filter, infinite lock time, GCLK reference -TODO what does this mean */
    OSCCTRL_REGS->DPLL[0].OSCCTRL_DPLLCTRLB = OSCCTRL_DPLLCTRLB_FILTER(0) |
            OSCCTRL_DPLLCTRLB_WUF(1) |
            OSCCTRL_DPLLCTRLB_REFCLK(OSCCTRL_DPLLCTRLB_REFCLK_XOSC32_Val) |
            OSCCTRL_DPLLCTRLB_LTIME(0x0)|
            OSCCTRL_DPLLCTRLB_LBYPASS(1) |
            OSCCTRL_DPLLCTRLB_DCOEN(0) |
            OSCCTRL_DPLLCTRLB_DIV(1);
    
    /* Set up a fractional divider of 3 and an integral divider of 3661 */
    /* OSC32K is 32.768 KHz, therefore PLL[0] is ~ 120 MHz */
    OSCCTRL_REGS->DPLL[0].OSCCTRL_DPLLRATIO = OSCCTRL_DPLLRATIO_LDRFRAC(3) |
            OSCCTRL_DPLLRATIO_LDR(0xe4d);
    while((OSCCTRL_REGS->DPLL[0].OSCCTRL_DPLLSYNCBUSY &
            OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Msk) ==
            OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Msk)
        ;
    
    /* Enable DPLL[0] */
    OSCCTRL_REGS->DPLL[0].OSCCTRL_DPLLCTRLA = OSCCTRL_DPLLCTRLA_ENABLE_Msk;
    while((OSCCTRL_REGS->DPLL[0].OSCCTRL_DPLLSYNCBUSY &
            OSCCTRL_DPLLSYNCBUSY_ENABLE_Msk) == OSCCTRL_DPLLSYNCBUSY_ENABLE_Msk)
        ;

    while((OSCCTRL_REGS->DPLL[0].OSCCTRL_DPLLSTATUS &
            (OSCCTRL_DPLLSTATUS_LOCK_Msk | OSCCTRL_DPLLSTATUS_CLKRDY_Msk)) !=
            (OSCCTRL_DPLLSTATUS_LOCK_Msk | OSCCTRL_DPLLSTATUS_CLKRDY_Msk))
        ;
#endif
}


static void DFLL_Initialize(void)
{
    /* Confirm DFLL48M is enabled */
    OSCCTRL_REGS->OSCCTRL_DFLLCTRLB =
            OSCCTRL_DFLLCTRLB_WAITLOCK(1);
    
    OSCCTRL_REGS->OSCCTRL_DFLLCTRLA =
            OSCCTRL_DFLLCTRLA_ENABLE(1) |
            OSCCTRL_DFLLCTRLA_ONDEMAND(0) |
            OSCCTRL_DFLLCTRLA_RUNSTDBY(1);
    while((OSCCTRL_REGS->OSCCTRL_DFLLCTRLA & OSCCTRL_DFLLCTRLA_ENABLE(1)) == 0)
        ;
}

static void CPUClock_Initialize(void)
{
    /* Set CPU clock Division - TODO: I think this results in 48 MHz */
    MCLK_REGS->MCLK_CPUDIV = MCLK_CPUDIV_DIV(1);
    while((MCLK_REGS->MCLK_INTFLAG & MCLK_INTFLAG_CKRDY_Msk) !=
            MCLK_INTFLAG_CKRDY_Msk)
        ;    
}

static void Peripheral_Generators_Initialize(void)
{
    /* Select GCLK1 for Peripheral Channel 4 (EIC) to GCLK1 - TODO; I think 60MHz */
    GCLK_REGS->GCLK_PCHCTRL[4] = GCLK_PCHCTRL_GEN(GCLK_PCHCTRL_GEN_GCLK1_Val) | GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[4] & GCLK_PCHCTRL_CHEN_Msk)
            != GCLK_PCHCTRL_CHEN_Msk)
        ;
    
    /* Select GCLK1 for Peripheral Channel 7 (SERCOM0 CORE) - again TODO: 60 MHz? */
    GCLK_REGS->GCLK_PCHCTRL[7] = GCLK_PCHCTRL_GEN(GCLK_PCHCTRL_GEN_GCLK1_Val) | GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[7] & GCLK_PCHCTRL_CHEN_Msk) !=
            GCLK_PCHCTRL_CHEN_Msk)
        ;
    
    /* Select GCLK1 for Peripheral Channel 9 (TCO TC1) - again TODO: 60 MHz? */
    GCLK_REGS->GCLK_PCHCTRL[9] = GCLK_PCHCTRL_GEN(GCLK_PCHCTRL_GEN_GCLK1_Val) | GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[9] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
        ;
    
    /* Selection of the Generator and write Lock for SERCOM2_CORE */
    GCLK_REGS->GCLK_PCHCTRL[23] = GCLK_PCHCTRL_GEN(GCLK_PCHCTRL_GEN_GCLK1_Val)  | GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[23] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
        
    /* Selection of the Generator and write Lock for SERCOM4_CORE */
    GCLK_REGS->GCLK_PCHCTRL[34] = GCLK_PCHCTRL_GEN(GCLK_PCHCTRL_GEN_GCLK1_Val)  | GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[34] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
        ;
    
    /* Selection of the Generator and write Lock for SERCOM5_CORE */
    GCLK_REGS->GCLK_PCHCTRL[35] = GCLK_PCHCTRL_GEN(GCLK_PCHCTRL_GEN_GCLK1_Val)  | GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[35] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
        ;
}

static void GCLK0_Initialize(void)
{
    /* Connect GCLK_GEN0 to DPLL[0], i.e. TODO I think 120 MHz */
    GCLK_REGS->GCLK_GENCTRL[0] = GCLK_GENCTRL_DIV(1)
            | GCLK_GENCTRL_SRC(GCLK_GENCTRL_SRC_DPLL0_Val) |
            GCLK_GENCTRL_GENEN_Msk;
    while((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL_GCLK0) ==
            GCLK_SYNCBUSY_GENCTRL_GCLK0)
        ;
}

static void GCLK1_Initialize(void)
{
    /* Connect GCLK_GEN1 to DPLL[0] and divide by 2 (I think 60 MHz) */
    GCLK_REGS->GCLK_GENCTRL[1] = GCLK_GENCTRL_DIV(2) |
            GCLK_GENCTRL_SRC(GCLK_GENCTRL_SRC_DPLL0_Val) |
            GCLK_GENCTRL_GENEN_Msk;
    while((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL_GCLK1) ==
            GCLK_SYNCBUSY_GENCTRL_GCLK1)
        ;
}

static void GCLK2_Initialize(void)
{
    /* Source GCLK2 from DFLL48M, divide by 48 (so generates 1M) and Enable */
    GCLK_REGS->GCLK_GENCTRL[2] = GCLK_GENCTRL_DIV(48) |
            GCLK_GENCTRL_SRC(GCLK_GENCTRL_SRC_DFLL_Val) |
            GCLK_GENCTRL_GENEN_Msk;
    while((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL_GCLK2) ==
            GCLK_SYNCBUSY_GENCTRL_GCLK2)
        ;
}

static void GCLK3_Initialize(void)
{
    /* Source GCLK3 for 32 KHz and Enable */
    GCLK_REGS->GCLK_GENCTRL[3] = GCLK_GENCTRL_DIV(1) |
            GCLK_GENCTRL_SRC(GCLK_GENCTRL_SRC_XOSC32K_Val) |
            GCLK_GENCTRL_GENEN_Msk;
    while((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL_GCLK3) ==
            GCLK_SYNCBUSY_GENCTRL_GCLK3)
        ;
}

static void AHB_APB_Initialize(void)
{
    /* Enable all the AHB Bridge Clocks */
    MCLK_REGS->MCLK_AHBMASK = 0xffffff;

    /* Configure the APBA Bridge Clocks */
    /* See SAMD5x/E5x Family Data Sheet MCLK - APBAMASK */
    MCLK_REGS->MCLK_APBAMASK = 0xd7ff;

    /* Configure the APBB Bridge Clocks */
    MCLK_REGS->MCLK_APBBMASK = 0x18256;

    /* Configure the APBD Bridge Clocks */
    MCLK_REGS->MCLK_APBDMASK = 0x3;
}

void CLOCK_Initialize (void)
{
    GCLK_REGS->GCLK_CTRLA &- 1;
    
    /* Function to Initialise the Oscillators */
    OSCCTRL_Initialize();

    /* Function to Initialise the 32.768 KHz Oscillators */
    OSC32KCTRL_Initialize();
    
    /* Set up for 32.768 KHz */
    GCLK3_Initialize();

    /* Generates DFLL48M */
    DFLL_Initialize();

    /* Based on DFLL48M */
    CPUClock_Initialize();
    GCLK2_Initialize();
    
    /* Based on GCLK2 */
    FDPLL0_Initialize();

    /* Based o FDPLL0 */
    GCLK0_Initialize();
    GCLK1_Initialize();

    /* Based on GCLK1 */
    Peripheral_Generators_Initialize();

    /* Gates */
    AHB_APB_Initialize();
}
/*******************************************************************************
  System Initialization File

  File Name:
    initialization.c

  Summary:
    This file contains source code necessary to initialize the system.

  Description:
    This file contains source code necessary to initialize the system.  It
    implements the "SYS_Initialize" function, defines the configuration bits,
    and allocates any necessary global system resources,
 *******************************************************************************/

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "configuration.h"
#include "definitions.h"
#include "device.h"
#include "shift_74hc595.h"
#include "smartflow_pins.h"
#include "d51_pins.h"
#include "tx_api.h"

// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************
#pragma config BOD33_DIS = SET
#pragma config BOD33USERLEVEL = 0x1c
#pragma config BOD33_ACTION = RESET
#pragma config BOD33_HYST = 0x2
#pragma config NVMCTRL_BOOTPROT = 0
#pragma config NVMCTRL_SEESBLK = 0x0
#pragma config NVMCTRL_SEEPSZ = 0x0
#pragma config RAMECC_ECCDIS = SET
#pragma config WDT_ENABLE = CLEAR
#pragma config WDT_ALWAYSON = CLEAR
#pragma config WDT_PER = CYC8192
#pragma config WDT_WINDOW = CYC8192
#pragma config WDT_EWOFFSET = CYC8192
#pragma config WDT_WEN = CLEAR
#pragma config NVMCTRL_REGION_LOCKS = 0xffffffff




// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="DRV_SPI Instance 0 Initialization Data">

/* SPI Client Objects Pool */
static DRV_SPI_CLIENT_OBJ drvSPI0ClientObjPool[DRV_SPI_CLIENTS_NUMBER_IDX0];

/* SPI Transfer Objects Pool */
static DRV_SPI_TRANSFER_OBJ drvSPI0TransferObjPool[DRV_SPI_QUEUE_SIZE_IDX0];

/* SPI PLIB Interface Initialization */
const DRV_SPI_PLIB_INTERFACE drvSPI0PlibAPI = {

    /* SPI PLIB Setup */
    .setup = (DRV_SPI_PLIB_SETUP)SERCOM4_SPI_TransferSetup,

    /* SPI PLIB WriteRead function */
    .writeRead = (DRV_SPI_PLIB_WRITE_READ)SERCOM4_SPI_WriteRead,

    /* SPI PLIB Transfer Status function */
    .isBusy = (DRV_SPI_PLIB_IS_BUSY)SERCOM4_SPI_IsBusy,

    /* SPI PLIB Callback Register */
    .callbackRegister = (DRV_SPI_PLIB_CALLBACK_REGISTER)SERCOM4_SPI_CallbackRegister,
};

const uint32_t drvSPI0remapDataBits[]= { 0x0, 0x1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
const uint32_t drvSPI0remapClockPolarity[] = { 0x0, 0x20000000 };
const uint32_t drvSPI0remapClockPhase[] = { 0x10000000, 0x0 };

const DRV_SPI_INTERRUPT_SOURCES drvSPI0InterruptSources =
{
    /* Peripheral has more than one interrupt vectors */
    .isSingleIntSrc                        = false,

    /* Peripheral interrupt lines */
    .intSources.multi.spiTxReadyInt      = SERCOM4_0_IRQn,
    .intSources.multi.spiTxCompleteInt   = SERCOM4_1_IRQn,
    .intSources.multi.spiRxInt           = SERCOM4_2_IRQn,
};

/* SPI Driver Initialization Data */
const DRV_SPI_INIT drvSPI0InitData =
{
    /* SPI PLIB API */
    .spiPlib = &drvSPI0PlibAPI,

    .remapDataBits = drvSPI0remapDataBits,

    .remapClockPolarity = drvSPI0remapClockPolarity,

    .remapClockPhase = drvSPI0remapClockPhase,

    /* SPI Number of clients */
    .numClients = DRV_SPI_CLIENTS_NUMBER_IDX0,

    /* SPI Client Objects Pool */
    .clientObjPool = (uintptr_t)&drvSPI0ClientObjPool[0],

    /* DMA Channel for Transmit */
    .dmaChannelTransmit = SYS_DMA_CHANNEL_NONE,

    /* DMA Channel for Receive */
    .dmaChannelReceive  = SYS_DMA_CHANNEL_NONE,

    /* SPI Queue Size */
    .transferObjPoolSize = DRV_SPI_QUEUE_SIZE_IDX0,

    /* SPI Transfer Objects Pool */
    .transferObjPool = (uintptr_t)&drvSPI0TransferObjPool[0],

    /* SPI interrupt sources (SPI peripheral and DMA) */
    .interruptSources = &drvSPI0InterruptSources,
};

// </editor-fold>



// *****************************************************************************
// *****************************************************************************
// Section: System Data
// *****************************************************************************
// *****************************************************************************
/* Structure to hold the object handles for the modules in the system. */
SYSTEM_OBJECTS sysObj;

// *****************************************************************************
// *****************************************************************************
// Section: Library/Stack Initialization Data
// *****************************************************************************
// *****************************************************************************

const AZURE_GLUE_NETWORK_CONFIG azure_net_config[] = 
{
/*** Interface 0 Configuration  ***/                    
{
   .macAddr = AZURE_INTERFACE_DEFAULT_MAC_ADDR_IDX0,
   .pMacObject = &AZURE_INTERFACE_DEFAULT_DRIVER_IDX0,
   .pMacInit = 0,
   .macInitSize = 0,
   .macIrq = 0,
   .macRxMaxFrame = 1518,
},
};

const AZURE_GLUE_INIT azure_glue_init = 
{
    .nNets = sizeof(azure_net_config) / sizeof(*azure_net_config),
    .pNetConf = azure_net_config,
};


// *****************************************************************************
// *****************************************************************************
// Section: System Initialization
// *****************************************************************************
// *****************************************************************************

const SYS_CMD_INIT sysCmdInit =
{
    .moduleInit = {0},
    .consoleCmdIOParam = SYS_CMD_SINGLE_CHARACTER_READ_CONSOLE_IO_PARAM,
	.consoleIndex = 0,
};


const SYS_DEBUG_INIT debugInit =
{
    .moduleInit = {0},
    .errorLevel = SYS_DEBUG_GLOBAL_ERROR_LEVEL,
    .consoleIndex = 0,
};


// <editor-fold defaultstate="collapsed" desc="SYS_TIME Initialization Data">

const SYS_TIME_PLIB_INTERFACE sysTimePlibAPI = {
    .timerCallbackSet = (SYS_TIME_PLIB_CALLBACK_REGISTER)TC0_TimerCallbackRegister,
    .timerStart = (SYS_TIME_PLIB_START)TC0_TimerStart,
    .timerStop = (SYS_TIME_PLIB_STOP)TC0_TimerStop,
    .timerFrequencyGet = (SYS_TIME_PLIB_FREQUENCY_GET)TC0_TimerFrequencyGet,
    .timerPeriodSet = (SYS_TIME_PLIB_PERIOD_SET)TC0_Timer32bitPeriodSet,
    .timerCompareSet = (SYS_TIME_PLIB_COMPARE_SET)TC0_Timer32bitCompareSet,
    .timerCounterGet = (SYS_TIME_PLIB_COUNTER_GET)TC0_Timer32bitCounterGet,
};

const SYS_TIME_INIT sysTimeInitData =
{
    .timePlib = &sysTimePlibAPI,
    .hwTimerIntNum = TC0_IRQn,
};

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="SYS_CONSOLE Instance 0 Initialization Data">


/* Declared in console device implementation (sys_console_uart.c) */
extern const SYS_CONSOLE_DEV_DESC sysConsoleUARTDevDesc;

const SYS_CONSOLE_UART_PLIB_INTERFACE sysConsole0UARTPlibAPI =
{
    .read = (SYS_CONSOLE_UART_PLIB_READ)SERCOM2_USART_Read,
	.readCountGet = (SYS_CONSOLE_UART_PLIB_READ_COUNT_GET)SERCOM2_USART_ReadCountGet,
	.readFreeBufferCountGet = (SYS_CONSOLE_UART_PLIB_READ_FREE_BUFFFER_COUNT_GET)SERCOM2_USART_ReadFreeBufferCountGet,
    .write = (SYS_CONSOLE_UART_PLIB_WRITE)SERCOM2_USART_Write,
	.writeCountGet = (SYS_CONSOLE_UART_PLIB_WRITE_COUNT_GET)SERCOM2_USART_WriteCountGet,
	.writeFreeBufferCountGet = (SYS_CONSOLE_UART_PLIB_WRITE_FREE_BUFFER_COUNT_GET)SERCOM2_USART_WriteFreeBufferCountGet,
};

const SYS_CONSOLE_UART_INIT_DATA sysConsole0UARTInitData =
{
    .uartPLIB = &sysConsole0UARTPlibAPI,    
};

const SYS_CONSOLE_INIT sysConsole0Init =
{
    .deviceInitData = (const void*)&sysConsole0UARTInitData,
    .consDevDesc = &sysConsoleUARTDevDesc,
    .deviceIndex = 0,
};



// </editor-fold>




// *****************************************************************************
// *****************************************************************************
// Section: Local initialization functions
// *****************************************************************************
// *****************************************************************************
void Gsm_Modem_PSU_Off()
{
        //USB_Output(GEN, "modem_off");
        cd74hc595_output_off(SO_LED_GSM_B); // modem off
        cd74hc595_output_off(SO_GSM_PWR);
        cd74hc595_shift_data();
}

void Gsm_Modem_PSU_On()
{
        //USB_Output(GEN, "modem_on");
        cd74hc595_output_on(SO_GSM_PWR);
        cd74hc595_output_on(SO_LED_GSM_B);
        cd74hc595_shift_data();
        tx_thread_sleep(300);
        cd74hc595_output_on(SO_GSM_SW);
        cd74hc595_output_on(SO_LED_GSM_G);
        cd74hc595_shift_data();
        tx_thread_sleep(900);
        cd74hc595_output_off(SO_GSM_SW);
        cd74hc595_output_off(SO_LED_GSM_G);
        cd74hc595_shift_data();
        tx_thread_sleep(900);
}

void todo_delay_ms(void)
{
    int i;
    volatile int *foo = 0;
    volatile int bar = 0;

    for(i = 0; i < 15000; i++)
        bar = *foo;
}


void todo_sleep(int ms)
{
    /* crude estimate - at 48 MHz, need 48,000 instructions for a 1 msecond delay */
    int i;

    for (i = 0; i < ms; i++)
        todo_delay_ms();
}

void Gsm_Modem_Boot_up()
{
        Gsm_Modem_PSU_Off();
        tx_thread_sleep(6000);
        todo_sleep(6000);
        Gsm_Modem_PSU_On();
        //todo_sleep(6000);
}

void Init_Shift_Data()
{
        pinMode(PIN_ST_CP, OUTPUT);
        pinMode(PIN_SH_CP, OUTPUT);
        pinMode(PIN_DS, OUTPUT);

        cd74hc595_shift_data();

        pinMode(PIN_OUTPUTS_OE, OUTPUT);
        digitalWrite(PIN_OUTPUTS_OE, LOW);
}

/*******************************************************************************
  Function:
    void SYS_Initialize ( void *data )

  Summary:
    Initializes the board, services, drivers, application and other modules.

  Remarks:
 */

void SYS_Initialize(void* data)
{
    USART_SERIAL_SETUP serialSetup;
    serialSetup.baudRate = 115200;
    serialSetup.dataWidth = USART_DATA_8_BIT;
    serialSetup.parity = USART_PARITY_NONE;
    serialSetup.stopBits = USART_STOP_1_BIT;
    
    NVMCTRL_Initialize(); 
    PORT_Initialize();
    CLOCK_Initialize();
    SERCOM0_USART_Initialize();
    SERCOM0_USART_SerialSetup(&serialSetup, 0);
    SERCOM2_USART_Initialize();
    EVSYS_Initialize();
    SERCOM4_SPI_Initialize();
    EIC_Initialize();
    TC0_TimerInitialize();
    RTC_Initialize();

    cd74hc595_init(PIN_DS, PIN_SH_CP, PIN_ST_CP);
    cd74hc595_setup();
    
    Gsm_Modem_Boot_up();

    /* Initialise SPI0 Driver Instance */
    //sysObj.drvSPI0 = DRV_SPI_Initialize(DRV_SPI_INDEX_0, (SYS_MODULE_INIT *)&drvSPI0InitData);
    /* Initialise the WINC Driver */
    //sysObj.drvWifiWinc = WDRV_WINC_Initialize(0, NULL);

    SYS_CMD_Initialize((SYS_MODULE_INIT*)&sysCmdInit);

    sysObj.sysDebug = SYS_DEBUG_Initialize(SYS_DEBUG_INDEX_0, (SYS_MODULE_INIT*)&debugInit);

    sysObj.sysTime = SYS_TIME_Initialize(SYS_TIME_INDEX_0, (SYS_MODULE_INIT *)&sysTimeInitData);
    sysObj.sysConsole0 = SYS_CONSOLE_Initialize(SYS_CONSOLE_INDEX_0, (SYS_MODULE_INIT *)&sysConsole0Init);

    APP_Initialize();
    APP_SIMCOM_Initialize();

    NVIC_Initialize();
}


/*******************************************************************************
 End of File
*/

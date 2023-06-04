/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_simcom.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app_smartflow.h"
#include "ewf_certs.h"
#include "system/console/sys_console.h"

#include "ewf_lib.c"
#include "ewf_platform_threadx.c"
#include "ewf_allocator.c"
#include "ewf_allocator_threadx.c"
#include "ewf_interface.c"
#include "ewf_interface_microchip_sam_uart.c"
#include "ewf_adapter.c"
#include "ewf_adapter_api_control.c"
#include "ewf_adapter_api_info.c"
#include "ewf_adapter_api_tls_basic.c"
#include "ewf_adapter_api_mqtt_basic.c"
#include "ewf_adapter_api_tcp.c"
#include "ewf_adapter_api_udp.c"
#include "ewf_adapter_api_modem.c"
#include "ewf_adapter_api_modem_general.c"
#include "ewf_adapter_api_modem_network_service.c"
#include "ewf_adapter_api_modem_packet_domain.c"
#include "ewf_adapter_api_modem_sim_utility.c"
#include "ewf_adapter_api_modem_sms.c"
#include "ewf_adapter_simcom_sim868.c"
#include "ewf_adapter_simcom_common.c"

#include "ewf_smartflow.config.h"
#include "ewf_app_simcom_sim868.c"

#include "ewf_smartflow.config.h"

char ewf_log_buffer[256];

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
EWF_CERTS_DATA ewf_certsData;

//#define SIMCOM_TODO "123456789" /* target AP's passphrase */

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_WIFI_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_SIMCOM_DATA app_simcomData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************
void ewf_sim868(void);
void ewf_sim868(void)
{
    ewf_result result;

    ewf_allocator* message_allocator_ptr = NULL;
    ewf_interface* interface_ptr = NULL;
    ewf_adapter* adapter_ptr = NULL;

    EWF_ALLOCATOR_THREADX_STATIC_DECLARE(message_allocator_ptr, message_allocator, EWF_CONFIG_MESSAGE_ALLOCATOR_BLOCK_COUNT, EWF_CONFIG_MESSAGE_ALLOCATOR_BLOCK_SIZE);
    EWF_INTERFACE_MICROCHIP_SAM_UART_STATIC_DECLARE(interface_ptr, sam_uart);
    EWF_ADAPTER_SIMCOM_SIM868_STATIC_DECLARE(adapter_ptr, simcom_sim868, message_allocator_ptr, NULL, interface_ptr);

    // Start the adapter
    if (ewf_result_failed(result = ewf_adapter_start(adapter_ptr)))
    {
        EWF_LOG_ERROR("Failed to start the adapter, ewf_result %d.\n", result);
        exit(result);
    }
    // Set the SIM PIN
    if (ewf_result_failed(result = ewf_adapter_modem_sim_pin_enter(adapter_ptr, EWF_CONFIG_SIM_PIN)))
    {
        EWF_LOG_ERROR("Failed to the SIM PIN, ewf_result %d.\n", result);
        exit(result);
    }
    // Call the certificate provisioning example
    if (ewf_result_failed(result = ewf_mqtt_connect_simcom_sim868(adapter_ptr)))
    {
        EWF_LOG_ERROR("The certificate provisioning example returned and error, ewf_result %d.\n", result);
        exit(result);
    }

    EWF_LOG("Done!\n");

    /* Stay here forever.  */
    while (1)
    {
        ewf_platform_sleep(EWF_PLATFORM_TICKS_PER_SECOND);
    }

}

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_SIMCOM_Initialize ( void )

  Remarks:
    See prototype in app_simcom.h.
 */
/*******************************************************************************
  Function:
    void EWF_CERTS_Initialize ( void )

  Remarks:
    See prototype in ewf_certs.h.
 */

void EWF_CERTS_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    ewf_certsData.state = EWF_CERTS_STATE_INIT;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

void APP_SIMCOM_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app_simcomData.state = APP_SIMCOM_STATE_INIT;
}


/******************************************************************************
  Function:
    void APP_SIMCOM_Tasks ( void )

  Remarks:
    See prototype in app_simcom.h.
 */

void APP_SIMCOM_Tasks ( void )
{
    switch ( app_simcomData.state )
    {
        /* Application's initial state. */
        case APP_SIMCOM_STATE_INIT:
        {
            if (0) //if (SYS_STATUS_READY == WDRV_WINC_Status(sysObj.drvWifiWinc))
            {
                app_simcomData.state = APP_SIMCOM_STATE_SIM868_READY;
            }
            break;
        }
        
        case APP_SIMCOM_STATE_SIM868_READY:
        {

            break;
        }

        case APP_SIMCOM_STATE_SERVICE_TASKS:
        {

            break;
        }
        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

/*******************************************************************************
 End of File
 */

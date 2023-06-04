/************************************************************************//**
 *
 * @file
 * @version Preview
 * SPDX-License-Identifier: MIT
 * @copyright Copyright (c) Microsoft Corporation. All rights reserved.
 * @brief The Embedded Wireless Framework configuration template.
 * Copy this file into your own project, remove the .template extension
 * and customize its contents.
 *
 ****************************************************************************/


#ifndef __EWF__config__h__included__
#define __EWF__config__h__included__

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************//**
 * @defgroup group_configuration EWF configuration
 * @brief The definitions to configure the Embedded Wireless Framework.
 * @{
 ****************************************************************************/

 /** Define this symbol to enable compilation of debug code. When this symbol is not defined, debug code is not present and the footprint is reduced.  */
#define EWF_DEBUG

/** Define this symbol to enable verbose logging */
//#define EWF_LOG_VERBOSE

/** Define this symbol to enable checking of function parameters. When this symbol is not defined, parameter checking code is not present and the footprint is reduced.  */
#define EWF_PARAMETER_CHECKING

/* Define the platform to be used, only one is valid */
//#define EWF_PLATFORM_BARE_METAL
#define EWF_PLATFORM_THREADX
//#define EWF_PLATFORM_FREERTOS
//#define EWF_PLATFORM_WIN32

/* Override the EWF_LOG definition on Microchip SAM */    
extern SYS_CONSOLE_HANDLE ewfConsoleHandle;
extern char ewf_log_buffer[256];
#define EWF_LOG(...)                                                            \
do {                                                                            \
    /*asm("bkpt");*/ \
	snprintf(ewf_log_buffer, sizeof(ewf_log_buffer), __VA_ARGS__);              \
    SYS_CONSOLE_Write( ewfConsoleHandle, ewf_log_buffer,                        \
             strlen(ewf_log_buffer));                                           \
    SYS_CONSOLE_Flush(ewfConsoleHandle);                                        \
} while (0)

/* Override the default definition on Microchip SAM to match the generated code */    
#define EWF_PLATFORM_TICKS_PER_SECOND          (TX_TICK_RATE_HZ)

/************************************************************************//**
 * @} *** group_configuration
 ****************************************************************************/

#define EWF_CONFIG_ADAPTER_SIMCOM_COMMON_ROOT_CA_CERTIFICATE_FILE_NAME "root_ca_cert.pem"
#define EWF_CONFIG_ADAPTER_COMMON_COMMON_USER_CA_CERTIFICATE_FILE_NAME "ca_cert.pem"
#define EWF_CONFIG_ADAPTER_SIMCOM_COMMON_CLIENT_CERTIFICATE_FILE_NAME "device_cert.pem"
#define EWF_CONFIG_ADAPTER_SIMCOM_COMMON_CLIENT_PRIVATE_KEY_FILE_NAME "device_key.pem"

#define EWF_CONFIG_ADAPTER_SIMCOM_COMMON_ROOT_CA_CERTIFICATE_BUFFER_NAME root_ca_cert_pem
#define EWF_CONFIG_ADAPTER_COMMON_COMMON_USER_CA_CERTIFICATE_BUFFER_NAME ca_cert_pem
#define EWF_CONFIG_ADAPTER_SIMCOM_COMMON_CLIENT_CERTIFICATE_BUFFER_NAME device_cert_pem
#define EWF_CONFIG_ADAPTER_SIMCOM_COMMON_CLIENT_PRIVATE_KEY_BUFFER_NAME device_key_pem

#ifdef __cplusplus
}
#endif

#endif /* __EWF__config__h__included__ */

/************************************************************************//**
 * @file
 * @version Preview
 * @copyright Copyright (c) Microsoft Corporation. All rights reserved.
 * SPDX-License-Identifier: MIT
 * @brief The Embedded Wireless Framework Simcom certificate provisioning example
 * @details EWF certificate provisioning example for all Simcom cellular modems with SSL/TLS support
 ****************************************************************************/

/**
 * @brief Certificate & Key header file include section
 * @details Include the certificate and key header files that will be
 * provisioned on the adapter/modem
 */
#include "root_ca_cert.pem.h"

#include "ewf_adapter_simcom_common.h"

#define EWF_CONFIG_APN_ONOMONDO "onomondo"
#define EWF_CONFIG_APN_ONOMONDO_USER ""
#define EWF_CONFIG_APN_ONOMONDO_PW ""

#define EWF_CONFIG_APN_ESEYE1 "ESEYE1"
#define EWF_CONFIG_APN_ESEYE1_USER "USER"
#define EWF_CONFIG_APN_ESEYE1_PW "PASS"

#define EWF_CONFIG_AZ_HOST "TEST-Smartflow.azure-devices.net"
#define EWF_CONFIG_AZ_PORT "8883"
#define EWF_CONFIG_AZ_API_VERSION "2016-11-14"
#define EWF_CONFIG_AZ_DEVICE_ID "9999"
#define EWF_CONFIG_AZ_SAS_TOKEN "DS2bbaYXsANATsMdAwesYfsV9A6tVxOvtOX%2BC1HV3jo"

struct device {
    char apn_name[32];
    char apn_username[32];
    char apn_password[32];
    char az_host[64];
    char az_port[8];
    char az_api_version[32];
    char az_device_id[32];
    char az_sas_token[64];
    uint32_t ip_address;
    uint32_t network_mask;
    uint32_t gateway_address;
    uint32_t dns_address;
};

struct device nv = {
    .apn_name = EWF_CONFIG_APN_ESEYE1,
    .apn_username = EWF_CONFIG_APN_ESEYE1_USER,
    .apn_password = EWF_CONFIG_APN_ESEYE1_PW,
    .az_host = EWF_CONFIG_AZ_HOST,
    .az_port = EWF_CONFIG_AZ_PORT,
    .az_api_version = EWF_CONFIG_AZ_API_VERSION,
    .az_device_id = EWF_CONFIG_AZ_DEVICE_ID,
    .az_sas_token = EWF_CONFIG_AZ_SAS_TOKEN,
};

extern void todo_sleep(uint32_t ms);
ewf_result ewf_simcom_common(ewf_adapter* adapter_ptr)
{
    EWF_ADAPTER_VALIDATE_POINTER(adapter_ptr);

    ewf_result result;

#if defined(EWF_CONFIG_ADAPTER_SIMCOM_COMMON_ROOT_CA_CERTIFICATE_FILE_NAME) && \
    defined(EWF_CONFIG_ADAPTER_SIMCOM_COMMON_ROOT_CA_CERTIFICATE_BUFFER_NAME)
    if (ewf_result_failed(result = ewf_adapter_simcom_common_ufs_delete(adapter_ptr,
        EWF_CONFIG_ADAPTER_SIMCOM_COMMON_ROOT_CA_CERTIFICATE_FILE_NAME)))
    {
        EWF_LOG("Failed to delete file, ewf_result %d.\n", result);
    }
    if (ewf_result_failed(result = ewf_adapter_simcom_common_ufs_upload(adapter_ptr,
        EWF_CONFIG_ADAPTER_SIMCOM_COMMON_ROOT_CA_CERTIFICATE_FILE_NAME,
        (const uint8_t*)EWF_CONFIG_ADAPTER_SIMCOM_COMMON_ROOT_CA_CERTIFICATE_BUFFER_NAME,
        sizeof(EWF_CONFIG_ADAPTER_SIMCOM_COMMON_ROOT_CA_CERTIFICATE_BUFFER_NAME))))
    {
        EWF_LOG_ERROR("Failed to upload, ewf_result %d.\n", result);
        return result;
    }
#endif

    if (ewf_result_failed(result = ewf_adapter_modem_functionality_set(adapter_ptr, EWF_ADAPTER_MODEM_FUNCTIONALITY_FULL)))
        EWF_LOG_ERROR("Failed to enable full modem functionality, ewf_result %d.\n", result);
    
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+CLTS=1\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); // return result;
     
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT&W\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); // return result;
    
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+CFUN=0\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\n+CPIN: NOT READY\r\n\r\nOK\r\n"))) asm("bkpt"); // return result;
    
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+CFUN=1\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\n+CPIN: READY\r\n\r\nOK\r\n"))) asm("bkpt"); // return result;

    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+CCLK?\r", NULL))) asm("bkpt"); // return result;
    ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\nOK\r\n");
    
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); // return result;
    
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SAPBR=3,1,\"APN\",", "\"", nv.apn_name, "\"\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); // return result;
    
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SAPBR=3,1,\"USER\",", "\"", nv.apn_username, "\"\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); // return result;

    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SAPBR=3,1,\"PWD\",", "\"", nv.apn_password, "\"\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); // return result;

    bool attached = false;
    while (!attached)
    {
        if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+CGATT?\r", NULL))) asm("bkpt"); // return result;
        result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\n+CGATT: 1\r\n\r\nOK\r\n");
        if (result == EWF_RESULT_OK)
            attached = true;
    }
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SAPBR=1,1\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response_ends_with(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); // return result;
    
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SAPBR=2,1\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response_starts_with(adapter_ptr->interface_ptr, "\r\n+SAPBR: 1,1"))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SAPBR=2,1\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response_starts_with(adapter_ptr->interface_ptr, "\r\n+SAPBR: 1,1"))) asm("bkpt"); // return result;

    if (ewf_result_failed(result = ewf_adapter_get_ipv4_address(adapter_ptr, &nv.ip_address)))
        EWF_LOG_ERROR("Failed to get ip address, ewf_result %d.\n", result);
    if (ewf_result_failed(result = ewf_adapter_get_ipv4_netmask(adapter_ptr, &nv.network_mask)))
        EWF_LOG_ERROR("Failed to get ip address, ewf_result %d.\n", result);
    
    if (ewf_result_failed(result = ewf_adapter_get_ipv4_gateway(adapter_ptr, &nv.gateway_address)))
        EWF_LOG_ERROR("Failed to get ip address, ewf_result %d.\n", result);

    if (ewf_result_failed(result = ewf_adapter_get_ipv4_dns(adapter_ptr, &nv.dns_address)))
        EWF_LOG_ERROR("Failed to get ip address, ewf_result %d.\n", result);

    if (ewf_result_failed(result = ewf_adapter_info(adapter_ptr)))
        EWF_LOG_ERROR("Failed to get adapter info, ewf_result %d.\n", result);

    char data_length_str[5];
    const char* data_length_cstr = ewfl_unsigned_to_str(sizeof(EWF_CONFIG_ADAPTER_SIMCOM_COMMON_ROOT_CA_CERTIFICATE_BUFFER_NAME),
            data_length_str, sizeof(data_length_str));
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SSLSETROOT=", 
            "\"", EWF_CONFIG_ADAPTER_SIMCOM_COMMON_ROOT_CA_CERTIFICATE_FILE_NAME, "\", ",
            "\"", data_length_cstr,"\"", "\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); // return result;
    
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SSLOPT=0,0\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SSLOPT=1,1\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); // return result;
    
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SMSSL=\"1\"\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); // return result;
    
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SMCONF=\"CLEANSS\", 0\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); // return result;

    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SMCONF=\"URL\",\"", nv.az_host, ":", nv.az_port, "\"\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); // return result;

    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SMCONF=\"CLIENTID\",\"", nv.az_device_id, "\"\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); // return result;

    char cmd[256] = { 0 };
    snprintf(cmd, sizeof(cmd), "%s/%s/?api-version=%s", nv.az_host, nv.az_device_id, nv.az_api_version);
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SMCONF=\"USERNAME\"", ",", "\"", cmd, "\"", "\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); // return result;
    
    memset(cmd, 0, sizeof(cmd));
    snprintf(cmd, sizeof(cmd), "AT+SMCONF=\"PASSWORD\",\"SharedAccessSignature sr=%s%%2Fdevices%%2F%s&sig=%s%%3D&se=1687442641\"\r", nv.az_host , nv.az_device_id, nv.az_sas_token/*"DS2bbaYXsANATsMdAwesYfsV9A6tVxOvtOX%2BC1HV3jo" */);
    if (ewf_result_failed(result = ewf_interface_send(adapter_ptr->interface_ptr, (uint8_t *)cmd, 100))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_send(adapter_ptr->interface_ptr, (uint8_t *)cmd + 100, strlen(cmd) - 100))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); // return result;

    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SMCONF=\"KEEPALIVE\",1200\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); // return result;
    
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SMCONF=\"TIMEOUT\",1000\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); // return result;
        
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SMCONN\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); // return result;

    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SMSTATE?\r", NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\n+SMSTATE: 1\r\n\r\nOK\r\n"))) asm("bkpt"); // return result;

    memset(cmd, 0, sizeof(cmd));
    snprintf(cmd, sizeof(cmd), "AT+SMSUB=\"devices/%s/messages/devicebound/#\",1\r", nv.az_device_id);
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, cmd, NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); //return result;  

    int attempts;
    for(attempts = 0; attempts < 10; attempts++) {
        if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SMSUB=\"$iothub/twin/PATCH/properties/desired/#\",1\r", NULL))) asm("bkpt"); // return result;
        //if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\n+SMSUB: 1,0\r\n\r\nOK\r\n"))) { asm("bkpt"); goto again; }//return result;
        result = ewf_interface_verify_response_ends_with(adapter_ptr->interface_ptr, "\r\nOK\r\n");
        if (result == EWF_RESULT_OK)
            break;
        todo_sleep(3000);
    }
    if(attempts == 10)
        asm("bkpt");
    
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, "AT+SMSUB=\"$iothub/methods/POST/#\",1\r", NULL))) asm("bkpt"); // return result;
    //if (ewf_result_failed(result = ewf_interface_verify_response(adapter_ptr->interface_ptr, "\r\n+SMSUB: 2,0\r\n\r\nOK\r\n"))) asm("bkpt"); //return result
    if (ewf_result_failed(result = ewf_interface_verify_response_ends_with(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); //return result;
    //asm("bkpt");
    memset(cmd, 0, sizeof(cmd));
    snprintf(cmd, sizeof(cmd), "AT+SMPUB=\"devices/%s/messages/events/\",1,0,\"%s\"\r", nv.az_device_id, "hello world");
    if (ewf_result_failed(result = ewf_interface_send_commands(adapter_ptr->interface_ptr, cmd, NULL))) asm("bkpt"); // return result;
    if (ewf_result_failed(result = ewf_interface_verify_response_ends_with(adapter_ptr->interface_ptr, "\r\nOK\r\n"))) asm("bkpt"); //return result;
    
    EWF_LOG("\nCompleted successfully!\n");
    asm("bkpt");
    return EWF_RESULT_OK;
}

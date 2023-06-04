/************************************************************************//**
 * @file
 * @version Preview
 * @copyright Copyright (c) Microsoft Corporation. All rights reserved.
 * SPDX-License-Identifier: MIT
 * @brief The Embedded Wireless Framework Simcom SIM868
 * @details EWF certificate provisioning example for Simcom SIM868
 ****************************************************************************/

#include "ewf_adapter_simcom_sim868.h"

#include "ewf_app_simcom_common.c"

ewf_result ewf_mqtt_connect_simcom_sim868(ewf_adapter* adapter_ptr)
{
    EWF_ADAPTER_VALIDATE_POINTER(adapter_ptr);
    EWF_ADAPTER_VALIDATE_POINTER_TYPE(adapter_ptr, EWF_ADAPTER_TYPE_SIMCOM_SIM868);

    return ewf_simcom_common(adapter_ptr);
}

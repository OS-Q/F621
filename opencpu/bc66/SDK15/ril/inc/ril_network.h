/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Quectel Co., Ltd. 2019
*
*****************************************************************************/
/*****************************************************************************
 *
 * Filename:
 * ---------
 *   ril_network.h 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   The file declares some API functions, which are related to network, including
 *   SIM state, GSM/GPRS network state and signal strength, and so forth.
 *
 * Author:
 * -------
 * -------
 *
 *============================================================================
 *             HISTORY
 *----------------------------------------------------------------------------
 * 
 ****************************************************************************/
#ifndef __RIL_NETWORK_H__
#define __RIL_NETWORK_H__
#include "ql_type.h"
#include "ril_sim.h"


/****************************************************************************
 * Definition for network State
 ***************************************************************************/
typedef enum {
    NW_STAT_NOT_REGISTERED = 0,    // Not register to network
    NW_STAT_REGISTERED,            // The normal network state
    NW_STAT_SEARCHING,             // Searching network
    NW_STAT_REG_DENIED,            // The register request is denied
    NW_STAT_UNKNOWN,
    NW_STAT_REGISTERED_ROAMING     //Registered and Roaming state
}Enum_NetworkState;

typedef enum {
    CFUN_MIN_FUNC,		/* Minimum functionality */
    CFUN_FULL_FUNC,		/* Full functionality */
    CFUN_DISABLE_RF_RXTX = 4,
    CFUN_FULL_RF_CLOSED_SIM = 7
}Enum_Cfun_Level;

typedef enum {
	PSM_DISABLE = 0,
	PSM_ENABLE = 1
}Enum_PSM_Mode;

/*****************************************************************
* Function:     RIL_NW_SetCFUN
* 
* Description:
*               This function selects the level of functionality in the MT. 
*		    Level "full functionality" is where the highest level of power is drawn. 
*		    Level "minimum functionality" is where minimum power is drawn.
*
* Parameters:       
*               cfun:
*                   [in] the level of functionality want to select, one value of Enum_Cfun_Level. 
*
* Return:        
*                RIL_AT_SUCCESS,send AT successfully.
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
*****************************************************************/
s32 RIL_NW_SetCFUN(Enum_Cfun_Level cfun);

/*****************************************************************
* Function:     RIL_NW_SetPSM
* 
* Description:
*               This function is used to set power saving mode.
*
* Parameters:       
*               mode:
*                   [in] power saving mode to set, one value of Enum_PSM_Mode. 
*
* Return:        
*                RIL_AT_SUCCESS,send AT successfully.
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
*****************************************************************/
s32 RIL_NW_SetPSM(Enum_PSM_Mode mode);

/******************************************************************************
* Function:     RIL_NW_GetGPRSState
*  
* Description:
*               This function gets the GPRS network register state. 
*
* Parameters:    
*               stat:
*                   [out]GPRS State.
* Return:  
*               One value of Enum_NetworkState: network register state code.
*               -1 : fail to get the network state.
******************************************************************************/
s32  RIL_NW_GetEGPRSState(s32 *stat);

/******************************************************************************
* Function:     RIL_NW_GetCSQ
*  
* Description:
*               This function gets the received signal strength level <rssi> and the channel bit error rate. 
*
* Parameters:    
*               value:
*                   [out]A pointer for store the signal quality value.
* Return:  
*                RIL_AT_SUCCESS,send AT successfully.
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32  RIL_NW_GetCSQ(s32 *value);

/******************************************************************************
* Function:     RIL_NW_GetCSCON
*  
* Description:
*               This function checks whether the MT is currently in idle mode or connected mode. 
*
* Parameters:    
*               state:
*                   [out]Current working status of module.
* Return:  
*                RIL_AT_SUCCESS,send AT successfully.
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32  RIL_NW_GetCSCON(u8 *state);

/******************************************************************************
* Function:     RIL_NW_GetQENG
*  
* Description:
*               This function querys current modem status information for serving cell and current network 
*		    status in Engineering Mode. 
*
* Parameters:    
*               mode:
*                   [in] integer value indicating requested engineering information.
*                   0   Display radio information for serving and neighbor cells.
*                   1   Display data transfer information only if modem in RRC-CONNECTED state.
*                   2   Display Tx/Rx total working duration time information.
*               rsp:
*			 [out]
*				If mode = 0: radio information for serving and neighbor cells.
*				If mode = 1: data transfer information  if modem in RRC-CONNECTED state.
*				If mode = 2: Tx/Rx total working duration time information.
*
* Return:  
*                RIL_AT_SUCCESS,send AT successfully.
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32  RIL_NW_GetQENG(u8 mode, s32* rsp);

#endif // __RIL_NETWORK_H__

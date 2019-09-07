#include "qurt_timetick.h"

qurt_time_t qurt_timetick_user_impl(UINT id, qurt_time_t a, UINT b)
{
  qurt_time_t qurt_time_tick_res = 0;
  UINT alower;
  UINT aupper;
  UINT c = 0, d = 0;
  switch(id)
  {
    case TXM_QURT_TIMETICK_GET_TICKS:
      if(TX_SUCCESS != (_txm_module_system_call12)(id, (ULONG) &c, (ULONG) &d, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
      {
        return (qurt_time_t)(~0x0);
      }
      break;
    case TXM_QURT_TIMETICK_GET_CVT_TIME_TO_TICKS:
    case TXM_QURT_TIMETICK_SET_CVT_TICKS_TO_TIME:
	  alower = a & 0xFFFFFFFF;					// lower word of 64-bits timetick 
	  aupper = (a>>32) & 0xFFFFFFFF ;			// upper word of 64-bits timetick
      if(TX_SUCCESS != (_txm_module_system_call12)(id, (ULONG) &c, (ULONG) &d, (ULONG) alower, (ULONG) aupper, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
      {
        return (qurt_time_t)(~0x0);
      }
      break;
    default :
      return (qurt_time_t)(~0x0);
  }
  qurt_time_tick_res = ((qurt_time_t)(c) << 32) | (d);
  return qurt_time_tick_res;
}


#include "qapi_adc.h"
int qapi_custom_cb_ADC_dispatcher(UINT cb_id, void *app_cb, 
									 UINT cb_param1, UINT cb_param2, 
									 UINT cb_param3, UINT cb_param4,
									 UINT cb_param5, UINT cb_param6,
									 UINT cb_param7, UINT cb_param8)
{
	qapi_AdcTM_Threshold_Cb_Type  pfn_app_cb1;
	
	if(cb_id == TXM_QAPI_ADC_AMP_THRESHOLD_CB)
	{
		pfn_app_cb1 = (qapi_AdcTM_Threshold_Cb_Type)app_cb;
		(pfn_app_cb1)((void *) cb_param1, (qapi_ADC_Threshold_Result_t *)&cb_param2);
		
	}	
	if(cb_id == TXM_QAPI_ADC_SET_TOLERENCE_CB)
	{
	    pfn_app_cb1 = (qapi_AdcTM_Threshold_Cb_Type)app_cb;
	    (pfn_app_cb1)((void *) cb_param1, (qapi_ADC_Threshold_Result_t *)&cb_param2);
		
	}
	return 0;
}
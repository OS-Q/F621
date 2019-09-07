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
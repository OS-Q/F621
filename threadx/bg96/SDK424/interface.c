/*
 *  Created on: 09.05.2018
 *      Author: Georgi Angelov
 */

#include "txm_module.h"
#include "tx_api.h"
#include "qapi_timer.h"
#include "qapi_timer_id.h"

#pragma GCC optimize 0

#define SEC_LIB __attribute__((section(".library"))) // just for sorting

SEC_LIB void fake_make_used(void) /* GCC MAKE PREAMBLE USED - DONT TOUCH */
{
	extern volatile TXM_MODULE_PREAMBLE _txm_module_preamble;
	if (_txm_module_preamble.txm_module_preamble_checksum)
		__asm__ volatile("NOP");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 	QUALCOMM LIBRARIES
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ULONG(*_txm_module_kernel_call_dispatcher)
(ULONG, ULONG, ULONG, ULONG) = NULL;
static TXM_MODULE_THREAD_ENTRY_INFO *_txm_module_entry_info = NULL;
static TXM_MODULE_INSTANCE *_txm_module_instance_ptr = NULL;

SEC_LIB void TXM_MODULE_SHELL_ENTRY(TX_THREAD *thread_ptr, TXM_MODULE_THREAD_ENTRY_INFO *thread_info)
{
	fake_make_used();
	if (thread_info->txm_module_thread_entry_info_start_thread)
	{
		_txm_module_instance_ptr = thread_info->txm_module_thread_entry_info_module;
		_txm_module_entry_info = thread_info;
		_txm_module_kernel_call_dispatcher = thread_info->txm_module_thread_entry_info_kernel_call_dispatcher;
		while (NULL == _txm_module_kernel_call_dispatcher)
			;
		tx_thread_resume(thread_info->txm_module_thread_entry_info_callback_request_thread); // 66
	}
	thread_info->txm_module_thread_entry_info_entry(thread_info->txm_module_thread_entry_info_parameter);
	txm_module_thread_system_suspend(thread_ptr); // 91
}

SEC_LIB void TXM_MODULE_CALLBACK_REQUEST(ULONG id)
{
	TXM_MODULE_CALLBACK_NOTIFY msg;
	TX_QUEUE *req_queue = _txm_module_entry_info->txm_module_thread_entry_info_callback_request_queue;
	TX_QUEUE *resp_queue = _txm_module_entry_info->txm_module_thread_entry_info_callback_response_queue;
	do
	{
		if (tx_queue_receive(req_queue, &msg, TX_NO_WAIT)) // 42
			break;
		switch (msg.txm_module_callback_notify_type)
		{
		case 0u:
		case 1u:
		case 2u:
		case 3u:
			((void (*)(ULONG))msg.txm_module_callback_notify_application_function)(msg.txm_module_callback_notify_param_1);
			break;
		case 4u:
			((void (*)(ULONG, ULONG))msg.txm_module_callback_notify_application_function)(msg.txm_module_callback_notify_param_1, msg.txm_module_callback_notify_param_2);
			break;
		default:
			break;
		}
	} while (TX_SUCCESS == tx_queue_send(resp_queue, &msg, TX_NO_WAIT)); // 43
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SEC_LIB ULONG _txm_module_system_call4(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4)
{
	ULONG extra_parameters[2];
	extra_parameters[0] = param_3;
	extra_parameters[1] = param_4;
	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG)extra_parameters);
}

SEC_LIB ULONG _txm_module_system_call5(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5)
{
	ULONG extra_parameters[3];
	extra_parameters[0] = param_3;
	extra_parameters[1] = param_4;
	extra_parameters[2] = param_5;
	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG)extra_parameters);
}

SEC_LIB ULONG _txm_module_system_call6(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6)
{
	ULONG extra_parameters[4];
	extra_parameters[0] = param_3;
	extra_parameters[1] = param_4;
	extra_parameters[2] = param_5;
	extra_parameters[3] = param_6;
	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG)extra_parameters);
}

SEC_LIB ULONG _txm_module_system_call7(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7)
{
	ULONG extra_parameters[5];
	extra_parameters[0] = param_3;
	extra_parameters[1] = param_4;
	extra_parameters[2] = param_5;
	extra_parameters[3] = param_6;
	extra_parameters[4] = param_7;
	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG)extra_parameters);
}

SEC_LIB ULONG _txm_module_system_call8(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8)
{
	ULONG extra_parameters[6];
	extra_parameters[0] = param_3;
	extra_parameters[1] = param_4;
	extra_parameters[2] = param_5;
	extra_parameters[3] = param_6;
	extra_parameters[4] = param_7;
	extra_parameters[5] = param_8;
	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG)extra_parameters);
}

SEC_LIB ULONG _txm_module_system_call9(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8, ULONG param_9)
{
	ULONG extra_parameters[7];
	extra_parameters[0] = param_3;
	extra_parameters[1] = param_4;
	extra_parameters[2] = param_5;
	extra_parameters[3] = param_6;
	extra_parameters[4] = param_7;
	extra_parameters[5] = param_8;
	extra_parameters[6] = param_9;
	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG)extra_parameters);
}

SEC_LIB ULONG _txm_module_system_call10(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8, ULONG param_9, ULONG param_10)
{
	ULONG extra_parameters[8];
	extra_parameters[0] = param_3;
	extra_parameters[1] = param_4;
	extra_parameters[2] = param_5;
	extra_parameters[3] = param_6;
	extra_parameters[4] = param_7;
	extra_parameters[5] = param_8;
	extra_parameters[6] = param_9;
	extra_parameters[7] = param_10;
	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG)extra_parameters);
}

SEC_LIB ULONG _txm_module_system_call11(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8, ULONG param_9, ULONG param_10, ULONG param_11)
{
	ULONG extra_parameters[9];
	extra_parameters[0] = param_3;
	extra_parameters[1] = param_4;
	extra_parameters[2] = param_5;
	extra_parameters[3] = param_6;
	extra_parameters[4] = param_7;
	extra_parameters[5] = param_8;
	extra_parameters[6] = param_9;
	extra_parameters[7] = param_10;
	extra_parameters[8] = param_11;
	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG)extra_parameters);
}

SEC_LIB ULONG _txm_module_system_call12(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8, ULONG param_9, ULONG param_10, ULONG param_11, ULONG param_12)
{
	ULONG extra_parameters[10];
	extra_parameters[0] = param_3;
	extra_parameters[1] = param_4;
	extra_parameters[2] = param_5;
	extra_parameters[3] = param_6;
	extra_parameters[4] = param_7;
	extra_parameters[5] = param_8;
	extra_parameters[6] = param_9;
	extra_parameters[7] = param_10;
	extra_parameters[8] = param_11;
	extra_parameters[9] = param_12;
	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG)extra_parameters);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "qapi_timer.h"
#include "qapi_timer_id.h"

#define HIDWORD(Z) Z >> 32
static int qapi_timer_user_initialized = 0;
static qapi_TIMER_handle_t *timer_user_handle = NULL;
char timer_client_stack[4096]; // Memory Protection !!!
static TX_THREAD *timer_client_module_thread;
static int timer_thread_state;
int timer_client_cb_handler(ULONG arg);

SEC_LIB void qapi_timer_user_init(void)
{
	if (!qapi_timer_user_initialized)
	{
		_txm_module_system_call12(TXM_QAPI_TIMER_GET_USER_HANDLE, (ULONG)timer_user_handle, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); //65794
		qapi_timer_user_initialized = 1;
		if (timer_user_handle)
		{
			txm_module_object_allocate(timer_client_module_thread, sizeof(TX_THREAD)); // 93
			timer_thread_state = _txm_module_system_call11(
				(ULONG)TXM_THREAD_CREATE_CALL, // 55
				(ULONG)timer_client_module_thread,
				(ULONG) "TIMER_USER_THREAD",
				(ULONG)timer_client_cb_handler,
				(ULONG)timer_user_handle,
				(ULONG)timer_client_stack, sizeof(timer_client_stack),
				15, 1, 0, 1, 280);
			if (timer_thread_state)
				qapi_timer_user_initialized = 0;
		}
		else
			qapi_timer_user_initialized = 0;
	}
}

SEC_LIB qapi_Status_t qapi_Timer_Get_Cbinfo(ULONG handle, void *cb)
{
	if (cb && handle)
		return _txm_module_system_call12(TXM_QAPI_TIMER_GET_CBINFO, (ULONG)handle, (ULONG)cb, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); //65793
	else
		return QAPI_ERR_INVALID_PARAM;
}

SEC_LIB int timer_client_cb_handler(ULONG arg)
{
	void (*cb)(int);
	int result = 0;
	if (arg)
	{
		while (1)
		{
			result = qapi_Timer_Get_Cbinfo(arg, &cb);
			if (result)
				break;
			if (cb)
				cb(0); // ???
		}
	}
	return result;
}

SEC_LIB qapi_Status_t qapi_Timer_Def(qapi_TIMER_handle_t *timer_handle, qapi_TIMER_define_attr_t *timer_attr)
{
	if (!timer_handle || !timer_attr)
		return QAPI_ERR_INVALID_PARAM;
	if (qapi_timer_user_initialized != 1)
		qapi_timer_user_init();
	return _txm_module_system_call12(TXM_QAPI_TIMER_DEF, (ULONG)timer_handle, (ULONG)timer_attr, (ULONG)timer_user_handle, 0, 0, 0, 0, 0, 0, 0, 0, 0); //65786
}

SEC_LIB qapi_Status_t qapi_Timer_Undef(qapi_TIMER_handle_t timer_handle)
{
	if (timer_handle)
		return _txm_module_system_call12(TXM_QAPI_TIMER_UNDEF, (ULONG)timer_handle, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); //65789
	return QAPI_ERR_INVALID_PARAM;
}

SEC_LIB qapi_Status_t qapi_Timer_Set(qapi_TIMER_handle_t timer_handle, qapi_TIMER_set_attr_t *timer_attr)
{
	if (timer_handle && timer_attr)
		return _txm_module_system_call12(TXM_QAPI_TIMER_SET, (ULONG)timer_handle, (ULONG)timer_attr, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); //65787
	return QAPI_ERR_INVALID_PARAM;
}

SEC_LIB qapi_Status_t qapi_Timer_Get_Timer_Info(qapi_TIMER_handle_t timer_handle, qapi_TIMER_get_info_attr_t *timer_get_info_attr, uint64_t *data)
{
	if (timer_handle && timer_get_info_attr && data)
		return _txm_module_system_call12(TXM_QAPI_TIMER_GET_INFO, (ULONG)timer_handle, (ULONG)timer_get_info_attr, (ULONG)data, 0, 0, 0, 0, 0, 0, 0, 0, 0); //65790
	return QAPI_ERR_INVALID_PARAM;
}

SEC_LIB qapi_Status_t qapi_Timer_Stop(qapi_TIMER_handle_t timer_handle)
{
	if (timer_handle)
		return _txm_module_system_call12(TXM_QAPI_TIMER_STOP, (ULONG)timer_handle, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); //65788
	return QAPI_ERR_INVALID_PARAM;
}

SEC_LIB qapi_Status_t qapi_time_get(qapi_time_unit_type time_get_unit, qapi_time_get_t *time)
{
	if (time_get_unit >= QAPI_TIME_STAMP && time_get_unit <= QAPI_TIME_JULIAN && time)
		return _txm_module_system_call12(TXM_QAPI_TIME_GET, time_get_unit, (ULONG)time, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); //65792
	return QAPI_ERR_INVALID_PARAM;
}

SEC_LIB qapi_Status_t qapi_Timer_Sleep(uint64_t timeout, qapi_TIMER_unit_type unit, qbool_t non_deferrable)
{
	if (unit < 6)
		return _txm_module_system_call12(TXM_QAPI_TIMER_SLEEP, HIDWORD(timeout), timeout, unit, non_deferrable, 0, 0, 0, 0, 0, 0, 0, 0); //65791
	return QAPI_ERR_INVALID_PARAM;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SEC_LIB ULONG psm_user_space_dispatcher(ULONG request, ULONG (*func)(ULONG), ULONG arg)
{
	if (request == 108 && func)
		return func(arg);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SEC_LIB ULONG diag_user_space_dispatcher(ULONG request, ULONG (*func)(ULONG), ULONG arg)
{
	if (request == 102 && func)
		return func(arg);
	return 0;
}
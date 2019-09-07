/*
 *  Created on: 04.06.2018
 *      Author: Georgi Angelov
 */

#include <txm_module.h>

//CONSTANTS FROM LINKER
extern volatile void (*IMAGE_ER_RO_LENGTH 	 []) (void);
extern volatile void (*IMAGE_ER_ZI_ZI_LENGTH []) (void);
extern volatile void (*IMAGE_ER_RW_LENGTH 	 []) (void);

//FUNCTIONS
extern void TXM_MODULE_SHELL_ENTRY(TX_THREAD *thread_ptr, TXM_MODULE_THREAD_ENTRY_INFO *thread_info);
extern int  TXM_MODULE_THREAD_ENTRY(void);
extern void TXM_MODULE_CALLBACK_REQUEST(ULONG id);

volatile TXM_MODULE_PREAMBLE _txm_module_preamble  __attribute__ (( section(".preamble"), used )) =
{
	(ULONG)0x4D4F4455,											/* Download Module ID ( UDOM )           */
	(ULONG)5,													/* Major Version ID                      */
    (ULONG)3,													/* Minor Version ID                      */
    (ULONG)32,													/* Module Preamble Size, in 32-bit words */
    (ULONG)0x12345678,											/* Module ID (application defined)       */
    (ULONG)0x01000000,											/* Properties Bit Map - RVDS, no MMU     */
    (ULONG)TXM_MODULE_SHELL_ENTRY       - _RO_BASE_,			/* Module Shell Entry Function           */
    (ULONG)TXM_MODULE_THREAD_ENTRY      - _RO_BASE_,			/* Module Thread Start Function          */
    (ULONG)0,													/* Module Thread Stop Function           */
    (ULONG)180,													/* Module Thread Priority            	 */
    (ULONG)8192,												/* Module Thread Stack            		 */
    (ULONG)TXM_MODULE_CALLBACK_REQUEST  - _RO_BASE_,			/* Module Callback Thread Function       */
    (ULONG)25,													/* Module Callback Thread Priority       */
    (ULONG)2048,												/* Module Callback Thread Stack Size     */
    (ULONG)IMAGE_ER_RO_LENGTH,									/* Module Instruction Area Size          */
    (ULONG)IMAGE_ER_ZI_ZI_LENGTH,								/* Module BSS Area Size                  */
    (ULONG)_RO_BASE_,											/* RO_BASE                               */
    (ULONG)IMAGE_ER_RW_LENGTH,									/* Module DATA Area Size                 */
};

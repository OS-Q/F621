/*
 *  Created on: 24.02.2019
 *      Author: Georgi Angelov
 * NOT READY
 */

#include <Arduino.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "coap.h"
#include "pdu.h"

#ifdef __cplusplus
} // extern "C"
#endif

typedef enum
{
    COAP_CLIENT = 0x0,
    COAP_SERVER = 0x1,
} coap_dev_role_t;

typedef enum
{
    COAP_DEV_TYPE_UNUSED = 0x0,
    COAP_DEV_TYPE_SOCKET = 0x1,
    COAP_DEV_TYPE_CID = 0x2,
    COAP_DEV_TYPE_CTX = 0x3,
    COAP_DEV_TYPE_SET = 0x4,
} coap_dev_type_t;

typedef enum
{
    COAP_GET = 0x1,
    COAP_POST = 0x2,
    COAP_PUT = 0x3,
    COAP_DELETE = 0x4,
} coap_method_t;

typedef struct
{
    uint8_t sign;
    uint8_t role;
    coap_address_t dst;
    coap_context_t *ctx;
    TaskHandle_t handle;
} coap_dev_info_t;

class COAP
{
  private:
    coap_dev_info_t dev;
    bool new_client();
    bool new_server();

  public:
    COAP(){}
    bool begin(coap_dev_role_t role, const char *host, u16_t port);
    void end();
    bool get(const char *s);
};
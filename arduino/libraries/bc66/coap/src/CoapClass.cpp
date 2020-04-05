/*
 *  Created on: 24.02.2019
 *      Author: Georgi Angelov
 * NOT READY
 */


#include "CoapClass.h"

#define TEST_RAW "\x40\x01\x41\xC7\xB7" \
                 "_wizio_"

static void client_callback(struct coap_context_t *,
                            const coap_address_t *remote,
                            coap_pdu_t *sent,
                            coap_pdu_t *received,
                            const coap_tid_t id)
{
    DBG("\n[COAP] Receive[%d] tid = %d %.62s . . .\n", (int)received->length, (int)id, received->data);
    //</test>;rt="test";ct=0,</validate>;rt="validate";ct=0,</hello>
}

static void coap_client_task(void *arg)
{
    if (arg)
    {
        coap_dev_info_t *dev = (coap_dev_info_t *)arg;
        DBG("[COAP] Client started\n");
        int res;
        timeval tv;
        fd_set rx;
        dev->sign = 0;
        while (1)
        {
            FD_ZERO(&rx);
            FD_SET(dev->ctx->sockfd, &rx);
            tv.tv_sec = 1;
            tv.tv_usec = 0;
            res = lwip_select(dev->ctx->sockfd + 1, &rx, 0, 0, &tv);
            if (res > 0 && FD_ISSET(dev->ctx->sockfd, &rx))
            {
                coap_read(dev->ctx);
                coap_dispatch(dev->ctx);
            }
        }
    }
}

bool COAP::new_client()
{
    coap_address_t local;
    local.size = 16;
    local.addr.sin.sin_addr.s_addr = 0;
    local.addr.sa.sa_len = 16;
    local.addr.sin.sin_port = 0;
    local.addr.sa.sa_family = AF_INET;
    dev.ctx = coap_new_context((const coap_address_t *)&local); //create UDP, reuse, bind
    if (dev.ctx)
    {
        coap_register_response_handler(dev.ctx, client_callback);
        xTaskGenericCreate(coap_client_task, "coapC", 512, &dev, 4u, &dev.handle, NULL, NULL);
    }
    else
    {
        DBG("[COAP] ERROR CONTEXT\n");
    }
    return (bool)dev.ctx;
}

bool COAP::new_server() { return false; }

bool COAP::begin(coap_dev_role_t role, const char *host, u16_t port)
{
    end();

    sockaddr_in sa;
    if (port && host && resolveAddress(host, &sa) < 0)
        return false;

    uint8_t *p = (uint8_t *)&sa.sin_addr.s_addr;
    DBG("[COAP] coap://%s:%d [%d.%d.%d.%d]\n", host, (int)port, (int)p[0], (int)p[1], (int)p[2], (int)p[3] );

    dev.sign = 1;
    dev.dst.addr.sin.sin_addr.s_addr = sa.sin_addr.s_addr;
    dev.dst.size = 16;
    dev.dst.addr.sa.sa_len = 16;
    dev.dst.addr.sa.sa_family = AF_INET;
    dev.dst.addr.sin.sin_port = lwip_htons(port);
    dev.role = role;
    if (COAP_CLIENT == role)
        return new_client();
    else
        return new_server();
}

void COAP::end()
{
    if (dev.handle)
        vTaskSuspend(dev.handle); // stop loop
    if (dev.ctx)
        coap_free_context(dev.ctx); //delete all and close
    if (dev.handle)
        vTaskDelete(dev.handle);
    memset(&dev, 0, sizeof(coap_dev_info_t));
}

coap_pdu_t *coap_new_pdu(void)
{
    coap_pdu_t *pdu;
    pdu = coap_pdu_init(0, 0, ntohs(COAP_INVALID_TID), COAP_MAX_PDU_SIZE);
    return pdu;
}

coap_pdu_t *coap_new_request(coap_context_t *ctx, coap_method_t m, coap_list_t *options, unsigned char *data, size_t size)
{
    unsigned char _token_data[8];
    str the_token = {0, _token_data};
    coap_pdu_t *pdu;
    coap_list_t *opt;
    if (NULL == ctx)
        return NULL;
    pdu = coap_new_pdu();
    if (NULL == pdu)
        return NULL;
    pdu->hdr->type = COAP_MESSAGE_CON;
    pdu->hdr->id = coap_new_message_id(ctx);
    pdu->hdr->code = m;
    pdu->hdr->token_length = the_token.length;
    if (!coap_add_token(pdu, the_token.length, the_token.s))
    {
        DBG("cannot add token to request\n");
    }
    for (opt = options; opt; opt = opt->next)
        coap_add_option(pdu,
                        COAP_OPTION_KEY(*(coap_option *)opt->data),
                        COAP_OPTION_LENGTH(*(coap_option *)opt->data),
                        COAP_OPTION_DATA(*(coap_option *)opt->data));
    if (size && data)
        coap_add_data(pdu, size, data);
    return pdu;
}

bool COAP::get(const char *s)
{
    while (dev.sign)
        Ql_Sleep(10);
    int res = -1;
    if (dev.ctx)
    {
        coap_pdu_t *pdu = coap_new_request(dev.ctx, COAP_GET, NULL, (uint8_t *)s, strlen(s));
        if (pdu)
            res = coap_send(dev.ctx, &dev.dst, pdu);
    }
    DBG("[COAP] GET tid = %d\n", res);
    return res == 0;
}
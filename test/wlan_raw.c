#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sys_config.h"
#include "rtos_pub.h"
#include "wlan_ui_pub.h"
#include "common.h"
#include "mem_pub.h"
#include "uart_pub.h"
#include "sys_ctrl_pub.h"
#include "drv_model_pub.h"
#include "rw_pub.h"
#include "rwnx.h"
#include "app.h"
#include "test_config.h"

#ifdef WLAN_RAW
extern WIFI_CORE_T g_wifi_core;

static uint8_t espnow_ethheader[] = {
	0xd0,
	0x00,
	0x3a, 0x01,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x11, 0x22, 0x33, 0x44, 0x55, 0x66,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x70, 0x51, 0x7f, 0x18,	0xfe, 0x34, 0xa2, 0x03, 0x92, 0xb0, 0xdd, 0xff, 0x18, 0xfe, 0x34, 0x04, 0x01
};
#define ETHHEADER_SIZE (sizeof(espnow_ethheader) * sizeof(uint8_t))
#define LEN_RAWBYTES_MAX 512
extern int bmsg_tx_raw_sender(uint8_t *payload, uint16_t length);


static int wlan_raw(int argc, char *argv[]) {
	bk_wlan_start_monitor();
	bk_wlan_set_channel_sync(1);

	os_printf("Sending ESPNOW broadcast\r\n");

	uint8_t payload[] = "bk7252_ESPNOW";
	int len_payload = sizeof(payload) -1; // -1 if payload is initialized as string

	uint16_t raw_len = ETHHEADER_SIZE + len_payload + 4;
	uint8_t *raw_msg = os_malloc(ETHHEADER_SIZE + len_payload + 4);

	os_memcpy(raw_msg, espnow_ethheader, ETHHEADER_SIZE);
	uint8_t src_mac[6] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
	uint8_t dst_mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	os_memcpy(raw_msg +4, dst_mac, sizeof(uint8_t) *6);
	os_memcpy(raw_msg +10, src_mac, sizeof(uint8_t) *6);
	os_memcpy(raw_msg +16, dst_mac, sizeof(uint8_t) *6);
	raw_msg[33] = len_payload +5;

	os_memcpy(raw_msg +ETHHEADER_SIZE, payload, len_payload);

	bmsg_tx_raw_sender(raw_msg, raw_len);

	bk_wlan_stop_monitor();
	
	return 0;
}

MSH_CMD_EXPORT(wlan_raw, send raw wlan frames);

#endif

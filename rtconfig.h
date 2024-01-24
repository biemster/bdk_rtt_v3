#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Configuration */

/* RT-Thread Kernel */

#define RT_NAME_MAX 8
#define RT_ALIGN_SIZE 4
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 1000
#define RT_DEBUG
#define RT_USING_OVERFLOW_CHECK 1
#define RT_DEBUG_INIT 0
#define RT_DEBUG_THREAD 0
#define RT_USING_HOOK 1
#define IDLE_THREAD_STACK_SIZE 512
#define RT_USING_TIMER_SOFT 1
#define RT_TIMER_THREAD_PRIO 6/*4*/
#define RT_TIMER_THREAD_STACK_SIZE 4096

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE 1
#define RT_USING_MUTEX 1
#define RT_USING_EVENT 1
#define RT_USING_MAILBOX 1
#define RT_USING_MESSAGEQUEUE 1

/* Memory Management */

#define RT_USING_MEMPOOL 1
#define RT_USING_MEMHEAP 1
#define RT_USING_MEMHEAP_AS_HEAP 1
#define RT_USING_HEAP 1

/* Kernel Device Object */

#define RT_USING_DEVICE 1
#define RT_USING_DEVICE_OPS 1
#define RT_USING_CONSOLE 1
#define RT_CONSOLEBUF_SIZE 128
#define RT_CONSOLE_DEVICE_NAME "uart2"

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT 1
#define RT_USING_USER_MAIN 1
#define RT_MAIN_THREAD_STACK_SIZE 4096

/* Command shell */

#define RT_USING_FINSH 1
#define FINSH_THREAD_NAME "tshell"
#define FINSH_USING_HISTORY 1
#define FINSH_HISTORY_LINES 5
#define FINSH_USING_SYMTAB 1
#define FINSH_USING_DESCRIPTION 1
#define FINSH_THREAD_PRIORITY 20
#define FINSH_THREAD_STACK_SIZE 8192
#define FINSH_CMD_SIZE 256
#define FINSH_USING_MSH 1
#define FINSH_USING_MSH_DEFAULT
#define FINSH_USING_MSH_ONLY
#define FINSH_ARG_MAX 16

/* Device virtual file system */
#define RT_USING_DFS 1
#define DFS_USING_WORKDIR 1
#define DFS_FILESYSTEMS_MAX 4
#define DFS_FILESYSTEM_TYPES_MAX 4
#define DFS_FD_MAX 16
#define RT_USING_DFS_ELMFAT 1

/* elm-chan's FatFs, Generic FAT Filesystem Module */

#define RT_DFS_ELM_CODE_PAGE 437
#define RT_DFS_ELM_WORD_ACCESS
#define RT_DFS_ELM_USE_LFN_3
#define RT_DFS_ELM_USE_LFN 3
#define RT_DFS_ELM_MAX_LFN 255
#define RT_DFS_ELM_DRIVES 2
#define RT_DFS_ELM_MAX_SECTOR_SIZE 512
#define RT_DFS_ELM_REENTRANT 1
#define RT_USING_DFS_DEVFS 1
#define RT_USING_DFS_NET 1
#define RT_USING_DFS_ROMFS 1

/* Device Drivers */
//#define BEKEN_USING_IIC
#define RT_USING_DEVICE_IPC 1
#define RT_USING_SERIAL 1
//#define RT_USING_I2C 1
//#define RT_USING_I2C_BITOPS 1
#define RT_USING_PIN 1
#define RT_USING_RTC 1
#define RT_USING_SOFT_RTC 1
#define RTC_SYNC_USING_NTP 1
#define RTC_NTP_FIRST_SYNC_DELAY 30
#define RTC_NTP_SYNC_PERIOD 3600
#define RT_USING_WDT 1
#define RT_USING_WIFI 1
#define RT_USING_WLAN_STA 1
#define RT_USING_WLAN_AP 1
#define WIFI_DEVICE_STA_NAME "w0"
#define WIFI_DEVICE_AP_NAME "ap"
#define RT_USING_AUDIO 1
#define RT_USING_SPI 1
#define RT_USING_I2S 1

/* Using USB */


/* POSIX layer and C standard library */

#define RT_USING_LIBC 1
#define RT_USING_POSIX 1

/* Network stack */

/* light weight TCP/IP stack */

#define RT_USING_LWIP 1
#define RT_USING_LWIP202 1
#define RT_LWIP_IGMP 1
#define RT_LWIP_ICMP 1
#define RT_LWIP_DNS 1
#define RT_LWIP_DHCP 1
#define IP_SOF_BROADCAST 1
#define IP_SOF_BROADCAST_RECV 1

/* Static IPv4 Address */

#define RT_LWIP_IPADDR "192.168.1.30"
#define RT_LWIP_GWADDR "192.168.1.1"
#define RT_LWIP_MSKADDR "255.255.255.0"
#define RT_LWIP_UDP 1
#define RT_LWIP_TCP 1
#define RT_LWIP_RAW 1
#define RT_MEMP_NUM_NETCONN 12
#define RT_LWIP_PBUF_NUM 14
#define RT_LWIP_RAW_PCB_NUM 2
#define RT_LWIP_UDP_PCB_NUM 6
#define RT_LWIP_TCP_PCB_NUM 8
#define RT_LWIP_TCP_SEG_NUM 40
#define RT_LWIP_TCP_SND_BUF 4380
#define RT_LWIP_TCP_WND 4380
#define RT_LWIP_TCPTHREAD_PRIORITY 4
#define RT_LWIP_TCPTHREAD_MBOX_SIZE 8
#define RT_LWIP_TCPTHREAD_STACKSIZE 2048
#define LWIP_NO_RX_THREAD
#define LWIP_NO_TX_THREAD
#define RT_LWIP_ETHTHREAD_PRIORITY 12
#define RT_LWIP_ETHTHREAD_STACKSIZE 512
#define RT_LWIP_ETHTHREAD_MBOX_SIZE 8
#define LWIP_NETIF_STATUS_CALLBACK 1
#define SO_REUSE 1
#define LWIP_SO_RCVTIMEO 1
#define LWIP_SO_SNDTIMEO 1
#define LWIP_SO_RCVBUF 1
#define LWIP_NETIF_LOOPBACK 0

/* Modbus master and slave stack */

#define LWIP_USING_DHCPD 1
#define DHCPD_SERVER_IP "192.168.169.1"
#define DHCPD_USING_ROUTER

/* VBUS(Virtual Software BUS) */


/* Utilities */


/* RT-Thread online packages */

/* IoT - internet of things */

#define PKG_USING_PAHOMQTT 1
#define PAHOMQTT_PIPE_MODE
#define PKG_USING_PAHOMQTT_EXAMPLE
#define RT_PKG_MQTT_THREAD_STACK_SIZE 4096
#define PKG_PAHOMQTT_SUBSCRIBE_HANDLERS 1
#define MQTT_DEBUG
#define PKG_USING_PAHOMQTT_LATEST
#define PKG_USING_WEBCLIENT 1
#define WEBCLIENT_HEADER_BUFSZ 4096
#define WEBCLIENT_RESPONSE_BUFSZ 4096
#define PKG_USING_WEBCLIENT_LATEST_VERSION
#define PKG_USING_CJSON 1
#define PKG_USING_CJSON_V102

/* Wi-Fi */

/* Marvell WiFi */


/* Wiced WiFi */

#define PKG_USING_NETUTILS 1
#define PKG_NETUTILS_PING
#define PKG_NETUTILS_NETIO
#define PKG_NETUTILS_NTP 1
#define NETUTILS_NTP_TIMEZONE 8
#define NETUTILS_NTP_HOSTNAME "cn.ntp.org.cn"
#define PKG_USING_NETUTILS_LATEST_VERSION

/* IoT Cloud */


/* security packages */
#define PKG_USING_TINYCRYPT 1
#define TINY_CRYPT_MD5 1
#define TINY_CRYPT_AES 1
#define TINY_CRYPT_AES_ROM_TABLES 1
//#define TINY_CRYPT_BASE64

/* language packages */


/* multimedia packages */


/* tools packages */


/* system packages */
#define CONFIG_SOUND_MIXER                   0

#define PKG_USING_FAL 1
#define FAL_DEBUG_CONFIG
#define FAL_DEBUG 1
#define PKG_USING_FAL_LATEST_VERSION
#define FAL_PART_TABLE_END_OFFSET (60 * 1024UL) //speed up if need change to 64k
#define FAL_PART_TABLE_FLASH_DEV_NAME "beken_onchip_crc"

/* peripheral libraries and drivers */


/* miscellaneous packages */

#define PKG_USING_OPTPARSE 1
#define PKG_USING_OPTPARSE_V100
#define PKG_USING_MULTIBUTTON 1
#define PKG_USING_MULTIBUTTON_V102
//#define PKG_USING_ZLIB

/* MultiButton Options */


/* sample package */


/* example package: hello */


/* Privated Packages of RealThread */


/* Network Utilities */
//#define PKG_NETUTILS_IPERF

/* RT-Thread Senior Membership Packages */

/* system packages */


/* IoT - internet of things */
//#define RT_USING_AIRKISS 1

/* Webnet: A web server package for rt-thread */
//#define PKG_USING_WEBNET
//#define WEBNET_USING_CGI

/* Hardware Drivers Config */
#define BEKEN_USING_UART1 1
#define BEKEN_USING_UART2 1
#define BEKEN_USING_WDT 1
#define BEKEN_USING_FLASH 1
#define BEKEN_USING_PWM 1
#define BEKEN_USING_GPIO 1
#define BEKEN_USING_WLAN 1
#define LWIP_NETIF_HOSTNAME 1
#define BEKEN_USING_WLAN_STA 1
#define RT_USING_CPU_FFS 1
//#define BEKEN_USING_SPI_FLASH
//#define BEKEN_USING_SPI_PSRAM
//#define BEKEN_USING_SPI_HSLAVE
#define RT_USING_BLE 1

/* Player Config */

/* PLAYER 1.2.7 ************************************************************************** */
#define PKG_USING_PLAYER 1
#define PKG_USING_PLAYER_V127
#define PLAYER_DEVICE "sound"
#define PLAYER_DEFAULT_VOLUME 65

/* PLAYER CODEC */
#define PLAYER_ENABLE_CODEC_PCM 1
#define PLAYER_ENABLE_CODEC_WAV 1
// #define PLAYER_ENABLE_FORMAT_TS

/* PLAYER */
#define PLAYER_ENABLE_NET_STREAM 1
#define PLAYER_ENABLE_HTTP_STREAM 1
#define PLAYER_ENABLE_HTTPS_STREAM 1
#define PLAYER_ENABLE_TTS_STREAM 1
// #define PLAYER_ENABLE_HLS_STREAM
// #define PLAYER_ENABLE_HLS_ACCELERATE
// #define PLAYER_ENABLE_PLS_STREAM

#define PLAYER_USING_NETSTREAM_BUFSZ 96

/* PLAYER */
#define PLAYER_USING_DEBUG 0

/* PLAYER Example */
#define PLAYER_USING_EXAMPLE00 1
//#define PLAYER_USING_EXAMPLE02
//#define PLAYER_USING_EXAMPLE03
/* PLAYER END **************************************************************************** */
/* Application Samples Config */


/* Test samples */

#define PKG_USING_RT_OTA 1

#define RT_USING_PTHREADS 1

/* voice changer */
//#define CONFIG_VOICE_CHANGER        0

/* tools packages */
#define PKG_USING_EASYFLASH 1


//#define PKG_USING_LITTLEFS
//#define RT_USING_MTD_NOR 1

/*xiaoya */
//#define XIAOYA_OS
#ifdef XIAOYA_OS
#define PKG_USING_MBEDTLS
#endif

#define RT_USING_MEMTRACE 1
#endif

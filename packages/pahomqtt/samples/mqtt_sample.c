#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <rtthread.h>

#define DBG_ENABLE
#define DBG_SECTION_NAME    "mqtt.sample"
#define DBG_LEVEL            DBG_LOG
#define DBG_COLOR
#include <rtdbg.h>

#include "mqtt_client.h"

/**
 * MQTT URI farmat:
 * domain mode
 * tcp://iot.eclipse.org:1883
 *
 * ipv4 mode
 * tcp://192.168.10.1:1883
 * ssl://192.168.10.1:1884
 *
 * ipv6 mode
 * tcp://[fe80::20c:29ff:fe9a:a07e]:1883
 * ssl://[fe80::20c:29ff:fe9a:a07e]:1884
 */
#define MQTT_URI                "tcp://192.168.3.236:1883" //"tcp://iot.eclipse.org:1883"
#define MQTT_SUBTOPIC           "/mqtt/test1"
#define MQTT_PUBTOPIC           "/mqtt/test1"
#define MQTT_WILLMSG            "Goodbye!"
#define MQTT_USERNAME           "admin"
#define MQTT_PASSWORD           "admin"
#define MQTT_CLIENTID           "rtthread-mqtt1"
/* define MQTT client context */
static mqtt_client client;
static int is_started = 0;
static uint32_t reciver_num=0;
static void mqtt_sub_callback(mqtt_client *c, message_data *msg_data)
{
    reciver_num++;
    *((char *)msg_data->message->payload + msg_data->message->payloadlen) = '\0';
    #if 1
    LOG_D("mqtt sub callback: num:%d  %.*s %.*s",reciver_num,
               msg_data->topic_name->lenstring.len,
               msg_data->topic_name->lenstring.data,
               msg_data->message->payloadlen,
               (char *)msg_data->message->payload);
    #endif
    //rt_kprintf("reciver_num:%d,topic:%.*s\r\n",reciver_num,msg_data->topic_name->lenstring.len,msg_data->topic_name->lenstring.len);
}

static void mqtt_sub_default_callback(mqtt_client *c, message_data *msg_data)
{
    *((char *)msg_data->message->payload + msg_data->message->payloadlen) = '\0';
    LOG_D("mqtt sub default callback: %.*s %.*s",
               msg_data->topic_name->lenstring.len,
               msg_data->topic_name->lenstring.data,
               msg_data->message->payloadlen,
               (char *)msg_data->message->payload);
}

static void mqtt_connect_callback(mqtt_client *c)
{
    LOG_D("inter mqtt_connect_callback!");
}

static void mqtt_online_callback(mqtt_client *c)
{
    LOG_D("inter mqtt_online_callback!");
}

static void mqtt_offline_callback(mqtt_client *c)
{
    LOG_D("inter mqtt_offline_callback!");
}

static int mqtt_start(int argc, char **argv)
{
    /* init condata param by using MQTTPacket_connectData_initializer */
    MQTTPacket_connectData condata = MQTTPacket_connectData_initializer;

    if (argc != 1)
    {
        rt_kprintf("mqtt_start    --start a mqtt worker thread.\n");
        return -1;
    }

    if (is_started)
    {
        LOG_E("mqtt client is already connected.");
        return -1;
    }
    /* config MQTT context param */
    {
        client.isconnected = 0;
        client.uri = MQTT_URI;

        /* config connect param */
        memcpy(&client.condata, &condata, sizeof(condata));
        client.condata.clientID.cstring = MQTT_CLIENTID;
        //client.condata.username.cstring = MQTT_USERNAME;
        //client.condata.password.cstring = MQTT_PASSWORD;
        client.condata.keepAliveInterval = 60;
        client.condata.cleansession = 1;

        /* config MQTT will param. */
        client.condata.willFlag = 1;
        client.condata.will.qos = 1;
        client.condata.will.retained = 0;
        client.condata.will.topicName.cstring = "/mqtt/will";//MQTT_SUBTOPIC;
        client.condata.will.message.cstring = MQTT_WILLMSG;

        /* malloc buffer. */
        client.buf_size = client.readbuf_size = 1024;
        client.buf = rt_calloc(1, client.buf_size);
        client.readbuf = rt_calloc(1, client.readbuf_size);
        if (!(client.buf && client.readbuf))
        {
            LOG_E("no memory for MQTT client buffer!");
            return -1;
        }

        /* set event callback function */
        client.connect_callback = mqtt_connect_callback;
        client.online_callback = mqtt_online_callback;
        client.offline_callback = mqtt_offline_callback;

        /* set subscribe table and event callback */
        client.message_handlers[0].topicFilter = rt_strdup(MQTT_SUBTOPIC);
        client.message_handlers[0].callback = mqtt_sub_callback;
        client.message_handlers[0].qos = QOS1;

        /* set default subscribe event callback */
        client.default_message_handlers = mqtt_sub_default_callback;
    }
    
    {
      int value;
      uint16_t u16Value;
      value = 5;
      paho_mqtt_control(&client, MQTT_CTRL_SET_CONN_TIMEO, &value);
      value = 5;
      paho_mqtt_control(&client, MQTT_CTRL_SET_MSG_TIMEO, &value);
      value = 5;
      paho_mqtt_control(&client, MQTT_CTRL_SET_RECONN_INTERVAL, &value);
      value = 30;
      paho_mqtt_control(&client, MQTT_CTRL_SET_KEEPALIVE_INTERVAL, &value);
      u16Value = 3;
      paho_mqtt_control(&client, MQTT_CTRL_SET_KEEPALIVE_COUNT, &u16Value);
    }

    /* run mqtt client */
    paho_mqtt_start(&client, 8196, 20);
    is_started = 1;

    return 0;
}

static int mqtt_stop(int argc, char **argv)
{
    if (argc != 1)
    {
        rt_kprintf("mqtt_stop    --stop mqtt worker thread and free mqtt client object.\n");
    }

    is_started = 0;

    return paho_mqtt_stop(&client);
}

static int mqtt_publish(int argc, char **argv)
{
    if (is_started == 0)
    {
        LOG_E("mqtt client is not connected.");
        return -1;
    }

    if (argc == 2)
    {
        paho_mqtt_publish(&client, QOS0, MQTT_PUBTOPIC, argv[1], strlen(argv[1]));
    }
    else if (argc == 3)
    {
        paho_mqtt_publish(&client, QOS0, argv[1], argv[2],strlen(argv[2]));
    }
    else
    {
        rt_kprintf("mqtt_publish <topic> [message]  --mqtt publish message to specified topic.\n");
        return -1;
    }

    return 0;
}

static void mqtt_new_sub_callback(mqtt_client *client, message_data *msg_data)
{
    *((char *)msg_data->message->payload + msg_data->message->payloadlen) = '\0';
    LOG_D("mqtt new subscribe callback: %.*s %.*s",
               msg_data->topic_name->lenstring.len,
               msg_data->topic_name->lenstring.data,
               msg_data->message->payloadlen,
               (char *)msg_data->message->payload);
}

static int mqtt_subscribe(int argc, char **argv)
{
    if (argc != 2)
    {
        rt_kprintf("mqtt_subscribe [topic]  --send an mqtt subscribe packet and wait for suback before returning.\n");
        return -1;
    }
	
	if (is_started == 0)
    {
        LOG_E("mqtt client is not connected.");
        return -1;
    }

    return paho_mqtt_subscribe(&client, QOS0, argv[1], mqtt_new_sub_callback);
}

static int mqtt_unsubscribe(int argc, char **argv)
{
    if (argc != 2)
    {
        rt_kprintf("mqtt_unsubscribe [topic]  --send an mqtt unsubscribe packet and wait for suback before returning.\n");
        return -1;
    }
	
	if (is_started == 0)
    {
        LOG_E("mqtt client is not connected.");
        return -1;
    }

    return paho_mqtt_unsubscribe(&client, argv[1]);
}

static int mq_pub_test()
{
    char msg[1024];
    int index=0;
    sprintf(msg,"msgid:%d",index);
    while(1)
    {
        index++;
        rt_kprintf("index:%d\r\n",index);
        memset(msg,0,1024);
        sprintf(msg,"{\"message_id\":%d,\"uri\":\"192.168.3.236\",\"port\":1883,\"code\":0,\"openid\":\"hdqwohdowqjdopjqefchqnvciqjciewjqhqij1237819hf1br983u19h3fc891hfhf1hd1hjdij81jxqsixniqvewfuwhfodihewofjoicjewifjo8742975r2y4hjwdiwqdjwq9du381ueu1389\",\"message\":\"hello this is rtthread mqtt test,the message from bk7251\", \"tick_time\":%d}",index,rt_tick_get());
        paho_mqtt_publish(&client, QOS1, MQTT_PUBTOPIC, msg, strlen(msg));
        rt_thread_delay(200);
    }
    return 0;
}
MSH_CMD_EXPORT(mq_pub_test, publish mqtt msg);

#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(mqtt_start, startup mqtt client);
MSH_CMD_EXPORT(mqtt_stop, stop mqtt client);
MSH_CMD_EXPORT(mqtt_publish, mqtt publish message to specified topic);
MSH_CMD_EXPORT(mqtt_subscribe,  mqtt subscribe topic);
MSH_CMD_EXPORT(mqtt_unsubscribe, mqtt unsubscribe topic);
#endif /* FINSH_USING_MSH */


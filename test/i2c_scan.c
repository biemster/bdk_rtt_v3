#include "include.h"
#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <string.h>
#include <time.h>
#include <drv_iic.h>
#include "icu_pub.h"
#include "i2c_pub.h"
#include "drv_model_pub.h"
#include "target_util_pub.h"
#include "test_config.h"

#ifdef I2C_SCAN

static int i2c_scan_rtt(int argc, char *argv[]) {
	const char *i2c_bus_device_name = "i2c";
	struct rt_i2c_bus_device *i2c_device;
	struct rt_i2c_msg msgs[2];
	
	rt_uint8_t attach_ret = iic_bus_attach();
	rt_kprintf("iic_bus_attach  ret:%d\n", attach_ret);    

	i2c_device = rt_i2c_bus_device_find(i2c_bus_device_name);
	if (i2c_device == RT_NULL) {
		rt_kprintf("i2c bus device %s not found!\n", i2c_bus_device_name);
		return -RT_ENOSYS;
	}
	else {
		rt_kprintf("found i2c bus\n");
	}

	rt_uint8_t reg = 0x17; // flip
	rt_uint8_t value = 0x00;
	for(rt_uint16_t i2c_addr = 0; i2c_addr < 256; i2c_addr++) {
		msgs[0].addr  = i2c_addr;
		msgs[0].flags = RT_I2C_WR;
		msgs[0].buf   = &reg;
		msgs[0].len   = 1;
	
		msgs[1].addr  = i2c_addr;
		msgs[1].flags = RT_I2C_RD; /* Read from slave */
		msgs[1].buf   = &value;
		msgs[1].len   = 1;
	
		if (rt_i2c_transfer(i2c_device, msgs, 2) == 2) {
			rt_kprintf("Got response from i2c addr %02X: %02X=%02X\n", i2c_addr, reg, value);
		}
	}

	return RT_EOK;
}

static int i2c_scan(int argc, char *argv[]) {
	unsigned int status;
	char *i2c_dev = I2C1_DEV_NAME;
	UINT32 i2c_trans_mode = 0;
	if(argc == 2 && atoi(argv[1]) == 2) {
		i2c_dev = I2C2_DEV_NAME;
		i2c_trans_mode = (0 & (~I2C2_MSG_WORK_MODE_MS_BIT)// master
							& (~I2C2_MSG_WORK_MODE_AL_BIT))// 7bit address
							| (I2C2_MSG_WORK_MODE_IA_BIT); // with inner address
	}

	DD_HANDLE i2c_handle = ddev_open(i2c_dev, &status, i2c_trans_mode);
	bk_printf("Opening %s returned 0x%02X\n", i2c_dev, status);

	I2C_OP_ST i2c_op;
	i2c_op.op_addr = 0x17; // flip addr
	char data;

	for(int a = 0; a < 256; a++) {
		i2c_op.salve_id = (UINT8)a;

		for(int i = 0; i < 20; i++) {
			bk_printf("trying %s address 0x%02X (%d)\r", i2c_dev, a, i+1);
			i2c_op.addr_width = ADDR_WIDTH_8;
			status = ddev_read(i2c_handle, &data, /*len*/1, (UINT32)&i2c_op);
			if(status == 0) {
				bk_printf("Device at %s address (w8): 0x%02X, status=0x%02X data=0x%02X\r\n", i2c_dev, a, status, data);
				break;
			}

			i2c_op.addr_width = ADDR_WIDTH_16;
			status = ddev_read(i2c_handle, &data, /*len*/1, (UINT32)&i2c_op);
			if(status == 0) {
				bk_printf("Device at %s address (w16): 0x%02X, status=0x%02X data=0x%02X\r\n", i2c_dev, a, status, data);
				break;
			}
		}
	}

	ddev_close(i2c_handle);
	return 0;
}

MSH_CMD_EXPORT(i2c_scan_rtt, i2c scan rtt);
MSH_CMD_EXPORT(i2c_scan, i2c scan);

#endif

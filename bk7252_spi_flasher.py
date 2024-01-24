#!/usr/bin/env python3
import sys
import os
import argparse
import spidev
import time
import RPi.GPIO as GPIO


SPI_CHIP_ERASE_CMD      = 0xc7
SPI_CHIP_ENABLE_CMD     = 0x06
SPI_READ_PAGE_CMD       = 0x03
SPI_WRITE_PAGE_CMD      = 0x02
SPI_SECTRO_ERASE_CMD    = 0x20
SPI_SECUR_SECTOR_ERASE  = 0x44
SPI_ID_READ_CMD         = 0x9F
SPI_STATU_WR_LOW_CMD    = 0x01
SPI_STATU_WR_HIG_CMD    = 0x31
SPI_READ_REG            = 0x05
SPI_READ_STATUS_S7_0    = 0x05
SPI_READ_STATUS_S15_8   = 0x35
SPI_WRITE_STATUS        = 0x01


def ChipReset():
    # Adjust it for your pin
    CENGPIO = 25
    GPIO.setup(CENGPIO, GPIO.OUT)
    GPIO.output(CENGPIO, GPIO.LOW)
    time.sleep(.3)
    GPIO.output(CENGPIO, GPIO.HIGH)

def BK_EnterSPIMode(spi):
    ChipReset()
    print("Send 4*64 'D2'")
    send_buf = bytearray([0xD2] * 64)
    a = spi.xfer2(send_buf)
    a = spi.xfer2(send_buf)
    a = spi.xfer2(send_buf)
    a = spi.xfer2(send_buf)
    print(bytes(a[:64]).hex())
    
    time.sleep(0.1)

    print("Get ID")
    cmd_id = bytearray(4)
    cmd_id[0] = SPI_ID_READ_CMD
    cmd_id[1] = 0x0
    cmd_id[2] = 0x0
    cmd_id[3] = 0x0
    
    chipid = spi.xfer2(cmd_id)
    print(bytes(chipid[:4]).hex())

    print("Get flash status bytes")
    cmd_fstat = bytearray(1)
    cmd_fstat[0] = SPI_READ_STATUS_S7_0
    flash_status1 = spi.xfer2(cmd_fstat)
    cmd_fstat[0] = SPI_READ_STATUS_S15_8
    flash_status2 = spi.xfer2(cmd_fstat)
    print(bytes(flash_status1).hex(), bytes(flash_status2).hex())
    
    id_bk7231 = [0x00, 0x1c, 0x70, 0x15]
    id_bk7252 = [0x00, 0x0b, 0x40, 0x16]
    return (chipid[:4] == id_bk7252);

def Wait_Busy_Down():
    while True:
        send_buf = bytearray(2)
        send_buf[0] = SPI_READ_REG
        send_buf[1] = 0x00
        out_buf = spi.xfer2(send_buf)
        if not (out_buf[1] & 0x01):
            break
        time.sleep(0.01)

def CHIP_ENABLE_Command():
    send_buf = bytearray(1)
    send_buf[0] = SPI_CHIP_ENABLE_CMD
    spi.xfer(send_buf)
    Wait_Busy_Down()
    
def WriteImage(startaddr,filename, maxSize):
    print("WriteImage "+filename)
    statinfo = os.stat(filename)
    # size = statinfo.st_size
    # size = (size+255)//256*256
    size = maxSize;

    # unprotect flash
    CHIP_ENABLE_Command()
    send_buf = bytearray(3)
    send_buf[0] = SPI_WRITE_STATUS
    send_buf[1] = 0x00
    send_buf[2] = 0x00
    spi.xfer(send_buf)
    Wait_Busy_Down()

    count = 0
    addr = startaddr
    f = open(filename, "rb")

    while count < size:
        print("count "+str(count) +"/"+str(size))
        if 0 == (addr & 0xfff):
            CHIP_ENABLE_Command()
            send_buf = bytearray(4)
            send_buf[0] = SPI_SECTRO_ERASE_CMD
            send_buf[1] = (addr & 0xFF0000) >> 16
            send_buf[2] = (addr & 0xFF00) >> 8
            send_buf[3] = addr & 0xFF
            spi.xfer(send_buf)
            Wait_Busy_Down()

        buf = f.read(256)
        if buf:
            CHIP_ENABLE_Command()
            send_buf = bytearray(4+256)
            send_buf[0] = SPI_WRITE_PAGE_CMD
            send_buf[1] = (addr & 0xFF0000) >> 16
            send_buf[2] = (addr & 0xFF00) >> 8
            send_buf[3] = addr & 0xFF
            send_buf[4:4+256] = buf
            spi.xfer(send_buf)
        count += 256
        addr += 256
        
    f.close()

    return True
    
def ReadStart(startaddr, filename, readlen):
    count = 0
    addr = startaddr
    f = open(filename, "wb")
    size = readlen
    size = (size+255)//256*256
    print("Reading")

    while count < size:
        print("count "+str(count) +"/"+str(size))
        send_buf = bytearray(4+256)
        send_buf[0] = SPI_READ_PAGE_CMD
        send_buf[1] = (addr & 0xFF0000) >> 16
        send_buf[2] = (addr & 0xFF00) >> 8
        send_buf[3] = addr & 0xFF
        result = spi.xfer2(send_buf)
        count += 256
        addr += 256
        part = bytearray(result[4:4+256])
        print(bytes(part[:256]).hex())
        f.write(part)

    f.close()

    ChipReset()
    return True


if __name__ == '__main__':
    # also adjust it
    GPIO.setmode(GPIO.BCM)

    spi = spidev.SpiDev()
    spi.open(0, 0)
    # SPI mode 3
    spi.mode = 0b11
    # it will fail to read ID with higher speeds (at least it fails for me)
    spi.max_speed_hz = 50000

    if not BK_EnterSPIMode(spi):
        print("Failed to read flash id")
        exit();
        
    # this will allow you to write directly bootloader + app
    #WriteImage(0,"OpenBK7231T_App_QIO_35a81303.bin", 0x200000)
    # if you have an app that was loaded by bkWriter 1.60 with offs 0x11000,
    # and you have broke your bootloader, you can take bootloader from OBK build
    # and then restore an app
    #WriteImage(0,"OpenBK7231T_App_QIO_35a81303.bin", 0x11000)
    #WriteImage(0x11000,"REST.bin", 0x200000)
    # I used this to verify my code and it work

    #ReadStart(0,"bootloader_bk7252_tuya.bin", 0x11000)
    #WriteImage(0,"bootloader_bk7251_uart2_v1.0.8_enc_crc.bin", 0x11000)
    #WriteImage(0,"a9_bl_enc_crc.bin", 0x11000)
    #WriteImage(0,"bootloader_bk7252_tuya.bin", 0x11000)
    WriteImage(0,"all_2M.1220_uncrc_enc_crc.bin", 0x11000)
    #ReadStart(0,"verify_bl.bin", 0x11000)

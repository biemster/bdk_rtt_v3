#!/usr/bin/env bash
./uncrc.py out/all_2M.1220.bin
tools/enc_binary/encrypt.exe out/all_2M.1220_uncrc.bin 510fb093 a3cbeadc 5993a17e c7adeb03 0
tools/crc_binary/encrypt.exe out/all_2M.1220_uncrc_enc.bin 0
rm out/*out out/*cpr

dd if=out/all_2M.1220_uncrc_enc_crc.bin of=out/bl_2M.1220_uncrc_enc_crc.bin ibs=69632 count=1
dd if=out/all_2M.1220_uncrc_enc_crc.bin of=out/app_2M.1220_uncrc_enc_crc.bin ibs=69632 skip=1
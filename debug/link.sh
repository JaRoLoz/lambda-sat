#!/usr/bin/env bash
set -e
arg_flashimg="debug_image.bin"
echo "[+] Building test binary"
rm -vf ${arg_flashimg}
dd if=/dev/zero bs=1024 count=4096 of=${arg_flashimg}
echo "[+] Linking bootloader.bin"
dd if=../.pio/build/esp32debug/bootloader.bin bs=1 seek=$((0x1000)) of=${arg_flashimg} conv=notrunc
echo "[+] Linking partitions.bin"
dd if=../.pio/build/esp32debug/partitions.bin bs=1 seek=$((0x8000)) of=${arg_flashimg} conv=notrunc
echo "[+] Linking firmware.bin, this may take a few minutes..."
dd if=../.pio/build/esp32debug/firmware.bin bs=1 seek=$((0x10000)) of=${arg_flashimg} conv=notrunc
echo "[+] Build completed"

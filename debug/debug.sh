#!/bin/bash
echo "
      \\\\\\        _                     _         _       
       \\\\\\      | |                   | |       | |      
       /\\\\\\     | |     __ _ _ __ ___ | |__   __| | __ _ 
      ///\\\\\\    | |    / _\` | '_ \` _ \| '_ \\ / _\` |/ _\` |
     ///  \\\\\\   | |___| (_| | | | | | | |_) | (_| | (_| |
    ///    \\\\\\  |______\\__,_|_| |_| |_|_.__/ \\__,_|\\__,_|"
echo ""

githubReleaseUrl="https://github.com/espressif/qemu/releases/download/esp-develop-7.2.0-20230223/esp-qemu-xtensa-softmmu-develop_7.2.0_20230223-x86_64-linux-gnu.tar.bz2"

echo "[+] Looking for qemu-xtensa"
if ! [ -f "/bin/qemu-xtensa/bin/qemu-system-xtensa" ]; then
    echo "[-] No QEMU installation found"
    echo "[+] Installing dependencies (libpixman)"
    sudo apt-get install libpixman-1-dev -y > /dev/null
    echo "[+] Installing dependencies (libslirp)"
    sudo apt-get install libslirp-dev -y > /dev/null
    echo "[+] Installing QEMU on /bin/qemu"
    wget -q -O xtensa.tar.bz2 ${githubReleaseUrl} > /dev/null
    tar -xf xtensa.tar.bz2 > /dev/null
    rm -rf xtensa.tar.bz2 > /dev/null
    mv qemu/ /bin/qemu-xtensa/
    rm -rf qemu > /dev/null
    echo "[+] QEMU successfully installed"
fi

./link.sh

/bin/qemu-xtensa/bin/qemu-system-xtensa -s -nographic -M esp32 -m 4 -drive file=./debug_image.bin,if=mtd,format=raw -nic user,model=open_eth
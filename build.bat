@ECHO ON

arm-none-eabi-gcc -O0 -mfpu=vfp -mfloat-abi=soft -march=armv6zk -mtune=arm1176jzf-s -nostartfiles -g -Wl,-T,rpi.x -I./csud-master/include -o kernel-009.elf gpio.s systemTimer.s armc-009.c armc-009-cstartup.c armc-009-start.S armc-009-cstubs.c -L. -lcsud 

arm-none-eabi-objcopy kernel-009.elf -O binary kernel.img

pause

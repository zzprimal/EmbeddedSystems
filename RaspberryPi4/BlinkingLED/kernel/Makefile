default:
	arm-none-eabi-as ledblink.s -o ledblink.o
	arm-none-eabi-ld ledblink.o -o kernel8.elf
	arm-none-eabi-objcopy kernel8.elf -O binary kernel8.img
clean:
	rm -r kernel8.elf kernel8.img

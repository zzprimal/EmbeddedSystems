default:
	arm-none-eabi-as ledblink.s -o ledblink.o
	arm-none-eabi-ld ledblink.o -o kernel7l.elf
	arm-none-eabi-objcopy kernel7l.elf -O binary kernel7l.img
clean:
	rm -r kernel7l.elf kernel7l.img ledblink.o

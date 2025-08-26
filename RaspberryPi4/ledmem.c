#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

#define MAIN_PERIPHERAL_BASE 0xFC000000
#define GPIO_OFFSET 0x2200000
#define GPIO_BASE MAIN_PERIPHERAL_BASE + GPIO_OFFSET
#define BLOCK sysconf(_SC_PAGE_SIZE)

#define GPFSEL_OFFSET 0x0
#define GPSET_OFFSET 0x1C
#define GPCLR_OFFSET 0x28



int main(int argc, char **argv){
	if (argc < 2){
		fprintf(stderr, "Error: no pin number given\n");
		exit(-1);
	}
	int pin = atoi(argv[1]);
	int fd = open("/dev/mem", O_RDWR);
	if (fd == -1){
		fprintf(stderr, "error open failed\n");
		return -1;
	}
	volatile uint32_t *gpio_base = (uint32_t *) mmap(NULL, BLOCK, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
	if (gpio_base == MAP_FAILED){
		fprintf(stderr, "error mmap failed\n");
		return -1;
	}

	// blinking led loop
	*(gpio_base + GPFSEL_OFFSET / 4 + (pin / 10)) &= ~(7 << (pin % 10)*3); // clear function select for pin
	*(gpio_base + GPFSEL_OFFSET / 4 + (pin / 10)) |= 1 << (pin % 10)*3; // set pin as output pin
	volatile uint32_t *gpio_set = gpio_base + GPSET_OFFSET / 4 + pin / 32;
	volatile uint32_t *gpio_clear = gpio_base + GPCLR_OFFSET / 4 + pin / 32;
	while (1){
		puts("set");
		*gpio_set |= 1 << (pin % 32);
		sleep(1);
		puts("clear");
		*gpio_clear |= 1 << (pin % 32);
		sleep(1);
	}	
}

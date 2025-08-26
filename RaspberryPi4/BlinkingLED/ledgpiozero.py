from gpiozero import LED
from time import sleep
import sys
if len(sys.argv) < 2:
    print("Error: gpio pin number not specified as CLI arg")

pin = int(sys.argv[1])
led = LED(pin)

while True:
    print("set")
    led.on()
    sleep(1)
    print("clear")
    led.off()
    sleep(1)

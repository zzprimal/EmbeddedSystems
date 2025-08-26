import RPi.GPIO as GPIO
import time
import sys


pin = 17
if len(sys.argv) < 2:
    print("Error: gpio pin number not given as CLI arg")
    exit(-1)

pin = int(sys.argv[1])
# Note, there are 2 modes GPIO.BCM and GPIO.BOARD, BPIO.BCM specifies the GPIO channels/pins, BPIO.BOARD specifies pin
# number on the pin board of the raspberry pi
GPIO.setmode(GPIO.BCM)
GPIO.setup(pin, GPIO.OUT)
try:
    while (True):
        GPIO.output(pin, GPIO.HIGH)
        print("set")
        time.sleep(1)
        GPIO.output(pin, GPIO.LOW)
        print("clear")
        time.sleep(1)
except:
    GPIO.cleanup()

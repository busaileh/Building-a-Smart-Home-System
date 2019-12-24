#Device 1 (001) Temprature Monitoing (Tempratue+LCD)
#Device 2 (010) Corridor Monitioing (Relay+NFC+Door Switch)
#Device 3 (011) Living Room Monitiring (TV+Couch)
#Device 4 (100) Room Monitiing (AC + Windows)

from xbee import ZigBee
from brain import brain
import serial
import pprint
from Recieving import sendMessage

ser = serial.Serial("/dev/ttyUSB0" , 9600)

xbee = ZigBee(ser,escaped=True)

sendMessage(ser,xbee,"none","restart")

while True :
    result = xbee.wait_read_frame()
    if(result):
        ##We have recieved something lets put it in the brain to know from where
        brain(result,xbee,ser)

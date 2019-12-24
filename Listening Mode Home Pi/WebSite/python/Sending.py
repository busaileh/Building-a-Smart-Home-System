from xbee import ZigBee
import serial
import pprint

ser = serial.Serial("/dev/ttyUSB0" , 9600)
xbee = ZigBee(ser,escaped=True)

#status , lighton , lightoff , tvon , tvoff , acon , acoff
#for the broadcast msg put the data as they are suppose to be sent

def send(device,data):

    msg = ""
    msg += device

    
    long_addr = "000000000000FFFF".decode('hex')
    
    if(data == "lighton"):
        msg+="lon"

    elif(data =="lightoff"):
        msg +="loff"

    elif(data=="tvon"):
        msg += "ton"

    elif(data=="tvoff"):
        msg += "toff"

    elif(data=="status"):
        msg += "status"
    elif(data =="acon"):
        msg += "aon"
    elif(data =="acoff"):
        msg +="aoff"
    else:
        msg+=data

    try:
        print(msg)
        small_addr = "0000".decode('hex')
        pprint.pprint(small_addr)
        xbee.tx(dest_addr_long=long_addr,dest_addr=small_addr,data=msg)
        xbee.halt()
        ser.close()
    except KeyboardInterrupt:
        print("Out")

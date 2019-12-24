from xbee import ZigBee
import serial



#status , lighton , lightoff , tvon , tvoff , acon , acoff
#for the broadcast msg put the data as they are suppose to be sent and device as all

def sendMessage(device,data):
    msg = ""
    msg += device
    small_addr= "0000".decode('hex')
    long_addr = "000000000000FFFF".decode('hex')

    if (data == "lighton"):
        msg+="lon"

    elif (data =="lightoff"):
        msg +="loff"

    elif (data=="tvon"):
        msg += "ton"

    elif (data=="tvoff"):
        msg += "toff"

    elif (data=="status"):
        msg += "status"

    elif (data =="acon"):
        msg += "aon"

    elif (data =="acoff"):
        msg +="aoff"
    else:
        msg+=data


    try:
        xbee.tx(dest_addr_long=long_addr,dest_addr=small_addr,data=msg)


    except KeyboardInterrupt:
        print("Out")

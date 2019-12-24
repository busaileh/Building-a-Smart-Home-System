import pprint,os

def analysPacket(packet,xbee,ser):
    returnedData = []
    device = packet[0]
    pprint.pprint(packet)

    if(device == "dev2"):
        returnedData.append("dev2")

        pprint.pprint(packet)
        dataType = packet[1][0]

        if(dataType == 20 ):
            ###Door Status
            deviceStatus = packet[1][1]
            returnedData.append("door")
            returnedData.append(deviceStatus)

            if(deviceStatus == 1):
                ##Run the HomeSecurity script
                ##Shell script to take pictures
                print("Door has been Opened")
                os.system("espeak -ven+f4  'Text Door has been Opened' 2>/dev/null")

            elif(deviceStatus == 0):
                print("Door has been Closed")
                os.system("espeak -ven+f4  'Text Door Closed' 2>/dev/null")


        elif(dataType == 30):
            ###touch ONE
            status = packet[1][1]
            sendMessage("all","off",xbee,ser)

        elif(dataType ==  40):
            secure = packet[1][1]
            returnedData.append("security")
            returnedData.append(secure)

        elif(dataType==50):
            alert = packet[1][1]
            returnData.append("alert")
            returnData.append(alert)    

    if(device == "dev4"):
        returnedData.append("dev4")

        pprint.pprint(packet)
        dataType = packet[1][0]

        if(dataType == 20 ):
            ###Window Status
            deviceStatus = packet[1][1]
            returnedData.append("window")
            returnedData.append(deviceStatus)

            if(deviceStatus == 1):
                ##Run the HomeSecurity script
                ##Shell script to take pictures
                print("Window has been Opened")
                os.system("espeak -ven+f4  'Text Window has been Opened' 2>/dev/null")

            elif(deviceStatus == 0):
                print("Door has been Closed")
                os.system("espeak -ven+f4  'Text Window Closed' 2>/dev/null")


        elif(dataType == 30):
            ###RainyStuff
            status = packet[1][1]
            returnedData.append("rainy")
            returnedData.append(status)




    return returnedData

def sendMessage(device,data,xbee,ser):
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

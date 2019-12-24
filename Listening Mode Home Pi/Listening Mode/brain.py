from Devices.Temprature import getTemprature
from Devices.Corridor import getCorridorData
from Devices.LivingRoom import getLivingRoomData
from Devices.Room import getRoomData
from Packet import analysPacket

import pprint,os,time

secure = False
lastSecure = 0 
rainy = False
window = False
door = False

def brain(result,xbee,ser):
    analys = []
    homeSecurity = ""
    device_addresses = ["53ef","93bc","eee7","c6e8"]
    checkTimes =0
    ##First we need to know if its a tx Status or an RX
    #pprint.pprint(result)

    device_id = result['id']


    ##analys array will have the data returned to know what to do

    if(device_id =="rx"):
        #Recieved RX packet
        rc_data = result['rf_data'].encode('hex')
        add_small = result['source_addr'].encode('hex')


        if(add_small == device_addresses[0]):
            ##The Temprature Device (Temprature + Humidity) Put in DB
            #analys.append("dev1")
            getTemprature(rc_data)

        if(add_small == device_addresses[1]):
            ##The Corridor (**NFC Very Important** , Touch Button)
            analys.append("dev2")
            analys.append(getCorridorData(rc_data))

            ##If Home Securty == True then we need to turn on Home Security
            ##If it equals False then we need to see what the light wants

        if(add_small == device_addresses[2]):
            #analys.append("dev3")
            ##The Living Room (NULL)
            analys.append("dev3")
            analys.append(getLivingRoomData(rc_data))


        if(add_small == device_addresses[3]):
            analys.append("dev4")
            #The Room Place (Rain Drop Sensor)
            analys.append(getRoomData(rc_data))


        pprint.pprint(analys)
    if(len(analys) >= 2 and analys[1]):
        returned = analysPacket(analys,xbee,ser)
        
        homeSecurityFunc(returned)

    elif(device_id =="tx_status"):
        #Recieved a tx status
        print("tx status")
        return

def timer():
   now = time.time()
   return now



    
def homeSecurityFunc(rc_data):
 
    global secure
    global lastSecure
    global rainy
    global window
    global door

    if(len(rc_data) > 0):

        print("Entered home sec func")
        pprint.pprint(rc_data)
        device = rc_data[0]
        dataType = rc_data[1]
        data = rc_data[2]

        if(device == "dev2"):

            if(dataType =="security"):
                #Let us check if window is closed First
                secure = data
                if(secure):
                    lastSecure = timer()
                    os.system("espeak -ven+f4  'Text Home Secured' 2>/dev/null")
                    print("Home secured")
                    if(window):
                        os.system("espeak -ven+f4  'Text Please close the window' 2>/dev/null")
                    if(rainy):
                        os.system("espeak -ven+f4  'Text It rainning dont forget your umbrella' 2>/dev/null")
                else:
                    os.system("espeak -ven+f4  'Text Home Security turninng off' 2>/dev/null")
                    lastSecure = 0

            elif(dataType =="door"):
                #Take your pictures
                door = data
                if(door):
                    #os.system("sudo ./extras/take_pics")
                    now = timer()
                    print("Timer:")
                    dif = now - lastSecure

                    if(secure and (now - lastSecure >= 60)):
                        #SEND AN SMS MESSAGE
                        print("Sending textMessage from door")


        if(device == "dev4"):

            if(dataType == "window"):
                window = data
                if(window and secure):
                    ##Send an SMS Message
                    print("Sending textMessage from window")

            elif(dataType == "rainy"):
                rainy = data
                

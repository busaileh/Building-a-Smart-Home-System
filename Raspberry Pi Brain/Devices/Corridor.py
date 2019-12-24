from Database import Database
from Converter import Converter
import pprint


def getCorridorData(rf_data):
    ##NFC turns on Home Security [type,Relay,(NFC)||(Touch)]

    data = Converter(rf_data)
    dataType = data[0]

    pprint.pprint(data)

    #analys array
    analys =[]

    if(dataType == 10): ##getStatus is always for website(Triggers Database Event)
        ##Relay + HomeSecuirtyStatus

        #Put in the Database
        Database("2",data)
        print("Recieved a status from Device 2")


    elif(dataType== 20): ##Wont triger DB only analys it
        ##door status proccesed to Take Pictures of when the door has been opened and home sec to send a message
        ##If home secuiert is on Put in One Folder Else in another folder()
        analys.append(dataType)
        doorStatus = data[1]
        analys.append(doorStatus)
        print("Recieved door status from device2")
        ##11(Turn all lights on) 10(Turn all lights off) 20 (Turn all devices off)

    elif(dataType== 30): ##Wont trigger DB only analys it
        ##Devices all most go Off
        analys.append(dataType)
        devicesControl = data[1]
        analys.append(devicesControl)
        print("Going to send bc msg from device2")
        ##11(Turn all lights on) 10(Turn all lights off) 20 (Turn all devices off)

    elif(dataType == 40):
        #Secure with NFC STUFF
        analys.append(dataType)
        nfc = data[1]
        analys.append(nfc)
        print("Recieved home sec status")

    elif (dataType ==50):
        #alert
        analys.append(dataType)
        alert = data[1]
        analys.append(alert)
        print("Recieved an alert notification")


    if(len(analys) > 0):
        return analys
    else:
        return False

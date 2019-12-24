from Converter import Converter
from Database import Database


def getRoomData(rf_data):
    analys = []
    data = Converter(rf_data)
    ##IF you added the AC Control here make it control it
    dataType =data[0]
    if(dataType == 10):
        Database("4",data)
        #return false

    elif(dataType == 20):
        #Window Status (Window Opened/Closed)
        analys.append(dataType)
        windowStatus = data[1]
        analys.append(windowStatus)
        print("Recieved window status")
    elif(dataType== 30):
        #Rainy Stuff
        analys.append(dataType)
        rainy = data[1]
        analys.append(rainy)
        print("rainy")


    if(len(analys) > 0):
        return analys
    else:
        return False

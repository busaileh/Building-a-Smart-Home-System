from Converter import Converter
from Database import Database


def getLivingRoomData(rf_data):

    data = Converter(rf_data)
    ##IF you added the AC Control here make it control it
    Database("3",data)

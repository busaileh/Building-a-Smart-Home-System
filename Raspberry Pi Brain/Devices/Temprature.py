from Converter import Converter
from Database import Database


def getTemprature(rf_data):

    data = Converter(rf_data)
    ##IF you added the AC Control here make it control it
    Database("1",data)

import MySQLdb
from time import localtime,strftime
import pprint


def Database(device,data):
    print("Attempting database")
    db=MySQLdb.connect("localhost","raspberry","helloworld","raspberry")
    pprint.pprint(data)
    curs=db.cursor()

    #Data Variables
    query =""
    temprature = ""
    humidity =""
    light_status=""
    date_time = strftime(("%Y-%m-%d %H:%M:%S"),localtime())
    if(device == "1"):
        #Save the temprature & Humidity
        tableName = "temprature"
        temprature=data[0]
        humidity = data[1]

        query ="insert into %s (device,temprature,humidity,date) values('%s','%s','%s','%s')"%(tableName,device,temprature,humidity,date_time)
        try:
            curs.execute(query)
            db.commit()
        except:
            print("Error")
            db.rollback()

    if(device == "2"):
        tableName = "corridor"
        light_status = "on" if(data[1]) else "off"
        door_status = "opened" if(data[2]) else "closed"
        secure = "secure" if(data[3]) else "unsecure"
        query ="insert into %s (device,light,door,homesecuriety,date) values('%s','%s','%s','%s','%s')"%(tableName,device,light_status,door_status,secure,date_time)
        print(query)
        try:
            curs.execute(query)
            db.commit()
        except:
            print("Error")
            db.rollback()

    if(device=="3"):
        tableName = "livingroom"
        light_status = "on" if(data[0]) else "off"
        tv_status = "on" if(data[1]) else "off"
        query = "insert into %s (device,light,tv,date) values('%s','%s','%s','%s')"%(tableName,device,light_status,tv_status,date_time)
        try:
            curs.execute(query)
            db.commit()
        except:
            print("Error")
            db.rollback()

    if(device=="4"):
        if(data[0]):
            pprint.pprint(data)

        tableName = "room"
        light_status = "on" if(data[1]) else "off"
        window_status = "opened" if(data[2]) else "closed"
        rainy = "rainy" if(data[3]) else "none"
        query = "insert into %s (device,light,window,rainy,date) values('%s','%s','%s','%s','%s')"%(tableName,device,light_status,window_status,rainy,date_time)
        try:
            curs.execute(query)
            db.commit()
        except:
            print("Error")
            db.rollback()
    print(query)

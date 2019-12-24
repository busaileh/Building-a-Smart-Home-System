def sendMessage(ser,xbee,device,data):
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



def recieve(ser,xbee,wait_for):
    small_addresses=["","","",""] #not caps small letters
    success =False
    i = 0

    if (wait_for =="rx"):


    elif (wait_for =="status"):



    if(wait_for =="status"):
        while (not success):
            i = i+ 1
            result = xbee.wait_read_frame()
            r_id = result['id']
            if(r_id=="tx_status"):
                del_status=result['deliver_status'].encode('hex')
                add = result['dest_addr'].encode('hex')

                for item in small_addresses:
                    if(add == item):
                        success = True
                        return True
            if(i==1 and not success):
                return False
                break

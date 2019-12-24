import sys
from Sending import send

#Device Number + data
#devic Number in binary 001,010,011,100
#status , lighton , lightoff , tvon , tvoff , acon , acoff
#If device == all a broadcast to all


length = len(sys.argv)
arr = []

if (length > 1):

    arr=sys.argv[1:]
    device = arr[0]
    data = arr[1]
    #print(device)
    #print(data)
    send(device,data)

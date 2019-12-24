def Converter(val):
    #Each hex digit translates to 4 binary digits,
    #so the length of the new string should be exactly
    #4 times the size of the original.

    hex_size = len(val) * 4
    binary_data = ( bin(int(val, 16))[2:] ).zfill(hex_size)#Hexa To Binary(Whole Packet)
    readings = len(binary_data) / 16 #Every Data is 16 bit(In Case we send floats)

    binary_list =read_array(binary_data,readings) #Split the packet in number of datas
    decimal_list = bin_dec(binary_list)#Convert binary to Decimal in array
    return decimal_list

def bin_dec(lis):
    lis2=[]
    for item in lis:
        #print(item)
        dec = int(item,2)
        lis2.append(dec)
    return lis2

def read_array(val,readings):
    lis=[]
    for i in range (0,readings):
        from_bit = 16*i
        to_bit=16+16*i
        data = val[from_bit:to_bit]
        lis.append(data)

    return lis

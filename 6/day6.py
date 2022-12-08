
with open("input.txt","r") as f:
    #Gets signal string
    signal = f.readline()

#Length of signal string
signal_length = len(signal)

#Loops through each character of the signal
for i in range(3,signal_length):

    #Gets a packet of 4 characters and puts them into a set
    packet = set(signal[i-4:i])

    #Sets can't have duplicate elememts
    #If the set has 4, there must be 4 unique values
    if len(packet) == 4:
        print("First start-of-packet at: ",i)
        break

#Loops through each character of the signal
for j in range(13,signal_length):

    #Gets a packet of 14 characters
    message = set(signal[j-14:j])

    #If the set has 14, there must be 14 unique values
    if len(message) == 14:
        print("First start-of-message at: ",j)
        break


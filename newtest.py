#!/usr/bin/python
import serial
import syslog
import time
import datetime

#The following line is for serial over GPIO
port = '/dev/ttyACM0' #


ard = serial.Serial(port,9600,timeout=.5)
time.sleep(2) # wait for Arduino

while 1:  
    # Serial write section
    setTempCar1 = 63
    setTempCar2 = 37
    setTemp1 = str(setTempCar1) + "Z"
    setTemp2 = str(setTempCar2)
    #print ("Python value sent: ") + setTemp1
    ard.write(setTemp1)
    time.sleep(2) # with the port open, the response will be buffered 
                  # so wait a bit longer for response here

    # Serial read section
    #msg = ard.read() # read everything in the input buffer
    msg = ard.readline()
   # print ("Message from arduino: ") + msg
    
    file = open ("testfile.txt", "a")
    
    
    ts = time.time()
    st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S')
    file.write(st + ' ' + msg + '\n') 

"""
# Importing Libraries
import serial
import time
arduino = serial.Serial(port='COM4', baudrate=115200, timeout=.1)
def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data
while True:
    num = input("Enter a number: ") # Taking input from user
    value = write_read(num)
    print(value) # printing the value
"""

#Librerias
import serial 

#Abriendo puerto serial
try:
    arduino = serial.Serial(port='COM4', baudrate=115200, timeout=.1)
except:
    print("Check port")

#Variables
    rawdata = []
    count = 0

#Recibiendo datos

while count < 5:
    rawdata.append(str(arduino.readline()))
    count+=1

print(rawdata)

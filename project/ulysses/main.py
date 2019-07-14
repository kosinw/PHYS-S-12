import serial
import datetime

HEADER = 'T'

def getTime():
    t = datetime.datetime.now();

    return str(t.hour) + ":" + str(t.minute) + ":" + str(t.second)

ser = serial.Serial('COM3', 9600)

ser.write((HEADER + getTime()).encode())

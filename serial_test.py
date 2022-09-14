from time import sleep
import serial.tools.list_ports
import serial

import pyautogui

import ctypes
user32 = ctypes.windll.user32

ports = serial.tools.list_ports.comports()
serialInst = serial.Serial()

portList = []

for onePort in ports:
    portList.append(str(onePort))
    print(str(onePort))

val = input("select Port: COM")

for x in range (0,len(portList)):
    if portList[x].startswith("COM" + str(val)):
        portVar = "COM" + str(val)
        print(portList[x])

serialInst.baudrate = 9600
serialInst.port = portVar
serialInst.open()
serialInst.write(b'h')
sleep(2)
serialInst.write(b'h')

while True:
    if serialInst.in_waiting:
        packet = serialInst.readline()
        decoded = packet.decode('utf-8').replace('\r\n', '').split('\t')
        print(decoded)
    
    # serialInst.write()
    screensize = user32.GetSystemMetrics(78), user32.GetSystemMetrics(79)
    steer = (pyautogui.position().x-screensize[0]/9)/screensize[0]
    # print(steer)

    serialInst.write(f"dir {steer}".encode('utf-8'))
    # serialInst.write(f"{steer}".encode('utf-8'))
    sleep(0.8)

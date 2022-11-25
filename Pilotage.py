import serial
import time

arduino=serial.Serial("/dev/ttyACM1",baudrate=9600,timeout=1)
rawdata=[]


def clear(L):
    newL=L[:-2]
    return newL

print("? : status")
print("setTemp : définir température idéale")
print("setHum : définir humidité idéale")
print("")
resume = ["Température intérieure (°C) : ", "Température extérieur (°C) : ", "Humidité de la terre (%) : ", "Ventilateur : ", "Lampe : ", "Pompe : "]
a=arduino.readline().decode('UTF-8')

while True:

    i = input("Saisissez une commande : ").strip()
    
    if(i!="?" and i!="setTemp" and i!="setHum"):
        print("Entrée non valide")
        print("")
    
    if(i=="?"):
        arduino.write(i.encode())
        time.sleep(2) #2s
        a=arduino.readline().decode('UTF-8')
        a=clear(a)
        info = a.split("/")
        
        for e in range (len(info)):
            print(resume[e] + info[e])
            
        print("")
    
    if(i=="setTemp"):
        arduino.write(i.encode())
        time.sleep(2)
        x = input(arduino.readline().decode('UTF-8'))
        arduino.write(x.encode())
        time.sleep(6)
        print(arduino.readline().decode('UTF-8'))
    
    
    if(i=="setHum"):
        arduino.write(i.encode())
        time.sleep(2)
        x = input(arduino.readline().decode('UTF-8'))
        arduino.write(x.encode())
        time.sleep(6)
        print(arduino.readline().decode('UTF-8'))
    

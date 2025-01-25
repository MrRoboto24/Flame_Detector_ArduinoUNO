import serial
import subprocess
import time

PORT = "COM5"

arduino = serial.Serial(port="COM5",baudrate=9600,timeout=1)

def listen_to_arduino():
    while True:
        data = arduino.readline().decode('utf-8').strip()
        if data == "Fire detected.":
            subprocess.run(["python", "email_sender.py"])
            print("Fire detected! Running email script...")
            subprocess.run(["python", "push_notification.py"])
            print("Fire detected! Running Push Notification script...")
            time.sleep(2)
try:
    if __name__ == "__main__":
        listen_to_arduino()

except KeyboardInterrupt:
    print("Program is Over")

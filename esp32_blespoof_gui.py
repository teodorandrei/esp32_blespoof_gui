import tkinter as tk
import serial
import time
import threading

port = "COM3"
debug = True

DEVICES = [
    "Airpods", "Airpods Pro", "Airpods Max", "Airpods Gen 2", "Airpods Gen 3",
    "Airpods Pro Gen 2", "Power Beats", "Power Beats Pro", "Beats Solo Pro",
    "Beats Studio Buds", "Beats Flex", "Beats X", "Beats Solo 3", "Beats Studio 3",
    "Beats Studio Pro", "Beats Fit Pro", "Beats Studio Buds Plus"
]

ser = serial.Serial(port, 115200, timeout=1)
time.sleep(2)

def read_serial_data():
    while True:
        if ser:
            line = ser.readline().decode('utf-8').strip()
            if line:
                serial_output.insert(tk.END, line + '\n')
                serial_output.see(tk.END)

def start_serial_monitoring():
    global ser
    try:
        threading.Thread(target=read_serial_data, daemon=True).start()
    except serial.SerialException as e:
        print(f"Error opening serial port: {e}")

def send_serial_data(data):
    try:
        ser.write(data)
        print(f"Sent data to serial! |{str(data)}|")
    except serial.SerialException as e:
        print(f"Error sending data to serial!: {e}")

def set_device(index):
    send_serial_data(b"SET_DEVICE " + str(index).encode() + b"\n")
    print(f"Selected device: {DEVICES[index]}")

def start_spoof():
    ser.write(b'start\n')
    print("Spoofing started :)")


def stop_spoof():
    ser.write(b'stop\n')
    print("Spoofing stopped :(")

root = tk.Tk()
root.title("BLE Spoofing Controller")
root.geometry("400x600")
root.configure(bg="#2c3e50")

title_label = tk.Label(root, text="BLE Spoofing Controller", bg="#2c3e50", fg="white", font=('Arial', 16, 'bold'))
title_label.pack(pady=20)

button_frame = tk.Frame(root, bg="#2c3e50")
button_frame.pack(expand=True, fill=tk.BOTH)

start_button = tk.Button(button_frame, text="Start Spoofing", command=start_spoof, bg="green", fg="white", font=('Arial', 12, 'bold'))
start_button.pack(side=tk.TOP, padx=10, pady=10, fill=tk.X)

stop_button = tk.Button(button_frame, text="Stop Spoofing", command=stop_spoof, bg="red", fg="white", font=('Arial', 12, 'bold'))
stop_button.pack(side=tk.TOP, padx=10, pady=10, fill=tk.X)


device_frame = tk.Frame(button_frame, bg="#2c3e50")
device_frame.pack(side=tk.TOP, fill=tk.BOTH, expand=True)

for i, device_name in enumerate(DEVICES):
    button = tk.Button(device_frame, text=device_name, command=lambda i=i: set_device(i), font=('Arial', 10), bg="#34495e", fg="white")
    button.pack(pady=5, fill=tk.X)

if debug:
    serial_output = tk.Text(root, height=10, width=50, bg="#34495e", fg="white", font=('Arial', 10))
    serial_output.pack(pady=10)
    start_serial_monitoring()

root.mainloop()
ser.close()

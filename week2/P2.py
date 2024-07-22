import serial
import time
from datetime import datetime

# Set up serial connection
serial_port = 'COM12'  # Update with your serial port
baud_rate = 9600
ser = serial.Serial(serial_port, baud_rate)

# Define filenames for each sensor
accelerometer_file = 'accelerometer_data.csv'

# Open files in append mode
with open(accelerometer_file, 'a') as accel_file:
    while True:
        if ser.in_waiting > 0:
            # Read data from serial
            data = ser.readline().decode().strip()
            
            # Get current timestamp
            timestamp = datetime.now().strftime('%Y%m%d%H%M%S')
            
            # Write data to file with timestamp
            accel_file.write(f"{timestamp},{data}\n")
            accel_file.flush()
            
            # Print to console (optional)
            print(f"{timestamp},{data}")
            

# Ensure to close the serial connection
ser.close()

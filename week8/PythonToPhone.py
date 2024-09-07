import csv
import time
from datetime import datetime
import sys
import traceback
from arduino_iot_cloud import ArduinoCloudClient



DEVICE_ID = "1724f62d-6a37-4356-841b-5a436f7dee61"
SECRET_KEY = "8ZQcDGqG?6qYbFNUi2Cop6a!X"

# Callback functions for accelerometer data
def on_accel_x_change(value):
    timestamp = datetime.now().isoformat()
    with open('accel_x_data.csv', 'a') as file:
        writer = csv.writer(file)
        writer.writerow([timestamp, value])

def on_accel_y_change(value):
    timestamp = datetime.now().isoformat()
    with open('accel_x_data.csv', 'a') as file:
        writer = csv.writer(file)
        writer.writerow([timestamp, value])

def on_accel_z_change(value):
    timestamp = datetime.now().isoformat()
    with open('accel_z_data.csv', 'a') as file:
        writer = csv.writer(file)
        writer.writerow([timestamp, value])

def main():
    print("main() function")

    # Make sure you have the correct import and initialization for ArduinoCloudClient
    client = ArduinoCloudClient(
        device_id=DEVICE_ID, username=DEVICE_ID, password=SECRET_KEY
    )

    # Registering callback functions for accelerometer variables
    client.register(
        "accel_x", value=None, 
        on_write=on_accel_x_change
    )

    client.register(
        "accel_y", value=None, 
        on_write=on_accel_y_change
    )

    client.register(
        "accel_z", value=None, 
        on_write=on_accel_z_change
    )

    # Start cloud client
    client.start()

if __name__ == "__main__":
    try:
        main()  # main function which runs in an internal infinite loop
    except Exception as e:
        exc_type, exc_value, exc_traceback = sys.exc_info()
        traceback.print_exc()  # Print the full traceback
        print(f"Error: {e}")

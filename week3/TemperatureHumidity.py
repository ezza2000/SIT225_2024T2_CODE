import sys
import traceback
import random
from arduino_iot_cloud import ArduinoCloudClient
import asyncio


DEVICE_ID = "ad1f281a-a59b-4b69-964d-dc5c334d5119"
SECRET_KEY = "d5rQ#r3pGYqGp@bAssIJJ3mPS"



# Callback function on temperature change event.
# 
def on_temperature_changed(client, value):            
     # Print to console (optional)
    print(f"Temperature: {value}")

def on_humidity_changed(client, value):            
     # Print to console (optional)
    print(f"Humidity: {value}")


def main():
    print("main() function")

    # Instantiate Arduino cloud client
    client = ArduinoCloudClient(
        device_id=DEVICE_ID, username=DEVICE_ID, password=SECRET_KEY
    )

    # Register with 'temperature' cloud variable
    # and listen on its value changes in 'on_temperature_changed'
    # callback function.
    # Register the temperature cloud variable
    client.register(
        "temperature", value=None, 
        on_write=on_temperature_changed
    )

    # Register the humidity cloud variable
    client.register(
        "humidity", value=None, 
        on_write=on_humidity_changed
    )

    # Start cloud client
    client.start()

if __name__ == "__main__":
    try:
        main()  # main function which runs in an internal infinite loop
    except:
        exc_type, exc_value, exc_traceback = sys.exc_info()
        traceback.print_tb(exc_type, file=print)
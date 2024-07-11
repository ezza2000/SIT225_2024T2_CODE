import serial
import random
import time
from datetime import datetime

# set baud rate, same speed as set in your Arduino sketch.
baud_rate = 9600

# set serial port as suits your operating system
s = serial.Serial("COM12", baud_rate, timeout=5)

# Give the Arduino some time to reset and be ready
time.sleep(2)

while True:  # Infinite loop, keep running

    # Generate a random number between 1 and 10
    data_send = random.randint(1, 10)
    send_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    print(f"{send_time} - Send >>> {data_send}")

    # Write to serial port, set data encoding
    s.write(bytes(str(data_send) + '\n', 'utf-8'))

    # Read from the serial port
    data_recv = s.readline().decode("utf-8").strip()
    recv_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    print(f"{recv_time} - Recv <<< {data_recv}")

    # Convert received data to integer
    try:
        sleep_time = int(data_recv)
    except ValueError:
        print(f"Invalid data received: {data_recv}")
        continue

    # Log sleeping event with timestamp
    sleep_start_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    print(f"{sleep_start_time} - Sleeping for {sleep_time} seconds...")

    # Sleep for the received number of seconds
    time.sleep(sleep_time)

    # Log the completion of sleep
    sleep_end_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    print(f"{sleep_end_time} - Sleep complete.")

    # Add a delay before sending the next number
    time.sleep(1)
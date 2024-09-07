import csv
from datetime import datetime

# Filenames of the input CSV files
file_x = 'accel_x_data.csv'
file_y = 'accel_y_data.csv'
file_z = 'accel_z_data.csv'

# Filename for the output merged CSV file
output_file = 'merged_accel_data.csv'

# Function to read data from a CSV file
def read_csv(filename):
    data = []
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        next(reader)  # Skip the header row
        for row in reader:
            # Assuming each row is [timestamp, value]
            timestamp = datetime.fromisoformat(row[0])
            value = float(row[1])
            data.append((timestamp, value))
    return data

# Read data from each file
data_x = read_csv(file_x)
data_y = read_csv(file_y)
data_z = read_csv(file_z)

# Open the output file to write the merged data
with open(output_file, 'w', newline='') as file:
    writer = csv.writer(file)
    # Write header row
    writer.writerow(['timestamp', 'accel_x', 'accel_y', 'accel_z'])

    # Use zip to merge the data
    for (timestamp_x, value_x), (timestamp_y, value_y), (timestamp_z, value_z) in zip(data_x, data_y, data_z):
        # Assuming timestamps are synchronized and sorted
        timestamp = timestamp_x.isoformat()
        writer.writerow([timestamp, value_x, value_y, value_z])

print(f"Merged data has been written to {output_file}")
